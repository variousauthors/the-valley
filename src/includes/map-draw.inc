IF !DEF(MAP_DRAW_INC)
MAP_DRAW_INC = 1

SECTION "SCENE_STATE", WRAM0
; store a scene address like overworld, or small world
CURRENT_MAP_HIGH_BYTE: ds 1
CURRENT_MAP_LOW_BYTE: ds 1

SECTION "MAP_DRAW_LOGIC", ROM0

; @return hl - address of current map
getCurrentMap:
  ld hl, CURRENT_MAP_HIGH_BYTE
  ld a, [hl+]
  ld l, [hl]
  ld h, a

  ret

; this method sets the pointer to the current map
; in RAM to the given bytes... so you give it de
; pointing to the high byte, it's a copy from
; pointer to pointer, not value to pointer
; @param de - address of a pointer to the map
; @return void CURRENT_MAP pointer is set to de
setCurrentMap:
  ; set the current map
  ld hl, CURRENT_MAP_HIGH_BYTE
  ld a, [de]
  ld [hl], a

  inc de
  ld hl, CURRENT_MAP_LOW_BYTE
  ld a, [de]
  inc de
  ld [hl], a

  ret

initCurrentMap:
  ld a, HIGH(Overworld)
  ld [CURRENT_MAP_HIGH_BYTE], a
  ld a, LOW(Overworld)
  ld [CURRENT_MAP_LOW_BYTE], a

  ret

getCurrentMapTileset:
  call getCurrentMap
  call getMapTileset ; hl has the tileset
  ret

MAP_METADATA_SIZE EQU 6 ; height, width, events pointer, tileset pointer

; @param hl - address of map meta data
; @return hl - address of map data
getMapData:
  ; just advancing past the meta data, no problem
  REPT MAP_METADATA_SIZE
    inc hl
  ENDR

  ret

; @param hl - address of map data
; @return hl - address of map meta data
rewindToMetaData:
  ; just decrementing down to the map root
  REPT MAP_METADATA_SIZE
    dec hl
  ENDR

  ret

; @param hl - address of map meta data
; @return hl - meta tile
getMapBlankTile:
  call getMapData
  ld a, [hl] ; now we have two tile indexes
  srl a
  srl a
  srl a
  srl a ; now we have the blank tile

  call metaTileIndexToAddressV2

  ret

; @param hl - address of map
; @return hl - address of map tileset
getMapTileset:
  ; advance to the auto events list pointer
  inc hl
  inc hl
  inc hl
  inc hl

  ; dereference the pointer
  ld a, [hl+]
  ld l, [hl]
  ld h, a

  ret

; the first auto event is the out of bounds event, by convention
; if we can get into a map from the parent, then there must be
; an exit, and that will point to the parent tile
getMapOutOfBoundsEvent:
  call getMapAutoEvents

  ret

; @param hl - address of map
; @return hl - address of map events list
getMapAutoEvents:
  ; advance to the auto events list pointer
  inc hl
  inc hl

  ; dereference the pointer
  ld a, [hl+]
  ld l, [hl]
  ld h, a

  ret

; MAP_METADATA_FLAGS
; these are stored in one byte _before_ the map meta data
; for ease of access you know
NO_BOUNDS EQU %00000000
HAS_BOUNDS EQU %00000001
IS_OVERWORLD EQU %00000010 ; unused! lol, was for knowing when to double speed (that was a potential feature at some point)

; check if the map has bounds
; @param hl - map
; @return z - no bounds
hasBounds:
  dec hl
  ld a, [hl]
  inc hl
  bit 0, a

  ret

; check if the map is overworld lol
; @param hl - map
; @return nz - is overworld
isOverworld:
  dec hl
  ld a, [hl]
  inc hl
  bit 1, a

  ret

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
  call fillMetaTileSlotV2
  pop hl

  ret

; @param de - where to write
; @param hl - map to write from
; @param bc - y,x of tile to write
; de is set up for next call
fillMetaTileSlotFromMap:
  push hl

  call worldPositionToMetaTile

  call metaTileIndexToAddressV2

  call fillMetaTileSlotV2
  pop hl

  ret

; @param l - index of first tile in metatile
; @param de - address to start filling
; @post de is ready for next call
fillMetaTileSlotV2:
  call getMetaTileTopLeftV2
  call fillTileSlotV2
  call getMetaTileTopRightV2
  call fillTileSlotV2
  call getMetaTileBottomLeftV2
  call fillTileSlotV2
  call getMetaTileBottomRightV2
  call fillTileSlotV2

  ret

