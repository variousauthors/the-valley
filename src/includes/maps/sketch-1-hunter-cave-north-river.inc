
IF !DEF(SKETCH_1_HUNTER_CAVE_NORTH_RIVER_INC)
SKETCH_1_HUNTER_CAVE_NORTH_RIVER_INC = 1

Section "Sketch_1_hunter_cave_north_river", ROMX, BANK[1]
  db NO_ENCOUNTERS
Sketch_1_hunter_cave_north_river:
  db 9, 8, 
  db HIGH(Sketch_1_hunter_cave_north_riverAutoEvents), LOW(Sketch_1_hunter_cave_north_riverAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_hunter_cave_north_riverBumpEvents), LOW(Sketch_1_hunter_cave_north_riverBumpEvents)
  db HIGH(Sketch_1_hunter_cave_north_riverEntities), LOW(Sketch_1_hunter_cave_north_riverEntities)
  db $22, $22, $22, $22, 
  db $22, $aa, $aa, $22, 
  db $2a, $00, $00, $a2, 
  db $a0, $09, $00, $0a, 
  db $a0, $0f, $00, $0a, 
  db $a0, $00, $0a, $0a, 
  db $2a, $00, $00, $0a, 
  db $22, $a0, $0a, $a2, 
  db $22, $a0, $a2, $22, 

Sketch_1_hunter_cave_north_riverAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 3, HIGH(Overworld), LOW(Overworld), 70, 107
  EndList

Sketch_1_hunter_cave_north_riverBumpEvents:
  AllocateCheckpointEvent 4, 3, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 3, 3, HIGH(HunterCaveNorthRiverNPC), LOW(HunterCaveNorthRiverNPC)
  EndList

Sketch_1_hunter_cave_north_riverEntities:
  ret

ENDC