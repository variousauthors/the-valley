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

.draw
  ld hl, _SCRN0 - 32 ; 
  ld de, 32 * 18 ; end here
  ld bc, 32 ; bytes per row

  ; loop down the side of the screen

.drawLoop
  add hl, bc
  ld [hl], $01 ; load the tile

  ; are we done?
  ld a, l
  cp a, e
  jp nz, .drawLoop
  ld a, h
  cp a, d
  jp nz, .drawLoop

  ; we done

  call turnOnLCD

main:
  halt
  jp main

; draws the left border on the edge of the play area
drawBorder:
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
EndTileData: