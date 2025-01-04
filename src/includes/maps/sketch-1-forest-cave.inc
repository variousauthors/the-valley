
IF !DEF(SKETCH_1_FOREST_CAVE_INC)
SKETCH_1_FOREST_CAVE_INC = 1

Section "Sketch_1_forest_cave", ROMX, BANK[1]
  db NO_BOUNDS | NO_ENCOUNTERS
Sketch_1_forest_cave:
  db 18, 20, 
  db HIGH(Sketch_1_forest_caveAutoEvents), LOW(Sketch_1_forest_caveAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_forest_caveBumpEvents), LOW(Sketch_1_forest_caveBumpEvents)
  db HIGH(Sketch_1_forest_caveEntities), LOW(Sketch_1_forest_caveEntities)
  db $22, $22, $22, $22, $44, $22, $22, $22, $22, $22, 
  db $22, $2a, $aa, $aa, $42, $22, $22, $22, $22, $22, 
  db $22, $a0, $00, $04, $4a, $22, $aa, $a2, $22, $22, 
  db $22, $a0, $f0, $05, $0a, $aa, $00, $0a, $22, $22, 
  db $22, $a0, $80, $44, $00, $00, $0c, $0a, $22, $22, 
  db $22, $a0, $00, $4a, $3a, $aa, $00, $0a, $22, $22, 
  db $22, $2a, $aa, $4a, $62, $22, $aa, $a2, $22, $22, 
  db $22, $22, $22, $42, $62, $22, $22, $22, $22, $22, 
  db $44, $44, $44, $42, $62, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $62, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $2a, $3a, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $a0, $00, $a2, $22, $22, $22, $22, 
  db $22, $22, $22, $a0, $d0, $a2, $22, $22, $22, $22, 
  db $22, $22, $22, $a0, $00, $a2, $22, $22, $22, $22, 
  db $22, $22, $22, $2a, $aa, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 

Sketch_1_forest_caveAutoEvents:
  AllocateTransportEvent 4, 13, HIGH(Sketch_1_forest_cave_lobby), LOW(Sketch_1_forest_cave_lobby), 5, 3
  AllocateTransportEvent 12, 8, HIGH(Sketch_1_underworld), LOW(Sketch_1_underworld), 12, 21
  EndList

Sketch_1_forest_caveBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  EndList

Sketch_1_forest_caveEntities:
  ret

ENDC