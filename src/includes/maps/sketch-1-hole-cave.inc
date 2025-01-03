
IF !DEF(SKETCH_1_HOLE_CAVE_INC)
SKETCH_1_HOLE_CAVE_INC = 1

Section "Sketch_1_hole_cave", ROMX, BANK[1]
  db NO_BOUNDS | NO_ENCOUNTERS
Sketch_1_hole_cave:
  db 18, 10, 
  db HIGH(Sketch_1_hole_caveAutoEvents), LOW(Sketch_1_hole_caveAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_hole_caveBumpEvents), LOW(Sketch_1_hole_caveBumpEvents)
  db HIGH(Sketch_1_hole_caveEntities), LOW(Sketch_1_hole_caveEntities)
  db $22, $22, $22, $22, $22, 
  db $22, $33, $33, $32, $22, 
  db $23, $00, $00, $03, $22, 
  db $30, $00, $02, $00, $32, 
  db $30, $02, $22, $20, $32, 
  db $30, $07, $22, $00, $32, 
  db $30, $00, $00, $00, $32, 
  db $23, $00, $00, $00, $32, 
  db $22, $30, $00, $03, $22, 
  db $22, $30, $00, $32, $22, 
  db $23, $00, $33, $22, $22, 
  db $23, $03, $22, $33, $32, 
  db $23, $03, $23, $00, $03, 
  db $23, $03, $23, $0f, $03, 
  db $23, $00, $33, $00, $03, 
  db $22, $30, $00, $00, $32, 
  db $22, $23, $03, $33, $22, 
  db $22, $23, $03, $22, $22, 

Sketch_1_hole_caveAutoEvents:
  AllocateTransportEvent 16, 4, HIGH(Sketch_1_hole_cave), LOW(Sketch_1_hole_cave), 14, 111
  EndList

Sketch_1_hole_caveBumpEvents:
  EndList

Sketch_1_hole_caveEntities:
  ret

ENDC