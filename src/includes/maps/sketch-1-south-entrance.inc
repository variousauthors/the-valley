
IF !DEF(SKETCH_1_SOUTH_ENTRANCE_INC)
SKETCH_1_SOUTH_ENTRANCE_INC = 1

Section "Sketch_1_south_entrance", ROMX, BANK[1]
  db NO_BOUNDS | NO_ENCOUNTERS
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
  AllocateTransportEvent 0, 0, HIGH(Overworld), LOW(Overworld), 23, 107
  AllocateTransportEvent 5, 5, HIGH(Sketch_1_underworld), LOW(Sketch_1_underworld), 49, 59
  EndList

Sketch_1_south_entranceBumpEvents:
  EndList

Sketch_1_south_entranceEntities:
  ret

ENDC