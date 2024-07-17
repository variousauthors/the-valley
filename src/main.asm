INCLUDE "includes/hardware.inc"
INCLUDE "includes/dma.inc"

VRAM_WIDTH EQU 32
VRAM_HEIGHT EQU 32
VRAM_SIZE EQU VRAM_WIDTH * VRAM_HEIGHT
SCRN_WIDTH EQU 20
SCRN_HEIGHT EQU 18


SECTION "OAMData", WRAM0, ALIGN[8]
Sprites: ; OAM Memory is for 40 sprites with 4 bytes per sprite
  ds 40 * 4
.end:
 
SECTION "CommonRAM", WRAM0

GAME_OVER: ds 1 ; a byte to note whether the game is over

; enough bytes to buffer the whole _SCRN
; I think I can drop this, it supports the full
; screen redraw... but since that is always done
; with LCD off maybe I can just naughty dirty
; draw rather than buffering, eh?
MAP_BUFFER_WIDTH EQU SCRN_WIDTH
MAP_BUFFER_HEIGHT EQU SCRN_HEIGHT
MAP_BUFFER:
TOP_MAP_BUFFER: ds MAP_BUFFER_WIDTH * 2
MIDDLE_MAP_BUFFER: ds MAP_BUFFER_WIDTH * (MAP_BUFFER_HEIGHT - 4)
BOTTOM_MAP_BUFFER: ds MAP_BUFFER_WIDTH * 2
MAP_BUFFER_END:

; this is $80 because the tiles are in the
; second tile set which starts at $80
; obviously this will change when we get new graphics
TILE_BLANK EQU $80 + 0

SECTION "CAMERA_STATE", WRAM0

; world position of the center of the camera
CAMERA_WORLD_X: ds 1
CAMERA_SUB_X: ds 1 ; 1/16th meta tile
CAMERA_WORLD_Y: ds 1
CAMERA_SUB_Y: ds 1
CAMERA_NEXT_WORLD_X: ds 1
CAMERA_NEXT_WORLD_Y: ds 1
CAMERA_INITIAL_WORLD_X: ds 1
CAMERA_INITIAL_WORLD_Y: ds 1

; Hardware interrupts
SECTION "vblank", ROM0[$0040]
  jp DMA_ROUTINE
SECTION "hblank", ROM0[$0048]
  jp HBlankHandler

SECTION "hblank handler", ROM0
HBlankHandler:
  push af
  push bc

  ; there is a thing where the STAT handler is called
  ; on the DMG after rSTAT is set, regardless
  ; this check ensures that LYC = LY
  ld a, [rWY]
  ld b, a
  ld a, [rLY]
  cp a, b
  jr nz, .done

  ; now we turn off objects so that we can draw the window in peace
  ld a, LCDCF_ON|LCDCF_BG8800|LCDCF_BG9800|LCDCF_BGON|LCDCF_OBJ8|LCDCF_OBJOFF|LCDCF_WIN9C00|LCDCF_WINON
  ld [rLCDC], a

.done
  pop bc
  pop af
  reti

SECTION "timer",  ROM0[$0050]
  reti
SECTION "serial", ROM0[$0058]
  reti
SECTION "joypad", ROM0[$0060]
  reti

SECTION "header", ROM0[$100]
  di
  jp init
  ds $150-@, 0

SECTION "main", ROM0[$150]

