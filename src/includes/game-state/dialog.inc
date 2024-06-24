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

  ; if the current character is not linefeed or null
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

  ; and reset the window index
  ld a, 0
  ld [DialogWindowIndex], a

  ret

  ; once the dialog is finished
.done

  call fromDialogGameState

  ret

drawDialogWindowFrame:
  ; draw the frame around the window
  ld a, WINDOW_FRAME_TL
  ld [ENCOUNTER_WINDOW_TL], a
  ld a, WINDOW_FRAME_TR
  ld [ENCOUNTER_WINDOW_TR], a
  ld a, WINDOW_FRAME_BL
  ld [ENCOUNTER_WINDOW_BL], a
  ld a, WINDOW_FRAME_BR
  ld [ENCOUNTER_WINDOW_BR], a

  ld a, WINDOW_FRAME_LEFT
  ld [ENCOUNTER_WINDOW_LEFT], a
  ld a, WINDOW_FRAME_RIGHT
  ld [ENCOUNTER_WINDOW_RIGHT], a

  ; draw top
  ld hl, ENCOUNTER_WINDOW_TOP
  ld a, WINDOW_FRAME_TOP
  ld b, SCRN_WIDTH - 2
.loop
  ld [hl+], a
  dec b
  jr nz, .loop

  ; draw bottom
  ld hl, ENCOUNTER_WINDOW_BOTTOM
  ld a, WINDOW_FRAME_BOTTOM
  ld b, SCRN_WIDTH - 2
.loop2
  ld [hl+], a
  dec b
  jr nz, .loop2

  ret

drawDialogWindow:
  call drawDialogWindowFrame

  ret

dialogGameStateDraw:
  call turnOnWindow
  ; not drawing because drawing it erases the dialog
  ; call drawDialogWindow
  call drawEncounterWindow

  ; if we are on linefeed or null then abort
  ; jump hl to the text
  ld hl, DialogTextPointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ; if the current character is linefeed or null
  ; then we are in a steady state
  ld a, [hl]
  cp a, 2
  ret c

  ; get the next character and draw it into the frame
  ld hl, DialogTextPointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ld b, [hl] ; store the character offset to print

  ld hl, _SCRN1
  ld a, [DialogWindowIndex]
  add 33 ; kind of in the middle of the window

  ; add window index to hl
  add l
	ld l, a
	adc h
	sub l
	ld h, a

  ; load the kana into that slot
  ld a, 128
  add a, b
  ld [hl], a

  ld a, [DialogWindowIndex]
  inc a
  ld [DialogWindowIndex], a

  ret

dialogGameStateUpdate:
  call enableEncounterStatusTemplateDraw
  call resetEncounterStatusTemplateDrawPointer
  call getEncounterStatusTemplatePointer

  ; if we are on linefeed or null then abort
  ; jump hl to the text
  ld hl, DialogTextPointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ; if the current character is linefeed or null
  ; then we are in a steady state
  ld a, [hl]
  cp a, 2
  ret c

  ; otherwise avance

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

  call resetPlayerMovement

  ret

ENDC