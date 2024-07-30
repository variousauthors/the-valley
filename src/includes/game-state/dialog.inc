IF !DEF(DIALOG_GAME_STATE)
DIALOG_GAME_STATE = 1

SECTION "DIALOG_GAME_STATE", WRAM0

; points to the start of text
DialogStartPointer: ds 2
DialogTextPointer: ds 2
DialogWindowIndex: ds 1

DIALOG_WORLD_Y: ds 1
DIALOG_WORLD_X: ds 1

SECTION "DialogGameState", ROM0

getContinueButton:
  ld hl, DIALOG_WORLD_Y
  ld b, [hl]
  inc hl
  ld c, [hl]
  call getPositionalTowardsButton

  ret

getCancelButton:
  ; any direction _other than_ towards
  ld hl, DIALOG_WORLD_Y
  ld b, [hl]
  inc hl
  ld c, [hl]
  call getPositionalTowardsButton
  ; 1000 xor 1111 -> 0111
  xor a, %11110000
  and a, %11110000

  ret

DIALOG_FRAME_TILE_BASE EQU 80
DIALOG_FRAME_TOP EQU DIALOG_FRAME_TILE_BASE

DIALOG_PANEL_TOP EQU _SCRN1

drawDialogWindowFrame:
  ; draw top border of window
  ld hl, DIALOG_PANEL_TOP
  ld a, DIALOG_FRAME_TOP
  ld b, SCRN_WIDTH + 1
.loop
  ld [hl+], a
  dec b
  jr nz, .loop
  ret

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
  ld a, [_PAD]
  or a
  ret z ; if there is really no input, we skip... makes debugging easier

  call getCancelButton
  ld b, a

  ld a, [_PREV_PAD]
  and a, b
  jr nz, .noCancel ; if A button is still UP return

  ; if A button was down, and they pressed A, then we have
  ; disco party time
  ld a, [_PAD]
  and a, b
  jr z, .noCancel

  ; handle cancel
  jr .done

  ; they did not cancel

.noCancel
  ret 
  ; we don't need a "continue" button 
  ; for now NPC dialog will all be on one
  ; sheet

  ; later when we need to be able to "advance" the dialog
  ; we can handle it here but remember: do not let "towards"
  ; end the dialog... or the dialog will just loop!

  call getContinueButton
  ld b, a

  ; if A button was up last frame then we won't do anything
  ; regardless
  ld a, [_PREV_PAD]
  and a, b
  jr nz, .noInput ; if A button is still UP return

  ; if A button was down, and they pressed A, then we have
  ; disco party time
  ld a, [_PAD]
  and a, b
  jr z, .noInput

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
  ; if we are talking to the dark lord
  ; then we have a battle to fight
  ; we have 4 bytes to compare
  ld hl, DarkLordSays
  ld a, [DialogStartPointer]
  cp a, l
  jr nz, .notDarkLord

  ld a, [DialogStartPointer + 1]
  cp a, h
  jr nz, .notDarkLord

  ; OMG GUYS it's the dark lord! Kill it!!!
  call fromDialogGameState
  call toGameOverState ; set up the state to return to after the battle
  call toRandomEncounterGameState
  ret

.notDarkLord

  call fromDialogGameState
  ret

.noInput
  ld a, 1
  or a ; nz indicates nothing happened
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

CHARACTER_VRAM EQU 128

dialogGameStateUpdate:
  call enableEncounterStatusTemplateDraw
  call resetEncounterStatusTemplateDrawPointer

  ; if we are on linefeed or null then abort
  ld hl, DialogTextPointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ; if the current character is not null
  ; then we are in a steady state
  ld a, [hl]
  cp a, 1
  ret c

  ; if it is a line feed, we handle that
  ld a, [hl]
  cp a, 2
  jr c, .handleLineFeed

  ; get the next character and draw it into the template
  ld hl, DialogTextPointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ld b, [hl] ; store the character to print

  call getTemplatePointerFromDialogWindowIndex

  ; load the kana into that slot
  ld a, CHARACTER_VRAM
  add a, b
  call fillTileSlot
  ld [hl], a

  ; advance the write pointer
  ld a, [DialogWindowIndex]
  inc a
  ld [DialogWindowIndex], a

  ; avance the read pointer
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

.handleLineFeed
  ; avance the read pointer past the line feed
  ld hl, DialogTextPointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  inc hl
  ld b, h
  ld c, l

  ld hl, DialogTextPointer
  ld a, c
  ld [hl+], a
  ld a, b
  ld [hl], a

  ; advance the write pointer to the next line

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

  ld a, 1
  cp a, 0

  ret

fromDialogGameState:
  call turnOffWindow
  call resetInput
  call disabledEncounterTemplateDraw

  ld a, 0
  ld [DIALOG_WORLD_Y], a
  ld [DIALOG_WORLD_X], a

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

  ; we use this to check for the dark lord
  ld hl, DialogStartPointer
  ld a, c
  ld [hl+], a
  ld a, b
  ld [hl], a

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
  call dialogPrefillVRAMAddresses

  ; we're enabling it here for the initial render
  call enableEncounterStatusTemplateDraw

  ld a, ENCOUNTER_WINDOW_LOWER_BORDER
  ld [rWY], a
  ld a, 0
  ld [rWX], a

  ; setup the hblanks for encounter
  call initHBlankArray
  ld hl, HBlankArray
  ld [hl], ENCOUNTER_WINDOW_LOWER_BORDER ; turn off objs

  call getNextHBlank
  ld [rLYC], a

  call resetPlayerMovement

  ret

DIALOG_WINDOW_TEXT_BASE EQU _SCRN1 + 2
DIALOG_WINDOW_TEXT_ROW_ONE EQU DIALOG_WINDOW_TEXT_BASE + 32
DIALOG_WINDOW_TEXT_ROW_TWO EQU DIALOG_WINDOW_TEXT_ROW_ONE + 32
DIALOG_WINDOW_TEXT_ROW_THREE EQU DIALOG_WINDOW_TEXT_ROW_TWO + 32

dialogPrefillVRAMAddresses:
  ; we know where we want to draw each tile
  ; so we can pre-fill that part of the template

  ; it is the whole 3 rows of VRAM

  call getEncounterStatusTemplatePointer
  ld hl, DIALOG_WINDOW_TEXT_ROW_ONE

  ; first we pre-fill the line at the top

  ld b, ONE_ROW_OF_TEXT
.loop1
  call fillVRAMAddressSlot
  inc hl
  dec b
  jr nz, .loop1
.done1

  ld hl, DIALOG_WINDOW_TEXT_ROW_TWO
  ld b, ONE_ROW_OF_TEXT
.loop2
  call fillVRAMAddressSlot
  inc hl
  dec b
  jr nz, .loop2
.done2

  ld hl, DIALOG_WINDOW_TEXT_ROW_THREE
  ld b, ONE_ROW_OF_TEXT
.loop3
  call fillVRAMAddressSlot
  inc hl
  dec b
  jr nz, .loop3
.done3

  ret

ENDC