init:
  di

  dma_Copy2HRAM	; sets up routine from dma.inc that updates sprites

  call ZeroOutWorkRAM ; it is easier to inspect this way

  call setSeed
  call resetTime
  call initPalettes
  call turnOffLCD

  call initGameState
  call initCurrentMap
  call initEventEncounterTable
  call initMapDrawTemplates
  call initEncounterSystem

  call initPlayer
  call initBoat
  ; GBC ONLY FEATURE
  ; call initGBCPalettes

  ; load sprite tiles into VRAM
  ld hl, SpriteTileset
  ld b, SPRITE_TILES_COUNT ; 8 sprite tiles
  ld de, SPRITE_TILES
  call loadTileData

  ; load encounter tiles into VRAM
  ld hl, EncounterTiles
  ld b, ENCOUNTER_TILES_COUNT ; 8 sprite tiles
  ld de, ENCOUNTER_TILES
  call loadTileData
 
  ; load window tiles into VRAM
  ld hl, WindowTileset
  ld b, WINDOW_TILES_COUNT ; 8 sprite tiles
  ld de, WINDOW_TILES
  call loadTileData

  call loadFontData

  ; we'll pre-draw the window frame into the window
  ; to save time during draw since everyone uses
  ; this little window frame
  ; call drawEncounterWindowFrame

  ; initial position will be defined by the scene,
  ; but in this case we will put the player in the
  ; center of the camera, and the camera in the top-left
  ; corner
  ld hl, CAMERA_WORLD_X
  ld a, [PLAYER_WORLD_X]
  sub a, META_TILES_TO_SCRN_LEFT
  ld [hl], a
  ld hl, CAMERA_NEXT_WORLD_X
  ld [hl], a

  ld hl, CAMERA_WORLD_Y
  ld a, [PLAYER_WORLD_Y]
  sub a, META_TILES_TO_TOP_OF_SCRN
  ld [hl], a
  ld hl, CAMERA_NEXT_WORLD_Y
  ld [hl], a

  call drawFreshNewMap

  call turnOnLCD

  ei

main:
  halt

  nop

  ; we only want to run main at the start of vblank
  ; so here we check that we are indeed in vblank
  ; because all the interrupts cause halt to stop
  ld a, [rLY]
  cp a, SCRN_Y
  jp c, main

  ld a, [rLCDC]
  or a, LCDCF_OBJON ; make sure objects are on
  ld [rLCDC], a

  call tick
  call performGameDraw

  call isGameStateSteady
  jr nz, .update

  call performGameStep

  jr nz, main

.update
  call performGameUpdate

  jr main
; -- END MAIN --

; -- GAME STATES --

; -- END MAIN --
; -- MOVE MOST OF THIS STUFF --

HALF_SCREEN_WIDTH EQU SCRN_WIDTH / 2 ; 10 meta tiles
HALF_SCREEN_HEIGHT EQU SCRN_HEIGHT / 2 ; 9 meta tiles

META_TILES_TO_SCRN_LEFT EQU HALF_SCREEN_WIDTH / 2 - 1
META_TILES_TO_SCRN_RIGHT EQU HALF_SCREEN_WIDTH / 2
META_TILES_TO_TOP_OF_SCRN EQU HALF_SCREEN_HEIGHT / 2
META_TILES_TO_BOTTOM_OF_SCRN EQU META_TILES_TO_TOP_OF_SCRN
META_TILES_PER_SCRN_ROW EQU HALF_SCREEN_WIDTH
META_TILE_ROWS_PER_SCRN EQU HALF_SCREEN_HEIGHT

; @param hl - address of world pos
; @param de - address of world pos
; @return a - pixel distance (hl - de)
; destroys hl, de
pixelDistance:
  push bc

  ld a, [de]
  ld b, a

  ld a, [hl]
  sub a, b
  
  ; translate to pixels
  sla a
  sla a
  sla a
  sla a

  ; move to sub x
  inc hl
  inc de

  ; a diff of sub x
  add a, [hl]
  ld h, d
  ld l, e
  sub a, [hl]

  pop bc

  ret

; the top-left corner of the screen needs to go
; to a position that is relative to where the camera
; started. Every tile the camera has moved to the left
; represents 8px the screen needs to move to the left
; assuming the screen started at 0,0
screenCenterOnCamera:
  ; figure camera offset from where
  ; it started
  ld a, [CAMERA_INITIAL_WORLD_X]
  ld b, a
  ld a, [CAMERA_WORLD_X]
  sub a, b

  ; translate to pixels
  sla a
  sla a
  sla a
  sla a

  ld b, a
  ld a, [CAMERA_SUB_X]
  add a, b
  ld [rSCX], a

  ld a, [CAMERA_INITIAL_WORLD_Y]
  ld b, a
  ld a, [CAMERA_WORLD_Y]
  sub a, b

  ; translate to pixels
  sla a
  sla a
  sla a
  sla a

  ld b, a
  ld a, [CAMERA_SUB_Y]
  add a, b
  ld [rSCY], a

  ret

