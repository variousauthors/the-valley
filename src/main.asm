INCLUDE "includes/hardware.inc"
INCLUDE "includes/dma.inc"

MAP_TILES EQU _VRAM
SPRITE_TILES EQU $8800 ; 2nd VRAM

VRAM_WIDTH EQU 32
VRAM_HEIGHT EQU 32
VRAM_SIZE EQU VRAM_WIDTH * VRAM_HEIGHT
SCRN_WIDTH EQU 20
SCRN_HEIGHT EQU 18

; temporary, useful for testing
; in practice maps will have their own entrances/exits
PLAYER_START_Y EQU 0;  4
PLAYER_START_X EQU 0; 5

SECTION "OAMData", WRAM0, ALIGN[8]
Sprites: ; OAM Memory is for 40 sprites with 4 bytes per sprite
  ds 40 * 4
.end:
 
SECTION "CommonRAM", WRAM0

GAME_OVER: ds 1 ; a byte to note whether the game is over

; all the bits we need for inputs 
_PAD: ds 2

; directions
RIGHT EQU %00010000
LEFT  EQU %00100000
UP    EQU %01000000
DOWN  EQU %10000000

A_BUTTON EQU %00000001
B_BUTTON EQU %00000010

; enough bytes to buffer the whole _SCRN
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

/*
player pushes left
if next y,x is valid
this sets the "next y,x"
if next y,x is not equal to y,x
add dy,dx to sub_y,sub_x
if sub_y is 16 set y to next y
if sub_x is 16 set x to next x

meanwhile, the camera
 - if the player has next y,x not equal to y,x
   wait for sub_y or sub_x to be > 4
   try to get 1 meta tile ahead of them
 - if the playr next y,x is y,x
   try to center them

*/


SECTION "PLAYER_STATE", WRAM0
; world position
PLAYER_WORLD_X: ds 1
PLAYER_SUB_X: ds 1 ; 1/16th meta tile
PLAYER_WORLD_Y: ds 1
PLAYER_SUB_Y: ds 1
PLAYER_NEXT_WORLD_X: ds 1
PLAYER_NEXT_WORLD_Y: ds 1

PLAYER_SPRITE_TILES: ds 4

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

SECTION "GAME_STATE", WRAM0

GAME_STATE_LOW_BYTE: ds 1
GAME_STATE_HIGH_BYTE: ds 1

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

  call resetTime
  call ZeroOutWorkRAM ; it is easier to inspect this way
  call initPalettes
  call turnOffLCD

  ld hl, OverworldTiles
  ld b, OVERWORLD_TILES_COUNT
  ld de, MAP_TILES
  call loadTileData

  ; initialize the game state to overworld
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(overworldGameState)
  ld [hl+], a
  ld a, HIGH(overworldGameState)
  ld [hl], a

  ; player starts in the overworld
  call initCurrentMap

  call initMapDrawTemplates

  ; initial position
  ld hl, PLAYER_WORLD_X
  ld a, PLAYER_START_X
  ld [hl], a
  ld hl, PLAYER_NEXT_WORLD_X
  ld [hl], a

  ld hl, PLAYER_WORLD_Y
  ld a, PLAYER_START_Y
  ld [hl], a
  ld hl, PLAYER_NEXT_WORLD_Y
  ld [hl], a

  ; init player sprite tiles
  ld hl, PLAYER_SPRITE_TILES
  ld a, 53
  ld [hl+], a
  ld a, 54
  ld [hl+], a
  ld a, 55
  ld [hl+], a
  ld a, 56
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

  call blankVRAM
  ; @TODO here I think I should just
  ; copy the memory to VRAM straight up
  ; since LCD will be off
  call getCurrentMap
  call drawFullScene
  call turnOnLCD

  ei

main:
  halt

  nop

  call tick
  call mapDraw
  call screenCenterOnCamera
  call drawPlayer

  ; -- INTERPOLATE STATE --

  ; every frame we might need to oscillate some states
  ; such as for animations, so we always interpolate

  call updatePlayerPosition
  call cameraFollowPlayer
  call updateCameraPosition

  ; -- STEADY STATE --
  ; if the game is in a steady state, ie "nothing is happening"
  ; then we move on to the next step in the game loop,

  ; there are two phases here:

  ; 1. is current state equal to next
  ; if not, keep animating
  call isCurrentStateEqualToNext
  jr nz, main

  ; 2. is the current step of the game loop finished
  ; if not, keep processing events
  call isCurrentStepFinished
  jr z, .nextStep

  ; -- MOVEMENT EVENTS --
  ; check for things like random encounters, entering doors, etc...
  ; things that are the results of state updates

  call checkForAutoEvent
  jr z, .noAutoEvents

  call handleAutoEvent

  ; if we had auto events we may not be in a steady state
  jr main

