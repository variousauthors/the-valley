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
  call initCurrentEncounterTable
  call initMapDrawTemplates

  call initPlayer

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

  ; init player sprite tiles
  ld hl, PLAYER_SPRITE_TILES
  ld a, 0
  ld [hl+], a
  ld a, 1
  ld [hl+], a
  ld a, 2
  ld [hl+], a
  ld a, 3
  ld [hl+], a

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

  ; record that initial world x, y
  ; so that we can later use it to
  ; set the screen to the camera position
  ld a, [CAMERA_WORLD_X]
  ld [CAMERA_INITIAL_WORLD_X], a
  ld a, [CAMERA_WORLD_Y]
  ld [CAMERA_INITIAL_WORLD_Y], a

  ld a, 0
  ld [rSCX], a
  ld [rSCY], a

  ld a, 16 * (META_TILE_ROWS_PER_SCRN - 1) - 8
  ld [rWY], a

  ld a, 7
  ld [rWX], a

  call drawFreshNewMap

  ei

main:
  halt

  nop

  call tick

  call performGameDraw
  call performGameUpdate

  call isGameStateSteady
  jr nz, main

  call performGameStep

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

; are we in a steady state
; each state should have its own one of these
; @return z - yes, current state is equal to next
isCurrentStateEqualToNext:
  ; we only record actions when 
  ; we are in a steady state
  ld a, [PLAYER_NEXT_WORLD_X]
  ld b, a
  ld a, [PLAYER_WORLD_X]
  cp a, b
  ret nz

  ld a, [PLAYER_NEXT_WORLD_Y]
  ld b, a
  ld a, [PLAYER_WORLD_Y]
  cp a, b
  ret nz

  ; ENCOUNTER STATE
  ld a, [PLAYER_NEXT_CURRENT_HP]
  ld b, a
  ld a, [PLAYER_CURRENT_HP]
  cp a, b
  ret nz

  ld a, [ENCOUNTER_NEXT_CURRENT_HP]
  ld b, a
  ld a, [ENCOUNTER_CURRENT_HP]
  cp a, b
  ret nz

  ret

; @return z - step finished
isCurrentStepFinished:
  call getInput
  cp a, 0

  ret

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

; prepare a sprite using the player data
drawPlayer:

  ; get the first free sprite from the pool
  ; we'll have to decide on how we're going to do this
  ; maybe an entity will request some sprites when it
  ; first joins the scene, and then those don't need to
  ; be contiguous
  ; yeah, I'm going to pretend that's happening
  ; so below I'm picking "random" positions in OAM for the
  ; sprite to go

  ld hl, PLAYER_WORLD_Y
  ld de, CAMERA_WORLD_Y
  call pixelDistance
  ld b, a

  ld hl, PLAYER_WORLD_X
  ld de, CAMERA_WORLD_X
  call pixelDistance
  ld c, a

  ld hl, PLAYER_SPRITE_TILES

  ; -- ONE SPRITE TILE --
  ld de, Sprites + (8 * 4) ; 8 sprites for the two animation frames, each 4 bytes per sprite
  ld a, 16
  add a, b ; player position y
  ld [de], a
  inc de
  ld a, 8
  add a, c ; player position x
  ld [de], a
  inc de

  ; animation
  call twoIn64Timer
  sla a
  sla a ; times 4 to get to the correct frame
  add a, [hl] ; get the tile

  ld [de], a ; draw
  inc de

  ld a, 0 ; attr
  ld [de], a
  inc de

  inc hl

  ; -- THE NEXT SPRITE TILE --
  ld de, Sprites + (14 * 4)
  ld a, 16 + 8
  add a, b ; player position y
  ld [de], a
  inc de
  ld a, 8
  add a, c ; player position x
  ld [de], a
  inc de

  ; animation
  call twoIn64Timer
  sla a
  sla a ; times 4 to get to the correct frame
  add a, [hl] ; get the tile

  ld [de], a ; draw
  inc de
  ld a, 0 ; attr
  ld [de], a
  inc de

  inc hl

  ; -- ANOTHER SPRITE TILE --
  ld de, Sprites + (11 * 4)
  ld a, 16
  add a, b ; player position y
  ld [de], a
  inc de
  ld a, 8 + 8
  add a, c ; player position x
  ld [de], a
  inc de

  ; animation
  call twoIn64Timer
  sla a
  sla a ; times 4 to get to the correct frame
  add a, [hl] ; get the tile

  ld [de], a ; draw
  inc de
  ld a, 0 ; attr
  ld [de], a
  inc de

  inc hl

  ; -- THE LAST SPRITE TILE --
  ld de, Sprites + (3 * 4)
  ld a, 16 + 8
  add a, b ; player position y
  ld [de], a
  inc de
  ld a, 8 + 8
  add a, c ; player position x
  ld [de], a
  inc de

  ; animation
  call twoIn64Timer
  sla a
  sla a ; times 4 to get to the correct frame
  add a, [hl] ; get the tile

  ld [de], a ; draw
  inc de
  ld a, 0 ; attr
  ld [de], a
  inc de

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

