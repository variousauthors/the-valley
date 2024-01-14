IF !DEF(GAME_STATE_INC)
GAME_STATE_INC = 1

SECTION "GAME_STATE", WRAM0

GAME_STATE_LOW_BYTE: ds 1
GAME_STATE_HIGH_BYTE: ds 1

GAME_STATE_UPDATE_LOW_BYTE: ds 1
GAME_STATE_UPDATE_HIGH_BYTE: ds 1

GAME_STATE_DRAW_LOW_BYTE: ds 1
GAME_STATE_DRAW_HIGH_BYTE: ds 1

ENCOUNTER_SPRITE_TILES: ds 4

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

  ld hl, GAME_STATE_DRAW_LOW_BYTE
  ld a, LOW(enterState)
  ld [hl+], a
  ld a, HIGH(enterState)
  ld [hl], a

  ld hl, GAME_STATE_UPDATE_LOW_BYTE
  ld a, LOW(enterState)
  ld [hl+], a
  ld a, HIGH(enterState)
  ld [hl], a

  ret

; @return hl - the handler for the current game state
getGameStateSubroutine:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ret

; @return hl - the handler for the current game state
getGameStateDrawSubroutine:
  ld hl, GAME_STATE_DRAW_LOW_BYTE
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ret

; @return hl - the handler for the current game state
getGameStateUpdateSubroutine:
  ld hl, GAME_STATE_UPDATE_LOW_BYTE
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ret

ENDC