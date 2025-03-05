
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
  db $11, $11, $11, $0a, $a0, 
  db $11, $00, $0a, $00, $0a, 
  db $10, $00, $aa, $ad, $0a, 
  db $10, $00, $00, $0a, $0a, 
  db $00, $0b, $0b, $b0, $0a, 
  db $10, $00, $10, $1a, $0a, 
  db $11, $00, $00, $01, $a1, 
  db $11, $11, $00, $00, $01, 
  db $11, $11, $11, $11, $11, 

Sketch_1_north_entranceAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_north_entranceBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Sketch_1_north_entranceEntities:
  ret

ENDC