; @param a - number
; @return |a|
absA:
  bit 7, a
  jr z, .skipNegate
  dec a
  cpl
.skipNegate

  ret

doubleSpeedExceptOverworld:
  ld c, a
  call twoInTwoTicks
  or a
  ld a, c
  jr z, .skip

  push hl
  call getCurrentMap
  call isOverworld
  pop hl
  ld a, c
  jr nz, .skip
  add a, a ; double if we are not overworld
.skip

  ret

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

  ; tried this! double is too fast, 1.5x seems jittery
  ; call doubleSpeedExceptOverworld

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

  ; tried this! double is too fast, 1.5x seems jittery
  ; call doubleSpeedExceptOverworld

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

drawFullScene:
  call writeMapToBuffer

  call drawBuffer
  ret

; @pre LCD is off
; @param hl - map
writeMapToBuffer:
  ; subtract from player y, x to get top left corner
  ld a, [CAMERA_WORLD_Y]
  ld de, MAP_BUFFER ; maybe get rid of this and just draw since LCD is OFF
  ld b, a

  ; while y is negative, draw blanks
.loop1
  ld a, b
  cp a, $80 ; is y negative?
  jr c, .done1

  call writeBlankRowToBuffer
  inc b

  jr .loop1
.done1

.loop2
  ; load map height from map
  ld a, [hl]
  dec a ; map height - 1

  ; stop if map height - 1 < y
  cp b
  jr c, .done2

  ; 
  ld a, [CAMERA_WORLD_Y]
  add a, META_TILE_ROWS_PER_SCRN - 1

  ; stop if we're past the last row we wanted to write
  cp b
  jr c, .done2

  call writeMapRowToBuffer
  inc b

  jr .loop2
.done2

  ; at this point y will always be equal to the map height
  ; because we've written as much map as we could
  ; and a < b so b - a = rows we wrote
  ; rows we wrote - rows per screen = rows to write
  ; b - a - rows per screen = rows to write
  ; a - b + rows per screen = - rows to write
  ld a, [CAMERA_WORLD_Y]
  sub b ; minus map height, - rows we wrote
  add META_TILE_ROWS_PER_SCRN ; rows to write?

  ld b, a ; be has rows to write
.loop3
  ld a, b
  or a
  jr z, .done3

  call writeBlankRowToBuffer
  dec b

  jr .loop3
.done3

  ret

; bc is used by seekIndex
; @param b - y to write
; @param hl - map to read
; @param de - where to write
writeMapRowToBuffer:
  push bc
  push hl

  ; approach: could expand the row first
  ; and leave the rest of the code as-is

  ; subtract from player x to get extreme left
  ld a, [CAMERA_WORLD_X]
  ld c, a ; now bc has y, x

  ; while x is negative, draw blanks
.loop1
  ld a, c
  cp a, $80 ; is y negative?
  jr c, .done1

  call writeBlankRowTileToBuffer
  inc c

  jr .loop1
.done1

.loop2
  ; load map width from map
  inc hl
  ld a, [hl]
  dec hl
  dec a ; map width - 1

  ; stop if map width - 1 < x
  cp c
  jr c, .done2

  ; 
  ld a, [CAMERA_WORLD_X]
  add a, META_TILES_PER_SCRN_ROW - 1

  ; stop if we're past the last tile we wanted to write
  cp c
  jr c, .done2

  push hl
  ; seek past map meta data
  call worldPositionToMetaTile
  ; now a has the meta tile index

  call writeRowMapTileToBuffer
  pop hl

  inc c

  jr .loop2
.done2

  ld a, [CAMERA_WORLD_X]
  sub c ; minus map width, - cols we wrote
  add META_TILES_PER_SCRN_ROW

  ld c, a ; be has blank tiles to write
.loop3
  ld a, c
  or a
  jr z, .done3

  call writeBlankRowTileToBuffer
  dec c

  jr .loop3
.done3

  ; after writing two rows of tiles (1 row of meta tiles)
  ; de will be pointing to the end of the top row
  ; so we have to advance de by MAP_BUFFER_WIDTH

  ld a, e
  add a, MAP_BUFFER_WIDTH
  ld e, a
  ld a, 0
  adc a, d
  ; de advanced one row

  pop hl
  pop bc

  ret

; @param hl - map to read
; @param de - where to write
writeBlankRowToBuffer:
  push bc

  ld a, META_TILES_PER_SCRN_ROW
  ld b, a
