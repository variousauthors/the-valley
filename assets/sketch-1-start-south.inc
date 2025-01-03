
IF !DEF(SKETCH_1_START_SOUTH_INC)
SKETCH_1_START_SOUTH_INC = 1

Section "Sketch_1_start_south", ROMX, BANK[1]
Sketch_1_start_south:
  db 9, 10, 
  db HIGH(Sketch_1_start_southAutoEvents), LOW(Sketch_1_start_southAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_start_southBumpEvents), LOW(Sketch_1_start_southBumpEvents)
  db HIGH(Sketch_1_start_southEntities), LOW(Sketch_1_start_southEntities)
  db $22, $22, $22, $62, $22, 
  db $22, $22, $23, $03, $22, 
  db $23, $33, $23, $03, $22, 
  db $30, $00, $30, $00, $32, 
  db $30, $70, $00, $00, $03, 
  db $30, $f0, $00, $01, $03, 
  db $30, $00, $00, $10, $32, 
  db $23, $00, $00, $03, $22, 
  db $22, $33, $33, $32, $22, 

Sketch_1_start_southAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_start_southBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_start_southEntities:
  ret

ENDC