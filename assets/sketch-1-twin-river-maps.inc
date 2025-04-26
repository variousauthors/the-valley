
IF !DEF(SKETCH_1_TWIN_RIVER_MAPS_INC)
SKETCH_1_TWIN_RIVER_MAPS_INC = 1

Section "Sketch_1_twin_river_maps", ROMX, BANK[1]
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
  db $22, $22, $22, $22, $22, $a0, $9a, $22, $22, $a0, $00, $00, $00, $a2, $22, 
  db $22, $22, $22, $22, $22, $a0, $0d, $a2, $22, $2a, $00, $00, $00, $a2, $22, 
  db $22, $22, $22, $22, $22, $2a, $aa, $22, $22, $22, $aa, $0a, $aa, $22, $22, 

Sketch_1_twin_river_mapsAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_twin_river_mapsBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Sketch_1_twin_river_mapsEntities:
  ret

ENDC