.loop
  ; the first tile in any map is the blank tile for that map
  call writeBlankRowTileToBuffer

  dec b
  jr nz, .loop
.done

  ; after writing two rows of tiles (1 row of meta tiles)
  ; de will be pointing to the end of the top row
  ; so we have to advance de by MAP_BUFFER_WIDTH

  ld a, e
  add a, MAP_BUFFER_WIDTH
  ld e, a
  ld a, 0
  adc a, d

  pop bc
  
  ret

; @param hl - meta tile to write
; @param de - write to address
writeRowMapTileToBuffer:
  push bc
  push hl
  push de

  ld l, a

  call metaTileIndexToAddress
  call getMetaTileTopLeft
  ld a, [hl]
  ld [de], a
  inc de

  call getMetaTileTopRight
  ld a, [hl]
  ld [de], a
  dec de

  ; advance 1 row in the buffer
  ld a, e
  add a, SCRN_WIDTH
  ld e, a
  ld a, 0
  adc a, d
  ld d, a

  ; @TODO should we check the carry here and maybe
  ; crash if we stepped wrongly?

  call getMetaTileBottomLeft
  ld a, [hl]
  ld [de], a
  inc de

  call getMetaTileBottomRight
  ld a, [hl]
  ld [de], a

  pop de
  pop hl
  pop bc

  inc hl ; we wrote one meta tile
  inc de
  inc de ; we wrote two tiles

  ret

; this doesn't actually need to change
; because it always uses the first nibble
; from the map
; @param hl - the map
; @param de - where to write to
writeBlankRowTileToBuffer:
  push bc
  push hl
  push de

  call getMapData
  ld a, [hl] ; the meta tile
  and a, %11110000 ; get the blank tile
  srl a
  srl a
  srl a
  srl a
  ld l, a

  call metaTileIndexToAddress
  ; now hl has the meta tile data
  call getMetaTileTopLeft
  ld a, [hl]
  ld [de], a
  inc de

  call getMetaTileTopRight
  ld a, [hl]
  ld [de], a
  dec de

  ; advance 1 row in the buffer
  ld a, e
  add a, SCRN_WIDTH
  ld e, a
  ld a, 0
  adc a, d
  ld d, a

  call getMetaTileBottomLeft
  ld a, [hl]
  ld [de], a
  inc de

  call getMetaTileBottomRight
  ld a, [hl]
  ld [de], a

  pop de
  pop hl
  pop bc

  inc de
  inc de ; we wrote 2 tiles

  ret

; @param a - a
; @param hl - hl
; @return hl - hl + a
addAToHL:
  add l ; a = a + l
	ld l, a ; l' = a'
	adc h ; a'' = a' + h + c ; what!?
	sub l ; l' here is a + l
	ld h, a ; so h is getting h + c yikes!

  ret

; @param bc - y, x in world space
; @param hl - address of map meta data
; @result hl - index of meta tile in map
seekIndex:
  push bc

  /** @TODO this needs to change 
   * seekIndex should take a map, not map data
   */

  ; @DEPENDS getMapData
  ; we are receiving map data and have to decrement to the metadata
  ; that sucks
  call rewindToMetaData
  inc hl ; inc to the length

  ld a, [hl] 
  srl a ; divide the width by 2 to get the byte width
  ld c, a

  dec hl ; back down to the map
  call getMapData ; and up to the map data
  call seekRow
  ; now hl points to the row

  pop bc

  ; now seek x
  ld a, c
  srl a ; divide by two to get the byte index
  inc a
.loop
  dec a
  jr z, .done
  inc hl

  jr .loop
.done

  ret

scrollUp:
  ld a, [rSCY]
  sub a, 16
  ld [rSCY], a

  ret

scrollDown:
  ld a, [rSCY]
  add a, 16
  ld [rSCY], a

  ret

scrollLeft:
  ld a, [rSCX]
  sub a, 16
  ld [rSCX], a

  ret

scrollRight:
  ld a, [rSCX]
  add a, 16
  ld [rSCX], a

  ret

drawBuffer:
  ld hl, MAP_BUFFER
  ld de, _SCRN0
  ld b, SCRN_HEIGHT

.loop
  call drawBufferRow
  REPT VRAM_WIDTH - SCRN_WIDTH ; advance to the next SCRN row
    inc de
  ENDR
  dec b
  jr nz, .loop
.done
  ret

drawBufferRow:
  ld c, SCRN_WIDTH
.loop
  ld a, [hl]
  ld [de], a
  inc hl
  inc de
  dec c
  jr nz, .loop
.done
  ret

initPalettes:
  ; darkest to lightest
  ld a, %11100100
  ld [rBGP], a
  ld [rOBP0], a

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

	ld a, IEF_VBLANK
	ld [rIE], a	; Set only Vblank interrupt flag

  ret

