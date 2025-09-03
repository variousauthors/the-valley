
IF !DEF(SKETCH_1_NORTH_RIVER_CAVES_INC)
SKETCH_1_NORTH_RIVER_CAVES_INC = 1

Section "Sketch_1_north_river_caves", ROMX, BANK[1]
Sketch_1_north_river_caves:
  db 23, 28, 
  db HIGH(Sketch_1_north_river_cavesAutoEvents), LOW(Sketch_1_north_river_cavesAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_north_river_cavesBumpEvents), LOW(Sketch_1_north_river_cavesBumpEvents)
  db HIGH(Sketch_1_north_river_cavesEntities), LOW(Sketch_1_north_river_cavesEntities)
  db $22, $aa, $aa, $aa, $22, $22, $22, $22, $2a, $a0, $aa, $22, $22, $22, 
  db $2a, $a0, $00, $0a, $a2, $22, $22, $2a, $aa, $00, $0a, $a2, $22, $22, 
  db $aa, $00, $00, $00, $aa, $22, $22, $2a, $00, $07, $00, $aa, $22, $22, 
  db $a0, $00, $70, $0d, $0a, $22, $22, $a0, $00, $0f, $00, $0a, $22, $22, 
  db $a0, $00, $f7, $00, $0a, $22, $22, $a0, $00, $00, $00, $0a, $22, $22, 
  db $aa, $00, $00, $00, $0a, $22, $22, $a0, $00, $00, $00, $0a, $22, $22, 
  db $2a, $a0, $00, $00, $aa, $22, $22, $aa, $00, $00, $00, $aa, $22, $22, 
  db $22, $aa, $00, $aa, $a2, $22, $22, $2a, $a0, $00, $00, $a2, $22, $22, 
  db $22, $2a, $a0, $a2, $22, $22, $22, $22, $2a, $0a, $aa, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $32, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $62, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $62, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $2a, $3a, $22, $22, $22, $a2, 
  db $22, $aa, $a2, $2a, $a2, $22, $22, $2a, $a0, $0a, $22, $22, $2a, $ca, 
  db $2a, $07, $0a, $ad, $0a, $22, $2a, $a0, $00, $00, $a2, $22, $2a, $0a, 
  db $a0, $00, $00, $00, $00, $aa, $a0, $00, $0f, $70, $a2, $22, $2a, $0a, 
  db $a0, $00, $00, $00, $00, $00, $00, $00, $00, $00, $a2, $22, $2a, $0a, 
  db $a0, $00, $0f, $70, $00, $00, $00, $00, $00, $00, $a2, $22, $2a, $0a, 
  db $2a, $00, $00, $00, $00, $aa, $aa, $00, $07, $0a, $22, $22, $2a, $0a, 
  db $2a, $00, $00, $00, $aa, $22, $2a, $a0, $00, $0a, $22, $22, $2a, $0a, 
  db $22, $a0, $00, $aa, $22, $22, $22, $aa, $0a, $a2, $22, $22, $2a, $0a, 
  db $22, $2a, $0a, $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $ca, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a2, 

Sketch_1_north_river_cavesAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_north_river_cavesBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Sketch_1_north_river_cavesEntities:
  ret

ENDC