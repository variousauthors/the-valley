IF !DEF(MAP_DRAW_INC)
MAP_DRAW_INC = 1

SECTION "MAP_DRAW_LOGIC", ROM0

; @param bc - y, x in screen space (0 - 255)
; @result hl - address in VRAM of that position
scrnPositionToVRAMAddress:
  ld hl, _SCRN0

  ; _SCRN0
  ; 1001 1000 0000 0000
  ; vvvt twyy yyyx xxxx

  ; set the high part of y
  ld a, b ; 000yyyyy
  srl a
  srl a
  srl a ; get just the high part 000000yy

  or a, h
  ld h, a

  ; 1001 10yy 0000 0000
  ; vvvt twyy yyyx xxxx

  ; set the low part of y
  ld a, b
  and $07 ; 00000111
  rrca
  rrca
  rrca
  or a, l
  ld l, a

  ; 1001 10yy yyy0 0000
  ; vvvt twyy yyyx xxxx

  ; set x
  ld a, c
  and $1F ; 00011111
  or a, l
  ld l, a

  ret


; @return bc - y, x of the top left tile of VRAM
getTopRightScreenPosition:
  ld a, [CAMERA_INITIAL_WORLD_Y]
  ld d, a
  ld a, [CAMERA_WORLD_Y]
  sub a, d ; y - initial_y

  sla a ; meta tile to tile
  ld b, a

  ld a, [CAMERA_INITIAL_WORLD_X]
  ld d, a
  ld a, [CAMERA_WORLD_X]
  sub a, d ; x - initial_x

  sla a ; meta tile to tile
  add a, SCRN_WIDTH - 1

  ld c, a

  ret


; @return bc - y, x of the top left tile of VRAM
getTopLeftScreenPosition:
  ld a, [CAMERA_INITIAL_WORLD_Y]
  ld d, a
  ld a, [CAMERA_WORLD_Y]
  sub a, d ; y - initial_y

  sla a ; meta tile to tile
  ld b, a

  ld a, [CAMERA_INITIAL_WORLD_X]
  ld d, a
  ld a, [CAMERA_WORLD_X]
  sub a, d ; x - initial_x

  sla a ; meta tile to tile

  ld c, a

  ret

; @return bc - y, x of the bottom left tile of VRAM
getBottomLeftScreenPosition:
  ld a, [CAMERA_INITIAL_WORLD_Y]
  ld d, a
  ld a, [CAMERA_WORLD_Y]
  sub a, d ; y - initial_y

  sla a ; meta tile to tile
  add SCRN_HEIGHT - 1
  ld b, a

  ld a, [CAMERA_INITIAL_WORLD_X]
  ld d, a
  ld a, [CAMERA_WORLD_X]
  sub a, d ; x - initial_x

  sla a ; meta tile to tile

  ld c, a

  ret

; sets the initial instructions to ret
disabledMapDraw:
  ld hl, MAP_DRAW_COLUMN_TEMPLATE
  ld [hl], RET_OP

  ld hl, MAP_DRAW_ROW_TEMPLATE
  ld [hl], RET_OP
  ret

; sets the initial instructions to nop
enableMapDrawRow:
  ld hl, MAP_DRAW_ROW_TEMPLATE
  ld [hl], NO_OP_OP
  ret

; sets the initial instructions to nop
enableMapDrawColumn:
  ld hl, MAP_DRAW_COLUMN_TEMPLATE
  ld [hl], NO_OP_OP
  ret

mapDraw:
  call MAP_DRAW_COLUMN_TEMPLATE
  call MAP_DRAW_ROW_TEMPLATE

  call disabledMapDraw

  ret

; request a column to the right of the camera
fillRightColumnTileData:
  call getCurrentMap

  ; subtract from camera y, x to get top right corner
  ld a, [CAMERA_WORLD_X]
  inc a ; going right
  add a, META_TILES_PER_SCRN_ROW - 1
  ld c, a

  ; if x is > map width, draw a blank row
  inc hl ; get to map width
  ld a, [hl]
  dec a ; map width - 1
  dec hl ; back to map
  cp a, c ; stop if map width - 1 < x
  jr c, .writeBlank

  ; safe to write a row
  call fillMapColumn
  ret

.writeBlank
  call fillBlankColumn

  ret

; request a column to the left of the camera
fillLeftColumnTileData:
  call getCurrentMap

  ; subtract from camera y, x to get top left corner
  ld a, [CAMERA_WORLD_X]
  dec a ; going left
  sub a, 0
  ld c, a

  ; if x is negative, draw a blank row
  cp a, $80
  jr nc, .writeBlank

  ; safe to write a row
  call fillMapColumn
  ret

