IF !DEF(SOUTH_GROVE_EXIT_INC)
SOUTH_GROVE_EXIT_INC = 1

Section "SouthGroveExit", ROM0
  db NO_BOUNDS
SouthGroveExit:
  db 12, 12, 
  db HIGH(SouthGroveExitAutoEvents), LOW(SouthGroveExitAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(RegionalEncounterTables + 4), LOW(RegionalEncounterTables + 4), 
  db HIGH(SouthGroveExitBumpEvents), LOW(SouthGroveExitBumpEvents)
  db $11, $11, $11, $11, $61, $11, 
  db $11, $b1, $0b, $b1, $11, $61, 
  db $1b, $66, $60, $61, $11, $11, 
  db $1b, $0d, $66, $06, $b1, $11, 
  db $11, $16, $06, $66, $b6, $11, 
  db $61, $16, $60, $11, $b6, $61, 
  db $11, $b1, $c1, $1b, $66, $41, 
  db $11, $11, $c6, $66, $64, $41, 
  db $11, $11, $c1, $44, $44, $41, 
  db $11, $61, $c0, $64, $46, $41, 
  db $11, $66, $66, $60, $61, $11, 
  db $11, $11, $c1, $11, $11, $11, 

SouthGroveExitAutoEvents:
  /** entrance */
  AllocateTransportEvent 11, 4, HIGH(Overworld), LOW(Overworld), 33, 41
  AllocateTransportEvent 3, 3, HIGH(GroveShortcut), LOW(GroveShortcut), 3, 0

  EndList

SouthGroveExitBumpEvents:
  EndList

ENDC