IF !DEF(ELDER_INC)
ELDER_INC = 1

SECTION "ELDER_STATE", WRAM0

ELDER_SIZE EQU 8

; world position
ELDER_STATE:
ELDER_WORLD_X: ds 1
ELDER_SUB_X: ds 1 ; 1/16th meta tile
ELDER_WORLD_Y: ds 1
ELDER_SUB_Y: ds 1
ELDER_NEXT_WORLD_X: ds 1
ELDER_NEXT_WORLD_SUB_X: ds 1 ; this is 2 bytes so that we can use the same pixelDistance call back, but in practice it is always zero
ELDER_NEXT_WORLD_Y: ds 1
ELDER_NEXT_WORLD_SUB_Y: ds 1

; this is constant, not part of the state
; this is the location where we record which tiles
; make up this sprite (this is NOT the VRAM location)
ELDER_SPRITE_TILES: ds 4

SECTION "ElderState", ROM0

; @param bc - y,x
initElder:
  call resetElder

  ; initial position
  ld hl, ELDER_WORLD_X ; if this is zero, we will not draw the elder
  ld a, c
  ld [hl], a
  ld hl, ELDER_NEXT_WORLD_X
  ld [hl], a

  ld hl, ELDER_WORLD_Y
  ld a, b
  ld [hl], a
  ld hl, ELDER_NEXT_WORLD_Y
  ld [hl], a

  ; init elder sprite tiles
  ld hl, ELDER_SPRITE_TILES
  ld a, 24
  ld [hl+], a
  ld a, 25
  ld [hl+], a
  ld a, 26
  ld [hl+], a
  ld a, 27
  ld [hl+], a

  ret

resetElder:
  ld hl, ELDER_STATE
  ld a, ELDER_SIZE ; number of bytes to wipe
  call resetEntity

  ret

; @return z - elder is not initialized
shouldDrawElder:
  ld a, [ELDER_STATE]
  or a

  ret

undrawElder:
  ld a, ELDER_SPRITE_INDEX
  call undrawSprite

  ret

; @param bc - y, x in pixel distance from camera
drawElder:
  call shouldDrawElder
  ret z

  ld a, [ELDER_WORLD_Y]
  ld b, a
  ld a, [ELDER_WORLD_X]
  ld c, a
  call cameraCullEntity
  jr c, .skipDraw

  ; draw the elder stationary
  ld hl, ELDER_WORLD_Y
  ld de, CAMERA_WORLD_Y
  call pixelDistance
  ld b, a

  ld hl, ELDER_WORLD_X
  ld de, CAMERA_WORLD_X
  call pixelDistance
  ld c, a

  ld hl, ELDER_SPRITE_TILES
  ld a, [hl]
  ld d, ELDER_SPRITE_INDEX

  call drawSprite
.skipDraw
 
  ret

; @return bc - y, x in world potision
getElderWorldPosition:
  ld a, [ELDER_WORLD_X]
  ld c, a
  ld a, [ELDER_WORLD_Y]
  ld b, a

  ret

ENDC