INCLUDE "includes/hardware.inc"

Section "start", ROM0[$0100]
  jp init

SECTION "main", ROM0[$150]

init:
  di

  ld a, %11100100
  ld [rBGP], a

  call turnOffLCD

  ; do stuff
  ld hl, TileData
  ld de, _VRAM
  ld b, 16

.loadData
  ld a, [hl]
  ld [de], a
  dec b
  jr z, .doneLoading
  inc hl
  inc de
  jr .loadData
.doneLoading

.draw
  ld hl, _SCRN0
  ld [hl], $00

  call turnOnLCD

main:
  halt
  jp main

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

TileData:
  DB  $7C, $7C, $82, $FE, $82, $D6, $82, $D6
  DB  $82, $FE, $82, $BA, $82, $C6, $7C, $7C
EndTileData: