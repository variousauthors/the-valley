IF !DEF(SOUTH_GROVE_EXIT_INC)
SOUTH_GROVE_EXIT_INC = 1

Section "SouthGroveExit", ROM0
  db NO_BOUNDS
SouthGroveExit:
  db 18, 20, 
  db HIGH(SouthGroveExitAutoEvents), LOW(SouthGroveExitAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(RegionalEncounterTables + 4), LOW(RegionalEncounterTables + 4), 
  db HIGH(SouthGroveExitBumpEvents), LOW(SouthGroveExitBumpEvents)
  db $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, $11, $11, $11, $66, $11, 
  db $11, $11, $1b, $10, $bb, $11, $11, $16, $06, $11, 
  db $11, $11, $b6, $66, $06, $11, $11, $06, $61, $11, 
  db $11, $11, $b0, $d6, $60, $6b, $11, $66, $61, $11, 
  db $11, $11, $11, $60, $66, $6b, $11, $60, $11, $11, 
  db $11, $16, $11, $66, $01, $1b, $11, $44, $66, $61, 
  db $11, $11, $1b, $1c, $11, $b1, $14, $44, $40, $61, 
  db $11, $11, $11, $1c, $11, $11, $64, $44, $46, $11, 
  db $11, $11, $11, $1c, $16, $64, $44, $44, $46, $11, 
  db $11, $11, $16, $1c, $06, $64, $64, $44, $61, $11, 
  db $11, $11, $16, $66, $66, $06, $64, $44, $61, $11, 
  db $11, $11, $16, $1c, $66, $66, $16, $66, $61, $11, 
  db $11, $11, $16, $6c, $06, $16, $61, $66, $61, $11, 
  db $11, $11, $11, $06, $61, $11, $66, $61, $11, $11, 
  db $11, $11, $11, $1c, $11, $11, $11, $11, $11, $11, 
  db $11, $11, $11, $1c, $11, $11, $11, $11, $11, $11, 

SouthGroveExitAutoEvents:
  /** entrance */
  AllocateTransportEvent 17, 7, HIGH(Overworld), LOW(Overworld), 33, 41
  AllocateTransportEvent 5, 6, HIGH(GroveShortcut), LOW(GroveShortcut), 3, 0

  EndList

SouthGroveExitBumpEvents:
  EndList

ENDC