IF !DEF(ELDER_INC)
ELDER_INC = 1

SECTION "ELDER_STATE", WRAM0

ELDER_START_Y EQU 24
ELDER_START_X EQU 46
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
ELDER_SPRITE_TILES: ds 4

SECTION "ElderState", ROM0

initElder:
  ld hl, ELDER_STATE
  ld b, ELDER_SIZE ; number of bytes to wipe
  call resetEntity

  ; initial position
  ld hl, ELDER_WORLD_X ; if this is zero, we will not draw the elder
  ld a, ELDER_START_X
  ld [hl], a
  ld hl, ELDER_NEXT_WORLD_X
  ld [hl], a

  ld hl, ELDER_WORLD_Y
  ld a, ELDER_START_Y
  ld [hl], a
  ld hl, ELDER_NEXT_WORLD_Y
  ld [hl], a

  ; init elder sprite tiles
  ld hl, ELDER_SPRITE_TILES
  ld a, 8
  ld [hl+], a
  ld a, 9
  ld [hl+], a
  ld a, 10
  ld [hl+], a
  ld a, 11
  ld [hl+], a

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

  ld hl, ELDER_SPRITE_TILES
  ld a, [hl]
  ld d, ELDER_SPRITE_INDEX
  call drawSprite
 
  ret

; @return bc - y, x in world potision
getElderWorldPosition:
  ld a, [ELDER_WORLD_X]
  ld c, a
  ld a, [ELDER_WORLD_Y]
  ld b, a

  ret

ENDC