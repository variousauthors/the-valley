IF !DEF(PLAYER_INC)
PLAYER_INC = 1

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

ENDC