; @param hl - address of the meta tile ie 1, 2, 3, 4
; @param de - address to start filling
; @post de is ready for next call
fillMetaTileSlot:
  call fillTileSlot
  call getMetaTileTopRight
  call fillTileSlot
  call getMetaTileBottomLeft
  call fillTileSlot
  call getMetaTileBottomRight
  call fillTileSlot

  ; back to top left
  call getMetaTileTopLeft

  ret

; @param hl - the map we are drawing from
fillBlankColumn:
  call getDrawColumnPointer

  call getMapBlankTile

  REPT META_TILE_ROWS_PER_SCRN
    call fillMetaTileSlotV2
  ENDR

  call resetMapDrawColumnPointer

  ret

; @param hl - the map we are drawing from
fillBlankRow:
  call getDrawRowPointer

  call getMapBlankTile

  REPT META_TILES_PER_SCRN_ROW
    call fillMetaTileSlotV2
  ENDR

  call resetMapDrawRowPointer

  ret

; @param a - index of first tile in meta tile
; @param de - address of instruction
; @post de is ready for next call
fillTileSlotV2:
  inc de ; skip to the hole

  ; fill the tile data hole
  ld [de], a
  inc de

  ; now we need to skip past the 3 byte write
  inc de
  inc de
  inc de

  ret

; @param hl - address of the tile to write
; @param de - address of instruction
; @post de is ready for next call
fillTileSlot:
  inc de ; skip to the hole

  ; fill the tile data hole
  ld a, [hl]
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

  ; copy the templates
  ld hl, _MAP_DRAW_COLUMN_TEMPLATE
  ld b, _MAP_DRAW_COLUMN_TEMPLATE.end - _MAP_DRAW_COLUMN_TEMPLATE
  ld a, HIGH(MAP_DRAW_COLUMN_TEMPLATE)
  ld d, a
  ld a, LOW(MAP_DRAW_COLUMN_TEMPLATE)
  ld e, a

.loop
  ld a, b
  cp a, 0
  jr z, .done

  ld a, [hl+]
  ld [de], a
  inc de
  dec b
  jr .loop
.done

  ld hl, _MAP_DRAW_ROW_TEMPLATE
  ld b, _MAP_DRAW_ROW_TEMPLATE.end - _MAP_DRAW_ROW_TEMPLATE
  ld a, HIGH(MAP_DRAW_ROW_TEMPLATE)
  ld d, a
  ld a, LOW(MAP_DRAW_ROW_TEMPLATE)
  ld e, a

.loop2
  ld a, b
  cp a, 0
  jr z, .done2

  ld a, [hl+]
  ld [de], a
  inc de
  dec b
  jr .loop2
.done2

  ret

/** loads the map's tileset from the master 
 * draws the map around the player */
drawFreshNewMap:
  call blankVRAM

  call getCurrentMapTileset ; hl has the tileset to load

  ld b, 16 ; each tileset is 16 tiles
  ld de, MAP_TILES
  call loadTileData

  call getCurrentMap
  call drawFullScene
  call turnOnLCD

  ret

; these templates get copied to ram on init
SECTION "_MAP_DRAW_TEMPLATES", ROM0

VRAM_ADDRESS EQU 0
TILE_DATA EQU 0

; ld a, n8 ; 2 bytes, 2 cycles
; ld [n16], a ; 3 bytes, 4 cycles

_MAP_DRAW_ROW_TEMPLATE:
  ret
REPT 20 * 2 ; SCREEN_WIDTH * 2 rows
  ld a, TILE_DATA
  ld [VRAM_ADDRESS], a
ENDR
  ret
_MAP_DRAW_ROW_TEMPLATE.end

_MAP_DRAW_COLUMN_TEMPLATE:
  ret
REPT 18 * 2 ; SCREEN_HEIGHT * 2 cols
  ld a, TILE_DATA
  ld [VRAM_ADDRESS], a
ENDR
  ret
_MAP_DRAW_COLUMN_TEMPLATE.end

; could we try...
; ld [hl+], TILE_DATA ; 3 cycles, 1 byte
; we could do this as long as we store
; rows with the ld hl, INITIAL_VRAM_ADDRESS
; at the start

; these guys get filled as we go
SECTION "MAP_DRAW_TEMPLATES", WRAM0

MAP_DRAW_ROW_POINTER: ds 2
MAP_DRAW_ROW_TEMPLATE: ds _MAP_DRAW_ROW_TEMPLATE.end - _MAP_DRAW_ROW_TEMPLATE

MAP_DRAW_COLUMN_POINTER: ds 2
MAP_DRAW_COLUMN_TEMPLATE: ds _MAP_DRAW_COLUMN_TEMPLATE.end - _MAP_DRAW_COLUMN_TEMPLATE

ENDC	; end definition of map draw file