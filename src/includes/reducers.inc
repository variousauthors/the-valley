IF !DEF(REDUCERS_INC)
REDUCERS_INC = 1

SECTION "REDUCER_ROM", ROM0

; @param hl - action
templateReducer:
  push hl
  ld a, [hl+] ; code

  ld bc, 0 ; assume no op

  cp a, PLAYER_MOVE_LEFT
  jr nz, .next1
  ld bc, fillVRAMAddressesForLeftColumn

.next1
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .next2
  ld bc, fillVRAMAddressesForRightColumn

.next2
  cp a, PLAYER_MOVE_UP
  jr nz, .next3
  ld bc, fillVRAMAddressesForTopRow

.next3
  cp a, PLAYER_MOVE_DOWN
  jr nz, .next4
  ld bc, fillVRAMAddressesForBottomRow

.next4

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
