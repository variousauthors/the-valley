IF !DEF(GAME_OVER_GAME_STATE_INC)
GAME_OVER_GAME_STATE_INC = 1

SECTION "GameOverGameState", ROM0

/** watching the game over happen */
gameOverGameState:
  call waitForVBlank

  ; hide the player
  ld a, LCDCF_ON|LCDCF_BG8000|LCDCF_BG9800|LCDCF_BGON|LCDCF_OBJ8|LCDCF_OBJOFF
  ld [rLCDC], a

  ; fade out the screen slowly
  call count4In4Seconds

  ld hl, WhiteOutPalettes
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

  ld a, 0
  ld [rIE], a
  halt ; forever

.continue

  ret

toGameOverState:
  ; set the game state to "GAME_OVER"
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(gameOverGameState)
  ld [hl+], a
  ld a, HIGH(gameOverGameState)
  ld [hl], a
  ret

ENDC