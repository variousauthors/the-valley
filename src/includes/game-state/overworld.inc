IF !DEF(OVERWORLD_GAME_STATE_INC)
OVERWORLD_GAME_STATE_INC = 1

SECTION "OverworldGameStateRAM", WRAM0

OVERWORLD_PAD: ds 2
ESCAPE_TRANSPORT_EVENT: ds 7 ; EVENT_SIZE

SECTION "OverworldGameState", ROM0

resetOverworldPad:
  ld a, 0
  ld [OVERWORLD_PAD], a
  ret

/** player pressed B so escape to another scene */
populateEscapeEvent:
  ; they are running away so send them to the boat
  ld hl, ESCAPE_TRANSPORT_EVENT
  ld a, TRANSPORT_EVENT
  ld [hl+], a
  ld a, [PLAYER_WORLD_Y]
  ld [hl+], a
  ld a, [PLAYER_WORLD_X]
  ld [hl+], a

  ld a, HIGH(Oubliette_menu)
  ld [hl+], a
  ld a, LOW(Oubliette_menu)
  ld [hl+], a

  ld a, 4
  ld [hl+], a
  ld a, 4
  ld [hl+], a

  ; increment the next oubliette pointer
  ; increment the oubliette message pointer
  ret

stateReadInput:
  ; call readInput to get the input device state
  ; OVERWORLD_PAD PREV_PAD PAD       -> OVERWORLD_PAD
  ; 0000          0000     0000      -> 0000
  ; 0000          0000     0001      -> 0001 "a fresh now button down"
  ; 0000          0001     0000      -> 0000
  ; 0000          0001     0001      -> 0000
  ; 0001          0000     0000      -> 0000 
  ; 0001          0000     0001      -> 0000 "coming back to overworld state after dialog, for example"
  ; 0001          0001     0000      -> 0000 "release button"
  ; 0001          0001     0001      -> 0000 "hold button"

  call readInput
  ld a, [OVERWORLD_PAD]
  or a
  jr z, .notMoving

.moving
  ; overworld pad is already set to some value
  ; so keep walking

  call getInput
  ld [OVERWORLD_PAD], a
  ret

.notMoving
  ; the only way to start moving is a _fresh_ button press

  ld a, [_PREV_PAD]
  call getInput
  or a
  jr nz, .inputWasHeldBeforeStateTransition

  ; OK so previously no button was down
  ; a button is down
  ; so update overworld pad
  ld a, [_PAD]
  call getInput

  jr z, .stopMoving

.startMoving
  ld [OVERWORLD_PAD], a
  ret

.stopMoving
  ld [OVERWORLD_PAD], a
  ret

.inputWasHeldBeforeStateTransition
  ; previously a button was down
  ; but we didn't record it in overworld pad
  ; so we were in a different state like dialog
  ; so ignore that input
  ld a, 0

  ret

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
  ; we do not clear OVERWORLD_PAD
  ; - you keep walking after transport
  ; - walking out of auto event dialog
  ; - walking after an encounter

  ; if we had auto events we may not be in a steady state
  ret

.noAutoEvents
  ; next grab the out of bounds event
  call checkForOutOfBoundsEvent
  jr z, .noOutOfBoundsEvents

  call handleOutOfBoundsEvents
  ; we do not clear OVERWORLD_PAD
  ; - you keep walking after transport
  ; - walking out of auto event dialog
  ; - walking after an encounter

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
  ; we do not clear OVERWORLD_PAD
  ; - you keep walking after transport
  ; - walking out of auto event dialog
  ; - walking after an encounter

  ret

.noBoatEvent

  ; done checking for events!
  ; we're in a steady state so it is time to perform game step

.nextStep

  ; -- INPUT PHASE JUST RECORDS ACTIONS --

  call stateReadInput
  and a
  jr z, .noInput

  ; record intents
  call recordPlayerMoveIntent
  call recordPlayerEscapeIntent

  ; -- UPDATE STATE BASED ON ACTIONS --

  ; recordPlayerMoveIntent puts the requested move somwhere for us
  ; we can use that to get the callback we need to respond to
  ; the movement

  call shouldPlayerEscape
  jr c, .noEscape

  ; player escapes
  call populateEscapeEvent
  ld de, ESCAPE_TRANSPORT_EVENT
  call handleTransportEvent

  ret

