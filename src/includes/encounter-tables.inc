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

; 16 encounters
EncounterStats:
  ;  hp att def xp
  db 7,   6,  2, 1 ; 0 starby
  db 10,  6,  2, 5 ; 1 snack
  db 50, 12,  6, 5 ; 2 angel
  db 10,  6,  2, 5 ; 3 stalker
  db 50, 12,  6, 5 ; 4 imp
  db 10,  6,  2, 5 ; 5 warrior
  db 10,  6,  2, 5 ; 6 witch
  db 5,   8,  1, 1 ; 7 gnome
  db 10,  6,  2, 5 ; 8 shrieker 
  db 10,  6,  2, 5 ; 9 lemure 
  db 10,  6,  2, 5 ; A bones 
  db 10,  6,  2, 5 ; B yeller 
  db 10,  6,  2, 5 ; C slug boss
  db 10,  6,  2, 5 ; D slug 
  db 10,  6,  2, 5 ; E diver
  db 10,  6,  2, 5 ; F ???? add a "glitch" as the last boss, maybe rotate it's sprite every few ticks

SECTION "EncounterTables", ROM0

; as a prototype lets switch between the two encounter tables
; when the player steps on the boat

ENCOUNTER_TABLE_LENGTH EQU 4
ENCOUNTER_TABLE_MASK EQU %00000011

/** each encounter table is a list of indexes 
 * into the Encounter Stats above*/
OverworldEncounters:
  db $0, $0, $7, $7

MountainPassEncounters:
  db $2, $2, $4, $4

RightSideBridgeEncounters:
  db $1, $1, $5, $5

/** based on the player's y,x they will be in one of these
 * grid cells, 8 x 8 with each region being 16x16 tiles */
/** 
 * @TODO this is 64 bytes but they can just be nibbles 
 * it's not really a big deal though 32 bytes */
OverworldRegions:
  db $0, $0, $0, $0, $0, $0, $0, $0
  db $0, $0, $0, $0, $0, $0, $0, $0
  db $0, $0, $0, $0, $0, $0, $0, $0
  db $0, $0, $0, $0, $0, $0, $0, $0
  db $0, $0, $0, $0, $0, $0, $0, $0
  db $0, $0, $1, $9, $0, $0, $0, $0
  db $0, $0, $2, $8, $0, $0, $0, $0
  db $0, $6, $4, $7, $0, $0, $0, $0

/** up to 16 encounter tables
 * these need to be bytes since presumably 
 * we will have more than 16 monsters,
 * even if some of them are "palette swaps" */
/**
 * Oh also, in Valentino style game, these
 * are really more like the probability of
 * encountering one of two possible monsters
 */
RegionalEncounterTables:
  db $0, $0, $0, $0 ; starby, starby, starby, yeller         - starting peninsula
  db $1, $1, $0, $0 ; starby, yeller, yeller, gnome - region around the first cave
  db $1, $1, $2, $2 ; gnome, gnome, lemure, lemure - first cave
  db $3, $3, $3, $4 ; big forest
  db $3, $4, $4, $4 ; cave to the island
  db $5, $5, $5, $5 ; island on the left
  db $6, $6, $7, $7 ; swamp
  db $8, $8, $7, $9 ; final area
  db $9, $9, $9, $9 ; tower F1

; 0 starby
; 1 snack
; 2 angel
; 3 stalker
; 4 imp
; 5 warrior
; 6 witch
; 7 gnome
; 8 shrieker 
; 9 lemure 
; A bones 
; B yeller 
; C slug boss
; D slug 
; E diver
; F ???? add a "glitch" as the last boss, maybe rotate it's sprite every few ticks

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
/** @TODO this is not actually used yet!*/
/* @TODO I want to add one more level of abstraction here 
 * rather than referencing the sprite directly this can
 * be an index into the sprite table, so that we can have
 * palette swaps, give each entry a name instead 
 * of "monster zero" etc... */
/*
OverworldEncounterSprites:
  db MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, 
  db MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, MONSTER_SPRITE_SEVEN, 

RightSideBridgeEncounterSprites:
  db MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO
  db MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO, MONSTER_SPRITE_ZERO
*/

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
  call getCurrentMap
  call isOverworld
  jp nz, .overworld

  call getMapEncounterTableFromMetadata
  ret

.overworld
  call getOverworldEncounterTable

  ret

; @return hl - an encounter table
getOverworldEncounterTable:
  call getWorldPosition
  ld a, b
  srl a
  srl a
  srl a
  srl a ; divide by 16, a in [0, 8] (to index the row)

  ; but each row is 8 bytes so we go back up
  sla a
  sla a
  sla a ; multiply by 8 to jump to the row

  ld hl, OverworldRegions
  call addAToHL
  
  ld a, c ; now do it for x
  srl a
  srl a
  srl a
  srl a ; divide by 16, a in [0, 8] (to index the col)

  call addAToHL

  ld a, [hl] ; now we have the index of the encounter table for this region

  sla a
  sla a ; x4 to advance to the correct table

  ld hl, RegionalEncounterTables
  call addAToHL

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

; @param a - index of current encounter
setCurrentEncounterIndex:
  ld [CURRENT_ENCOUNTER_INDEX], a
  ret

; @return a - current encounter index
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
