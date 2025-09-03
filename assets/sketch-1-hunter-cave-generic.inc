
IF !DEF(SKETCH_1_HUNTER_CAVE_GENERIC_INC)
SKETCH_1_HUNTER_CAVE_GENERIC_INC = 1

Section "Sketch_1_hunter_cave_generic", ROMX, BANK[1]
Sketch_1_hunter_cave_generic:
  db 9, 8, 
  db HIGH(Sketch_1_hunter_cave_genericAutoEvents), LOW(Sketch_1_hunter_cave_genericAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_hunter_cave_genericBumpEvents), LOW(Sketch_1_hunter_cave_genericBumpEvents)
  db HIGH(Sketch_1_hunter_cave_genericEntities), LOW(Sketch_1_hunter_cave_genericEntities)
  db $22, $22, $22, $22, 
  db $22, $aa, $aa, $22, 
  db $2a, $00, $00, $a2, 
  db $a0, $09, $00, $0a, 
  db $a0, $0f, $00, $0a, 
  db $a0, $00, $0a, $0a, 
  db $2a, $00, $00, $0a, 
  db $22, $a0, $0a, $a2, 
  db $22, $a0, $a2, $22, 

Sketch_1_hunter_cave_genericAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_hunter_cave_genericBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Sketch_1_hunter_cave_genericEntities:
  ret

ENDC