INCLUDE "includes/hardware.inc"

SCRN_VERTICAL_STEP EQU 32
SCRN_HORIZONTAL_STEP EQU 1
SCRN_SIZE EQU SCRN_VERTICAL_STEP * SCRN_VERTICAL_STEP
BG_WIDTH EQU 20
BG_HEIGHT EQU 18

; field includes the 8 px borders
FIELD_TOP EQU 16 + 8
FIELD_RIGHT EQU 160 - 8
FIELD_BOTTOM EQU 152 ; there is no border on the bottom
FIELD_LEFT EQU 8 + 8

; ball sprite
BALL_SPRITE_Y EQU _OAMRAM ; the first sprite in OAM
BALL_SPRITE_X EQU _OAMRAM+1
BALL_SPRITE_NO EQU _OAMRAM+2
BALL_SPRITE_ATTRIBUTES EQU _OAMRAM+3
 
; ball velocity
BALL_DX EQU _RAM
BALL_DY EQU _RAM + 1

Section "start", ROM0[$0100]
  jp init

SECTION "main", ROM0[$150]

init:
  di

  call initPalettes
  call turnOffLCD
  call loadTileData
  call blankScreen
  call drawBorder
  call initSprites
  call turnOnLCD

main:
  call waitForVBlank
  call updateBallPosition
  call handleBallWallCollision
  call pause

  jp main

updateBallPosition:
  ; increment x
  ld a, [BALL_SPRITE_X]    ; We load the current X position of the sprite
  ld hl, BALL_DX       ; hl, the incrementing direction X
  add a, [hl]         ; add

  ld hl, BALL_SPRITE_X
  ld [hl], a         ; keep

  ; incrementamos las y
  ld a, [BALL_SPRITE_Y]    ;  And we load the current position of the sprite
  ld hl, BALL_DY       ; hl in the direction of increasing Y
  add a, [hl]         ; add
  ld hl, BALL_SPRITE_Y
  ld [hl], a         ; keep

  ret

; magical number that makes the ball / wall collision look nice
; the ball is only 4 pixels across, which leaves 2 pixels on either
; side of the sprite... but 3 looks better
WALL_COLLISION_CONSTANT EQU 3

handleBallWallCollision:
.check_bottom
  ld a, [BALL_SPRITE_Y]
  cp FIELD_BOTTOM + WALL_COLLISION_CONSTANT ; 
  jr nz, .check_top

  ; if we hit we bounce up
  ld a, -1
  ld [BALL_DY], a

.check_top
  ld a, [BALL_SPRITE_Y]
  cp FIELD_TOP - WALL_COLLISION_CONSTANT
  jr nz, .check_right

  ; if we hit we bounce down
  ld a, 1
  ld [BALL_DY], a

.check_right
  ld a, [BALL_SPRITE_X]
  cp FIELD_RIGHT + WALL_COLLISION_CONSTANT
  jr nz, .check_left

  ; if we hit we bounce left
  ld a, -1
  ld [BALL_DX], a

.check_left
  ld a, [BALL_SPRITE_X]
  cp FIELD_LEFT - WALL_COLLISION_CONSTANT
  jr nz, .done

  ; if we hit we bounce right
  ld a, 1
  ld [BALL_DX], a

.done

  ret

ARBITRARY_WAIT_CONSTANT EQU 4000

pause:
  ld de, ARBITRARY_WAIT_CONSTANT
.loop:
  dec de
  ld a, d
  or e
  jr nz, .loop

  ret

blankSprites:
  ld hl, BALL_SPRITE_NO
  ld bc, 4 ; bytes per sprite
  ld d, 40 ; number of sprites
  ld e, TILE_BLANK
  call drawLine

  ret

START_Y EQU 30
START_X EQU 30

initSprites:
  call blankSprites

  ld a, START_Y
  ld [BALL_SPRITE_Y], a    ;Y position of the sprite     
  ld a, START_X
  ld [BALL_SPRITE_X], a    ; X position of the sprite
  ld a, TILE_BALL 
  ld [BALL_SPRITE_NO], a  ; number of tile on the table that we will use tiles
  ld a, 0
  ld [BALL_SPRITE_ATTRIBUTES], a  ; special attributes, so far nothing.

  ; We prepare animation variables
  ld a, 1
  ld [BALL_DX], a
  ld [BALL_DY], a

  ret

; scratches a
drawBorder:
  push bc
  push de
  push hl

  ; left
  ld hl, _SCRN0
  ld bc, SCRN_VERTICAL_STEP
  ld d, BG_HEIGHT
  ld e, BORDER_LEFT
  call drawLine

  ; top
  ld hl, _SCRN0
  ld bc, SCRN_HORIZONTAL_STEP
  ld d, BG_WIDTH
  ld e, BORDER_TOP
  call drawLine

  ; right
  ld hl, _SCRN0 + BG_WIDTH - 1
  ld bc, SCRN_VERTICAL_STEP
  ld d, BG_HEIGHT
  ld e, BORDER_RIGHT
  call drawLine

  ; corners

  ld hl, _SCRN0
  ld e, BORDER_TOP_LEFT
  call drawPoint

  ld hl, _SCRN0 + BG_WIDTH - 1
  ld e, BORDER_TOP_RIGHT
  call drawPoint

  pop hl
  pop de
  pop bc

  ret


; it draws the given tile byte once at the given address
; @param hl where
; @param e the tile
drawPoint:
  ld a, e
  ld [hl], a
  ret

; it draws the given tile byte the given number of times
; at the given interval, starting from the given address
; resulting in a "line" of the same tile
; @param hl where to start
; @param bc bytes per step
; @param d how many steps
; @param e the tile
drawLine:
.loop
  ld a, e
  ld [hl], a ; load the tile
  add hl, bc

  dec d
  ld a, 0
  cp d ; if a == d we are done
  jp nz, .loop

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

  ret

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


loadTileData:
  ; do stuff
  ld hl, TileData
  ld de, _VRAM
  ld b, EndTileData - TileData

.loadData
  ld a, [hl]
  ld [de], a
  dec b
  jr z, .doneLoading
  inc hl
  inc de
  jr .loadData
.doneLoading
  ret

TileData:
opt g.123
TILE_BLANK EQU 0
  dw `........
  dw `........
  dw `........
  dw `........
  dw `........
  dw `........
  dw `........
  dw `........

BORDER_LEFT EQU 1
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223

BORDER_TOP EQU 2
  dw `33333333
  dw `22222222
  dw `11111111
  dw `11111111
  dw `11111111
  dw `22222222
  dw `22222222
  dw `33333333

BORDER_RIGHT EQU 3
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123

BORDER_TOP_LEFT EQU 4
  dw `33333333
  dw `33222222
  dw `32311111
  dw `32121111
  dw `32112111
  dw `32111322
  dw `32111232
  dw `32111223

BORDER_TOP_RIGHT EQU 5
  dw `33333333
  dw `22222233
  dw `11111323
  dw `11112123
  dw `11121123
  dw `22311123
  dw `23211123
  dw `32211123

TILE_BALL EQU 6
  dw `........
  dw `........
  dw `...33...
  dw `..3.33..
  dw `..3333..
  dw `...33...
  dw `........
  dw `........

EndTileData: