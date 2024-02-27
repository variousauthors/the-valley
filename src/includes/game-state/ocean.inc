IF !DEF(OCEAN_GAME_STATE_INC)
OCEAN_GAME_STATE_INC = 1

SECTION "OceanGameState", ROM0

/** wandering the ocean */
oceanGameState:
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

  ; we have to handle boat -> grass collision
  ; which will transition to overworld game state
  ; and update the BOAT position with the PLAYER position
  ; but the move should still happen, ie the player steps
  ; off the boat

  /**
   * @TODO
   * handle player movement currently 
   * - checks for collision 
   * - updates the player next position
   * - checks for boat landing
   * - checks for random encounter
   * - possibly resets the player movement
   * - possibly updates the draw tables
   *
   * this is too much! So move the "boat landing" and "random encounter"
   * checking code out here so that each state is in control over whether
   * to check for those things
   */
  call handlePlayerMovement
  call nz, resetInput ; if there was no move (ie collision, or random encounter)

  ret

oceanGameStateDraw:
  call mapDraw
  call screenCenterOnCamera
  ; call drawPlayer

  ; set up y, x for boat position using player position
  ; since the player is the boat in this state
  ld hl, PLAYER_WORLD_Y
  ld de, CAMERA_WORLD_Y
  call pixelDistance
  ld b, a

  ld hl, PLAYER_WORLD_X
  ld de, CAMERA_WORLD_X
  call pixelDistance
  ld c, a

  call drawBoat

  ret

oceanGameStateUpdate:
  call updatePlayerPosition
  call cameraFollowPlayer
  call updateCameraPosition

  ret

; reset the encounter table to
; grass overworld encounters
; set the boat event position
fromOceanGameState:
  ; update the boat to the player's position
  call updateBoatPosition

  ld hl, OverworldTileset
  call setCurrentMapTileset

  ret

toOceanGameState:
  call undrawPlayer
  ld hl, OverworldOceanTileset
  call setCurrentMapTileset

  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(oceanGameState)
  ld [hl+], a
  ld a, HIGH(oceanGameState)
  ld [hl], a

  ld hl, GAME_STATE_DRAW_LOW_BYTE
  ld a, LOW(oceanGameStateDraw)
  ld [hl+], a
  ld a, HIGH(oceanGameStateDraw)
  ld [hl], a

  ld hl, GAME_STATE_UPDATE_LOW_BYTE
  ld a, LOW(oceanGameStateUpdate)
  ld [hl+], a
  ld a, HIGH(oceanGameStateUpdate)
  ld [hl], a

  ld hl, GAME_STATE_IS_STEADY_LOW_BYTE
  ld a, LOW(oceanGameStateIsSteady)
  ld [hl+], a
  ld a, HIGH(oceanGameStateIsSteady)
  ld [hl], a

  ld hl, GAME_STATE_TRANSITION_FN_LOW_BYTE
  ld a, LOW(toOceanGameState)
  ld [hl+], a
  ld a, HIGH(toOceanGameState)
  ld [hl], a

  ret

; @return z - yes, we are in a steady state
oceanGameStateIsSteady:
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

; we probably want to add a "pre-move" subroutine
; to all the states... but for now it's this

; @return z - player is trying to land
checkForLanding:
  ; is it boat state
  ld a, [GAME_STATE_LOW_BYTE]
  ld hl, oceanGameState
  ld b, l

  cp a, b
  ret nz ; if we are not in the ocean gamestate abort

  ld a, [GAME_STATE_HIGH_BYTE]
  ld hl, oceanGameState
  ld b, h

  cp a, b
  ret nz ; if we are not in the ocean gamestate abort

  call getNextWorldPosition
  call isTileGrass
  ; z - tile is grass so yes we are landing

  ret

; @param bc - player next y, x in world position
; @return z - is grass tile
isTileGrass:
  call getCurrentMap
  call worldPositionToMetaTile
  push af
  call getCurrentMapTileset
  pop af

  call addAToHL
  ld a, [hl]
  cp a, GRASS_TILE

  ret


ENDC