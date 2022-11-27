IF !DEF(RESOLVERS_INC)
RESOLVERS_INC = 1

updateVRAM:
  ; iterate down the list until we hit 0
  ; switch on each instruction and call a subroutine
  ld hl, ACTION_QUEUE

  ; loop until the instruction is NO_OP
.loop
  ld a, [hl]
  cp a, NO_OP
  jp z, .done

  push hl

  ; perform the instruction
  cp a, PLAYER_MOVE_LEFT
  jr nz, .next1
  ld hl, drawLeftColumn

.next1
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .next2
  ld hl, drawRightColumn

.next2
  cp a, PLAYER_MOVE_UP
  jr nz, .next3
  ld hl, drawTopRow

.next3
  cp a, PLAYER_MOVE_DOWN
  jr nz, .next4
  ld hl, drawBottomRow

.next4

  call indirectCall

  pop hl

  inc hl
  jr .loop
  
.done

  ret

updateScrolling:
  ; iterate down the list until we hit 0
  ; switch on each instruction and call a subroutine
  ld hl, ACTION_QUEUE

  ; loop until the instruction is NO_OP
.loop
  ld a, [hl]
  cp a, NO_OP
  jp z, .done

  push hl

    ; perform the instruction
    cp a, PLAYER_MOVE_LEFT
    jr nz, .next1
    ld hl, scrollLeft
  
  .next1
    cp a, PLAYER_MOVE_RIGHT
    jr nz, .next2
    ld hl, scrollRight
  
  .next2
    cp a, PLAYER_MOVE_UP
    jr nz, .next3
    ld hl, scrollUp
  
  .next3
    cp a, PLAYER_MOVE_DOWN
    jr nz, .next4
    ld hl, scrollDown
  
  .next4
  
    call indirectCall

  pop hl

  inc hl
  jr .loop
  
.done

  ret

updatePlayer:
  ; iterate down the list until we hit 0
  ; switch on each instruction and call a subroutine
  ld hl, ACTION_QUEUE

  ; loop until the instruction is NO_OP
.loop
  ld a, [hl]
  cp a, NO_OP
  jp z, .done

  push hl

  ; perform the instruction
  cp a, PLAYER_MOVE_LEFT
  jr nz, .next1
  ld hl, moveLeft

.next1
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .next2
  ld hl, moveRight

.next2
  cp a, PLAYER_MOVE_UP
  jr nz, .next3
  ld hl, moveUp

.next3
  cp a, PLAYER_MOVE_DOWN
  jr nz, .next4
  ld hl, moveDown

.next4

  call indirectCall

  pop hl

  inc hl
  jr .loop
  
.done

  ret

; @param - hl the address of some subroutie to call
indirectCall:
  jp hl


ENDC	; end definition of DMA.inc file