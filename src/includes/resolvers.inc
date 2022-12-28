IF !DEF(RESOLVERS_INC)
RESOLVERS_INC = 1

runReducers:
  ld hl, ACTION_LIST

.loop
  ld a, [hl] ; get an action
  cp a, NO_OP ; if it is zero we are done
  jr z, .done
  ; each action is a fixed size so we can iterate over them easily

  call playerReducer
  call templateReducer
  ; call drawReducer
  call scrollingReducer
  call bufferReducer

  ; advance to next action
  ld bc, ACTION_SIZE
  add hl, bc

  jr .loop
.done

  ret

; OK so reducer stuff
; in code we call dispatch action
; and this creates an action which is like
; CODE ARGC BC DE HL
; and in the reducers, each reducer adds
; a routine based on the action
; then we iterate through all the actions
; call each reducer with the action
; then at the end we jump to the dynamic code

; WHY? This is so that code out there can record params
; without knowing what is going to be called with them
; so a routine that fires the gun could record direction
; and then various reducers could consume the fact that the
; gun was fired, and the direction

; @param hl - action
templateReducer:
  push hl
  ld a, [hl+] ; code

  ld bc, 0 ; assume no op

  cp a, PLAYER_MOVE_LEFT
  jr nz, .next1
  ld bc, drawLeftColumn

.next1
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .next2
  ld bc, drawRightColumn

.next2
  cp a, PLAYER_MOVE_UP
  jr nz, .next3
  ld bc, writeTopRowTemplate

.next3
  cp a, PLAYER_MOVE_DOWN
  jr nz, .next4
  ld bc, drawBottomRow

.next4

  call prepareAction

  pop hl
  ret

; @param hl - action
drawReducer:
  push hl
  ld a, [hl+] ; code

  ld bc, 0 ; assume no op

  cp a, PLAYER_MOVE_LEFT
  jr nz, .next1
  ld bc, drawLeftColumn

.next1
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .next2
  ld bc, drawRightColumn

.next2
  cp a, PLAYER_MOVE_UP
  jr nz, .next3
  ld bc, drawTopRow

.next3
  cp a, PLAYER_MOVE_DOWN
  jr nz, .next4
  ld bc, drawBottomRow

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
  ld bc, writeLeftColumnToBuffer

.next1
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .next2
  ld bc, writeRightColumnToBuffer

.next2
  cp a, PLAYER_MOVE_UP
  jr nz, .next3
  ld bc, writeTopRowToBuffer

.next3
  cp a, PLAYER_MOVE_DOWN
  jr nz, .next4
  ld bc, writeBottomRowToBuffer

.next4

  call prepareAction

  pop hl
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
ACTIONS_PER_FRAME EQU 4
ACTION_SIZE EQU 6 ; CODE, ARGC, HIGH, LOW, HIGH, LOW
ACTION_LIST_POINTER: ds 2
ACTION_LIST: ds ACTION_SIZE * ACTIONS_PER_FRAME

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

SECTION "ACTION_ROM", ROM0

CALL_OP EQU $CD ; remember, low then high!
RET_OP EQU $C9
LD_A_N16 EQU $FA
LD_N16_A EQU $EA

initDispatch:
  ; point the action list pointer to the beginning
  ld a, high(ACTION_LIST)
  ld h, a
  ld [ACTION_LIST_POINTER], a
  ld a, low(ACTION_LIST)
  ld l, a
  ld [ACTION_LIST_POINTER + 1], a

  ld [hl], NO_OP ; it is a zero terminated list

  ; point the action dispatcher pointer to the beginning
  ld a, high(FLUX_SMC_ZONE)
  ld [FLUX_SMC_POINTER], a
  ld a, low(FLUX_SMC_ZONE)
  ld [FLUX_SMC_POINTER + 1], a

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

; dispatch an action with zero params
; @params b - CODE
dispatchAction0:
  ; get the action list in hl
  ld a, [ACTION_LIST_POINTER]
  ld h, a
  ld a, [ACTION_LIST_POINTER + 1]
  ld l, a

  ; record the CODE
  ld a, b
  ld [hl+], a

  ; record the ARGC
  ld a, 0
  ld [hl+], a

  ; move the pointer
  ld [hl], NO_OP ; end the list
  ld a, h
  ld [ACTION_LIST_POINTER], a
  ld a, l
  ld [ACTION_LIST_POINTER + 1], a

  ret

; dispatch an action with one params
; @param b - CODE
; @param de - param 1
dispatchAction1:
  ; get the action list in hl
  ld a, [ACTION_LIST_POINTER]
  ld h, a
  ld a, [ACTION_LIST_POINTER + 1]
  ld l, a

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

  ; move the pointer
  ld [hl], NO_OP ; end the list
  ld a, h
  ld [ACTION_LIST_POINTER], a
  ld a, l
  ld [ACTION_LIST_POINTER + 1], a

  ret

ENDC	; end definition of resolvers file
