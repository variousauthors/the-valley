IF !DEF(PLAYER_INC)
PLAYER_INC = 1

SECTION "PLAYER_STATE", WRAM0

PLAYER_START_Y EQU 75
PLAYER_START_X EQU 48
PLAYER_START_HP EQU 40
PLAYER_START_ATT EQU 4
PLAYER_START_DEF EQU 2

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
  ld a, 10
  ld [PLAYER_XP_TARGET], a

  ; init BCDs
  ld hl, PLAYER_CURRENT_HP
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [PLAYER_CURRENT_HP_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [PLAYER_CURRENT_HP_BCD + 1], a

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

  ; load player sprite tiles into VRAM
  ld hl, SpriteTileset
  ld b, SPRITE_TILES_COUNT ; 8 sprite tiles
  ld de, SPRITE_TILES
  call loadTileData

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

ENDC