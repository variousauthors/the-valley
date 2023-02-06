IF !DEF(REDUCERS_INC)
REDUCERS_INC = 1

; a section for each reducer that will serve as a look-up table
; aligned to 6 bits so that we can have up to 32 actions
; and not have to check for overflow when we add
SECTION "TEMPLATE_REDUCER", ROM0, ALIGN[5]
TEMPLATE_REDUCER:
  TEMPLATE_REDUCER.NO_OP: db 0, 0
  TEMPLATE_REDUCER.PLAYER_MOVE_RIGHT: db HIGH(fillVRAMAddressesForRightColumn), LOW(fillVRAMAddressesForRightColumn)
  TEMPLATE_REDUCER.PLAYER_MOVE_LEFT: db HIGH(fillVRAMAddressesForLeftColumn), LOW(fillVRAMAddressesForLeftColumn)
  TEMPLATE_REDUCER.PLAYER_MOVE_UP: db HIGH(fillVRAMAddressesForTopRow), LOW(fillVRAMAddressesForTopRow)
  TEMPLATE_REDUCER.PLAYER_MOVE_DOWN: db HIGH(fillVRAMAddressesForBottomRow), LOW(fillVRAMAddressesForBottomRow)
  TEMPLATE_REDUCER.SLACK: db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

SECTION "REDUCER_ROM", ROM0

; @param hl - action
; @param de - reducer
reduce:
  push hl
  ld a, [hl+] ; action code
  sla a

  or a, e
  ld e, a
  
  ld a, [de]
  ld b, a
  inc de
  ld a, [de]
  ld c, a

  ; now bc has address to write

  call prepareAction

  pop hl
  ret; @param - hl the address of some subroutie to call

indirectCall:
  jp hl

SECTION "MAP_DRAW_REDUCER", ROM0, ALIGN[5]
MAP_DRAW_REDUCER:
  MAP_DRAW_REDUCER.NO_OP: db 0, 0
  MAP_DRAW_REDUCER.PLAYER_MOVE_RIGHT: db HIGH(enableMapDrawColumn), LOW(enableMapDrawColumn)
  MAP_DRAW_REDUCER.PLAYER_MOVE_LEFT: db HIGH(enableMapDrawColumn), LOW(enableMapDrawColumn)
  MAP_DRAW_REDUCER.PLAYER_MOVE_UP: db HIGH(enableMapDrawRow), LOW(enableMapDrawRow)
  MAP_DRAW_REDUCER.PLAYER_MOVE_DOWN: db HIGH(enableMapDrawRow), LOW(enableMapDrawRow)
  MAP_DRAW_REDUCER.SLACK: db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

SECTION "SCROLLING_REDUCER", ROM0, ALIGN[5]
SCROLLING_REDUCER:
  SCROLLING_REDUCER.NO_OP: db 0, 0
  SCROLLING_REDUCER.PLAYER_MOVE_RIGHT: db HIGH(scrollRight), LOW(scrollRight)
  SCROLLING_REDUCER.PLAYER_MOVE_LEFT: db HIGH(scrollLeft), LOW(scrollLeft)
  SCROLLING_REDUCER.PLAYER_MOVE_UP: db HIGH(scrollUp), LOW(scrollUp)
  SCROLLING_REDUCER.PLAYER_MOVE_DOWN: db HIGH(scrollDown), LOW(scrollDown)
  SCROLLING_REDUCER.SLACK: db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

SECTION "PLAYER_REDUCER", ROM0, ALIGN[5]
PLAYER_REDUCER:
  PLAYER_REDUCER.NO_OP: db 0, 0
  PLAYER_REDUCER.PLAYER_MOVE_RIGHT: db HIGH(moveRight), LOW(moveRight)
  PLAYER_REDUCER.PLAYER_MOVE_LEFT: db HIGH(moveLeft), LOW(moveLeft)
  PLAYER_REDUCER.PLAYER_MOVE_UP: db HIGH(moveUp), LOW(moveUp)
  PLAYER_REDUCER.PLAYER_MOVE_DOWN: db HIGH(moveDown), LOW(moveDown)
  PLAYER_REDUCER.SLACK: db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

SECTION "BUFFER_REDUCER", ROM0, ALIGN[5]
BUFFER_REDUCER:
  BUFFER_REDUCER.NO_OP: db 0, 0
  BUFFER_REDUCER.PLAYER_MOVE_RIGHT: db HIGH(fillRightColumnTileData), LOW(fillRightColumnTileData)
  BUFFER_REDUCER.PLAYER_MOVE_LEFT: db HIGH(fillLeftColumnTileData), LOW(fillLeftColumnTileData)
  BUFFER_REDUCER.PLAYER_MOVE_UP: db HIGH(fillTopRowTileData), LOW(fillTopRowTileData)
  BUFFER_REDUCER.PLAYER_MOVE_DOWN: db HIGH(fillBottomRowTileData), LOW(fillBottomRowTileData)
  BUFFER_REDUCER.SLACK: db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

ENDC	; end definition of resolvers file
