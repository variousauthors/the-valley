IF !DEF(PLAYER_MOVEMENT_INC)
PLAYER_MOVEMENT_INC = 1

; ACTIONS
NO_OP EQU 0
PLAYER_MOVE_RIGHT EQU 1
PLAYER_MOVE_LEFT EQU 2
PLAYER_MOVE_UP EQU 3
PLAYER_MOVE_DOWN EQU 4

SECTION "PLAYER_MOVEMENT_RAM", WRAM0

; record the direction of movement
PLAYER_MOVE_DIRECTION: ds 1

SECTION "PLAYER_MOVEMENT_ROM", ROM0

; @param b - intent to record
recordMovement:
  ld hl, PLAYER_MOVE_DIRECTION
  ld [hl], b

  ret

; @return nz - we cancelled the move
handlePlayerMovement: 
  ; recover the direction
  ld hl, PLAYER_MOVE_DIRECTION
  ld a, [hl]

  call getPlayerMovementHandler

  ; the meta tile should still be in c
  call indirectCall

  ; discard the move
  ld a, 0
  ld [PLAYER_MOVE_DIRECTION], a

  ret

; @param a - direction to move
; @return hl - handler to call
getPlayerMovementHandler:
  sla a ; double it because callback addresses are 2 bits

  ; get the callback address and call it
  ld hl, PLAYER_MOVE_HANDLERS
  add a, l
  ld l, a

  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ret

; a table for each direction so that we can just call hl + bc
; to perform all the effects of movement

SECTION "PLAYER_MOVE_HANDLERS", ROM0, ALIGN[3]
PLAYER_MOVE_HANDLERS:
  ; we need this no op because the movement enum starts at 1
  PLAYER_MOVE_HANDLERS.NO_OP: dw handleNoMove
  PLAYER_MOVE_HANDLERS.RIGHT: dw handleMoveRight
  PLAYER_MOVE_HANDLERS.LEFT: dw handleMoveLeft
  PLAYER_MOVE_HANDLERS.UP: dw handleMoveUp
  PLAYER_MOVE_HANDLERS.DOWN: dw handleMoveDown

/** handlers 
 * the idea here is that the player has nominated a direction to move in
 * and we now have to check the target for collision, etc...
 * before committing the move */

/** @TODO @DRY there is a lot of repetition here */

/**
 * check for collision, check for auto event
 * @param bc - y,x
 * @param hl - map
 * @return nz - abort the move
 */
handleMove:
  call getCurrentMap

  call checkForOutOfBounds
  jr z, .inBounds

.outOfBounds
  call hasBounds
  jr z, .skipCollisionCheck

  ; nz - we are out of bounds in a bounded map
  ; abort the move
  ret

.inBounds

  ; check if we are moving into the boat
  call checkForBoatEvent
  jr z, .skipCollisionCheck

  ; check for a collision
  call worldPositionToMetaTile
  call checkForCollision
  ret

.skipCollisionCheck

  ret

/** this is kind of weird
 * but basically after the player has commit
 * a move, but before the move is resolved,
 * some things can happen. Right now this is the
 * same in every state: 
 * - if they are landing the boat 
 * - if they are hitting a random encounter 
 * 
 * but different states will be different...
 * for example, on a boat we may not have random
 * encounters
 * or in a cave we may not have to check for boat */
; @return c - skip this move because we encountered an interrupt
moveReplacementEffects:
  ; @TODO feels like all this could be 
  ; implemented in the game state...
  ; so we register like, "pre-move"
  ; and call it here

  ; in the boat state we need to 
  ; check for attempts to move onto
  ; land and:
  ; 1. change to overworld state
  ; 2. not cancel the move
  ; we may still need to reset input!?
  call checkForLanding
  jr nz, .noLanding

  call fromOceanGameState
  call toOverworldGameState
  
  ld a, 0
  add a, 1 ; set nc to indicate no interrupt required
  ret

.noLanding

  ; now we know where we are moving to
  ; we can check for random encounters
  ; we will need to reset player next y,x
  ; once the encounter starts,
  ; but we need it to decide where the monster is
  call checkForRandomEncounter
  ret nc ; nc to indicate there is no interupt required

  ; start a random encounter
  call toRandomEncounterGameState
  call resetPlayerMovement
  call resetTime
  call resetInput

  ld a, 1
  add a, 255 ; set c

  ret

; @return nz - the move was cancelled
handleMoveLeft:
  call getLeftWorldPosition

  call handleMove
  jr nz, .skip

  call moveLeft

  call moveReplacementEffects
  jp c, .skip

  /** @TODO we should really move this out 
   * like, main should look at nz and 
   * then schedule the animations etc... */
  call fillVRAMAddressesForLeftColumn
  call enableMapDrawColumn
  call fillLeftColumnTileData
  cp a ; set z since we moved
.skip

  ret

handleNoMove:
  ret

; @return nz - the move was cancelled
handleMoveRight:
  call getRightWorldPosition

  call handleMove
  jr nz, .skip

  call moveRight

  call moveReplacementEffects
  jp c, .skip

  call fillVRAMAddressesForRightColumn
  call enableMapDrawColumn
  call fillRightColumnTileData
  cp a
.skip

  ret

; @return nz - the move was cancelled
handleMoveUp:
  call getUpWorldPosition

  call handleMove
  jr nz, .skip

  call moveUp

  call moveReplacementEffects
  jp c, .skip

  call fillVRAMAddressesForTopRow
  call enableMapDrawRow
  call fillTopRowTileData
  cp a
