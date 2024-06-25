IF !DEF(DIALOG_GAME_STATE)
DIALOG_GAME_STATE = 1

SECTION "DIALOG_GAME_STATE", WRAM0

; points to the start of text
DialogTextPointer: ds 2
DialogWindowIndex: ds 1

SECTION "DialogGameState", ROM0

dialogGameState:
  ; jump hl to the text
  ld hl, DialogTextPointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ; if the current character is not null
  ; then keep advancing
  ld a, [hl]
  cp a, 2 ; line feed and null are 0 and 1
  ret nc ; if a > 1 return

  ; otherwise wait for input

  ; -- INPUT PHASE JUST RECORDS ACTIONS --

  call readInput

  ; if A button was up last frame then we won't do anything
  ; regardless
  ld a, [_PREV_PAD]
  and a, A_BUTTON
  ret nz ; if A button is still UP return

  ; if A button was down, and they pressed A, then we have
  ; disco party time
  ld a, [_PAD]
  and a, A_BUTTON
  ret z

  ; there was input
  ld hl, DialogTextPointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ; if the character is null we are done
  ld a, [hl]
  cp a, 0
  jr z, .done

  ; otherwise we advance past the line feed
  inc hl ; advance
  ld b, h
  ld c, l
  ; write back to the pointer

  ld hl, DialogTextPointer
  ld a, c
  ld [hl+], a
  ld a, b
  ld [hl], a

  ; advance to the next line

  ; advance the template cursor pointer until it is
  ; 18 or 36 (indicating the start of a line)
  ; we are not bounds checking, the author must be
  ; careful to ensure each text is < 54 chars and null terminated
  ; with each line being < 18 char and line feed terminated
  ld a, [DialogWindowIndex]
.seek
  inc a
  cp 18
  jr z, .doneSeeking
  cp 36
  jr z, .doneSeeking
  jr .seek
.doneSeeking

  ; now it will be at the start of a line
  ld [DialogWindowIndex], a

  ret

  ; once the dialog is finished
.done

  call fromDialogGameState

  ret

dialogGameStateDraw:
  call turnOnWindow
  call drawEncounterWindow

  ret

; b is somehow safe throughout this subroutine
; @return de - pointer into the template
getTemplatePointerFromDialogWindowIndex:
  ; get the index
  ld a, [DialogWindowIndex]

  ; multiply by five to give us an index
  ; into the draw template

  ; n * 5 = n * (4 + 1) => n*4 + n
  ld d, a ; let d = n
  sla a
  sla a ; 4n
  add d ; + n

  ; get the pointer into de
  push af
  call getEncounterStatusTemplatePointer
  pop af

  call addAToDE

  ret

dialogGameStateUpdate:
  call enableEncounterStatusTemplateDraw
  call resetEncounterStatusTemplateDrawPointer

  ; if we are on linefeed or null then abort
  ld hl, DialogTextPointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ; if the current character is linefeed or null
  ; then we are in a steady state
  ld a, [hl]
  cp a, 2
  ret c

  ; get the next character and draw it into the template
  ld hl, DialogTextPointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ld b, [hl] ; store the character to print

  call getTemplatePointerFromDialogWindowIndex

  ; load the kana into that slot
  ld a, 128
  add a, b
  call fillTileSlot
  ld [hl], a

  ; advance the index
  ld a, [DialogWindowIndex]
  inc a
  ld [DialogWindowIndex], a

  ; avance the text pointer
  ld hl, DialogTextPointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  inc hl
  ld b, h
  ld c, l

  ; write back to the pointer
  ld hl, DialogTextPointer
  ld a, c
  ld [hl+], a
  ld a, b
  ld [hl], a

  ret

; @return z - yes, we are in a steady state
dialogGameStateIsSteady:
  ; jump hl to the text
  ld hl, DialogTextPointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ; if the current character is linefeed or null
  ; then we are in a steady state
  ld a, [hl]
  cp a, 0
  ret z

  ld a, [hl]
  cp a, 1

  ret

fromDialogGameState:
  call turnOffWindow
  call resetInput
  call disabledEncounterTemplateDraw

  ; we don't know which state to return to
  ; so we do the PrevTransition
  call performPrevTransition

  ret

/** call toDialogeGameState with some
 * dialoge and it will open the dialog
 * box and step through the given text */
; @param bc - a text
toDialogGameState:
  call bookmarkGameState

  ld hl, DialogTextPointer
  ld a, c
  ld [hl+], a
  ld a, b
  ld [hl], a

  ld a, 0
  ld [DialogWindowIndex], a

  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(dialogGameState)
  ld [hl+], a
  ld a, HIGH(dialogGameState)
  ld [hl], a

  ld hl, GAME_STATE_DRAW_LOW_BYTE
  ld a, LOW(dialogGameStateDraw)
  ld [hl+], a
  ld a, HIGH(dialogGameStateDraw)
  ld [hl], a

  ld hl, GAME_STATE_UPDATE_LOW_BYTE
  ld a, LOW(dialogGameStateUpdate)
  ld [hl+], a
  ld a, HIGH(dialogGameStateUpdate)
  ld [hl], a

  ld hl, GAME_STATE_IS_STEADY_LOW_BYTE
  ld a, LOW(dialogGameStateIsSteady)
  ld [hl+], a
  ld a, HIGH(dialogGameStateIsSteady)
  ld [hl], a

  ld hl, GAME_STATE_TRANSITION_FN_LOW_BYTE
  ld a, LOW(toDialogGameState)
  ld [hl+], a
  ld a, HIGH(toDialogGameState)
  ld [hl], a

  ; initialize the template
  call clearEncounterStatusTemplate

  ld b, ENCOUNTER_STATUS_DRAW_TEMPLATE_SIZE
  ld hl, ENCOUNTER_STATUS_DRAW_TEMPLATE
  call makeVRAMTemplate
  call prefillVRAMAddresses

  call resetPlayerMovement

  ret

ENDC