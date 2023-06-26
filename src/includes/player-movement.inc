
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

; a table for each direction so that we can just call hl + bc
; to perform all the effects of movement

SECTION "PLAYER_MOVE_HANDLERS", ROM0, ALIGN[3]
PLAYER_MOVE_HANDLERS:
  ; we need this no op because the movement enum starts at 1
  PLAYER_MOVE_HANDLERS.NO_OP: dw handleMoveRight
  PLAYER_MOVE_HANDLERS.RIGHT: dw handleMoveRight
  PLAYER_MOVE_HANDLERS.LEFT: dw handleMoveLeft
  PLAYER_MOVE_HANDLERS.UP: dw handleMoveUp
  PLAYER_MOVE_HANDLERS.DOWN: dw handleMoveDown

handleMoveLeft:
  call moveLeft
  call fillVRAMAddressesForLeftColumn
  call enableMapDrawColumn
  call fillLeftColumnTileData

  ret

handleMoveRight:
  call moveRight
  call fillVRAMAddressesForRightColumn
  call enableMapDrawColumn
  call fillRightColumnTileData

  ret

handleMoveUp:
  call moveUp
  call fillVRAMAddressesForTopRow
  call enableMapDrawRow
  call fillTopRowTileData

  ret

handleMoveDown:
  call moveDown
  call fillVRAMAddressesForBottomRow
  call enableMapDrawRow
  call fillBottomRowTileData

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

/** the player can't move here */
checkForCollision:
  ret

/** the player has triggered an auto event */
checkForAutoEvent:
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
