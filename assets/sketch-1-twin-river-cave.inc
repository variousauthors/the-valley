
IF !DEF(SKETCH_1_TWIN_RIVER_CAVE_INC)
SKETCH_1_TWIN_RIVER_CAVE_INC = 1

Section "Sketch_1_twin_river_cave", ROMX, BANK[1]
Sketch_1_twin_river_cave:
  db 27, 30, 
  db HIGH(Sketch_1_twin_river_caveAutoEvents), LOW(Sketch_1_twin_river_caveAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_twin_river_caveBumpEvents), LOW(Sketch_1_twin_river_caveBumpEvents)
  db HIGH(Sketch_1_twin_river_caveEntities), LOW(Sketch_1_twin_river_caveEntities)
  db $24, $22, $22, $22, $22, $22, $22, $22, $22, $aa, $a2, $22, $22, $22, $22, 
  db $44, $42, $22, $2a, $aa, $a2, $22, $22, $2a, $00, $0a, $22, $22, $22, $22, 
  db $44, $44, $22, $a0, $00, $0a, $a2, $22, $2a, $0c, $0a, $22, $22, $22, $22, 
  db $24, $44, $4a, $00, $aa, $00, $0a, $aa, $aa, $00, $0a, $22, $22, $22, $22, 
  db $2a, $44, $40, $0a, $22, $aa, $00, $00, $00, $0a, $a2, $22, $22, $22, $22, 
  db $22, $a0, $50, $a2, $22, $2a, $0a, $aa, $aa, $00, $a2, $22, $22, $22, $22, 
  db $22, $a0, $44, $44, $42, $a0, $0a, $22, $22, $a0, $0a, $22, $22, $22, $22, 
  db $22, $a0, $44, $44, $44, $a0, $a4, $44, $a2, $2a, $0a, $aa, $22, $22, $22, 
  db $2a, $00, $a2, $2a, $44, $40, $44, $44, $4a, $2a, $00, $00, $a2, $22, $22, 
  db $2a, $0a, $22, $aa, $a4, $44, $40, $04, $44, $2a, $0a, $a0, $0a, $22, $22, 
  db $2a, $0a, $aa, $00, $0a, $44, $00, $00, $44, $2a, $0a, $2a, $0a, $22, $22, 
  db $2a, $00, $00, $0a, $00, $a0, $0a, $a0, $04, $a0, $0a, $2a, $0a, $22, $22, 
  db $22, $aa, $0a, $a2, $a0, $00, $0a, $24, $44, $a0, $a2, $2a, $0a, $22, $22, 
  db $22, $2a, $0a, $22, $2a, $00, $a2, $44, $40, $00, $a2, $2a, $0a, $22, $22, 
  db $22, $2a, $0a, $22, $22, $aa, $24, $44, $4a, $0a, $22, $2a, $0a, $22, $22, 
  db $22, $22, $a0, $a2, $22, $22, $24, $22, $44, $0a, $22, $a0, $0a, $22, $22, 
  db $22, $22, $a0, $0a, $22, $22, $44, $22, $24, $44, $22, $a0, $a2, $22, $22, 
  db $22, $aa, $aa, $00, $aa, $22, $42, $22, $2a, $04, $42, $a0, $a2, $22, $22, 
  db $2a, $00, $00, $00, $00, $a2, $42, $2a, $a0, $0a, $44, $00, $a2, $22, $22, 
  db $2a, $0a, $aa, $aa, $a0, $0a, $42, $a0, $00, $a2, $24, $4a, $22, $22, $22, 
  db $a0, $00, $a2, $22, $2a, $00, $4a, $00, $aa, $22, $a0, $44, $42, $22, $22, 
  db $a0, $c0, $a2, $22, $22, $a0, $44, $aa, $22, $2a, $00, $a2, $44, $42, $22, 
  db $a0, $00, $a2, $22, $22, $2a, $a4, $44, $22, $a0, $0a, $22, $22, $44, $44, 
  db $2a, $aa, $22, $22, $22, $22, $2a, $a4, $42, $2a, $a2, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $44, $44, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $24, $44, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $24, $44, $44, $42, $22, 

Sketch_1_twin_river_caveAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_twin_river_caveBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Sketch_1_twin_river_caveEntities:
  ret

ENDC