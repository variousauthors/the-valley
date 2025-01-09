
IF !DEF(SKETCH_1_START_SOUTH_INC)
SKETCH_1_START_SOUTH_INC = 1

Section "Sketch_1_start_south", ROMX, BANK[1]
  db NO_BOUNDS | NO_ENCOUNTERS
Sketch_1_start_south:
  db 9, 10, 
  db HIGH(Sketch_1_start_southAutoEvents), LOW(Sketch_1_start_southAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_start_southBumpEvents), LOW(Sketch_1_start_southBumpEvents)
  db HIGH(Sketch_1_start_southEntities), LOW(Sketch_1_start_southEntities)
  db $22, $22, $2a, $0a, $22, 
  db $22, $22, $2a, $0a, $22, 
  db $2a, $aa, $2a, $0a, $22, 
  db $a0, $00, $a0, $00, $a2, 
  db $a0, $70, $00, $00, $0a, 
  db $a0, $f0, $00, $01, $0a, 
  db $a0, $00, $00, $10, $a2, 
  db $2a, $00, $00, $0a, $22, 
  db $22, $aa, $aa, $a2, $22, 

Sketch_1_start_southAutoEvents:
  AllocateTransportEvent 0, 6, HIGH(Overworld), LOW(Overworld), 14, 91
  EndList

Sketch_1_start_southBumpEvents:
  AllocateCheckpointEvent 5, 2, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 4, 2, HIGH(StartSouth), LOW(StartSouth)
  EndList

Sketch_1_start_southEntities:
  ret

ENDC