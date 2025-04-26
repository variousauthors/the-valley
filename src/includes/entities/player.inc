IF !DEF(PLAYER_INC)
PLAYER_INC = 1

SECTION "PLAYER_STATE", WRAM0

PLAYER_START_Y EQU 2
PLAYER_START_X EQU 11
PLAYER_INITIAL_CHECKPOINT_Y EQU PLAYER_START_Y
PLAYER_INITIAL_CHECKPOINT_X EQU PLAYER_START_X
PLAYER_START_HP EQU 30
PLAYER_START_ATT EQU 4
PLAYER_START_DEF EQU 0
PLAYER_XP_PER_LEVEL EQU 4

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
  ; player should have ATT = 4 + LVL / 2
  ; and if they have not hit this target
  ; then their next level should not be
  ; doubled

  ; ATT | XP TARGET
  ;   4 | 4
  ;   5 | 8
  ;   6 | 12
  ; so basically their level is based on ATT stat
  ; and if they have not "leveled up" then don't
  ; charge more XP for the next level?
  ld a, [PLAYER_ATT]
  sub a, 3
  sla a
  sla a ; (ATT - 3) * 4 = TARGET XP
  ld [PLAYER_XP_TARGET], a

  ret

playerUpdateHP:
  ; experimenting with different curves
  ; hp goes up [2, 6]
  ld b, 0
  ld a, [Rand]
  and a, %00000011
  add a, 2
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

playerUpdateATT:
  ; 1 in 2 chance to buff ATT
  ld a, [Rand]
  and a, %00000001
  ld b, a

  ld a, [PLAYER_ATT]
  add a, b
  ld [PLAYER_ATT], a
  ret

playerUpdateDEF:
  ; ATT | DEF
  ;   4 | 0
  ;   8 | 1
  ;  16 | 2
  ; DEF = ATT / 8
  ; goes up every 4 levels
  ld a, [PLAYER_ATT]
  srl a
  srl a
  srl a
  ld [PLAYER_DEF], a

  ret

playerApplyLevel:
  call playerConsumeXP

  ; do update
  call playerUpdateHP
  call playerUpdateATT
  call playerUpdateDEF
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

  ; calculate next level target xp
  call playerCalculateNextXPTarget

  ; update BCD
  ld hl, PLAYER_XP_TARGET
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [PLAYER_XP_TARGET_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [PLAYER_XP_TARGET_BCD + 1], a

  ret

ENDC