.noAutoEvents
  ; check for random encounters

.noRandomEncounters

.nextStep
  call performGameStep

  jp main
; -- END MAIN --

; -- GAME STATES --

performGameStep:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  call indirectCall

  ret

/** wandering the overworld */
overworldGameState:
  ; -- INPUT PHASE JUST RECORDS ACTIONS --

  call readInput

  ; if there is not input this frame, skip thinking
  ld a, [_PAD]
  and a
  ret z

  ; record intents
  call doPlayerMovement

  ; -- UPDATE STATE BASED ON ACTIONS --

  ; doPlayerMovement puts the requested move somwhere for us
  ; we can use that to get the callback we need to respond to
  ; the movement

  call handlePlayerMovement
  call nz, resetInput ; if there was no move (ie collision)

  ret

/** watching the game over happen */
gameOverGameState:
  call waitForVBlank

  ; hide the player
  ld a, LCDCF_ON|LCDCF_BG8000|LCDCF_BG9800|LCDCF_BGON|LCDCF_OBJ8|LCDCF_OBJOFF
  ld [rLCDC], a

  ; fade out the screen slowly
  call count4In4Frames

  ld hl, WhiteOutPalettes
  push af

  ; add a to hl
  add l
	ld l, a
	adc h
	sub l
	ld h, a

  ; get the next palette
  ld a, [hl]

  ld [rBGP], a
  ld [rOBP0], a
  
  pop af
  cp a, 3 ; are we done fading out?
  jp nz, .continue

  ld a, 0
  ld [rIE], a
  halt ; forever

.continue

  ret

WhiteOutPalettes:
  db %11100100
  db %10010000
  db %01000000
  db %00000000

BlackOutPalettes:
  db %11100100
  db %11111001
  db %11111110
  db %11111111

; @param - hl the address of some subroutie to call
indirectCall:
  jp hl


HALF_SCREEN_WIDTH EQU SCRN_WIDTH / 2 ; 10 meta tiles
HALF_SCREEN_HEIGHT EQU SCRN_HEIGHT / 2 ; 9 meta tiles

META_TILES_TO_SCRN_LEFT EQU HALF_SCREEN_WIDTH / 2 - 1
META_TILES_TO_SCRN_RIGHT EQU HALF_SCREEN_WIDTH / 2
META_TILES_TO_TOP_OF_SCRN EQU HALF_SCREEN_HEIGHT / 2
META_TILES_TO_BOTTOM_OF_SCRN EQU META_TILES_TO_TOP_OF_SCRN
META_TILES_PER_SCRN_ROW EQU HALF_SCREEN_WIDTH
META_TILE_ROWS_PER_SCRN EQU HALF_SCREEN_HEIGHT

; are we in a steady state
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

  ret

; @return z - step finished
isCurrentStepFinished:
  ; check _Pad
  ld a, [_PAD]
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

  ld hl, PLAYER_WORLD_Y
  ld de, CAMERA_WORLD_Y
  call pixelDistance
  ld b, a

  ld hl, PLAYER_WORLD_X
  ld de, CAMERA_WORLD_X
  call pixelDistance
  ld c, a

  ld hl, PLAYER_SPRITE_TILES

  ld de, Sprites + (8 * 4)
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

