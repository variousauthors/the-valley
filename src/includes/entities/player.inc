IF !DEF(PLAYER_INC)
PLAYER_INC = 1

SECTION "PLAYER_STATE", WRAM0

PLAYER_START_Y EQU 6
PLAYER_START_X EQU 9
PLAYER_START_HP EQU 20
PLAYER_START_ATT EQU 4
PLAYER_START_DEF EQU 0
PLAYER_XP_PER_LEVEL EQU 5

; world position
PLAYER_WORLD_X: ds 1
PLAYER_SUB_X: ds 1 ; 1/16th meta tile
PLAYER_WORLD_Y: ds 1
PLAYER_SUB_Y: ds 1
PLAYER_NEXT_WORLD_X: ds 1
PLAYER_NEXT_WORLD_SUB_X: ds 1 ; this is 2 bytes so that we can use the same pixelDistance call back, but in practice it is always zero
PLAYER_NEXT_WORLD_Y: ds 1
PLAYER_NEXT_WORLD_SUB_Y: ds 1

PLAYER_MAX_HP: ds 1
PLAYER_MAX_HP_BCD: ds 2
PLAYER_CURRENT_HP: ds 1
PLAYER_CURRENT_SUB_HP: ds 1
PLAYER_NEXT_CURRENT_HP: ds 1
PLAYER_CURRENT_HP_BCD: ds 2

PLAYER_ATT: ds 1
PLAYER_ATT_BCD: ds 2
PLAYER_DEF: ds 1
PLAYER_DEF_BCD: ds 2
PLAYER_XP: ds 1
PLAYER_XP_SUB_HP: ds 1
PLAYER_NEXT_XP: ds 1 ; for animatine XP gain later
PLAYER_XP_BCD: ds 2

PLAYER_XP_TARGET: ds 1 ; next level
PLAYER_XP_TARGET_BCD: ds 2

PLAYER_SPRITE_TILES: ds 4

SECTION "Player", ROM0

initPlayer:
  ; initial plater stats
  ld a, PLAYER_START_HP
  ld [PLAYER_MAX_HP], a
  ld [PLAYER_CURRENT_HP], a
  ld [PLAYER_NEXT_CURRENT_HP], a
  ld a, PLAYER_START_ATT
  ld [PLAYER_ATT], a
  ld a, PLAYER_START_DEF
  ld [PLAYER_DEF], a
  ld a, 0
  ld [PLAYER_XP], a
  ld a, PLAYER_XP_PER_LEVEL
  ld [PLAYER_XP_TARGET], a

  ; init BCDs
  ld hl, PLAYER_MAX_HP
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [PLAYER_MAX_HP_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [PLAYER_MAX_HP_BCD + 1], a

  ld hl, PLAYER_CURRENT_HP
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [PLAYER_CURRENT_HP_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [PLAYER_CURRENT_HP_BCD + 1], a

  ld hl, PLAYER_XP_TARGET
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [PLAYER_XP_TARGET_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [PLAYER_XP_TARGET_BCD + 1], a

  ; initial position
  ld hl, PLAYER_WORLD_X
  ld a, PLAYER_START_X
  ld [hl], a
  ld hl, PLAYER_NEXT_WORLD_X
  ld [hl], a

  ld hl, PLAYER_WORLD_Y
  ld a, PLAYER_START_Y
  ld [hl], a
  ld hl, PLAYER_NEXT_WORLD_Y
  ld [hl], a

  ; init player sprite tiles
  ld hl, PLAYER_SPRITE_TILES
  ld a, 0
  ld [hl+], a
  ld a, 1
  ld [hl+], a
  ld a, 2
  ld [hl+], a
  ld a, 3
  ld [hl+], a

  ret

playerFullHeal:
  ld a, [PLAYER_MAX_HP]
  ld [PLAYER_CURRENT_HP], a
  ld [PLAYER_NEXT_CURRENT_HP], a

  ; recalc double dabble
  ld hl, PLAYER_CURRENT_HP
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [PLAYER_CURRENT_HP_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [PLAYER_CURRENT_HP_BCD + 1], a

  ret

undrawPlayer:
  ld a, PLAYER_SPRITE_INDEX
  call undrawSprite

  ret

; prepare a sprite using the player data
drawPlayer:

  ; get the first free sprite from the pool
  ; we'll have to decide on how we're going to do this
  ; maybe an entity will request some sprites when it
  ; first joins the scene, and then those don't need to
  ; be contiguous
  ; yeah, I'm going to pretend that's happening
  ; so below I'm picking "random" positions in OAM for the
  ; sprite to go

  ld hl, PLAYER_WORLD_Y
  ld de, CAMERA_WORLD_Y
  call pixelDistance
  ld b, a

  ld hl, PLAYER_WORLD_X
  ld de, CAMERA_WORLD_X
  call pixelDistance
  ld c, a

  ld hl, PLAYER_SPRITE_TILES

  ; animation
  call twoIn64Timer
  sla a
  sla a ; times 4 to get to the correct frame
  add a, [hl] ; get the tile

  ld d, PLAYER_SPRITE_INDEX
  call drawSprite

  ret

ENDC