.noEscape
  call handlePlayerMovement
  call nz, resetInput ; if there was no move (ie collision, or random encounter)
  jr nz, .skipDraw

  ld a, [PLAYER_MOVE_DIRECTION]
  call drawPlayerMove

.noInput
  ld a, 1
  or a
  ret

.skipDraw

  ret

overworldGameStateDraw:
  call mapDraw
  call screenCenterOnCamera
  call drawPlayer
  call drawElder
  call drawCultist
  call undrawBoat

  ; if we are in the overworld, draw the boat
  call getCurrentMap
  call isOverworld
  ret z

  ld a, [BOAT_WORLD_Y]
  ld b, a
  ld a, [BOAT_WORLD_X]
  ld c, a
  call cameraCullEntity
  jr c, .skipDrawBoat

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
.skipDrawBoat

  ret

; @param bc - y, x
; @destroys hl
; @return c - cull the entity
cameraCullEntity:

.top
  ld hl, CAMERA_WORLD_Y
  ld a, b
  ld b, [hl]
  dec b ; we want to start drawing _before_ entity is on screen
  sub a, b

  ; first, if camera y < 1
  ; so we decremented, if it was 0 or less it will be negative
  bit 7, b ; is it negative?
  jp nz, .bottom ; then skip

  ; otherwise, c is still the carry from sub a, b above
  ret c ; y was less than camera y
  ; y is above camera y so a is positive
  ; but how positive...

.bottom
  ld b, a
  ld a, META_TILE_ROWS_PER_SCRN + 2 ; the buffer to start drawing early
  cp a, b

  ret c ; y was greater than camera y + view port height

.left
  ld hl, CAMERA_WORLD_X
  ld a, c
  ld c, [hl]
  dec c
  sub a, c

  ; first, if camera x < 1
  ; so we decremented, if it was 0 or less it will be negative
  bit 7, c ; is it negative?
  jp nz, .right ; then skip

  ret c ; x was less than camera x
  ; x is above camera x so a is positive
  ; but how positive...

.right
  ld c, a
  ld a, META_TILES_PER_SCRN_ROW + 2
  cp a, c

  ret c ; x was greater than camera x + view port width
  
  ret

overworldGameStateUpdate:
  call updatePlayerPosition
  call cameraFollowPlayer
  call updateCameraPosition

  ret

OUBLIETTE_MESSAGE_UPPER_BORDER EQU 2 * META_TILE_PIXEL_DIM
OUBLIETTE_MESSAGE_LOWER_BORDER EQU 7 * META_TILE_PIXEL_DIM

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

  ; reset the encounter count-down
  call resetEncounterHits
  call resetPlayerEscape

  ; regenerate the templates

  ; create the row template
  ld hl, MAP_DRAW_ROW_TEMPLATE
  ld b, SCRN_WIDTH * 2
  call makeVRAMTemplate

  ; create the column template
  ld hl, MAP_DRAW_COLUMN_TEMPLATE
  ld b, SCRN_HEIGHT * 2
  call makeVRAMTemplate

  /*
  call turnOffLCD

  ; oubliette message stuff

  ld hl, OublietteMessage1
  ld de, DIALOG_WINDOW_TEXT_ROW_ONE

  ; iterate until a null
.oublietteMessage
  ld a, [hl+]
  cp NULL
  jr z, .doneOublietteMessage

  cp LINE_FEED
  jr nz, .noLineFeed

  ; advance line
  ld de, DIALOG_WINDOW_TEXT_ROW_TWO
  jr .oublietteMessage

.noLineFeed

  ld b, CHARACTER_VRAM
  add a, b

  ld [de], a
  inc de
  jr .oublietteMessage

.doneOublietteMessage

  ld a, OUBLIETTE_MESSAGE_LOWER_BORDER
  ld [rWY], a
  ld a, 7 ; needs to be 7 rather than zero to avoid stuttering window bug
  ld [rWX], a

  ; setup the hblanks for dialog
  ; to hide sprites under the dialog
  call initHBlankArray
  ld hl, HBlankArray
  ld [hl], OUBLIETTE_MESSAGE_LOWER_BORDER ; turn off objs

  call getNextHBlank
  ld [rLYC], a

  ; write the current message to the window
  call turnOnLCD
  call turnOnWindow
  */

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