.writeBlank
  call fillBlankColumn

  ret

; request a row bellow the camera
fillBottomRowTileData:
  call getCurrentMap

  ; subtract from camera y, x to get top left corner
  ld a, [CAMERA_WORLD_Y]
  inc a ; going down
  add a, META_TILE_ROWS_PER_SCRN - 1
  ld b, a

  ; y can't be < 0 since we are moving down

  ; if y > map height, draw a blank row

  ; load map height from map
  ld a, [hl]
  dec a ; map height - 1

  ; stop if map height - 1 < y
  cp b
  jr c, .writeBlank

  ; safe to write a row
  call fillMapRow
  ret

.writeBlank
  call fillBlankRow
  ret

; request a row above the camera
fillTopRowTileData:
  call getCurrentMap

  ; subtract from camera y to get map y to draw
  ld a, [CAMERA_WORLD_Y]
  dec a ; going up
  sub a, 0
  ld b, a

  ; if y is negative, draw a blank row
  cp a, $80
  jr nc, .writeBlank

  ; y can't be greater than map height since we are moving up

  ; safe to write a row
  call fillMapRow
  ret
.writeBlank
  call fillBlankRow
  ret

fillMapColumn:
  call getDrawColumnPointer

  ; get the y to start from
  ld a, [CAMERA_WORLD_Y]
  sub a, 0
  ld b, a ; now bc has y, x to start from

  REPT META_TILE_ROWS_PER_SCRN
    ld a, b
    cp a, $00 ; c is set if a < 0, ie if y is negative
    jr c, .writeBlank\@

    ld a, [hl] ; get map height
    dec a ; get height - 1
    cp a, b ; (height - 1) < c, ie y is higher than the last map position
    jr c, .writeBlank\@

    ; otherwise we write a tile from the map
    call fillMetaTileSlotFromMap

    jr .done\@
  .writeBlank\@
    call fillBlankMetaTileSlotFromMap

  .done\@
    inc b
  ENDR

  call resetMapDrawColumnPointer

  ret

; @param hl - the map
; @param b - y to fill from
fillMapRow:
  call getDrawRowPointer

  ; get the x to start from
  ld a, [CAMERA_WORLD_X]
  sub a, 0
  ld c, a ; now bc has y, x to start from

  REPT META_TILES_PER_SCRN_ROW
    ld a, c
    cp a, $00 ; c is set if a < 0, ie if x is negative
    jr c, .writeBlank\@

    inc hl
    ld a, [hl] ; get map width
    dec a ; get width - 1
    dec hl
    cp a, c ; (width - 1) < c, ie x is higher than the last map position
    jr c, .writeBlank\@

    ; otherwise we write a tile from the map
    call fillMetaTileSlotFromMap

    jr .done\@
  .writeBlank\@
    call fillBlankMetaTileSlotFromMap

  .done\@
    inc c
  ENDR

  call resetMapDrawRowPointer

  ret

fillBlankMetaTileSlotFromMap:
  push hl

  call getMapBlankTile
  call fillMetaTileSlot
  pop hl

  ret

; @param de - where to write
; @param hl - map to write from
; @param bc - y,x of tile to write
; de is set up for next call
fillMetaTileSlotFromMap:
  push hl

  call worldPositionToMetaTile

  call metaTileIndexToAddress

  call fillMetaTileSlot
  pop hl

  ret

; @param l - index of first tile in metatile
; @param de - address to start filling
; @post de is ready for next call
fillMetaTileSlot:
  call getMetaTileTopLeft
  call fillTileSlot
  call getMetaTileTopRight
  call fillTileSlot
  call getMetaTileBottomLeft
  call fillTileSlot
  call getMetaTileBottomRight
  call fillTileSlot

  ret

; @param hl - the map we are drawing from
fillBlankColumn:
  call getDrawColumnPointer

  call getMapBlankTile

  REPT META_TILE_ROWS_PER_SCRN
    call fillMetaTileSlot
  ENDR

  call resetMapDrawColumnPointer

  ret

; @param hl - the map we are drawing from
fillBlankRow:
  call getDrawRowPointer

  call getMapBlankTile

  REPT META_TILES_PER_SCRN_ROW
    call fillMetaTileSlot
  ENDR

  call resetMapDrawRowPointer

  ret


