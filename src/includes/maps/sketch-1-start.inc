
IF !DEF(SKETCH_1_START_INC)
SKETCH_1_START_INC = 1

Section "Sketch_1_start", ROMX, BANK[1]
  db NO_BOUNDS | NO_ENCOUNTERS
Start:
Sketch_1_start:
  db 9, 10, 
  db HIGH(Sketch_1_startAutoEvents), LOW(Sketch_1_startAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_startBumpEvents), LOW(Sketch_1_startBumpEvents)
  db HIGH(Sketch_1_startEntities), LOW(Sketch_1_startEntities)
  db $22, $33, $33, $33, $22, 
  db $22, $30, $00, $33, $32, 
  db $23, $30, $70, $00, $33, 
  db $33, $00, $f0, $00, $03, 
  db $30, $00, $00, $00, $03, 
  db $30, $01, $00, $00, $03, 
  db $33, $00, $00, $01, $03, 
  db $33, $30, $00, $00, $33, 
  db $23, $33, $30, $33, $32, 

Sketch_1_startAutoEvents:
  ; AllocateTransportEvent  9, 5, HIGH(Sketch_1_overworld), LOW(Sketch_1_overworld), 11, 92
  AllocateTransportEvent  9, 5, HIGH(Sketch_1_forest_cave), LOW(Sketch_1_forest_cave), 11, 92
  EndList

Sketch_1_startBumpEvents:
  EndList

Sketch_1_startEntities:
  ret

ENDC