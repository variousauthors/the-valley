IF !DEF(BOAT_INC)
BOAT_INC = 1

SECTION "BOAT_STATE", WRAM0

BOAT_START_Y EQU 87
BOAT_START_X EQU 47

; world position
BOAT_WORLD_X: ds 1
BOAT_SUB_X: ds 1 ; 1/16th meta tile
BOAT_WORLD_Y: ds 1
BOAT_SUB_Y: ds 1
BOAT_NEXT_WORLD_X: ds 1
BOAT_NEXT_WORLD_SUB_X: ds 1 ; this is 2 bytes so that we can use the same pixelDistance call back, but in practice it is always zero
BOAT_NEXT_WORLD_Y: ds 1
BOAT_NEXT_WORLD_SUB_Y: ds 1

BOAT_SPRITE_TILES: ds 4

SECTION "BoatState", ROM0

initBoat:
  ; initial position
  ld hl, BOAT_WORLD_X
  ld a, BOAT_START_X
  ld [hl], a
  ld hl, BOAT_NEXT_WORLD_X
  ld [hl], a

  ld hl, BOAT_WORLD_Y
  ld a, BOAT_START_Y
  ld [hl], a
  ld hl, BOAT_NEXT_WORLD_Y
  ld [hl], a

  ; init boat sprite tiles
  ld hl, BOAT_SPRITE_TILES
  ld a, 8
  ld [hl+], a
  ld a, 9
  ld [hl+], a
  ld a, 10
  ld [hl+], a
  ld a, 11
  ld [hl+], a

  ret

updateBoatPosition:
  ld hl, BOAT_WORLD_X
  ld a, [PLAYER_WORLD_X]
  ld [hl], a
  ld hl, BOAT_NEXT_WORLD_X
  ld [hl], a

  ld hl, BOAT_WORLD_Y
  ld a, [PLAYER_WORLD_Y]
  ld [hl], a
  ld hl, BOAT_NEXT_WORLD_Y
  ld [hl], a

  ret

undrawBoat:
  ld a, BOAT_SPRITE_INDEX
  call undrawSprite

  ret

; @param bc - y, x in pixel distance from camera
drawBoat:
  ld hl, BOAT_SPRITE_TILES
  ld a, [hl]
  ld d, BOAT_SPRITE_INDEX
  call drawSprite
 
  ret

; @param bc - y, x world position to check
; @return z - if there was a boat in the position
checkForBoatEvent:
  ld a, [BOAT_WORLD_Y]
  cp b
  ret nz

  ld a, [BOAT_WORLD_X]
  cp c
  ret nz

  ret

; @return bc - y, x in world potision
getBoatWorldPosition:
  ld a, [BOAT_WORLD_X]
  ld c, a
  ld a, [BOAT_WORLD_Y]
  ld b, a

  ret

ENDC