/*
@param a - tile data to write
@param hl - address to write
@param de - address of instruction
@post de is ready for next call
*/
fillTileAndVRAMAddressSlots:
  inc de ; skip to the hole in ld a, n8

  ; fill the tile data hole
  ld [de], a
  inc de ; move past the hole
  inc de ; move to the next hole

  ; fill the VRAM address hole
  ld a, l
  ld [de], a
  inc de
  ld a, h
  ld [de], a
  inc de

  ret

; @param a - tile data to write
; @param de - address of instruction
; @post de is ready for next call
fillTileSlot:
  inc de ; skip to the hole

  ; fill the tile data hole
  ld [de], a
  inc de

  ; now we need to skip past the 3 byte write
  inc de
  inc de
  inc de

  ret

; @param bc - y, x
; @return bc - y mod 32, x mod 32
posMod32:
  ld a, b
  and a, $1F
  ld b, a

  ld a, c
  and a, $1F
  ld c, a

  ret

fillVRAMAddressesForBottomRow:
  call getBottomLeftScreenPosition
  inc b
  call posMod32

  call scrnPositionToVRAMAddress
  call fillVRAMAddressesForRow

  ret

fillVRAMAddressesForTopRow:
  call getTopLeftScreenPosition
  dec b
  dec b
  call posMod32

  call scrnPositionToVRAMAddress
  call fillVRAMAddressesForRow

  ret

fillVRAMAddressesForLeftColumn:
  call getTopLeftScreenPosition
  dec c
  dec c
  call posMod32

  call scrnPositionToVRAMAddress
  call fillVRAMAddressesForColumn

  ret

fillVRAMAddressesForRightColumn:
  call getTopRightScreenPosition
  inc c
  call posMod32

  call scrnPositionToVRAMAddress
  call fillVRAMAddressesForColumn

  ret

; fills the column template with VRAM addresses
; such that meta tiles can be written linearly
; a b c d a b c d ...
; that is, it writes in a zig-zag down the screen
; @param hl - address in VRAM of position to start
fillVRAMAddressesForColumn:
  call getDrawColumnPointer

  ld bc, VRAM_WIDTH - 1

  ; hl has the first address
  ; de has the template pointer
  REPT META_TILE_ROWS_PER_SCRN
    call fillVRAMAddressSlot
    inc hl
    call fillVRAMAddressSlot
    add hl, bc
    call fillVRAMAddressSlot
    inc hl
    call fillVRAMAddressSlot
    add hl, bc

    ; now we have to check for vertical wrap
    ; _SCRN0
    ; 1001 1000 0000 0000
    ; vvvt twyy yyyx xxxx

    ; check if y is 0
    ; if so, it may have flipped so unset w

    ; check the low part first, it changes more
    ld a, l
    and a, $E0 ; select the low part of y
    jr nz, .noSkip\@ ; if it is not 000 we have nothing to do

    ld a, h
    and a, $03 ; select the high part of y
    jr nz, .noSkip\@ ; if it is zero we must skip around

    ; y is 00000 so set w to 0
    res 2, h
  .noSkip\@
  ENDR

  call resetMapDrawColumnPointer

  ret

; fills the row template with VRAM addresses
; such that meta tiles can be written linearly
; a b c d a b c d ...
fillVRAMAddressesForRow:
  call getDrawRowPointer

  ld bc, VRAM_WIDTH - 1
  ; hl has the first address
  ; de has the template pointer
  REPT META_TILES_PER_SCRN_ROW
    call fillVRAMAddressSlot
    inc hl
    push hl
    call fillVRAMAddressSlot
    add hl, bc
    call fillVRAMAddressSlot
    inc hl
    call fillVRAMAddressSlot
    pop hl
    inc hl

    ; now we have to check for wrap
    ; _SCRN0
    ; 1001 1000 0000 0000
    ; vvvt twyy yyyx xxxx

    ; check if x is zero
    ; and if so, decrement y (ie subtract 32) 

    ld a, l
    and a, $1F ; 00011111

    jr nz, .noSkip\@

    dec hl
    ld a, l
    ; reset x to zero
    and $E0 ; 11100000
    ld l, a
  .noSkip\@
  ENDR

  call resetMapDrawRowPointer

  ret

; @param hl - address to write
; @param de - address of instruction
; @post de is ready for next call
fillVRAMAddressSlot:
  ; skip past the load (ld a, n8) is 2 bytes
  inc de
  inc de

  inc de ; skip to the hole

  ; fill the VRAM address hole
  ld a, l
  ld [de], a
  inc de
  ld a, h
  ld [de], a
  inc de

  ret

