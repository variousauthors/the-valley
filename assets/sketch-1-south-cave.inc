
IF !DEF(SKETCH_1_SOUTH_CAVE_INC)
SKETCH_1_SOUTH_CAVE_INC = 1

Section "Sketch_1_south_cave", ROMX, BANK[1]
Sketch_1_south_cave:
  db 9, 10, 
  db HIGH(Sketch_1_south_caveAutoEvents), LOW(Sketch_1_south_caveAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_south_caveBumpEvents), LOW(Sketch_1_south_caveBumpEvents)
  db HIGH(Sketch_1_south_caveEntities), LOW(Sketch_1_south_caveEntities)
  db $22, $22, $22, $22, $22, 
  db $22, $aa, $aa, $a2, $22, 
  db $2a, $00, $00, $0a, $22, 
  db $2a, $00, $e0, $00, $a2, 
  db $22, $a0, $00, $00, $0a, 
  db $2a, $00, $44, $40, $00, 
  db $a0, $04, $44, $00, $aa, 
  db $2a, $00, $00, $0a, $22, 
  db $22, $aa, $aa, $a2, $22, 

Sketch_1_south_caveAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_south_caveBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Sketch_1_south_caveEntities:
  ret

ENDC