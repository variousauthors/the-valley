IF !DEF(ENCOUNTER_TABLES)
ENCOUNTER_TABLES = 1

SECTION "ENCOUNTER_TABLES", WRAM0

; pointer to the encounter table 
CURRENT_ENCOUNTER_TABLE_LOW_BYTE: ds 1
CURRENT_ENCOUNTER_TABLE_HIGH_BYTE: ds 1
; index of the current encounter
CURRENT_ENCOUNTER_INDEX: ds 1

/** aligned to the size of an encounter */
SECTION "EncounterStats", ROM0, ALIGN[2]

BYTES_PER_ENCOUNTER_STAT EQU 4

EncounterStats:
  ;  hp att def xp
  db 7,   6,  2, 1 ; 0 ; 0 starby
  db 10,  6,  2, 5 ; 1
  db 50, 12,  6, 5 ; 2 ; harpy
  db 10,  6,  2, 5 ; 3
  db 50, 12,  6, 5 ; 4 ; stone warrior
  db 10,  6,  2, 5 ; 5
  db 10,  6,  2, 5 ; 6
  db 5,   8,  1, 1 ; 7 ; 0 gnome
  db 10,  6,  2, 5 ; 8
  db 10,  6,  2, 5 ; 9
  db 10,  6,  2, 5 ; A
  db 10,  6,  2, 5 ; B
  db 10,  6,  2, 5 ; C
  db 10,  6,  2, 5 ; D

SECTION "EncounterTables", ROM0

; as a prototype lets switch between the two encounter tables
; when the player steps on the boat

/** each encounter table is a list of indexes 
 * into the Encounter Stats above*/
OverworldEncounters:
  db $0, $0, $0, $0, $0, $0, $0, $0
  db $7, $7, $7, $7, $7, $7, $7, $7

MountainPassEncounters:
  db $2, $2, $2, $2, $2, $2, $2, $2
  db $4, $4, $4, $4, $4, $4, $4, $4

RightSideBridgeEncounters:
  db 0, 0, 0, 0, 0, 0, 0, 0
  db 0, 0, 0, 0, 0, 0, 0, 0

/** the sprites for an encounter region are
 * tiles from the master graphics */
/** when we load an encounter table
 * we should call loadTileData just like
 * we do for main passing in the correspondig
 * encounter sprites */
/* this table only instructs what to load into VRAM
 * to get the index of the sprite for the current
 * encounter we still use OverworldEncounter table
 * above **/
/* @TODO implement this */
OverworldEncounterSprites:
  db MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, 
  db MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, 

RightSideBridgeEncounterSprites:
  db MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO
  db MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO

; @return hl - the encounter table
getCurrentEncounterTable:
  ld hl, CURRENT_ENCOUNTER_TABLE_LOW_BYTE

  ; dereference the pointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ret

initCurrentEncounterTable:
  ld hl, CURRENT_ENCOUNTER_TABLE_LOW_BYTE
  ld a, LOW(OverworldEncounters)
  ld [hl+], a
  ld a, HIGH(OverworldEncounters)
  ld [hl], a

  ret

; @param de - address of high byte of table pointer
setCurrentEncounterTable:
  ; set the current encounter table
  ld hl, CURRENT_ENCOUNTER_TABLE_HIGH_BYTE
  ld a, [de]
  ld [hl], a

  inc de
  ld hl, CURRENT_ENCOUNTER_TABLE_LOW_BYTE
  ld a, [de]
  inc de
  ld [hl], a

  ret

; @param a - index of current encounter 0 - 15
setCurrentEncounterIndex:
  ld [CURRENT_ENCOUNTER_INDEX], a
  ret

; @return a - current encounter index 0 - 15
getCurrentEncounterIndex:
  ld a, [CURRENT_ENCOUNTER_INDEX]
  ret

getCurrentEncounterId:
  call getCurrentEncounterTable
  call getCurrentEncounterIndex

  ; add a to hl to get the encounter
  ld d, 0
	ld e, a
	add hl, de

  ld a, [hl] ; now we have the encounter id

  ret

; @return hl - address of current encounter stats
getCurrentEncounterStats:
  call getCurrentEncounterId

  ; encounter stats are 4 bytes so index * 4
  sla a
  sla a ; index -> offset

  ld hl, EncounterStats

  ; add a to hl to get the encounter stats
  ld d, 0
	ld e, a
	add hl, de

  ret

ENCOUNTER_TILE_BASE EQU 64

; @return a - index into VRAM
getCurrentEncounterSprite:
  call getCurrentEncounterId

  ; encounter stats are 4 bytes so index * 4
  sla a
  sla a ; index -> offset

  add a, ENCOUNTER_TILE_BASE ; shift over to the encounter sprites

  ret

ENDC
