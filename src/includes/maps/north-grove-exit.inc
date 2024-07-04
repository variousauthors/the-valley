IF !DEF(NORTH_GROVE_EXIT_INC)
NORTH_GROVE_EXIT_INC = 1

Section "NorthGroveExit", ROM0
  db NO_BOUNDS
NorthGroveExit:
  db 18, 20, 
  db HIGH(NorthGroveExitAutoEvents), LOW(NorthGroveExitAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(RegionalEncounterTables), LOW(RegionalEncounterTables), 
  db HIGH(NorthGroveExitBumpEvents), LOW(NorthGroveExitBumpEvents)
  db $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, 
  db $11, $11, $11, $16, $66, $11, $11, $11, $11, $11, 
  db $11, $11, $11, $66, $b6, $bb, $11, $11, $11, $11, 
  db $11, $11, $11, $61, $66, $0b, $66, $11, $11, $11, 
  db $11, $11, $10, $11, $66, $11, $66, $11, $11, $11, 
  db $11, $11, $66, $66, $06, $61, $16, $01, $11, $11, 
  db $11, $11, $66, $14, $44, $61, $66, $16, $11, $11, 
  db $11, $16, $06, $64, $44, $66, $61, $11, $66, $11, 
  db $11, $16, $61, $44, $41, $10, $16, $66, $16, $66, 
  db $11, $61, $61, $44, $11, $16, $66, $16, $11, $11, 
  db $11, $61, $06, $16, $11, $6b, $66, $10, $11, $11, 
  db $11, $61, $16, $11, $66, $66, $06, $16, $11, $11, 
  db $11, $61, $16, $61, $06, $6b, $61, $66, $11, $11, 
  db $11, $16, $60, $66, $66, $16, $bb, $61, $11, $11, 
  db $11, $11, $11, $66, $60, $61, $60, $11, $11, $11, 
  db $11, $11, $11, $11, $60, $66, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, $11, $11, $11, $11, $11, 

NorthGroveExitAutoEvents:
  /** entrance */
  AllocateTransportEvent 9, 19, HIGH(Overworld), LOW(Overworld), 31, 41
  AllocateTransportEvent 3, 3, HIGH(GroveShortcut), LOW(GroveShortcut), 0, 4

  EndList

NorthGroveExitBumpEvents:
  EndList

ENDC