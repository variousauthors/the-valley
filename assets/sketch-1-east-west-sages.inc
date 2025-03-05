
IF !DEF(SKETCH_1_EAST_WEST_SAGES_INC)
SKETCH_1_EAST_WEST_SAGES_INC = 1

Section "Sketch_1_east_west_sages", ROMX, BANK[1]
Sketch_1_east_west_sages:
  db 25, 34, 
  db HIGH(Sketch_1_east_west_sagesAutoEvents), LOW(Sketch_1_east_west_sagesAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_east_west_sagesBumpEvents), LOW(Sketch_1_east_west_sagesBumpEvents)
  db HIGH(Sketch_1_east_west_sagesEntities), LOW(Sketch_1_east_west_sagesEntities)
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $0a, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $aa, $a2, $22, $2a, $0a, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $d0, $a2, $22, $2a, $0a, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $a0, $aa, $aa, $aa, $9a, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a0, $a0, $00, $00, $0a, $22, $22, 
  db $22, $22, $22, $aa, $aa, $aa, $a2, $22, $22, $22, $a0, $a0, $00, $00, $00, $a2, $22, 
  db $22, $22, $aa, $aa, $aa, $aa, $aa, $a2, $22, $22, $a0, $00, $08, $07, $00, $a2, $22, 
  db $22, $22, $aa, $00, $00, $00, $0a, $a2, $22, $22, $2a, $a0, $00, $f0, $0a, $22, $22, 
  db $22, $2a, $a0, $a0, $00, $00, $a0, $aa, $22, $22, $22, $a0, $00, $00, $a2, $22, $22, 
  db $22, $2a, $a0, $00, $00, $00, $00, $aa, $22, $22, $22, $2a, $a0, $00, $a2, $22, $22, 
  db $22, $2a, $a0, $00, $e0, $e9, $00, $aa, $22, $22, $22, $22, $aa, $0a, $a2, $22, $22, 
  db $2a, $aa, $a0, $00, $00, $00, $00, $aa, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $aa, $a0, $a0, $00, $00, $a0, $aa, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $a0, $00, $00, $00, $00, $00, $00, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $a0, $44, $40, $a0, $a0, $10, $10, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $a0, $48, $50, $00, $00, $07, $00, $aa, $22, $22, $22, $2a, $0a, $22, $22, $22, 
  db $2a, $a0, $44, $40, $a0, $a0, $10, $10, $aa, $22, $22, $22, $2a, $0a, $22, $22, $22, 
  db $2a, $a0, $00, $00, $00, $00, $00, $00, $aa, $22, $22, $22, $2a, $0a, $22, $22, $22, 
  db $2a, $aa, $a0, $aa, $aa, $aa, $a0, $aa, $aa, $22, $22, $2a, $aa, $9a, $aa, $22, $22, 
  db $2a, $aa, $a0, $aa, $aa, $aa, $a0, $aa, $aa, $22, $22, $a0, $00, $00, $00, $a2, $22, 
  db $aa, $00, $00, $00, $00, $00, $00, $00, $0a, $a2, $22, $a0, $a8, $07, $a0, $0a, $22, 
  db $aa, $0c, $00, $00, $00, $00, $00, $0c, $0a, $a2, $22, $a0, $00, $f0, $0a, $0a, $22, 
  db $aa, $00, $0a, $aa, $aa, $aa, $aa, $00, $0a, $a2, $22, $a0, $00, $00, $0a, $da, $22, 
  db $aa, $aa, $aa, $aa, $aa, $aa, $aa, $aa, $aa, $a2, $22, $2a, $a0, $00, $00, $a2, $22, 
  db $aa, $aa, $a2, $22, $22, $22, $22, $aa, $aa, $a2, $22, $22, $2a, $0a, $aa, $22, $22, 

Sketch_1_east_west_sagesAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_east_west_sagesBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Sketch_1_east_west_sagesEntities:
  ret

ENDC