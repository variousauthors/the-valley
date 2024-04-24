IF !DEF(GBC_UTILS_INC)
GBC_UTILS_INC = 1

SECTION "GBCUtils", ROM0

LIGHT_GREEN EQU $23f3 ; $23ee ; $136a
MID_GREEN EQU $02c8 ; $034c ; $02e9 ; $0265
DARK_GREEN EQU $0120
OCEAN_BLUE EQU $7e29 ; $75c1 ; $7AAC
WAVES_BLUE EQU $7e24
WHITE EQU $7fff
BLACK EQU $0000
LIGHT_GRAY EQU $39ce
DARK_GRAY EQU $2529
BRIDGE_BROWN EQU $0552

initGBCPalettes:
  ld a, %10000000
  ld [rBCPS], a
  ld hl, rBCPD

  ; grey scale
  ld de, LIGHT_GREEN 
  ld [hl], e
  ld [hl], d
  ld de, LIGHT_GRAY
  ld [hl], e
  ld [hl], d
  ld de, DARK_GRAY
  ld [hl], e
  ld [hl], d
  ld de, BLACK
  ld [hl], e
  ld [hl], d

  ; blue scale
  ld de, WHITE
  ld [hl], e
  ld [hl], d
  ld de, OCEAN_BLUE
  ld [hl], e
  ld [hl], d
  ld de, BRIDGE_BROWN
  ld [hl], e
  ld [hl], d
  ld de, $7626
  ld [hl], e
  ld [hl], d

  ; green scale
  ld de, LIGHT_GREEN
  ld [hl], e
  ld [hl], d
  ld de, MID_GREEN
  ld [hl], e
  ld [hl], d
  ld de, DARK_GREEN
  ld [hl], e
  ld [hl], d
  ld de, $0000
  ld [hl], e
  ld [hl], d


  ret

/** OK so the strategy here was to store 
 * the top two bits of the attrubutes (the palette)
 * _with_ the meta tile address since we only use 127 
 * BG tiles per map that's 00111111 and the palette index
 * can go in the top two bits 
 * this limits us to 4 palettes but it makes it easy to
 * just "draw the buffer again" into the second VRAM bank
 * ignoring the tile data and just shifting 11000000 into
 * the correct form */
drawGBCAttributes:
  ld hl, MAP_BUFFER
  ld de, _SCRN0
  ld b, SCRN_HEIGHT

  ; select GBC bank 1
  ld a, 1
  ld [rVBK], a

.loop
  call drawAttributesRow
  REPT VRAM_WIDTH - SCRN_WIDTH ; advance to the next SCRN row
    inc de
  ENDR
  dec b
  jr nz, .loop
.done
  ret

drawAttributesRow:
  ld c, SCRN_WIDTH
.loop
  ld a, [hl]

  ; select out the attributes
  and a, %11000000
  ; shift left 4 times %00001100
  swap a
	and $f
  sra a
  sra a ; %00000011 <-- attributes

  ld [de], a
  inc hl
  inc de
  dec c
  jr nz, .loop
.done
  ret

/*** @see drawGBCAttributes 
  * here we get the tile attributes
  * for the metatile and put just the palette
  * index into the top 2 bits of the buffer */
packGBCPaletteIndex:
  push de
  push af
  call getCurrentMapTilesetAttributes
  pop af
  pop de

  push af
  call addAToHL
  ld a, [hl]
  and a, %11000000 ; we just want the palette
  ld b, a ; now b has the attributes
  pop af
  ret


ENDC