cameraFollowPlayer:
  ; ok , player x, player next x, player sub x

  ld a, [PLAYER_NEXT_WORLD_X]
  sub a, META_TILES_TO_SCRN_LEFT
  ld [CAMERA_NEXT_WORLD_X], a

  ld a, [PLAYER_NEXT_WORLD_Y]
  sub a, META_TILES_TO_TOP_OF_SCRN
  ld [CAMERA_NEXT_WORLD_Y], a

  ret

/** @TODO the idea here is that updatePosition 
 * could be generalized and replaced with this function
 * that updates anything with a position/sub-position 
 * structure.
 * these subroutines differ only in the stuff about negative/positive
 * I used this subroutine to lerp numbers and it worked
 * but when I try to replace updatePosition with it, I get
 * bad behaviour */
; @param hl - stat in position/sub position
; @param b - target stat
; destroys c
updateStat:
  ld a, [hl] ; current stat
  ld c, a
  ld a, b ; target start
  sub a, c ; diff will be signed int

  or a ; if a is zero we do nothing
  jr nz, .next
  ret

.next
  ; if it is not zero we want it to be 1 or -1
  and a, %10000000 ; check if negative
  jr z, .positive
.negative
  ld a, -1
  jr .done

.positive
  ld a, 1

.done
  ld c, a ; save this for later
  inc hl ; set to sub pos

  add a, [hl]
  ld [hl], a ; adjust sub_x by the 1 or -1

  call absA
  ; if abs(a) is 16 set x to next x
  cp a, 8
  ret c

  dec hl ; reset to world pos
  ld a, [hl] ; current pos
  add a, c ; adjust by 1
  ld [hl], a
  inc hl
  ld [hl], 0

  ret

