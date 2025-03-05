
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
  db $00, $01, $10, $10, $00, 
  db $01, $01, $01, $01, $00, 
  db $00, $00, $33, $31, $10, 
  db $01, $10, $00, $13, $00, 
  db $00, $31, $00, $13, $10, 
  db $01, $30, $0d, $00, $01, 
  db $01, $30, $10, $13, $10, 
  db $00, $10, $33, $31, $00, 
  db $00, $01, $00, $00, $00, 

Sketch_1_south_entranceAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_south_entranceBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Sketch_1_south_entranceEntities:
  ret

ENDC