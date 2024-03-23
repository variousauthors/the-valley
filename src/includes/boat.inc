IF !DEF(BOAT_INC)
BOAT_INC = 1

SECTION "BOAT_STATE", WRAM0

BOAT_START_Y EQU 107
BOAT_START_X EQU 50

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
  ld a, 0
  ld hl, Sprites + (19 * 4)
  ld [hl+], a
  ld [hl+], a
  ld [hl+], a
  ld [hl], a
  ld hl, Sprites + (24 * 4)
  ld [hl+], a
  ld [hl+], a
  ld [hl+], a
  ld [hl], a
  ld hl, Sprites + (4 * 4)
  ld [hl+], a
  ld [hl+], a
  ld [hl+], a
  ld [hl], a
  ld hl, Sprites + (1 * 4)
  ld [hl+], a
  ld [hl+], a
  ld [hl+], a
  ld [hl], a

  ret

; @param bc - y, x in pixel distance from camera
drawBoat:

  ; get the first free sprite from the pool
  ; we'll have to decide on how we're going to do this
  ; maybe an entity will request some sprites when it
  ; first joins the scene, and then those don't need to
  ; be contiguous
  ; yeah, I'm going to pretend that's happening
  ; so below I'm picking "random" positions in OAM for the
  ; sprite to go

  ld hl, BOAT_SPRITE_TILES

  ; -- ONE SPRITE TILE --
  ld de, Sprites + (19 * 4) ; 8 sprites for the two animation frames, each 4 bytes per sprite
  ld a, 16
  add a, b ; player position y
  ld [de], a
  inc de
  ld a, 8
  add a, c ; player position x
  ld [de], a
  inc de

  ld a, [hl] ; get the tile
  ld [de], a ; draw
  inc de

  ; palette 1
  ld a, %00010000 ; attr
  ld [de], a
  inc de

  inc hl

  ; -- THE NEXT SPRITE TILE --
  ld de, Sprites + (24 * 4)
  ld a, 16 + 8
  add a, b ; player position y
  ld [de], a
  inc de
  ld a, 8
  add a, c ; player position x
  ld [de], a
  inc de

  ld a, [hl] ; get the tile
  ld [de], a ; draw
  inc de

  ; palette 1
  ld a, %00010000 ; attr
  ld [de], a
  inc de

  inc hl

  ; -- ANOTHER SPRITE TILE --
  ld de, Sprites + (4 * 4)
  ld a, 16
  add a, b ; player position y
  ld [de], a
  inc de
  ld a, 8 + 8
  add a, c ; player position x
  ld [de], a
  inc de

  ld a, [hl] ; get the tile
  ld [de], a ; draw
  inc de

  ; palette 1
  ld a, %00010000 ; attr
  ld [de], a
  inc de

  inc hl

  ; -- THE LAST SPRITE TILE --
  ld de, Sprites + (1 * 4)
  ld a, 16 + 8
  add a, b ; player position y
  ld [de], a
  inc de
  ld a, 8 + 8
  add a, c ; player position x
  ld [de], a
  inc de

  ld a, [hl] ; get the tile
  ld [de], a ; draw
  inc de

  ; palette 1
  ld a, %00010000 ; attr
  ld [de], a
  inc de

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