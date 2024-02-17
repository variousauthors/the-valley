IF !DEF(ENCOUNTER_TABLES)
ENCOUNTER_TABLES = 1

SECTION "ENCOUNTER_TABLES", WRAM0

; pointer to the encounter table 
CURRENT_ENCOUNTER_TABLE_LOW_BYTE: ds 2
; index of the current encounter
CURRENT_ENCOUNTER_INDEX: ds 1

/** aligned to the size of an encounter */
SECTION "EncounterStats", ROM0, ALIGN[2]

BYTES_PER_ENCOUNTER_STAT EQU 2

EncounterStats:
EncounterOne:
  ; HP, ATT, DEF, XP
  db 10, 6, 2, 5

EncounterTwo:
  ; HP, ATT, DEF, XP
  db 10, 6, 2, 5

SECTION "EncounterTables", ROM0

; as a prototype lets switch between the two encounter tables
; when the player steps on the boat

/** each encounter table is a list of indexes 
 * into the Encounter Stats above*/
OverworldEncounters:
  db 1, 0, 0, 0, 0, 0, 0, 0
  db 0, 0, 0, 0, 0, 0, 0, 0

/** the sprites for an encounter region are
 * tiles from the master graphics */
/** when we load an encounter table
 * we should call loadTileData just like
 * we do for main passing in the correspondig
 * encounter sprites */
OverworldEncounterSprites:
  db MONSTER_SPRITE_ONE, MONSTER_SPRITE_ZERO, 0, 0, 0, 0, 0, 0
  db 0, 0, 0, 0, 0, 0, 0, 0

getCurrentEncounterTable:
  ld hl, OverworldEncounters

  ret

setCurrentEncounterTable:
  ret

; @param a - index of current encounter 0 - 15
setCurrentEncounterIndex:
  ld [CURRENT_ENCOUNTER_INDEX], a
  ret

; @return a - current encounter index 0 - 15
getCurrentEncounterIndex:
  ld a, [CURRENT_ENCOUNTER_INDEX]
  ret

; @return hl - address of current encounter stats
getCurrentEncounterStats:
  call getCurrentEncounterIndex
  ld hl, EncounterStats

  ; encounter stats are 4 bytes so index * 4
  sla a
  sla a ; index -> offset

  add [hl]

  ret

ENCOUNTER_TILE_BASE EQU 64

; @return a - index into VRAM
getCurrentEncounterSprite:
  call getCurrentEncounterIndex

  ; advance to the index
  sla a
  sla a ; index -> offset

  add a, ENCOUNTER_TILE_BASE ; shift over to the encounter sprites

  ret

ENDC
