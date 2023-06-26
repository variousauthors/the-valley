IF !DEF(REDUCERS_INC)
REDUCERS_INC = 1

REDUCER_SIZE EQU 2 ; bytes per reducer
CASE_COUNT EQU 16 ; number of possible actions
CONCRETE_CASES EQU 5 ; number of actions that exist

SLACK EQU CASE_COUNT * REDUCER_SIZE - (CONCRETE_CASES * REDUCER_SIZE)

; a section for each reducer that will serve as a look-up table
; aligned to 6 bits so that we can have up to 32 actions
; and not have to check for overflow when we add
SECTION "TEMPLATE_REDUCER", ROM0, ALIGN[5]
TEMPLATE_REDUCER:
  TEMPLATE_REDUCER.NO_OP: dw
  TEMPLATE_REDUCER.PLAYER_MOVE_RIGHT: dw fillVRAMAddressesForRightColumn
  TEMPLATE_REDUCER.PLAYER_MOVE_LEFT: dw fillVRAMAddressesForLeftColumn
  TEMPLATE_REDUCER.PLAYER_MOVE_UP: dw fillVRAMAddressesForTopRow
  TEMPLATE_REDUCER.PLAYER_MOVE_DOWN: dw fillVRAMAddressesForBottomRow
  TEMPLATE_REDUCER.SLACK: ds SLACK

SECTION "MAP_DRAW_REDUCER", ROM0, ALIGN[5]
MAP_DRAW_REDUCER:
  MAP_DRAW_REDUCER.NO_OP: dw
  MAP_DRAW_REDUCER.PLAYER_MOVE_RIGHT: dw enableMapDrawColumn
  MAP_DRAW_REDUCER.PLAYER_MOVE_LEFT: dw enableMapDrawColumn
  MAP_DRAW_REDUCER.PLAYER_MOVE_UP: dw enableMapDrawRow
  MAP_DRAW_REDUCER.PLAYER_MOVE_DOWN: dw enableMapDrawRow
  MAP_DRAW_REDUCER.SLACK: ds SLACK

SECTION "PLAYER_REDUCER", ROM0, ALIGN[5]
PLAYER_REDUCER:
  PLAYER_REDUCER.NO_OP: dw
  PLAYER_REDUCER.PLAYER_MOVE_RIGHT: dw moveRight
  PLAYER_REDUCER.PLAYER_MOVE_LEFT: dw moveLeft
  PLAYER_REDUCER.PLAYER_MOVE_UP: dw moveUp
  PLAYER_REDUCER.PLAYER_MOVE_DOWN: dw moveDown
  PLAYER_REDUCER.SLACK: ds SLACK

SECTION "BUFFER_REDUCER", ROM0, ALIGN[5]
BUFFER_REDUCER:
  BUFFER_REDUCER.NO_OP: dw
  BUFFER_REDUCER.PLAYER_MOVE_RIGHT: dw fillRightColumnTileData
  BUFFER_REDUCER.PLAYER_MOVE_LEFT: dw fillLeftColumnTileData
  BUFFER_REDUCER.PLAYER_MOVE_UP: dw fillTopRowTileData
  BUFFER_REDUCER.PLAYER_MOVE_DOWN: dw fillBottomRowTileData
  BUFFER_REDUCER.SLACK: ds SLACK

SECTION "REDUCER_ROM", ROM0

; @param hl - action
; @param de - reducer
reduce:
  push hl
  ld a, [hl+] ; action code
  sla a ; double it because each case in the reducer is two bytes

  ; move de to point to the case reducer
  or a, e
  ld e, a
  
  ; get the address to call which is stored LOW, HIGH
  ld a, [de]
  ld c, a ; low
  inc de
  ld a, [de]
  ld b, a ; high

  ; if bc is a no-op, return
  ld a, 0
  or b
  or c
  or a
  ret z

  ; now bc has address to write
  call prepareAction

  pop hl
  ret
  
; @param - hl the address of some subroutie to call
indirectCall:
  jp hl


ENDC	; end definition of resolvers file
