IF !DEF(FLUX_INC)
FLUX_INC = 1

SECTION "FLUX_ROM", ROM0

runReducers:
  ld hl, ACTION_LIST

.loop
  ld a, [hl] ; get an action
  cp a, NO_OP ; if it is zero we are done
  jr z, .done
  ; each action is a fixed size so we can iterate over them easily

  call playerReducer
  call templateReducer
  call mapDrawReducer
  call scrollingReducer
  call bufferReducer

  ; advance to next action
  ld bc, ACTION_SIZE
  add hl, bc

  jr .loop
.done

  ; reset the action list pointer
  call resetActionListWritePointer

  ret

runFluxSMC:
  call FLUX_SMC_ZONE
  call resetFluxSMC
  ret

resetActionListReadPointer:
  ; point the action list pointer to the beginning
  ld a, high(ACTION_LIST)
  ld h, a
  ld [ACTION_LIST_READ_POINTER], a
  ld a, low(ACTION_LIST)
  ld l, a
  ld [ACTION_LIST_READ_POINTER + 1], a

  ld [hl], NO_OP ; it is a zero terminated list

  ret

resetActionListWritePointer:
  ; point the action list pointer to the beginning
  ld a, high(ACTION_LIST)
  ld h, a
  ld [ACTION_LIST_WRITE_POINTER], a
  ld a, low(ACTION_LIST)
  ld l, a
  ld [ACTION_LIST_WRITE_POINTER + 1], a

  ld [hl], NO_OP ; it is a zero terminated list

  ret

resetFluxSMC:
  ; point the action dispatcher pointer to the beginning
  ld a, high(FLUX_SMC_ZONE)
  ld [FLUX_SMC_POINTER], a
  ld h, a
  ld a, low(FLUX_SMC_ZONE)
  ld [FLUX_SMC_POINTER + 1], a
  ld l, a

  ; for safety the last instruction should always be a ret
  ld a, RET_OP
  ld [hl], a

  ret

initDispatch:
  call resetActionListReadPointer
  call resetActionListWritePointer
  call resetFluxSMC

  ret

; @param hl - pointer to the action, at ARGC
; @param bc - the call address to write in the hole
prepareAction:
  ld a, [hl+] ; argc

  cp a, 0
  jr nz, .next
  call prepareAction0
  ret

.next
  cp a, 1
  jr nz, .done
  call prepareAction1
  ret

.done

  ret

; @param bc - the call address to write in the hole
prepareAction0:
  ld a, [FLUX_SMC_POINTER]
  ld h, a
  ld a, [FLUX_SMC_POINTER + 1]
  ld l, a
  ; hl has the next action dispatcher

  ; start the call op
  ld a, CALL_OP ; remember, low then high!
  ld [hl+], a
  ld a, c ; write bc into the hole
  ld [hl+], a
  ld a, b
  ld [hl+], a

  ; set the last instruction to ret
  ; but don't advance hl
  ; so that the next instruction overwrites this return
  ; and adds its own (ie the last instruction is always ret)
  ld a, RET_OP
  ld [hl], a

  ; update the pointer to the next dispatcher
  ld a, h
  ld [FLUX_SMC_POINTER], a
  ld a, l
  ld [FLUX_SMC_POINTER + 1], a

  ret

; @param hl - address of param 1
; @param bc - the call address to write in the hole
prepareAction1:
  ret

; @param hl - the pointer
getActionListReadPointer:
  ld a, [ACTION_LIST_READ_POINTER]
  ld h, a
  ld a, [ACTION_LIST_READ_POINTER + 1]
  ld l, a

  ret

; advances the action list read pointer
; by one action, and wraps if we ran out of
; space
; @param hl - the new pointer address
incrementActionListReadPointer:
  call getActionListReadPointer

  ld bc, ACTION_SIZE
  add hl, bc ; point to the next action

  ; if we wrapped, set it to the start
  ; ie if hl > ACTION_LIST_END
  ld bc, ACTION_LIST_END
  ld a, b
  cp a, h
  jr nz, .noWrap
  ld a, c
  cp a, l
  jr nz, .noWrap

  ld hl, ACTION_LIST
.noWrap

  ld a, h
  ld [ACTION_LIST_READ_POINTER], a
  ld a, l
  ld [ACTION_LIST_READ_POINTER + 1], a

  ret

; @param hl - the pointer
getActionListWritePointer:
  ; get the action list in hl
  ld a, [ACTION_LIST_WRITE_POINTER]
  ld h, a
  ld a, [ACTION_LIST_WRITE_POINTER + 1]
  ld l, a

  ret

; advances the action list write pointer
; by one action, and wraps if we ran out of
; space
; @param hl - the new pointer address
incrementActionListWritePointer:
  call getActionListWritePointer

  ld bc, ACTION_SIZE
  add hl, bc ; point to the next action

  ; if we wrapped, set it to the start
  ; ie if hl > ACTION_LIST_END
  ld bc, ACTION_LIST_END
  ld a, b
  cp a, h
  jr nz, .noWrap
  ld a, c
  cp a, l
  jr nz, .noWrap

  ld hl, ACTION_LIST
.noWrap

  ld [hl], NO_OP ; end the list
  ld a, h
  ld [ACTION_LIST_WRITE_POINTER], a
  ld a, l
  ld [ACTION_LIST_WRITE_POINTER + 1], a

  ret

; dispatch an action with zero params
; @params b - CODE
dispatchAction0:
  call getActionListWritePointer

  ; record the CODE
  ld a, b
  ld [hl+], a

  ; record the ARGC
  ld a, 0
  ld [hl+], a

  call incrementActionListWritePointer

  ret

; dispatch an action with one params
; @param b - CODE
; @param de - param 1
dispatchAction1:
  call getActionListWritePointer

  ; record the CODE
  ld a, b
  ld [hl+], a

  ; record the ARGC
  ld a, 1
  ld [hl+], a

  ; record the first param
  ld a, d
  ld [hl+], a
  ld a, e
  ld [hl+], a

  call incrementActionListWritePointer

  ret

SECTION "FLUX_RAM", WRAM0

; ACTIONS
NO_OP EQU 0
PLAYER_MOVE_RIGHT EQU 1
PLAYER_MOVE_LEFT EQU 2
PLAYER_MOVE_UP EQU 3
PLAYER_MOVE_DOWN EQU 4

; the list of actions to process
ACTIONS_PER_FRAME EQU 4
ACTION_SIZE EQU 6 ; CODE, ARGC, HIGH, LOW, HIGH, LOW
; the next action to process
ACTION_LIST_READ_POINTER: ds 2
; the next address to write an action
ACTION_LIST_WRITE_POINTER: ds 2
ACTION_LIST: ds ACTION_SIZE * ACTIONS_PER_FRAME
ACTION_LIST_END:

; Self Modifying Code
; SMC_ACTIONS
REDUCERS_COUNT EQU 4
FLUX_SMC_SIZE EQU 8
; a reducer might write between 4 an 8 bytes
; ld b, CONST ; 2 bytes
; ld c, CONST ; 2 bytes
; call __ ; 3 bytes
; ret ; 1 byte
FLUX_SMC_POINTER: ds 2
; so for SMC we need at most the size * actions * reducers
FLUX_SMC_ZONE: ds FLUX_SMC_SIZE * ACTIONS_PER_FRAME * REDUCERS_COUNT


ENDC	; end definition of flux stuff file