; @param hl - position in tile/sub tile
; @param b - target position
; destroys c
updatePosition:
  ld a, [hl] ; world pos
  ld c, a
  ld a, b ; target pos
  sub a, c ; diff will be 1 or -1 (uh, why don't we store dx instead of a target pos...)

  or a
  jr nz, .next
  ret

.next
  inc hl ; set to sub pos
  add a, [hl]
  ld [hl], a ; adjust sub_x by the 1 or -1

  call absA
  ; if abs(a) is 16 set x to next x
  cp a, 16
  ret nz

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

; @param hl - map
writeMapToBuffer:
  ; subtract from player y, x to get top left corner
  ld a, [CAMERA_WORLD_Y]
  ld de, MAP_BUFFER
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
  call getMapData
  call seekIndex
  ; now hl has the map index to start reading from

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

  ld a, 5 ; META_TILES_PER_SCRN_ROW
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

  ld a, [hl] ; the meta tile
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

; @param hl - the map
; @param de - where to write to
writeBlankRowTileToBuffer:
  push bc
  push hl
  push de

  call getMapData
  ld a, [hl] ; the meta tile
  and a, %11110000 ; get first index
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

  push bc
  push hl
  push de

  inc de
  inc de ; we wrote 2 tiles

  ; NOW WRITE THE NEXT TILE

  call getMapData
  ld a, [hl] ; the meta tile
  and a, %00001111 ; get first index
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

  inc de
  inc de
  inc de
  inc de ; we wrote 4 tiles total

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

  dec hl ; 
  dec hl ; we have to decrement across the other metadata 
  dec hl ; the map width is before the map
  ld a, [hl] 
  ld c, a
  inc hl ; 
  inc hl ; and then inc back up to the data...
  inc hl ; point to the start of the map
  call seekRow
  ; now hl points to the row

  pop bc

  ld a, c
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

waitForVBlank:
.loop
  ld a, [rLY]
  cp 145
  jr nz, .loop

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
  ld a, LCDCF_ON|LCDCF_BG8000|LCDCF_BG9800|LCDCF_BGON|LCDCF_OBJ8|LCDCF_OBJON
  ld [rLCDC], a

	ld a, IEF_VBLANK
	ld [rIE], a	; Set only Vblank interrupt flag

  ret

resetInput:
  ld hl, _PAD
  ld [hl], 0
  ret

readInput:
  ; read the cruzeta (the d-pad)
  ld a, %00100000 ; select the d-pad
  ld [rP1], a

  ; read the d-pad several times to avoid bouncing
  ld a, [rP1] ; could also do
  ld a, [rP1] ; rept 4
  ld a, [rP1] ; ld a, [rP1]
  ld a, [rP1] ; endr

  and $0F
  swap a
  ld b, a

  ; we go for the buttons
  ld a, %00010000 ; bit 4 to 1 bit 5 to 0 (enable buttons, disable d-pad)
  ld [rP1], a

  ; read the buttons several times to avoid bouncing
  ld a, [rP1] ; could also do
  ld a, [rP1] ; rept 4
  ld a, [rP1] ; ld a, [rP1]
  ld a, [rP1] ; endr

  and $0F
  or b

  ; we now have a with 0 for down and 1 for up
  cpl ; complement so 1 means down :D
  ld [_PAD], a
.done
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

; @param hl -- tileset
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

  ; each tile is 16 bytes
  ld c, 16
.loadTile
  ld a, [hl+]
  ld [de], a
  inc de
  dec c
  jr nz, .loadTile
.doneTile
  ; next tile
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

INCLUDE "includes/time.inc"
INCLUDE "includes/smc-utils.inc"
INCLUDE "includes/map-draw.inc"
INCLUDE "includes/meta-tiles.inc"
INCLUDE "includes/player-movement.inc"
INCLUDE "includes/events.inc"
INCLUDE "includes/maps/start.inc"
INCLUDE "includes/maps/start-interior.inc"
INCLUDE "includes/maps/overworld.inc"
INCLUDE "includes/maps/ford-01.inc"
INCLUDE "includes/maps/the-long-road.inc"
INCLUDE "includes/maps/old-swamp.inc"
INCLUDE "includes/maps/old-swamp-south.inc"
INCLUDE "includes/maps/swamp-tunnel-west.inc"
INCLUDE "includes/maps/swamp-tunnel-east.inc"
INCLUDE "includes/maps/twins-crossing-west.inc"
INCLUDE "includes/maps/twins-crossing-east.inc"
INCLUDE "includes/maps/ruined-temple.inc"
INCLUDE "includes/maps/old-pond.inc"
INCLUDE "includes/maps/north-forest-temple.inc"
INCLUDE "includes/maps/central-forest-temple.inc"
INCLUDE "includes/maps/south-forest-temple.inc"
INCLUDE "includes/maps/coastal-grove.inc"
INCLUDE "includes/maps/peninsula-ruins.inc"
INCLUDE "includes/maps/the-catacombs.inc"
INCLUDE "includes/maps/underpass-one.inc"
INCLUDE "includes/maps/underpass-two.inc"
INCLUDE "includes/maps/tunnels-entrance.inc"
INCLUDE "includes/maps/tunnels.inc"
INCLUDE "includes/maps/meditation-room.inc"
INCLUDE "includes/maps/final-maze.inc"
INCLUDE "includes/maps/ruins-one.inc"
INCLUDE "includes/maps/ruins-one-interior.inc"
INCLUDE "includes/maps/ruins-two.inc"
INCLUDE "includes/maps/ruins-two-interior.inc"
INCLUDE "includes/maps/ruins-three.inc"
INCLUDE "includes/maps/ruins-three-interior.inc"
INCLUDE "includes/maps/tower.inc"
INCLUDE "includes/maps/tower-interior.inc"
INCLUDE "includes/maps/tower-approach.inc"
INCLUDE "includes/maps/desert.inc"
INCLUDE "includes/maps/hidden-peninsula.inc"
INCLUDE "includes/maps/desert-town.inc"
INCLUDE "includes/maps/underworld.inc"

Section "GraphicsData", ROM0

/* @TODO later each map will include its own tiles */
OverworldTiles: INCBIN "assets/valley-graphics-8x8-tiles.2bpp"
OVERWORLD_TILES_COUNT EQU 69

