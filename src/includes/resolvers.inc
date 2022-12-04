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
;   ld a, [de]
;   inc de
;   ld [hl+], a
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


ENDC	; end definition of DMA.inc file