IF !DEF(RESOLVERS_INC)
RESOLVERS_INC = 1

; @TODO so I had this thought...
; I've moved a lot of the thinking out of VRAM by buffering
; and deciding what to draw out of VRAM, and then just drawing
; in VRAM but actually _most_ of the `drawTopRow` subroutine
; is figuring out where in VRAM to draw
; 
; so we could figure that out ahead and write it somewhere, and then
; just read it in `drawTopRow`
;
; OR, wilder idea: in the "figure out what to do" step we do literally
; everything except the drawRow, which is this:
;
; drawRow:
; REPT SCRN_WIDTH
;   ld a, [TILE_ADDRESS]
;   ld [VRAM_ADDRESS], a
; ENDR
;
; ret
;
; this routine is 60 bytes, so we'd have to copy that
;
; and then we append that code (those bytes) to some address
; which we later jump to... so that VRAM is just "jp to dynamic draw code; brrrrr"
; 
; I thought also, we can dynamically hard code the de/hl args
; 
; I go to thinking this because otherwise, if I don't do something
; like this, then I really should code a wait for VRAM into the drawTopRow
; because there's no guarantee that I finish the work before VRAM is done
; where as if literally all I'm doing in vblank is copying tiles... then
; if I can't get it done in time it means I was just copying too many tiles
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

updateBuffer:
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
  ld hl, writeLeftColumnToBuffer

.next1
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .next2
  ld hl, writeRightColumnToBuffer

.next2
  cp a, PLAYER_MOVE_UP
  jr nz, .next3
  ld hl, writeTopRowToBuffer

.next3
  cp a, PLAYER_MOVE_DOWN
  jr nz, .next4
  ld hl, writeBottomRowToBuffer

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

SECTION "ACTION_RAM", WRAM0

NO_OP EQU 0
PLAYER_MOVE_RIGHT EQU 1
PLAYER_MOVE_LEFT EQU 2
PLAYER_MOVE_UP EQU 3
PLAYER_MOVE_DOWN EQU 4

; the list of actions to process
; CODE, HIGH, LOW
ACTIONS_PER_FRAME EQU 4
ACTION EQU 3
ACTION_LIST: ds ACTION * ACTIONS_PER_FRAME
ACTION_LIST_POINTER: ds 2

ACTION_DISPATCHER_SIZE EQU 8
; one dispatcher is like ~ 8 bytes
; ld b, CONST ; 2 bytes
; ld c, CONST ; 2 bytes
; call __ ; 3 bytes
; ret ; 1 byte
ACTION_DISPATCHERS: ds ACTION_DISPATCHER_SIZE * ACTIONS_PER_FRAME
ACTION_DISPATCHERS_POINTER: ds 2

SECTION "ACTION_ROM", ROM0

CALL_OP EQU $CD
RET_OP EQU $C9

; dispatch an action with zero params
; @params b - CODE
dispatchAction0:
  ld a, [ACTION_DISPATCHERS_POINTER]
  ld h, a
  ld a, [ACTION_DISPATCHERS_POINTER + 1]
  ld l, a
  ; hl has the next action dispatcher

  ld a, CALL_OP
  ld [hl+], a
  ld a, 0
  ld [hl+], a
  ld [hl+], a

  ld a, RET_OP
  ld [hl+], a

  ; recover the address we just wrote to
  ; (this seems faster than a push/pop)
  ld a, [ACTION_DISPATCHERS_POINTER]
  ld d, a
  ld a, [ACTION_DISPATCHERS_POINTER + 1]
  ld e, a

  ; update the pointer to the next dispatcher
  ld a, h
  ld [ACTION_DISPATCHERS_POINTER], a
  ld a, l
  ld [ACTION_DISPATCHERS_POINTER + 1], a

  ; get the action list in hl
  ld a, [ACTION_LIST_POINTER]
  ld h, a
  ld a, [ACTION_LIST_POINTER + 1]
  ld l, a

  ; record the CODE
  ld a, b
  ld [hl+], a

  ; record the address to jump to as HIGH LOW
  ld a, d
  ld [hl+], a
  ld a, e
  ld [hl+], a

  ; move the pointer
  ld a, h
  ld [ACTION_LIST_POINTER], a
  ld a, l
  ld [ACTION_LIST_POINTER + 1], a

  ret

ENDC	; end definition of resolvers file