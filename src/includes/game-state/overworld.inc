IF !DEF(OVERWORLD_GAME_STATE_INC)
OVERWORLD_GAME_STATE_INC = 1

SECTION "OverworldGameState", ROM0

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
  call nz, resetInput ; if there was no move (ie collision, or random encounter)

  ret

overworldGameStateDraw:
  call mapDraw
  call screenCenterOnCamera
  call drawPlayer

  ret

overworldGameStateUpdate:
  call updatePlayerPosition
  call cameraFollowPlayer
  call updateCameraPosition

  ret

toOverworldGameState:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(overworldGameState)
  ld [hl+], a
  ld a, HIGH(overworldGameState)
  ld [hl], a

  ld hl, GAME_STATE_DRAW_LOW_BYTE
  ld a, LOW(overworldGameStateDraw)
  ld [hl+], a
  ld a, HIGH(overworldGameStateDraw)
  ld [hl], a

  ld hl, GAME_STATE_UPDATE_LOW_BYTE
  ld a, LOW(overworldGameStateUpdate)
  ld [hl+], a
  ld a, HIGH(overworldGameStateUpdate)
  ld [hl], a

  ret

ENDC