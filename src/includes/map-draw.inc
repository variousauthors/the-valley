IF !DEF(MAP_DRAW_INC)
MAP_DRAW_INC = 1

SECTION "MAP_DRAW_LOGIC", ROM0

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

fillVRAMAddressesForBottomRow:
  call getBottomLeftScreenPosition

  ; if y is 31, set it to zero
  ld a, b
  xor a, $1F
  jr nz, .noWrap
  ld b, 0
  jr .done
.noWrap
  inc b ; advance y to get the row to draw
.done

  call scrnPositionToVRAMAddress
  call fillVRAMAddressesForRow

  ret

fillVRAMAddressesForTopRow:
  call getTopLeftScreenPosition

  ; if b is 0 flip a bit
  ld a, b
  cp 0
  jr nz, .noWrap
  set 5, a ; add 32
  ld b, a
.noWrap
  ; otherwise dec b to get the row to draw

  dec b
  dec b

  call scrnPositionToVRAMAddress
  call fillVRAMAddressesForRow

  ret

fillVRAMAddressesForLeftColumn:
  call getTopLeftScreenPosition

  ; if c is 0 flip a bit
  ld a, c
  cp 0
  jr nz, .noWrap
  set 5, a ; add 32
  ld c, a
.noWrap
  ; otherwise dec c

  dec c
  dec c

  call scrnPositionToVRAMAddress
  call fillVRAMAddressesForColumn

  ret

fillVRAMAddressesForRightColumn:
  call getTopRightScreenPosition

  ; if c is 31 set it to zero 
  ld a, c
  xor a, $1F
  jr nz, .noWrap
  ld c, 0
  jr .done
.noWrap
  inc c ; advance x
.done

  call scrnPositionToVRAMAddress
  call fillVRAMAddressesForColumn

  ret

; fills the column template with VRAM addresses
; such that meta tiles can be written linearly
; a b c d a b c d ...
fillVRAMAddressesForColumn:
  ; get instruction pointer in de
  ld a, [MAP_DRAW_ROW_POINTER]
  ld d, a
  ld a, [MAP_DRAW_ROW_POINTER + 1]
  ld e, a

  ld bc, VRAM_WIDTH - 1

  ; hl has the first address
  ; de has the template pointer
  REPT META_TILES_PER_SCRN_ROW
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
  ; get instruction pointer in de
  ld a, [MAP_DRAW_ROW_POINTER]
  ld d, a
  ld a, [MAP_DRAW_ROW_POINTER + 1]
  ld e, a

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

; these templates get copied to ram on init
SECTION "_MAP_DRAW_TEMPLATES", ROM0

VRAM_ADDRESS EQU 0
TILE_DATA EQU 0

; ld a, n8 ; 2 bytes
; ld [n16], a ; 3 bytes

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

; these guys get filled as we go
SECTION "MAP_DRAW_TEMPLATES", WRAM0

MAP_DRAW_ROW_POINTER: ds 2
MAP_DRAW_ROW_TEMPLATE: ds _MAP_DRAW_ROW_TEMPLATE.end - _MAP_DRAW_ROW_TEMPLATE

MAP_DRAW_COLUMN_POINTER: ds 2
MAP_DRAW_COLUMN_TEMPLATE: ds _MAP_DRAW_COLUMN_TEMPLATE.end - _MAP_DRAW_COLUMN_TEMPLATE

ENDC	; end definition of map draw file