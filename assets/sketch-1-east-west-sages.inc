
IF !DEF(SKETCH_1_EAST_WEST_SAGES_INC)
SKETCH_1_EAST_WEST_SAGES_INC = 1

Section "Sketch_1_east_west_sages", ROMX, BANK[1]
Sketch_1_east_west_sages:
  db 36, 34, 
  db HIGH(Sketch_1_east_west_sagesAutoEvents), LOW(Sketch_1_east_west_sagesAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_east_west_sagesBumpEvents), LOW(Sketch_1_east_west_sagesBumpEvents)
  db HIGH(Sketch_1_east_west_sagesEntities), LOW(Sketch_1_east_west_sagesEntities)
  db $2a, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a0, $a2, 
  db $ad, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a0, $a2, 
  db $a0, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a0, $a2, 
  db $20, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $aa, $a9, $a2, 
  db $26, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a2, $22, $22, $ad, $00, $00, $a2, 
  db $26, $22, $22, $aa, $aa, $aa, $a2, $22, $22, $2a, $da, $22, $22, $aa, $a0, $00, $0a, 
  db $26, $22, $aa, $aa, $aa, $aa, $aa, $a2, $22, $22, $02, $22, $22, $a0, $80, $70, $0a, 
  db $26, $22, $aa, $00, $00, $00, $0a, $a2, $22, $22, $62, $22, $22, $a0, $0f, $00, $a2, 
  db $26, $2a, $a0, $a0, $00, $00, $a0, $aa, $22, $22, $62, $22, $22, $a0, $00, $0a, $22, 
  db $26, $63, $00, $00, $00, $00, $00, $aa, $22, $22, $62, $22, $22, $aa, $00, $0a, $22, 
  db $22, $2a, $a0, $00, $e0, $e9, $00, $a3, $66, $66, $62, $22, $22, $2a, $a0, $aa, $22, 
  db $2a, $aa, $a0, $00, $00, $00, $00, $a3, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $aa, $a0, $a0, $00, $00, $a0, $a0, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $a0, $00, $00, $00, $00, $00, $00, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $a0, $44, $40, $a0, $a0, $10, $10, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $a0, $48, $50, $00, $00, $07, $00, $aa, $22, $22, $22, $2a, $0a, $22, $22, $22, 
  db $2a, $a0, $44, $40, $a0, $a0, $10, $10, $aa, $22, $22, $22, $2a, $0a, $22, $22, $22, 
  db $2a, $a0, $00, $00, $00, $00, $00, $00, $aa, $22, $22, $22, $2a, $0a, $22, $22, $22, 
  db $2a, $aa, $a0, $00, $a0, $a0, $00, $aa, $aa, $22, $22, $2a, $aa, $9a, $aa, $22, $22, 
  db $2a, $aa, $a0, $00, $00, $00, $00, $aa, $aa, $22, $22, $a0, $00, $00, $00, $a2, $22, 
  db $aa, $aa, $a0, $00, $a0, $a0, $00, $aa, $aa, $a2, $22, $a0, $a8, $07, $a0, $0a, $22, 
  db $aa, $aa, $aa, $00, $00, $00, $0a, $aa, $aa, $a2, $22, $a0, $00, $f0, $0a, $0a, $22, 
  db $aa, $aa, $aa, $aa, $00, $0a, $aa, $aa, $aa, $a2, $22, $a0, $00, $00, $0a, $da, $22, 
  db $aa, $aa, $aa, $aa, $a0, $aa, $aa, $aa, $aa, $a2, $22, $2a, $a0, $00, $00, $a2, $22, 
  db $aa, $aa, $a0, $00, $00, $00, $00, $aa, $aa, $a2, $22, $22, $2a, $0a, $aa, $22, $22, 
  db $44, $44, $00, $10, $0b, $00, $10, $04, $44, $42, $22, $22, $22, $22, $22, $22, $22, 
  db $44, $44, $40, $01, $0b, $01, $00, $44, $44, $42, $22, $22, $22, $22, $22, $22, $22, 
  db $44, $44, $44, $00, $0b, $00, $04, $44, $44, $42, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $aa, $aa, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $00, $0a, $22, $22, $22, 
  db $2a, $aa, $aa, $aa, $aa, $aa, $aa, $a2, $22, $2a, $aa, $aa, $0a, $0a, $aa, $aa, $a2, 
  db $2a, $c0, $00, $0a, $00, $00, $00, $a2, $22, $2a, $00, $00, $0a, $0a, $00, $0c, $a2, 
  db $2a, $aa, $0a, $aa, $a0, $aa, $a0, $a2, $22, $2a, $0a, $aa, $aa, $0a, $0a, $aa, $a2, 
  db $22, $2a, $00, $00, $00, $a2, $ac, $a2, $22, $2a, $ca, $22, $2a, $00, $0a, $22, $22, 
  db $22, $2a, $aa, $aa, $aa, $a2, $aa, $a2, $22, $2a, $aa, $22, $2a, $aa, $aa, $22, $22, 

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