IF !DEF(ENTER_GAME_STATE_INC)
ENTER_GAME_STATE_INC = 1

/** the game state used when entering a door */
SECTION "EnterGameState", ROM0

toEnterState:
  ; set the palette to blank
  ld a, %00000000
  ld [rBGP], a
  ld [rOBP0], a

  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(enterState)
  ld [hl+], a
  ld a, HIGH(enterState)
  ld [hl], a

  ld hl, GAME_STATE_DRAW_LOW_BYTE
  ld a, LOW(enterStateDraw)
  ld [hl+], a
  ld a, HIGH(enterStateDraw)
  ld [hl], a

  ld hl, GAME_STATE_UPDATE_LOW_BYTE
  ld a, LOW(enterStateUpdate)
  ld [hl+], a
  ld a, HIGH(enterStateUpdate)
  ld [hl], a

  ld hl, GAME_STATE_IS_STEADY_LOW_BYTE
  ld a, LOW(enterStateIsSteady)
  ld [hl+], a
  ld a, HIGH(enterStateIsSteady)
  ld [hl], a

  ld hl, GAME_STATE_TRANSITION_FN_LOW_BYTE
  ld a, LOW(toEnterState)
  ld [hl+], a
  ld a, HIGH(toEnterState)
  ld [hl], a

  ret

enterState:
  call waitForVBlank

  ; fade in the screen slowly
  call count4In8Frames

  ld hl, FadeInPalettes
  push af

  ; add a to hl
  add l
	ld l, a
	adc h
	sub l
	ld h, a

  ; get the next palette
  ld a, [hl]

  ld [rBGP], a
  ld [rOBP0], a
  
  pop af
  cp a, 3 ; are we done fading out?
  jp nz, .continue

  ; transition to overworld state
  call toOverworldGameState
  ret

.continue

  ret

enterStateDraw:
  ret

enterStateUpdate:
  ret

; @return z - yes, we are in a steady state
enterStateIsSteady:
  cp a ; no state to monitor
  ret

ENDC