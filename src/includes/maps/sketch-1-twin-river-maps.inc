
IF !DEF(SKETCH_1_TWIN_RIVER_MAPS_INC)
SKETCH_1_TWIN_RIVER_MAPS_INC = 1

Section "Sketch_1_twin_river_maps", ROMX, BANK[1]
  db NO_ENCOUNTERS
;Start:
Sketch_1_twin_river_maps:
  db 22, 30, 
  db HIGH(Sketch_1_twin_river_mapsAutoEvents), LOW(Sketch_1_twin_river_mapsAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_twin_river_mapsBumpEvents), LOW(Sketch_1_twin_river_mapsBumpEvents)
  db HIGH(Sketch_1_twin_river_mapsEntities), LOW(Sketch_1_twin_river_mapsEntities)
  db $22, $22, $22, $22, $22, $aa, $aa, $22, $22, $22, $22, $2a, $aa, $aa, $22, 
  db $22, $22, $22, $22, $2a, $00, $0a, $a2, $22, $22, $22, $aa, $00, $0a, $a2, 
  db $22, $22, $22, $22, $aa, $00, $00, $0a, $22, $22, $2a, $a0, $00, $00, $a2, 
  db $22, $22, $22, $2a, $a0, $0f, $00, $00, $a2, $22, $2a, $00, $70, $00, $aa, 
  db $2a, $a2, $22, $2a, $00, $00, $00, $00, $36, $66, $30, $00, $f7, $01, $0a, 
  db $a0, $03, $66, $63, $00, $10, $07, $0a, $22, $22, $2a, $00, $00, $00, $0a, 
  db $a0, $a2, $22, $2a, $a0, $00, $00, $1a, $22, $22, $2a, $14, $44, $00, $aa, 
  db $a0, $a2, $22, $2a, $aa, $00, $00, $0a, $22, $22, $2a, $01, $44, $00, $a2, 
  db $a0, $a2, $22, $22, $aa, $aa, $0a, $a2, $22, $22, $22, $a0, $00, $00, $a2, 
  db $a0, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, $aa, $00, $0a, $a2, 
  db $a0, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a0, $aa, $22, 
  db $a0, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $a0, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $a0, $a2, $22, $22, $2a, $aa, $aa, $aa, $22, $22, $22, $22, $22, $22, $22, 
  db $a0, $aa, $22, $22, $a0, $00, $00, $00, $aa, $aa, $22, $22, $22, $22, $22, 
  db $a0, $00, $36, $66, $30, $00, $00, $00, $00, $00, $aa, $aa, $a2, $22, $22, 
  db $2a, $aa, $22, $22, $a0, $f7, $00, $00, $00, $00, $00, $00, $0a, $22, $22, 
  db $22, $22, $22, $22, $a0, $00, $0a, $aa, $aa, $00, $00, $70, $00, $a2, $22, 
  db $22, $22, $22, $22, $2a, $00, $a2, $22, $22, $a0, $00, $f7, $00, $a2, $22, 
  db $22, $22, $22, $22, $22, $aa, $22, $22, $22, $a0, $00, $00, $00, $a2, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $00, $00, $00, $a2, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $aa, $0a, $aa, $22, $22, 

Sketch_1_twin_river_mapsAutoEvents:
  AllocateTransportEvent 8, 12, HIGH(Overworld), LOW(Overworld), 96, 101
  AllocateTransportEvent 10, 25, HIGH(Overworld), LOW(Overworld), 99, 104
  AllocateTransportEvent 21, 22, HIGH(Overworld), LOW(Overworld), 101, 101

  EndList

Sketch_1_twin_river_mapsBumpEvents:
  ; checkpoints
  AllocateCheckpointEvent 3, 11, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateCheckpointEvent 4, 24, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateCheckpointEvent 18, 22, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateCheckpointEvent 16, 10, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)

  ; dialog
  AllocateNPCDialogEvent 5, 13, HIGH(TwinRiverNPC1), LOW(TwinRiverNPC1)

  AllocateNPCDialogEvent 3, 24, HIGH(TwinRiverNPC2), LOW(TwinRiverNPC2)
  AllocateNPCDialogEvent 4, 25, HIGH(TwinRiverNPC3), LOW(TwinRiverNPC3)

  AllocateNPCDialogEvent 17, 22, HIGH(TwinRiverNPC4), LOW(TwinRiverNPC4)
  AllocateNPCDialogEvent 18, 23, HIGH(TwinRiverNPC5), LOW(TwinRiverNPC5)
  AllocateNPCDialogEvent 16, 11, HIGH(TwinRiverNPC6), LOW(TwinRiverNPC6)

  EndList

Sketch_1_twin_river_mapsEntities:
  ret

ENDC