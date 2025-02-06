
IF !DEF(SKETCH_1_START_INC)
SKETCH_1_START_INC = 1

Section "Sketch_1_start", ROMX, BANK[1]
  db NO_BOUNDS | NO_ENCOUNTERS
Start:
Sketch_1_start:
  db 9, 10, 
  db HIGH(Sketch_1_startAutoEvents), LOW(Sketch_1_startAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_startBumpEvents), LOW(Sketch_1_startBumpEvents)
  db HIGH(Sketch_1_startEntities), LOW(Sketch_1_startEntities)
  db $22, $aa, $aa, $aa, $22, 
  db $22, $a0, $00, $aa, $a2, 
  db $2a, $a0, $70, $00, $aa, 
  db $aa, $00, $f0, $00, $0a, 
  db $a0, $00, $00, $00, $0a, 
  db $a0, $01, $00, $00, $0a, 
  db $aa, $00, $00, $01, $0a, 
  db $aa, $a0, $00, $00, $aa, 
  db $2a, $aa, $a0, $aa, $a2, 

Sketch_1_startAutoEvents:
  AllocateTransportEvent 8, 5, HIGH(Overworld), LOW(Overworld), 56, 125
  EndList

Sketch_1_startBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 2, 4, HIGH(StartCave), LOW(StartCave)
  EndList

Sketch_1_startEntities:
  ret

ENDC