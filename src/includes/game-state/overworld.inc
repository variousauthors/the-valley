IF !DEF(OVERWORLD_GAME_STATE_INC)
OVERWORLD_GAME_STATE_INC = 1

SECTION "OverworldGameState", ROM0

/** wandering the overworld */
overworldGameState:
  ; -- handle events --

  ; 2. is the current step of the game loop finished
  ; Moving on to the next step means: 
  ; - executing the current state's update
  ; - probably gathering new input
  ; - once we have new inputs we start resolving
  ;   events, state might need to be interpolated, etc
  ; 
  ; once we have "no input" again it means the state
  ; cleared its inputs and we are ready to get the next set
  ; ready to do the next state update
  ; I need a diagram or something...
  ; @TODO we should really replace this with a proper
  ; array of events... see NEXTSTEPS
  call isCurrentStepFinished
  jr z, .nextStep

  ; start reacting to the current step

  ; -- MOVEMENT EVENTS --
  ; check for things like random encounters, entering doors, etc...
  ; things that are the results of state updates

  call getWorldPosition
  call checkForAutoEvent
  jr z, .noAutoEvents

  call handleAutoEvent

  ; if we had auto events we may not be in a steady state
  ret

.noAutoEvents
  ; next grab the out of bounds event
  call checkForOutOfBoundsEvent
  jr z, .noOutOfBoundsEvents

  call handleOutOfBoundsEvents

  ; if we had auto events we may not be in a steady state
  ret

.noOutOfBoundsEvents
  ; next check for boat event
  ; if the player is on the boat then
  ; go to ocean game state

  call getWorldPosition
  call checkForBoatEvent
  jr nz, .noBoatEvent

  ; player heals when they get on the boat
  call playerFullHeal

  call toOceanGameState
  ret

.noBoatEvent

  ; done checking for events!
  ; we're in a steady state so it is time to perform game step

.nextStep

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

  ; in this state we draw the boat with boat y,x
  ; so that it doesn't move
  ld hl, BOAT_WORLD_Y
  ld de, CAMERA_WORLD_Y
  call pixelDistance
  ld b, a

  ld hl, BOAT_WORLD_X
  ld de, CAMERA_WORLD_X
  call pixelDistance
  ld c, a

  call drawBoat

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

  ld hl, GAME_STATE_IS_STEADY_LOW_BYTE
  ld a, LOW(overworldGameStateIsSteady)
  ld [hl+], a
  ld a, HIGH(overworldGameStateIsSteady)
  ld [hl], a

  ld hl, GAME_STATE_TRANSITION_FN_LOW_BYTE
  ld a, LOW(toOverworldGameState)
  ld [hl+], a
  ld a, HIGH(toOverworldGameState)
  ld [hl], a

  ret

; @return z - yes, we are in a steady state
overworldGameStateIsSteady:
  ld a, [PLAYER_NEXT_WORLD_X]
  ld b, a
  ld a, [PLAYER_WORLD_X]
  cp a, b
  ret nz

  ld a, [PLAYER_NEXT_WORLD_Y]
  ld b, a
  ld a, [PLAYER_WORLD_Y]
  cp a, b
  ret nz

  ret

ENDC