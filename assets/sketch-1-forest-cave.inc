
IF !DEF(SKETCH_1_FOREST_CAVE_INC)
SKETCH_1_FOREST_CAVE_INC = 1

Section "Sketch_1_forest_cave", ROMX, BANK[1]
Sketch_1_forest_cave:
  db 18, 20, 
  db HIGH(Sketch_1_forest_caveAutoEvents), LOW(Sketch_1_forest_caveAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_forest_caveBumpEvents), LOW(Sketch_1_forest_caveBumpEvents)
  db HIGH(Sketch_1_forest_caveEntities), LOW(Sketch_1_forest_caveEntities)
  db $22, $22, $22, $22, $44, $22, $22, $22, $22, $22, 
  db $22, $23, $33, $33, $42, $22, $22, $22, $22, $22, 
  db $22, $30, $00, $04, $43, $22, $33, $32, $22, $22, 
  db $22, $30, $f0, $05, $03, $33, $00, $03, $22, $22, 
  db $22, $30, $80, $44, $00, $00, $0c, $03, $22, $22, 
  db $22, $30, $00, $43, $a3, $33, $00, $03, $22, $22, 
  db $22, $23, $33, $43, $62, $22, $33, $32, $22, $22, 
  db $22, $22, $22, $42, $62, $22, $22, $22, $22, $22, 
  db $44, $44, $44, $42, $62, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $62, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $23, $a3, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $30, $00, $32, $22, $22, $22, $22, 
  db $22, $22, $22, $30, $d0, $32, $22, $22, $22, $22, 
  db $22, $22, $22, $30, $00, $32, $22, $22, $22, $22, 
  db $22, $22, $22, $23, $33, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 

Sketch_1_forest_caveAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_forest_caveBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  EndList

Sketch_1_forest_caveEntities:
  ret

ENDC