; @param hl - position in tile/sub tile
; @param b - target position
; destroys c
updatePosition:
  ld a, [hl] ; world pos
  ld c, a
  ld a, b ; target pos
  sub a, c ; diff will be 1 or -1 (uh, why don't we store dx instead of a target pos...)

  or a ; if a is zero we do nothing
  jr nz, .next
  ret

.next
  inc hl ; set to sub pos

  add a, [hl]
  ld [hl], a ; adjust sub_x by the 1 or -1

  call absA
  ; if abs(a) is 16 set x to next x
  cp a, 16
  ret c

  dec hl ; reset to world pos
  ld a, b ; target pos
  ld [hl], a
  inc hl
  ld [hl], 0

  ret

updatePlayerPosition:
  ld hl, PLAYER_WORLD_X
  ld a, [PLAYER_NEXT_WORLD_X]
  ld b, a
  call updatePosition

  ld hl, PLAYER_WORLD_Y
  ld a, [PLAYER_NEXT_WORLD_Y]
  ld b, a
  call updatePosition

  ret

updateCameraPosition:
  ld hl, CAMERA_WORLD_X
  ld a, [CAMERA_NEXT_WORLD_X]
  ld b, a
  call updatePosition

  ld hl, CAMERA_WORLD_Y
  ld a, [CAMERA_NEXT_WORLD_Y]
  ld b, a
  call updatePosition

  ret

; @param hl - start of tile
; @param de - where to copy
copy1bpp:
  ; copy the first bit plane
  ld c, 8

.loop
  ; first byte
  ld a, [hl+]
  ld [de], a
  inc de

  ; second byte is zero
  ld a, 0
  ld [de], a
  inc de

  dec c
  jp nz, .loop
.done

  ret

initPalettes:
  ; darkest to lightest
  ld a, %11100100
  ld [rBGP], a
  ld [rOBP0], a

  ; obp1 is for objects on the ocean
  ld a, %11100001
  ld [rOBP1], a

  ret

turnOffLCD:
  ld a, [rLCDC]
  rlca
  ret nc

  call waitForVBlank

  ; in VBlank
  ld a, [rLCDC]
  res 7, a
  ld [rLCDC], a

  ret

turnOnLCD:
  ; configure and activate the display
  ld a, LCDCF_ON|LCDCF_BG8800|LCDCF_BG9800|LCDCF_BGON|LCDCF_OBJ8|LCDCF_OBJON|LCDCF_WIN9C00
  ld [rLCDC], a

  ; enable the interrupts
  ld a, IEF_VBLANK | IEF_LCDC
  ldh [rIE], a

  ret

turnOnWindow:
  ; configure and activate the display
  ld a, LCDCF_ON|LCDCF_BG8800|LCDCF_BG9800|LCDCF_BGON|LCDCF_OBJ8|LCDCF_OBJON|LCDCF_WIN9C00|LCDCF_WINON
  ld [rLCDC], a

  ld a, [rSTAT]
  or STATF_LYC
  ldh [rSTAT],a

  ret

turnOffWindow:
  ; configure and activate the display
  ld a, LCDCF_ON|LCDCF_BG8800|LCDCF_BG9800|LCDCF_BGON|LCDCF_OBJ8|LCDCF_OBJON|LCDCF_WIN9C00|LCDCF_WINOFF
  ld [rLCDC], a

  ld a, 0
  ldh [rSTAT],a

  ret

; write the blank tile to the whole SCRN0
blankVRAM:
  ld hl, _SCRN0
  ld de, VRAM_SIZE
.loop
  ld a, TILE_BLANK
  ld [hl], a
  dec de
  ld a, d
  or e
  jp z, .done
  inc hl
  jp .loop
.done
  ret

; @param hl -- map tileset (a bunch of indexes into master tileset)
; @param de -- location
; @param b -- count
loadTileData:
  push de
  push bc

; load one tile at a time
.loadData
  ld a, b
  cp 0
  jr z, .doneLoading

  ; we have to find the tile
  ; in the master tileset
  ld a, [hl] ; get the index

  push hl ; we are going to advance through the master tile set

  ; we can remove this push later since we know the count is always 16
  push bc ; b has the count, 

  ld bc, %01000000 ; master tileset is aligned to 64 bytes
  ld hl, MasterTileset
  inc a ; pre-increment for the loop
.findTileData
  dec a
  jr z, .doneFindTileData
  add hl, bc
  jr .findTileData

.doneFindTileData
  ; now hl is pointing to the start of tile data

  pop bc ; b has the count

  ; then copy the tile
  ; each tile is 16 bytes
  ; we want to load 4 at once
  ld c, 16 * 4
.loadTile
  ld a, [hl+]
  ld [de], a
  inc de
  dec c
  jr nz, .loadTile
.doneTile

  pop hl ; back to the top of master tileset
  inc hl ; next tile in the tileset
  dec b

  jr .loadData
.doneLoading

  pop bc
  pop de

  ret

ZeroOutWorkRAM:
  ld hl, _RAM
  ld de, $DFFF - _RAM ; number of bytes to write
.write
  ld a, $00
  ld [hli], a
  dec de
  ld a, d
  or e
  jr nz, .write
  ret

INCLUDE "includes/utilities.inc"
INCLUDE "includes/smc-utils.inc"
INCLUDE "includes/rand.inc"
INCLUDE "includes/time.inc"
INCLUDE "includes/input.inc"
INCLUDE "includes/databases/text.inc"
INCLUDE "includes/gbc-utilities.inc"
INCLUDE "includes/sprite-utils.inc"
INCLUDE "includes/encounter-tables.inc"
INCLUDE "includes/game-state.inc"
INCLUDE "includes/game-state/overworld.inc"
INCLUDE "includes/game-state/ocean.inc"
INCLUDE "includes/game-state/random-encounter.inc"
INCLUDE "includes/game-state/game-over.inc"
INCLUDE "includes/game-state/exit.inc"
INCLUDE "includes/game-state/enter.inc"
INCLUDE "includes/game-state/dialog.inc"
INCLUDE "includes/map-utils.inc"
INCLUDE "includes/map-draw.inc"
INCLUDE "includes/map-tilesets.inc"
INCLUDE "includes/meta-tiles.inc"
INCLUDE "includes/player-movement.inc"
INCLUDE "includes/events.inc"
INCLUDE "includes/entity-utils.inc"
INCLUDE "includes/entities/player.inc"
INCLUDE "includes/entities/boat.inc"
INCLUDE "includes/entities/elder.inc"
INCLUDE "includes/maps/overworld.inc"
INCLUDE "includes/maps/cave-passage.inc"
INCLUDE "includes/maps/north-grove-exit.inc"
INCLUDE "includes/maps/south-grove-exit.inc"
INCLUDE "includes/maps/grove-shortcut.inc"

Section "GraphicsData", ROM0

FontTileset:
INCBIN "assets/misaki_gothic.1bpp" ; 83 tiles

MasterTileset: 
INCBIN "assets/valley-graphics-8x8-tiles.2bpp" ; 80 tiles, 20 metatiles
INCBIN "assets/valley-map-8x8-tiles.2bpp" ; 44 tiles, 11 metatiles
INCBIN "assets/valley-sprites-8x8-tiles.2bpp" ; 8 tiles, the sprite, 2 metatiles @ 1F
INCBIN "assets/valley-additional-8x8-tiles.2bpp" ; 12 tiles, the boat, 3 metatiles @ 21
INCBIN "assets/window-graphics.2bpp" ; 32 tiles, the digits, 8 metatiles lol @ 24 - 2B
INCBIN "assets/valley-monsters.2bpp" ; 52 tiles, monsters, 13 meta tiles @ 2C - 37
INCBIN "assets/valley-hero-8x8-tiles.2bpp" ; 8 tiles, 2 metatilees @ 38

PLAYER_SPRITE_WALK_0 EQU $1f
PLAYER_SPRITE_WALK_1 EQU $20

HERO_SPRITE_WALK_0 EQU $39
HERO_SPRITE_WALK_1 EQU $3A

WINDOW_DIGITS_A EQU $24
WINDOW_DIGITS_B EQU $25
WINDOW_DIGITS_C EQU $26
WINDOW_DIGITS_D EQU $2A

WINDOW_FRAME_A EQU $28
WINDOW_FRAME_B EQU $29

MONSTER_SPRITE_ZERO EQU $27
MONSTER_SPRITE_ONE EQU $2B
MONSTER_SPRITE_TWO EQU $2C
MONSTER_SPRITE_THREE EQU $2D
MONSTER_SPRITE_FOUR EQU $2E
MONSTER_SPRITE_FIVE EQU $2F
MONSTER_SPRITE_SIX EQU $30
MONSTER_SPRITE_SEVEN EQU $31
MONSTER_SPRITE_EIGHT EQU $32
MONSTER_SPRITE_NINE EQU $33
MONSTER_SPRITE_TEN EQU $34
MONSTER_SPRITE_ELEVEN EQU $35
MONSTER_SPRITE_TWELVE EQU $36
MONSTER_SPRITE_THIRTEEN EQU $37
MONSTER_SPRITE_FOURTEEN EQU $38
; MONSTER_SPRITE_FIFTEEN EQU $39

SPRITE_TILES EQU $8000 ; 1st VRAM
SPRITE_TILES_COUNT EQU 6
SpriteTileset:
  db HERO_SPRITE_WALK_0, HERO_SPRITE_WALK_1, BOAT_TILE, BOAT_TILE, PLAYER_SPRITE_WALK_0, PLAYER_SPRITE_WALK_1, $00, $00,
  db $00, $00, $00, $00, $00, $00, $00, $00,

ENCOUNTER_TILES EQU $8400
ENCOUNTER_TILES_COUNT EQU 15
EncounterTiles:
  db MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ONE, MONSTER_SPRITE_TWO, MONSTER_SPRITE_THREE, MONSTER_SPRITE_FOUR, MONSTER_SPRITE_FIVE, MONSTER_SPRITE_SIX, MONSTER_SPRITE_SEVEN
  db MONSTER_SPRITE_EIGHT, MONSTER_SPRITE_NINE, MONSTER_SPRITE_TEN, MONSTER_SPRITE_ELEVEN, MONSTER_SPRITE_TWELVE, MONSTER_SPRITE_THIRTEEN, MONSTER_SPRITE_FOURTEEN, $00

MAP_TILES EQU $9000

WINDOW_TILES EQU $9400 ; 2nd line of 2nd VRAM
WINDOW_TILES_COUNT EQU 7
WindowTileset:
  db WINDOW_DIGITS_A, WINDOW_DIGITS_B, WINDOW_DIGITS_C, $00, WINDOW_FRAME_A, WINDOW_FRAME_B, WINDOW_DIGITS_D, $00,
  db $00, $00, $00, $00, $00, $00, $00, $00,

FONT_TILES EQU $8800 ; 3rd VRAM block
FONT_TILES_COUNT EQU 83