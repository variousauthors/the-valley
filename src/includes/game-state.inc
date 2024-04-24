IF !DEF(GAME_STATE_INC)
GAME_STATE_INC = 1

SECTION "GAME_STATE", WRAM0

; pointers
GAME_STATE_LOW_BYTE: ds 1
GAME_STATE_HIGH_BYTE: ds 1
GAME_STATE_UPDATE_LOW_BYTE: ds 2
GAME_STATE_DRAW_LOW_BYTE: ds 2
GAME_STATE_IS_STEADY_LOW_BYTE: ds 2

; for hierarchical states
GAME_STATE_TRANSITION_FN_LOW_BYTE: ds 2
PREV_GAME_STATE_TRANSITION_FN_LOW_BYTE: ds 2

SECTION "GameState", ROM0

RANDOM_TEXT: db 1, 2, 3, 4, 5, 6, 1, 7, 8, 9, 0

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
  call toEnterState

  ret

/** store the transition function from 
 * the previous game state, so that we can
 * transition back to it from some nested
 * game state, eg menu or random encounter */
bookmarkGameState:
  ld hl, GAME_STATE_TRANSITION_FN_LOW_BYTE
  ld de, PREV_GAME_STATE_TRANSITION_FN_LOW_BYTE

  ; copy the pointer
  ld a, [hl+]
  ld [de], a
  inc de

  ld a, [hl]
  ld [de], a

  ret

performPrevTransition:
  ld hl, PREV_GAME_STATE_TRANSITION_FN_LOW_BYTE
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  call indirectCall

  ret

performGameStep:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  call indirectCall

  ret

performGameUpdate:
  ld hl, GAME_STATE_UPDATE_LOW_BYTE
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  call indirectCall

  ret

performGameDraw:
  ld hl, GAME_STATE_DRAW_LOW_BYTE
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  call indirectCall

  ret

isGameStateSteady:
  ld hl, GAME_STATE_IS_STEADY_LOW_BYTE
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  call indirectCall

  ret

; @return z - step finished
isCurrentStepFinished:
  call getInput
  cp a, 0

  ret

ENDC