IF !DEF(GAME_STATE_INC)
GAME_STATE_INC = 1

SECTION "GAME_STATE", WRAM0

GAME_STATE_LOW_BYTE: ds 1
GAME_STATE_HIGH_BYTE: ds 1

SECTION "GameState", ROM0

/** we want to add a fade out / fade in over 3 frames 
 * fade out, then draw the new screen, then fade in
 * this means the screen transition event should
 * end by setting the game state to fade out
 * and then that should transition to a "draw" state
 * and then fade in 
 * lets do this in 2 states: exit state and enter state
 * exit state runs the fade out and then transitions
 * to enter state, which runs the draw and then fades in */

initGameState:
  ; initialize the game state to overworld
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(enterState)
  ld [hl+], a
  ld a, HIGH(enterState)
  ld [hl], a

  ret

exitState:
  call waitForVBlank

  ; fade out the screen slowly
  call count4In8Frames

  ld hl, FadeOutPalettes
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

  ; get the transition event
  call getCurrentEvent
  call doTransportRedraw
  call resetTime
  call toEnterState

  ret

.continue

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

/** random encounter */
randomEncounterGameState:
  ; -- INPUT PHASE JUST RECORDS ACTIONS --

  call readInput

  ; if there is not input this frame, skip thinking
  call getInput
  and a
  ret z

  ; otherwise there was input so exit this state
  call turnOffWindow
  call toOverworldGameState
  call resetInput

  ret


/** wandering the overworld */
overworldGameState:
  ; -- INPUT PHASE JUST RECORDS ACTIONS --

  call readInput

  ; if there is not input this frame, skip thinking
  call getInput
  and a
  ret z

  ; record intents
  call doPlayerMovement

  ; -- UPDATE STATE BASED ON ACTIONS --

  ; doPlayerMovement puts the requested move somwhere for us
  ; we can use that to get the callback we need to respond to
  ; the movement

  call handlePlayerMovement
  call nz, resetInput ; if there was no move (ie collision)

  ret

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

WhiteOutPalettes:
  db %11100100
  db %10010000
  db %01000000
  db %00000000

FadeOutPalettes:
  db %11100100
  db %10010000
  db %01000000
  db %00000000

FadeInPalettes:
  db %00000000
  db %01000000
  db %10010000
  db %11100100

toExitState:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(exitState)
  ld [hl+], a
  ld a, HIGH(exitState)
  ld [hl], a
  ret

toEnterState:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(enterState)
  ld [hl+], a
  ld a, HIGH(enterState)
  ld [hl], a
  ret

toOverworldGameState:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(overworldGameState)
  ld [hl+], a
  ld a, HIGH(overworldGameState)
  ld [hl], a
  ret

toRandomEncounterGameState:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(randomEncounterGameState)
  ld [hl+], a
  ld a, HIGH(randomEncounterGameState)
  ld [hl], a

  call turnOnWindow

  ret

toGameOverState:
  ; set the game state to "GAME_OVER"
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(gameOverGameState)
  ld [hl+], a
  ld a, HIGH(gameOverGameState)
  ld [hl], a
  ret

; @return hl - the handler for the current game state
getGameStateSubroutine:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ret

drawScore:
 ; draw each of those into VRAM
  ld a, [PLAYER_WORLD_X_BCD]
  and %00001111
  add 144
  ld [_SCRN1 + 33], a

  ; draw each of those into VRAM
  ld a, [PLAYER_WORLD_X_BCD + 1]
  and %11110000
  srl a
  srl a
  srl a
  srl a
  add 144
  ld [_SCRN1 + 34], a

  ; draw each of those into VRAM
  ld a, [PLAYER_WORLD_X_BCD + 1]
  and %00001111
  add 144
  ld [_SCRN1 + 35], a


  ; draw each of those into VRAM
  ld a, [PLAYER_WORLD_Y_BCD]
  and %00001111
  add 144
  ld [_SCRN1 + 37], a

  ; draw each of those into VRAM
  ld a, [PLAYER_WORLD_Y_BCD + 1]
  and %11110000
  srl a
  srl a
  srl a
  srl a
  add 144
  ld [_SCRN1 + 38], a

  ; draw each of those into VRAM
  ld a, [PLAYER_WORLD_Y_BCD + 1]
  and %00001111
  add 144
  ld [_SCRN1 + 39], a

  ret

updateScore:
  ld hl, PLAYER_WORLD_Y
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [PLAYER_WORLD_Y_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [PLAYER_WORLD_Y_BCD + 1], a

  ld hl, PLAYER_WORLD_X
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [PLAYER_WORLD_X_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [PLAYER_WORLD_X_BCD + 1], a

  ret

ENDC