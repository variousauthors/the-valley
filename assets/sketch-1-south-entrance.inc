
IF !DEF(SKETCH_1_SOUTH_ENTRANCE_INC)
SKETCH_1_SOUTH_ENTRANCE_INC = 1

Section "Sketch_1_south_entrance", ROMX, BANK[1]
Sketch_1_south_entrance:
  db 9, 10, 
  db HIGH(Sketch_1_south_entranceAutoEvents), LOW(Sketch_1_south_entranceAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_south_entranceBumpEvents), LOW(Sketch_1_south_entranceBumpEvents)
  db HIGH(Sketch_1_south_entranceEntities), LOW(Sketch_1_south_entranceEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 
  db $00, $00, $33, $31, $11, 
  db $11, $10, $00, $13, $11, 
  db $11, $31, $10, $13, $11, 
  db $11, $30, $0d, $00, $01, 
  db $11, $30, $10, $13, $11, 
  db $11, $10, $33, $31, $11, 
  db $11, $11, $11, $11, $11, 

Sketch_1_south_entranceAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_south_entranceBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  EndList

Sketch_1_south_entranceEntities:
  ret

ENDC