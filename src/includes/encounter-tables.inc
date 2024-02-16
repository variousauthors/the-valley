IF !DEF(ENCOUNTER_TABLES)
ENCOUNTER_TABLES = 1

SECTION "ENCOUNTER_TABLES", WRAM0

CURRENT_ENCOUNTER_TABLE_LOW_BYTE: ds 2

/** aligned to the size of an encounter */
SECTION "EncounterStats", ROM0, ALIGN[2]

BYTES_PER_ENCOUNTER_STAT EQU 2

EncounterStats:
EncounterOne:
  ; HP, ATT, DEF, XP
  db 10, 6, 2, 5

SECTION "EncounterTables", ROM0

; as a prototype lets switch between the two encounter tables
; when the player steps on the boat

/** each encounter table is a list of indexes 
 * into the Encounter Stats above*/
OverworldEncounters:
  db 0, 0, 0, 0, 0, 0, 0, 0
  db 0, 0, 0, 0, 0, 0, 0, 0

getCurrentEncounterTable:
  ret

setCurrentEncounterTable:
  ret

; roll randomly on the table
; return a pointer to an encounter
; stat block
getEncounter:
  ld hl, EncounterStats

  ret

ENDC
