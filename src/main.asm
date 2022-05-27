INCLUDE "includes/hardware.inc"

SCRN_VERTICAL_STEP EQU 32
SCRN_HORIZONTAL_STEP EQU 1
SCRN_SIZE EQU SCRN_VERTICAL_STEP * SCRN_VERTICAL_STEP
BG_WIDTH EQU 20
BG_HEIGHT EQU 18

Section "start", ROM0[$0100]
  jp init

SECTION "main", ROM0[$150]

init:
  di

  ld a, %11100100
  ld [rBGP], a

  call turnOffLCD
  call loadTileData
  call blankScreen

  call drawBorder

  call turnOnLCD

main:
  halt
  jp main

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

turnOffLCD:
  ld a, [rLCDC]
  rlca
  ret nc

.waitForVBlank
  ld a, [rLY]
  cp 145
  jr nz, .waitForVBlank

  ; in VBlank
  ld a, [rLCDC]
  res 7, a
  ld [rLCDC], a

  ret

turnOnLCD:
  ; configure and activate the display
  ld a, LCDCF_ON|LCDCF_BG8000|LCDCF_BG9800|LCDCF_BGON|LCDCF_OBJ8|LCDCF_OBJOFF
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

EndTileData: