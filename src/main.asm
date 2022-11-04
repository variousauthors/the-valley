INCLUDE "includes/hardware.inc"
INCLUDE "includes/dma.inc"

MAP_TILES EQU _VRAM
SPRITE_TILES EQU $8800 ; 2nd VRAM

SCRN_VERTICAL_STEP EQU 32
SCRN_HORIZONTAL_STEP EQU 1
SCRN_SIZE EQU SCRN_VERTICAL_STEP * SCRN_VERTICAL_STEP
BG_WIDTH EQU 20
BG_HEIGHT EQU 18

CHUNK_WIDTH EQU 20
CHUNK_HEIGHT EQU 18

PLAYER_START_X EQU 14
PLAYER_START_Y EQU 16


; 

; ball start in WORLD position
START_Y EQU 8
START_X EQU 8

; field includes the 8 px borders
FIELD_TOP EQU 16 + 8
FIELD_RIGHT EQU 160 - 8
FIELD_BOTTOM EQU 152 ; there is no border on the bottom
FIELD_LEFT EQU 8 + 8

SECTION "OAMData", WRAM0, ALIGN[8]
Sprites: ; OAM Memory is for 40 sprites with 4 bytes per sprite
  ds 40 * 4
.end:
 
SECTION "CommonRAM", WRAM0

; all the bits we need for inputs 
_PAD: ds 2

; directions
RIGHT EQU %00010000
LEFT  EQU %00100000
UP    EQU %01000000
DOWN  EQU %10000000

A_BUTTON EQU %00000001
B_BUTTON EQU %00000010


; ball velocity
BALL_DX: ds 1
BALL_DY: ds 1
; ball position
BALL_X: ds 1
BALL_Y: ds 1

; where is the current chunk being rendered
CURRENT_CHUNK_CORNER_X: ds 1
CURRENT_CHUNK_CORNER_Y: ds 1

CAMERA_X: ds 1
CAMERA_Y: ds 1

NEXT_SPRITE: ds 1
ONE_SPRITE EQU 4 ; bytes per sprite

; ball sprite
BALL_SPRITE_NO: ds 1
BALL_SPRITE_ATTRIBUTES: ds 1

; brick position table
BRICK_SIZE EQU 1 ; just a flag to see if the brick exists

; remembet, the bricks are "half tall" only 4 pixels tall
TOP_LEFT_BRICK_X EQU 10 ; 10 x 8 pixels over
TOP_LEFT_BRICK_Y EQU 18 ; 18 x 4 pixels down

BRICK_PER_ROW EQU 12
BRICK_ROWS EQU 8

MAX_BRICKS EQU BRICK_PER_ROW * BRICK_ROWS ; that's just a rectangle of bricks

BRICK_TABLE: ds BRICK_SIZE * MAX_BRICKS

; enough bytes to buffer the whole _SCRN
MAP_BUFFER: ds BG_WIDTH * BG_HEIGHT
MAP_BUFFER_END:

TILE_BLANK EQU $80 + 0
BRICK_BOTTOM EQU $80 + 1
BRICK_TOP EQU $80 + 2
BRICK_DOUBLE EQU $80 + 3
BORDER_LEFT EQU $80 + 4
BORDER_TOP EQU $80 + 5
BORDER_RIGHT EQU $80 + 6
BORDER_TOP_LEFT EQU $80 + 7
BORDER_TOP_RIGHT EQU $80 + 8
TILE_BALL EQU $80 + 9

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

Section "start", ROM0[$0100]
  jp init

SECTION "main", ROM0[$150]

init:
  di

  dma_Copy2HRAM	; sets up routine from dma.inc that updates sprites

  call ZeroOutWorkRAM ; it is easier to inspect this way
  call initPalettes
  call turnOffLCD

  ld hl, ArkanoidTiles
  ld b, ArkanoidTiles.end - ArkanoidTiles
  ld de, MAP_TILES
  call loadTileData

  ld hl, ArkanoidGraphics
  ld b, ArkanoidGraphics.end - ArkanoidGraphics
  ld de, SPRITE_TILES
  call loadTileData

  ld hl, BALL_X ; world position
  ld a, PLAYER_START_X
  ld [hl], a

  ld hl, BALL_Y ; world position
  ld a, PLAYER_START_Y
  ld [hl], a

  call blankScreen
  call writeOverworldToBuffer

  call drawBuffer
  call turnOnLCD

  ei

main:
  halt

  nop

  ; if there was no input last frame, skip drawing
  ld a, [_PAD]
  and a
  jp z, .skipDrawing

  call turnOffLCD
  call drawBuffer
  call turnOnLCD

  ; but don't do anythihng else, we want to wait
  ; for a frame with no input... ie the user has to lift the key
  ; with each input. this is just temporary to prevent duplicate inputs
  call readInput
  jp main

.skipDrawing
  call readInput

  ; if there is not input this frame, skip thinking
  ld a, [_PAD]
  and a
  jp z, main

  call doPlayerMovement
  call writeOverworldToBuffer

  jp main
; -- END MAIN --

drawBuffer:
  ld hl, MAP_BUFFER
  ld de, _SCRN0
  ld b, BG_HEIGHT

.loop
  call drawBufferRow
  REPT 12 ; advance to the next visible row
    inc de
  ENDR
  dec b
  jr nz, .loop
.done
  ret

drawBufferRow:
  ld c, BG_WIDTH
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

doPlayerMovement:
  ; if there is no input bail
  ld a, [_PAD]
  and a
  ret z

  ; now we update the player depending on the buttons
  ld a, [_PAD]
  and RIGHT
  jr nz, .moveRight ; move right

  ld a, [_PAD]
  and LEFT
  jr nz, .moveLeft ; move left

  ld a, [_PAD]
  and UP
  jr nz, .moveUp ; move up

  ld a, [_PAD]
  and DOWN
  jr nz, .moveDown ; move down

.moveRight
  ld a, [BALL_X]
  inc a
  ld [BALL_X], a

  ret
.moveLeft
  ld a, [BALL_X]
  dec a
  ld [BALL_X], a

  ret
.moveUp
  ld a, [BALL_Y]
  dec a
  ld [BALL_Y], a
  ret
.moveDown
  ld a, [BALL_Y]
  inc a
  ld [BALL_Y], a
  ret
; -- END readInput --

; write the blank tile to the whole SCRN0
blankScreen:
  ld hl, _SCRN0
  ld de, SCRN_SIZE
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
; @param b - width
; @param c - row to seek
; @return hl - the row
seekRow:
  ld a, c
  push de

  ; de gets the width
  ld d, 0
  ld e, b

.loop
  add hl, de
  dec a
  jr nz, .loop
.done
  pop de
  ret

HALF_SCREEN_WIDTH EQU BG_WIDTH / 2 ; 10 meta tiles
HALF_SCREEN_HEIGHT EQU BG_HEIGHT / 2 ; 9 meta tiles

; based on the player's overworld position (0 - 128)
; fill the visible screen
; from the overworld data
writeOverworldToBuffer:
  ld a, [BALL_Y] ; PLAYER_POS_Y
  sub a, HALF_SCREEN_HEIGHT
  ld c, a ; y of the row to write

  ; seek to c
  ld hl, Overworld
  ld b, OVERWORLD_WIDTH
  call seekRow
  ; now hl points to the first row

  ld de, MAP_BUFFER

; assumption, b and c are positive
; ie the player cannot approach the edges of the overworld
  ld b, BG_HEIGHT ; we will just write 18 rows
.loop
  call writeOverworldRowToBuffer
  dec b
  jr nz, .loop

.done
  ret

; @param b - index of the start tile
; @param c - OVERWORLD_WIDTH - index of the current tile
; @return nz - if we should draw
shouldDrawTile:
  ld a, OVERWORLD_WIDTH
  sub a, c
  ; now a has the index of the current tile to draw

  ; index < start tile => don't draw
  cp a, b
  jr c, .tooSoon

  ; index - screen_width >= start tile => don't draw
  sub a, BG_WIDTH
  jr c, .draw ; if index < screen width, we certainly draw

  cp a, b
  jr z, .tooLate
  jr nc, .tooLate

.draw
  ; returning nz

  ret

.tooSoon
  cp a ; setting z
  ret

.tooLate
  cp a ; setting z
  ret

; @param hl - row to write
; @param de - MAP_BUFFER at row
writeOverworldRowToBuffer: 
  push bc
  ld a, [BALL_X] ; PLAYER_POS_X
  sub a, HALF_SCREEN_WIDTH
  ld b, a ; b gets topLeftX

  ; move across the whole row
  ; drawing only where we need to

  ; go until we write the whole row
  ld c, OVERWORLD_WIDTH
.loop
  ; determine if hl is inside visible bounds
  call shouldDrawTile
  jr z, .skip
.draw
  ld a, [hl]
  ld [de], a
  inc de ; we drew, so advance the buffer pointer
.skip
  inc hl
  dec c
  jr nz, .loop

.done

  pop bc
  ret

; @param hl -- tileset
; @param de -- location
; @param b -- bytes
loadTileData:
  push de
  push bc

.loadData
  ld a, [hl]
  ld [de], a
  dec b
  jr z, .doneLoading
  inc hl
  inc de
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

Section "overworld", ROM0
OVERWORLD_WIDTH EQU 32
OVERWORLD_HEIGHT EQU 32
Overworld:
  db 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0
EndOverworld:

Section "GraphicsData", ROM0

ArkanoidTiles: INCBIN "assets/arkanoid-map.2bpp"
.end

ArkanoidGraphics: INCBIN "assets/arkanoid-graphics.2bpp"
.end

ArkanoidMap: INCBIN "assets/arkanoid-map.tilemap"
.end