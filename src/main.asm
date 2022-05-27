INCLUDE "includes/hardware.inc"

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

  ; left
  ld hl, _SCRN0
  ld bc, 32
  ld d, 18
  ld e, $01
  call drawLine

  ; top
  ld hl, _SCRN0
  ld bc, 1
  ld d, 20
  ld e, $02
  call drawLine

  ; right
  ld hl, _SCRN0 + 20 - 1
  ld bc, 32
  ld d, 18
  ld e, $03
  call drawLine

  ; corners

  ld hl, _SCRN0
  ld e, $04
  call drawPoint

  ld hl, _SCRN0 + 20 - 1
  ld e, $05
  call drawPoint

  call turnOnLCD

main:
  halt
  jp main

; @param hl where
; @param e the tile
drawPoint:
  ld a, e
  ld [hl], a
  ret

; draws the left border on the edge of the play area
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
  cp d ; a == d
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

blankScreen:
  ld hl, _SCRN0
  ld de, 32 * 32
.loop
  ld a, 0
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
  dw `........
  dw `........
  dw `........
  dw `........
  dw `........
  dw `........
  dw `........
  dw `........

  ; tile left
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223

  ; tile top
  dw `33333333
  dw `22222222
  dw `11111111
  dw `11111111
  dw `11111111
  dw `22222222
  dw `22222222
  dw `33333333

  ; tile right
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123

  ; top-left corner
  dw `33333333
  dw `33222222
  dw `32311111
  dw `32121111
  dw `32112111
  dw `32111322
  dw `32111232
  dw `32111223

  ; top-right corner
  dw `33333333
  dw `22222233
  dw `11111323
  dw `11112123
  dw `11121123
  dw `22311123
  dw `23211123
  dw `32211123

EndTileData: