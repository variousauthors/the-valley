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
  REST: db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

SECTION "REDUCER_ROM", ROM0

; @param hl - action
templateReducer:
  push hl
  ld a, [hl+] ; action code
  sla a

  ld de, TEMPLATE_REDUCER
  ld e, a
  
  ld a, [de]
  ld b, a
  inc de
  ld a, [de]
  ld c, a

  ; now bc has call address

  call prepareAction

  pop hl
  ret

; @param hl - action
mapDrawReducer:
  push hl
  ld a, [hl+] ; code

  ld bc, 0 ; assume no op

  cp a, PLAYER_MOVE_LEFT
  jr nz, .next1
  ld bc, enableMapDrawColumn

.next1
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .next2
  ld bc, enableMapDrawColumn

.next2
  cp a, PLAYER_MOVE_UP
  jr nz, .next3
  ld bc, enableMapDrawRow

.next3
  cp a, PLAYER_MOVE_DOWN
  jr nz, .next4
  ld bc, enableMapDrawRow

.next4

  call prepareAction

  pop hl
  ret

; @param hl - action
scrollingReducer:
  push hl
  ld a, [hl+] ; code

  ld bc, 0 ; assume no op

  cp a, PLAYER_MOVE_LEFT
  jr nz, .next1
  ld bc, scrollLeft

.next1
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .next2
  ld bc, scrollRight

.next2
  cp a, PLAYER_MOVE_UP
  jr nz, .next3
  ld bc, scrollUp

.next3
  cp a, PLAYER_MOVE_DOWN
  jr nz, .next4
  ld bc, scrollDown

.next4

  call prepareAction

  pop hl
  ret

; @param hl - action
playerReducer:
  push hl
  ld a, [hl+] ; code

  ld bc, 0 ; assume no op

  cp a, PLAYER_MOVE_LEFT
  jr nz, .next1
  ld bc, moveLeft

.next1
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .next2
  ld bc, moveRight

.next2
  cp a, PLAYER_MOVE_UP
  jr nz, .next3
  ld bc, moveUp

.next3
  cp a, PLAYER_MOVE_DOWN
  jr nz, .next4
  ld bc, moveDown

.next4

  call prepareAction

  pop hl
  ret

; @param hl - action
bufferReducer:
  push hl
  ld a, [hl+] ; code

  ld bc, 0 ; assume no op

  cp a, PLAYER_MOVE_LEFT
  jr nz, .next1
  ld bc, fillLeftColumnTileData

.next1
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .next2
  ld bc, fillRightColumnTileData

.next2
  cp a, PLAYER_MOVE_UP
  jr nz, .next3
  ld bc, fillTopRowTileData

.next3
  cp a, PLAYER_MOVE_DOWN
  jr nz, .next4
  ld bc, fillBottomRowTileData

.next4

  call prepareAction

  pop hl
  ret

; @param - hl the address of some subroutie to call
indirectCall:
  jp hl


ENDC	; end definition of resolvers file
