IF !DEF(PLAYER_INC)
PLAYER_INC = 1

SECTION "PLAYER_STATE", WRAM0

PLAYER_START_Y EQU 4
PLAYER_START_X EQU 4
PLAYER_INITIAL_CHECKPOINT_Y EQU PLAYER_START_Y
PLAYER_INITIAL_CHECKPOINT_X EQU PLAYER_START_X
PLAYER_START_HP EQU 30
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

; the last place on the overworld where
; a player healed
PLAYER_CHECKPOINT_Y: ds 1
PLAYER_CHECKPOINT_X: ds 1
PLAYER_CHECKPOINT_MAP: ds 2

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

  ; initial checkpoint position
  call initPlayerCheckpoint

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

initPlayerCheckpoint:
  ld hl, PLAYER_CHECKPOINT_Y
  ld a, PLAYER_INITIAL_CHECKPOINT_Y
  ld [hl], a

  ld hl, PLAYER_CHECKPOINT_X
  ld a, PLAYER_INITIAL_CHECKPOINT_X
  ld [hl], a

  ld hl, PLAYER_CHECKPOINT_MAP
  ld a, HIGH(Start)
  ld [hl+], a
  ld a, LOW(Start)
  ld [hl], a

  ret

setPlayerCheckpoint:
  call getCurrentMap

  ld a, h
  ld [PLAYER_CHECKPOINT_MAP], a
  ld a, l
  ld [PLAYER_CHECKPOINT_MAP + 1], a

  call getWorldPosition

  ld hl, PLAYER_CHECKPOINT_Y
  ld a, b
  ld [hl], a

  ld hl, PLAYER_CHECKPOINT_X
  ld a, c
  ld [hl], a


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

playerApplyXP:
  ld a, [ENCOUNTER_XP]
  ld b, a
  ld a, [PLAYER_XP]
  add a, b
  ld [PLAYER_XP], a

  ret

; @return c - no we should not
playerShouldDoLevel:
  ld a, [PLAYER_XP_TARGET]
  ld b, a
  ld a, [PLAYER_XP]
  cp a, b

  ret

playerConsumeXP:
  ; subtract one level's worth of XP from the player
  ld a, [PLAYER_XP_TARGET]
  ld b, a
  ld a, [PLAYER_XP]
  sub a, b
  ld [PLAYER_XP], a

  ret

; targets: 5, 10, 15, 20, 25, 30, 35
; level x = 5 * ((n)(n + 1) / 2)
; handshake curve, 5xp, 15xp, 30xp, 50xp, 
playerCalculateNextXPTarget:
  ld b, PLAYER_XP_PER_LEVEL
  ld a, [PLAYER_XP_TARGET]
  add a, b
  ld [PLAYER_XP_TARGET], a 

  ret

playerUpdateHP:
  ; hp goes up (hp / 16) + ([0, 7])
  ld a, [PLAYER_MAX_HP]
  srl a
  srl a
  srl a
  srl a ; divide by 16
  ld b, a
  ld a, [Rand]
  and a, %00000111
  add a, b
  ld b, a

  ld a, [PLAYER_MAX_HP]
  call add255
  ld [PLAYER_MAX_HP], a

  ld a, [PLAYER_CURRENT_HP]
  call add255
  ld [PLAYER_CURRENT_HP], a
  ld [PLAYER_NEXT_CURRENT_HP], a

  ret

playerUpdateStats:
  ld a, [Rand]
  and a, %00000001
  ld b, a

  ld a, [PLAYER_ATT]
  add a, b
  ld [PLAYER_ATT], a

  ld a, [Rand]
  and a, %00000010
  sra a
  ld b, a

  ld a, [PLAYER_DEF]
  add a, b
  ; NO DEF INCREASE FOR NOW
  ; open ended it is too strong
  ; ld [PLAYER_DEF], a

  ret

playerApplyLevel:
  call playerConsumeXP

  ; calculate next level target xp
  call playerCalculateNextXPTarget

  ; update BCD
  ld hl, PLAYER_XP_TARGET
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [PLAYER_XP_TARGET_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [PLAYER_XP_TARGET_BCD + 1], a

  ; do update
  call playerUpdateHP
  call playerUpdateStats
  ; done updating

  ; we are just adding in the new HP above
  ; call playerFullHeal

  ; update BCD
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

  ret

ENDC