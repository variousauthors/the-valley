
IF !DEF(GENERIC_CLEARING_INC)
GENERIC_CLEARING_INC = 1

Section "Generic_clearing", ROMX, BANK[1]
Generic_clearing:
  db 11, 12, 
  db HIGH(Generic_clearingAutoEvents), LOW(Generic_clearingAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Generic_clearingBumpEvents), LOW(Generic_clearingBumpEvents)
  db HIGH(Generic_clearingEntities), LOW(Generic_clearingEntities)
  db $10, $00, $00, $00, $00, $00, 
  db $00, $10, $01, $00, $10, $10, 
  db $10, $01, $10, $13, $11, $01, 
  db $01, $00, $00, $00, $31, $00, 
  db $01, $30, $07, $00, $30, $10, 
  db $13, $00, $00, $00, $00, $00, 
  db $00, $07, $0f, $07, $00, $00, 
  db $01, $00, $00, $00, $00, $10, 
  db $00, $00, $00, $00, $01, $03, 
  db $01, $00, $10, $01, $00, $30, 
  db $01, $01, $00, $00, $11, $01, 

Generic_clearingAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Generic_clearingBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  EndList

Generic_clearingEntities:
  ret

ENDC