.skip

  ret

; @return nz - the move was cancelled
handleMoveDown:
  call getDownWorldPosition

  call handleMove
  jr nz, .skip

  call moveDown

  call moveReplacementEffects
  jp c, .skip

  call fillVRAMAddressesForBottomRow
  call enableMapDrawRow
  call fillBottomRowTileData
  cp a
.skip

  ret

; @return bc - y, x in world potision
getWorldPosition:
  ld a, [PLAYER_WORLD_X]
  ld c, a
  ld a, [PLAYER_WORLD_Y]
  ld b, a

  ret

resetPlayerMovement:
  ; reset player next y, x
  ld a, [PLAYER_WORLD_Y]
  ld [PLAYER_NEXT_WORLD_Y], a
  ld a, [PLAYER_WORLD_X]
  ld [PLAYER_NEXT_WORLD_X], a

  ret

; @return bc - player next y, x
getNextWorldPosition:
  ld a, [PLAYER_NEXT_WORLD_X]
  ld c, a
  ld a, [PLAYER_NEXT_WORLD_Y]
  ld b, a

  ret

getLeftWorldPosition:
  ld a, [PLAYER_WORLD_X]
  dec a ; intended move
  ld c, a
  ld a, [PLAYER_WORLD_Y]
  ld b, a

  ret

getRightWorldPosition:
  ld a, [PLAYER_WORLD_X]
  inc a ; intended move
  ld c, a
  ld a, [PLAYER_WORLD_Y]
  ld b, a

  ret

getUpWorldPosition:
  ld a, [PLAYER_WORLD_X]
  ld c, a
  ld a, [PLAYER_WORLD_Y]
  dec a ; intended move
  ld b, a

  ret

getDownWorldPosition:
  ld a, [PLAYER_WORLD_X]
  ld c, a
  ld a, [PLAYER_WORLD_Y]
  inc a ; intended move
  ld b, a

  ret


; @TODO for movement we want it to feel smooth
; so if the player was pressing down left
; and then they rolled their thumb onto down
; we want to be able to see "last frame we saw left
; but this frame we see left and down, so we will
; interpret this as down"
; for now though left > right > up > down
;
; while the player is walking around, we want to
; interpret their direction pad as movement
doPlayerMovement:
  ; if there is no input bail
  ld a, [_PAD]
  and a
  ret z

  ; if there is no relevant input bail
  ld a, [_PAD]
  and UP | RIGHT | LEFT | DOWN
  ret z

  ; now we dispatch actions based on the input

  ld a, [_PAD]
  and RIGHT
  ld b, PLAYER_MOVE_RIGHT
  jr nz, .done

  ld a, [_PAD]
  and LEFT
  ld b, PLAYER_MOVE_LEFT
  jr nz, .done ; move left

  ld a, [_PAD]
  and UP
  ld b, PLAYER_MOVE_UP
  jr nz, .done ; move up

  ld a, [_PAD]
  and DOWN
  ld b, PLAYER_MOVE_DOWN
  jr nz, .done ; move down

  ret
.done

  call recordMovement

  ret

/** movement including checking for collision and events */

/** to check for collision or events we need the metatile number
 * from the player x, y 
 * then we check the 2 highest bits against a table:

 * 00 EVENT (PASSABLE OVER) (nor)
 * 10 PASSABLE OVER (or)
 * 01 PASSABLE UNDER (or)
 * 11 UNPASSABLE (xor)
 * 
 */

/** the player tried to move off the world
 * @param bc - y, x of next position
 * @param hl - map
 * @return nz - yes, out of bounds (collision)
 */
checkForOutOfBounds:
  ld a, [hl] ; get y
  dec a ; height - 1

  ; since b is in the range 0 - 127
  ; if y is < 0 it will be a big int like 255
  ; if y is > b then it will also be bigger than b :D 
  cp b ; 0 < y < upper
  jr c, .outOfBounds

  inc hl
  ld a, [hl] ; get x
  dec hl
  dec a ; height - 1

  cp c ; 0 < x < upper
  jr c, .outOfBounds

  cp a ; set z

  ret
.outOfBounds
  or a, 1 ; set nz
  ret

; @param a - metatile
; @return nz - collision
checkForCollision:
  ld b, a
  call getCurrentMapTilesetAttributes

  ld a, b
  call addAToHL
  ld a, [hl]
  and a, UNPASSABLE

  ret

moveLeft:
  ld a, [PLAYER_WORLD_X]
  dec a
  ld [PLAYER_NEXT_WORLD_X], a

  ret

moveRight:
  ld a, [PLAYER_WORLD_X]
  inc a
  ld [PLAYER_NEXT_WORLD_X], a

  ret

moveUp:
  ld a, [PLAYER_WORLD_Y]
  dec a
  ld [PLAYER_NEXT_WORLD_Y], a

  ret

moveDown:
  ld a, [PLAYER_WORLD_Y]
  inc a
  ld [PLAYER_NEXT_WORLD_Y], a

  ret

; @param bc - y, x position
; @param hl - map
; @return a - metatile
worldPositionToMetaTile: 
  call getMapData
  call seekIndex
  ld a, [hl]

  bit 0, c ; is x even or odd
  jp z, .even

.odd
  and a, %00001111
  ret
.even
  and a, %11110000
  srl a
  srl a
  srl a
  srl a

  ret

ENDC	; end definition of player movement file