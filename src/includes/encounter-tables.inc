IF !DEF(ENCOUNTER_TABLES)
ENCOUNTER_TABLES = 1

SECTION "ENCOUNTER_TABLES", WRAM0

; pointer to the encounter table 
EVENT_ENCOUNTER_TABLE_LOW_BYTE: ds 1
EVENT_ENCOUNTER_TABLE_HIGH_BYTE: ds 1
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
/* @TODO I want to add one more level of abstraction here 
 * rather than referencing the sprite directly this can
 * be an index into the sprite table, so that we can have
 * palette swaps, give each entry a name instead 
 * of "monster zero" etc... */
OverworldEncounterSprites:
  db MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, 
  db MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, 

RightSideBridgeEncounterSprites:
  db MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO
  db MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO

/*

ENCOUNTER TABLE LOGIC

- each map has an encounter table
- the overworld is divided into encounter tables by region
- events can set the encounter table

getCurrentEncounterTable accounts for all of this

it calls
- getEventEncounterTable (set by setEventEncounterTable, formerly "getCurrentEncounterTable")
- if there is none (pointer is 0), it calls "getMap"
- if the map is not overworld, use the encounter table in the metadata
- if the map is overworld, use determine the region, and use the regional encounter table

Currently encounter tables are 16 bytes but I think we should have them be 4 bytes now
I will go check the DQ dungeon encounter tables... yeah DQ gets away with 20 tables or 5 bytes
each so I think that's good. DQ divides the world into 8x8 squares and the overworld is 128x128

they have a grid of nibbles defining which encounters are in each region so they first
convert y,x into this nibble position thing and then each nibble is an index into the
list of encounter tables of which there are as many as 16

convert y,x world position to encounter region position
y * 4 + x to index into it, but we are using nibbles
so divide x / 2 to see if we need the left or right nibble
check out how we did this in the map code


*/

/** gets the encounter table:
 - if there is an event encounter table, returns that
 - otherwise, if we are in the overworld
 - it returns the regional encounter table 
 - otherwise, it returns the map encounter table 
*/
; @return hl - the encounter table
getCurrentEncounterTable:
  call getEventEncounterTable

  ; check for null
  ld a, 0
  add a, l
  add a, h
  or a

  ret nz

  ; otherwise use map
  ld hl, OverworldEncounters

  ret

; @return hl - the encounter table
getEventEncounterTable:
  ld hl, EVENT_ENCOUNTER_TABLE_LOW_BYTE

  ; dereference the pointer
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ret

/*
The event encounter table is set when the player
hits an event, like a choke point or crossing a bridge
and it overrides the ambient tables.
It is initially NULL
*/
initEventEncounterTable:
  ld hl, EVENT_ENCOUNTER_TABLE_LOW_BYTE
  ld a, 0
  ld [hl+], a
  ld a, 0
  ld [hl], a

  ret

; @param de - address of high byte of table pointer
setEventEncounterTable:
  ; set the event encounter table
  ld hl, EVENT_ENCOUNTER_TABLE_HIGH_BYTE
  ld a, [de]
  ld [hl], a

  inc de
  ld hl, EVENT_ENCOUNTER_TABLE_LOW_BYTE
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
