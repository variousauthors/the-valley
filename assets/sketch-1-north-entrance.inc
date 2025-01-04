
IF !DEF(SKETCH_1_NORTH_ENTRANCE_INC)
SKETCH_1_NORTH_ENTRANCE_INC = 1

Section "Sketch_1_north_entrance", ROMX, BANK[1]
Sketch_1_north_entrance:
  db 9, 10, 
  db HIGH(Sketch_1_north_entranceAutoEvents), LOW(Sketch_1_north_entranceAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_north_entranceBumpEvents), LOW(Sketch_1_north_entranceBumpEvents)
  db HIGH(Sketch_1_north_entranceEntities), LOW(Sketch_1_north_entranceEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $10, $01, $11, $11, 
  db $11, $00, $13, $33, $11, 
  db $11, $11, $31, $00, $31, 
  db $11, $31, $10, $d0, $31, 
  db $11, $31, $00, $00, $31, 
  db $00, $00, $01, $13, $11, 
  db $11, $33, $11, $00, $01, 
  db $11, $11, $11, $11, $11, 

Sketch_1_north_entranceAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_north_entranceBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  EndList

Sketch_1_north_entranceEntities:
  ret

ENDC