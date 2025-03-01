
IF !DEF(SKETCH_1_NORTH_RIVER_CAVES_INC)
SKETCH_1_NORTH_RIVER_CAVES_INC = 1

Section "Sketch_1_north_river_caves", ROMX, BANK[1]
  db NO_ENCOUNTERS
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
  db $22, $2a, $a0, $a2, $22, $22, $22, $22, $2a, $3a, $aa, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $62, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $62, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $62, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $2a, $3a, $22, $22, $22, $a2, 
  db $22, $aa, $a2, $2a, $a2, $22, $22, $2a, $a0, $0a, $22, $22, $2a, $ca, 
  db $2a, $07, $0a, $ad, $0a, $22, $2a, $a0, $00, $00, $a2, $22, $2a, $0a, 
  db $2a, $00, $00, $00, $00, $aa, $a0, $00, $0f, $70, $a2, $22, $2a, $0a, 
  db $2a, $00, $00, $00, $00, $00, $00, $00, $00, $00, $a2, $22, $2a, $0a, 
  db $2a, $00, $0f, $70, $00, $00, $00, $00, $00, $00, $a2, $22, $2a, $0a, 
  db $a0, $00, $00, $00, $00, $aa, $aa, $00, $07, $0a, $22, $22, $2a, $0a, 
  db $2a, $00, $00, $00, $aa, $22, $2a, $a0, $00, $0a, $22, $22, $2a, $0a, 
  db $22, $a0, $00, $aa, $22, $22, $22, $aa, $0a, $a2, $22, $22, $2a, $0a, 
  db $22, $2a, $0a, $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $ca, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a2, 

Sketch_1_north_river_cavesAutoEvents:
  ; overworld
  AllocateTransportEvent 8, 5, HIGH(Overworld), LOW(Overworld), 84, 123
  AllocateTransportEvent 21, 4, HIGH(Overworld), LOW(Overworld), 80, 123
  AllocateTransportEvent 20, 16, HIGH(Overworld), LOW(Overworld), 79, 125
  AllocateTransportEvent 0, 19, HIGH(Overworld), LOW(Overworld), 76, 125

  ; stairs
  AllocateTransportEvent 3, 7, HIGH(Sketch_1_north_river_caves), LOW(Sketch_1_north_river_caves), 21, 26
  AllocateTransportEvent 21, 26, HIGH(Sketch_1_north_river_caves), LOW(Sketch_1_north_river_caves), 3, 7
  AllocateTransportEvent 14, 7, HIGH(Sketch_1_north_river_caves), LOW(Sketch_1_north_river_caves), 13, 26
  AllocateTransportEvent 13, 26, HIGH(Sketch_1_north_river_caves), LOW(Sketch_1_north_river_caves), 14, 7

  EndList

Sketch_1_north_river_cavesBumpEvents:
  AllocateNPCDialogEvent 4, 5, HIGH(NorthRiverNPC1), LOW(NorthRiverNPC1)
  AllocateNPCDialogEvent 3, 4, HIGH(NorthRiverNPC2), LOW(NorthRiverNPC2)
  AllocateNPCDialogEvent 17, 6, HIGH(NorthRiverNPC3), LOW(NorthRiverNPC3)
  AllocateNPCDialogEvent 14, 3, HIGH(NorthRiverNPC4), LOW(NorthRiverNPC4)
  AllocateNPCDialogEvent 18, 17, HIGH(NorthRiverNPC5), LOW(NorthRiverNPC5)
  AllocateNPCDialogEvent 15, 18, HIGH(NorthRiverNPC6), LOW(NorthRiverNPC6)
  AllocateNPCDialogEvent 2, 19, HIGH(NorthRiverNPC7), LOW(NorthRiverNPC7)

  AllocateCheckpointEvent 4, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateCheckpointEvent 17, 5, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateCheckpointEvent 3, 19, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateCheckpointEvent 15, 17, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)

  EndList

Sketch_1_north_river_cavesEntities:
  ret

ENDC