turnOnWindow:
  ; configure and activate the display
  ld a, LCDCF_ON|LCDCF_BG8800|LCDCF_BG9800|LCDCF_BGON|LCDCF_OBJ8|LCDCF_OBJON|LCDCF_WIN9C00|LCDCF_WINON
  ld [rLCDC], a

  ret

turnOffWindow:
  ; configure and activate the display
  ld a, LCDCF_ON|LCDCF_BG8800|LCDCF_BG9800|LCDCF_BGON|LCDCF_OBJ8|LCDCF_OBJON|LCDCF_WIN9C00|LCDCF_WINOFF
  ld [rLCDC], a

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

; @param hl - start
; @param b - the y to seek
; @param c - width
; @return hl - the row
seekRow:
  push de

  ld a, b
  or a ; if y is zero we are done
  jr z, .done
  rlca ; if y is negative we are done
  jr c, .done

  ld a, b

  ; de gets the width
  ld d, 0
  ld e, c
.loop
  add hl, de
  dec a
  jr nz, .loop
.done
  pop de
  ret

loadFontData:
  ld hl, FontTileset
  ld de, FONT_TILES
  ld b, FONT_TILES_COUNT

  ; each tile is 16 bytes
.loop
  call copy1bpp
  dec b
  jp nz, .loop
.done

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
INCLUDE "includes/rand.inc"
INCLUDE "includes/time.inc"
INCLUDE "includes/input.inc"
INCLUDE "includes/encounter-tables.inc"
INCLUDE "includes/game-state.inc"
INCLUDE "includes/game-state/overworld.inc"
INCLUDE "includes/game-state/random-encounter.inc"
INCLUDE "includes/game-state/game-over.inc"
INCLUDE "includes/game-state/exit.inc"
INCLUDE "includes/game-state/enter.inc"
INCLUDE "includes/game-state/dialog.inc"
INCLUDE "includes/smc-utils.inc"
INCLUDE "includes/map-draw.inc"
INCLUDE "includes/meta-tiles.inc"
INCLUDE "includes/player-movement.inc"
INCLUDE "includes/events.inc"
INCLUDE "includes/player.inc"
INCLUDE "includes/maps/underworld.inc"
INCLUDE "includes/maps/overworld.inc"

Section "GraphicsData", ROM0, ALIGN[6]

FontTileset:
INCBIN "assets/misaki_gothic.1bpp" ; 83 tiles

MasterTileset: 
INCBIN "assets/valley-graphics-8x8-tiles.2bpp" ; 80 tiles, 20 metatiles
INCBIN "assets/valley-map-8x8-tiles.2bpp" ; 44 tiles, 11 metatiles
INCBIN "assets/valley-sprites-8x8-tiles.2bpp" ; 8 tiles, the sprite, 2 metatiles @ 1F
INCBIN "assets/valley-additional-8x8-tiles.2bpp" ; 12 tiles, the boat, 3 metatiles @ 21
INCBIN "assets/window-graphics.2bpp" ; 12 tiles, the digits, 3 metatiles lol @ 24

PLAYER_SPRITE_WALK_0 EQU $1f
PLAYER_SPRITE_WALK_1 EQU $20

WINDOW_DIGITS_A EQU $24
WINDOW_DIGITS_B EQU $25
WINDOW_DIGITS_C EQU $26
WINDOW_DIGITS_D EQU $2A

WINDOW_FRAME_A EQU $28
WINDOW_FRAME_B EQU $29

MONSTER_SPRITE_ZERO EQU $27
MONSTER_SPRITE_ONE EQU $2B

SPRITE_TILES EQU $8000 ; 1st VRAM
SPRITE_TILES_COUNT EQU 3
SpriteTileset:
  db PLAYER_SPRITE_WALK_0, PLAYER_SPRITE_WALK_1, $00, $00, $00, $00, $00, $00,
  db $00, $00, $00, $00, $00, $00, $00, $00,

ENCOUNTER_TILES EQU $8400
ENCOUNTER_TILES_COUNT EQU 2
EncounterTiles:
  db MONSTER_SPRITE_ONE, MONSTER_SPRITE_ZERO, $00, $00, $00, $00, $00, $00
  db $00, $00, $00, $00, $00, $00, $00, $00,

MAP_TILES EQU $9000

WINDOW_TILES EQU $9400 ; 2nd line of 2nd VRAM
WINDOW_TILES_COUNT EQU 7
WindowTileset:
  db WINDOW_DIGITS_A, WINDOW_DIGITS_B, WINDOW_DIGITS_C, $00, WINDOW_FRAME_A, WINDOW_FRAME_B, WINDOW_DIGITS_D, $00,
  db $00, $00, $00, $00, $00, $00, $00, $00,

FONT_TILES EQU $8800 ; 3rd VRAM block
FONT_TILES_COUNT EQU 83