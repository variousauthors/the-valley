
IF !DEF(SKETCH_1_HOLE_CAVE_INC)
SKETCH_1_HOLE_CAVE_INC = 1

Section "Sketch_1_hole_cave", ROMX, BANK[1]
Sketch_1_hole_cave:
  db 18, 10, 
  db HIGH(Sketch_1_hole_caveAutoEvents), LOW(Sketch_1_hole_caveAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_hole_caveBumpEvents), LOW(Sketch_1_hole_caveBumpEvents)
  db HIGH(Sketch_1_hole_caveEntities), LOW(Sketch_1_hole_caveEntities)
  db $22, $22, $22, $22, $22, 
  db $22, $aa, $aa, $a2, $22, 
  db $2a, $00, $00, $0a, $22, 
  db $a0, $00, $02, $00, $a2, 
  db $a0, $02, $22, $20, $a2, 
  db $a0, $07, $22, $00, $a2, 
  db $a0, $00, $00, $00, $a2, 
  db $2a, $00, $00, $00, $a2, 
  db $22, $a0, $00, $0a, $22, 
  db $22, $a0, $00, $a2, $22, 
  db $2a, $00, $aa, $22, $22, 
  db $2a, $0a, $22, $aa, $a2, 
  db $2a, $0a, $2a, $00, $0a, 
  db $2a, $0a, $2a, $0f, $0a, 
  db $2a, $00, $aa, $00, $0a, 
  db $22, $a0, $00, $00, $a2, 
  db $22, $2a, $0a, $aa, $22, 
  db $22, $2a, $0a, $22, $22, 

Sketch_1_hole_caveAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_hole_caveBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Sketch_1_hole_caveEntities:
  ret

ENDC