; unusual for pointers we actually want to point
; to the second address, since the first is the nop/ret
resetMapDrawColumnPointer:
  ld a, high(MAP_DRAW_COLUMN_TEMPLATE + 1)
  ld h, a
  ld [MAP_DRAW_COLUMN_POINTER], a
  ld a, low(MAP_DRAW_COLUMN_TEMPLATE + 1)
  ld l, a
  ld [MAP_DRAW_COLUMN_POINTER + 1], a
  ret
  
; unusual for pointers we actually want to point
; to the second address, since the first is the nop/ret
resetMapDrawRowPointer:
  ld a, high(MAP_DRAW_ROW_TEMPLATE + 1)
  ld h, a
  ld [MAP_DRAW_ROW_POINTER], a
  ld a, low(MAP_DRAW_ROW_TEMPLATE + 1)
  ld l, a
  ld [MAP_DRAW_ROW_POINTER + 1], a
  ret

; @return de the column pointer
getDrawColumnPointer:
  ld a, [MAP_DRAW_COLUMN_POINTER]
  ld d, a
  ld a, [MAP_DRAW_COLUMN_POINTER + 1]
  ld e, a

  ret

; @return de the row pointer
getDrawRowPointer:
  ld a, [MAP_DRAW_ROW_POINTER]
  ld d, a
  ld a, [MAP_DRAW_ROW_POINTER + 1]
  ld e, a

  ret

initMapDrawTemplates:
  call resetMapDrawColumnPointer
  call resetMapDrawRowPointer

  ; create the row template
  ld hl, MAP_DRAW_ROW_TEMPLATE
  ld b, SCRN_WIDTH * 2
  call makeVRAMTemplate

  ; create the column template
  ld hl, MAP_DRAW_COLUMN_TEMPLATE
  ld b, SCRN_HEIGHT * 2
  call makeVRAMTemplate

  ret

/** loads the map's tileset from the master 
 * draws the map around the player */
drawFreshNewMap:
  ; record that initial world x, y
  ; so that we can later use it to
  ; set the screen to the camera position
  ld a, [CAMERA_WORLD_X]
  ld [CAMERA_INITIAL_WORLD_X], a
  ld a, [CAMERA_WORLD_Y]
  ld [CAMERA_INITIAL_WORLD_Y], a

  ; reset scroll
  ld a, 0
  ld [rSCX], a
  ld [rSCY], a

  call blankVRAM

  call getCurrentMapTileset ; hl has the tileset to load

  ld b, 16 ; each tileset is 16 tiles
  ld de, MAP_TILES
  call loadTileData

  call getCurrentMap
  call drawFullScene

  ret

drawFullScene:
  call writeMapToBuffer

  call drawBuffer
  ; GBC ONLY FEATURE, SKIP ON GB
  ; call drawGBCAttributes
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

; @param a - meta tile index
; @param hl - meta tile to write
; @param de - write to address
writeRowMapTileToBuffer:
  push bc
  push hl
  push de

  /** interesting! this is GBC only code 
   * but if I remove it the game breaks */
  call packGBCPaletteIndex

  ; now we have index in a, attributes in b

  call metaTileIndexToAddress
  call getMetaTileTopLeft
  or b ; add in the GBCPalette
  ld [de], a
  inc de

  call getMetaTileTopRight
  or b ; add in the GBCPalette
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
  or b ; add in the GBCPalette
  ld [de], a
  inc de

  call getMetaTileBottomRight
  or b ; add in the GBCPalette
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
  ld [de], a
  inc de

  call getMetaTileTopRight
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
  ld [de], a
  inc de

  call getMetaTileBottomRight
  ld [de], a

  pop de
  pop hl
  pop bc

  inc de
  inc de ; we wrote 2 tiles

  ret

drawBuffer:
  ld hl, MAP_BUFFER
  ld de, _SCRN0
  ld b, SCRN_HEIGHT

  ; select GBC bank 0
  ld a, 0
  ld [rVBK], a

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

  ; ignore the attributes
  ; @see drawGBCAttributes to understand why
  and a, %00111111

  ld [de], a
  inc hl
  inc de
  dec c
  jr nz, .loop
.done
  ret


; these guys get filled as we go
SECTION "MAP_DRAW_TEMPLATES", WRAM0

MAP_DRAW_ROW_POINTER: ds 2
MAP_DRAW_ROW_TEMPLATE: ds START_TEMPLATE + (TEMPLATE_SLOT * SCRN_WIDTH * 2) + END_TEMPLATE

MAP_DRAW_COLUMN_POINTER: ds 2
MAP_DRAW_COLUMN_TEMPLATE: ds START_TEMPLATE + (TEMPLATE_SLOT * SCRN_HEIGHT * 2) + END_TEMPLATE

ENDC	; end definition of map draw file