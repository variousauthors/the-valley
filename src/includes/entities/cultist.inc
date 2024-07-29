IF !DEF(CULTIST_INC)
CULTIST_INC = 1

SECTION "CULTIST_STATE", WRAM0

CULTIST_SIZE EQU 8

; world position
CULTIST_STATE:
CULTIST_WORLD_X: ds 1
CULTIST_SUB_X: ds 1 ; 1/16th meta tile
CULTIST_WORLD_Y: ds 1
CULTIST_SUB_Y: ds 1
CULTIST_NEXT_WORLD_X: ds 1
CULTIST_NEXT_WORLD_SUB_X: ds 1 ; this is 2 bytes so that we can use the same pixelDistance call back, but in practice it is always zero
CULTIST_NEXT_WORLD_Y: ds 1
CULTIST_NEXT_WORLD_SUB_Y: ds 1

; this is constant, not part of the state
; this is the location where we store the tiles
; that make make up this sprite (this is NOT the VRAM location, or the OAM location)
CULTIST_SPRITE_TILES: ds 4

SECTION "CultistState", ROM0

; @param bc - y,x
initCultist:
  call resetCultist

  ; initial position
  ld hl, CULTIST_WORLD_X ; if this is zero, we will not draw the cultist
  ld a, c
  ld [hl], a
  ld hl, CULTIST_NEXT_WORLD_X
  ld [hl], a

  ld hl, CULTIST_WORLD_Y
  ld a, b
  ld [hl], a
  ld hl, CULTIST_NEXT_WORLD_Y
  ld [hl], a

  ; init cultist sprite tiles
  ld hl, CULTIST_SPRITE_TILES
  ld a, 16
  ld [hl+], a
  ld a, 17
  ld [hl+], a
  ld a, 18
  ld [hl+], a
  ld a, 19
  ld [hl+], a

  ret

resetCultist:
  ld hl, CULTIST_STATE
  ld a, CULTIST_SIZE ; number of bytes to wipe
  call resetEntity

  ret

; @return z - cultist is not initialized
shouldDrawCultist:
  ld a, [CULTIST_STATE]
  or a

  ret

undrawCultist:
  ld a, CULTIST_SPRITE_INDEX
  call undrawSprite

  ret

; @param bc - y, x in pixel distance from camera
drawCultist:
  call shouldDrawCultist
  ret z

  ld a, [CULTIST_WORLD_Y]
  ld b, a
  ld a, [CULTIST_WORLD_X]
  ld c, a
  call cameraCullEntity
  jr c, .skipDraw

  ; draw the cultist stationary
  ld hl, CULTIST_WORLD_Y
  ld de, CAMERA_WORLD_Y
  call pixelDistance
  ld b, a

  ld hl, CULTIST_WORLD_X
  ld de, CAMERA_WORLD_X
  call pixelDistance
  ld c, a

  ld hl, CULTIST_SPRITE_TILES
  ld a, [hl]
  ld d, CULTIST_SPRITE_INDEX

  call drawSprite
.skipDraw
 
  ret

; @return bc - y, x in world potision
getCultistWorldPosition:
  ld a, [CULTIST_WORLD_X]
  ld c, a
  ld a, [CULTIST_WORLD_Y]
  ld b, a

  ret

ENDC