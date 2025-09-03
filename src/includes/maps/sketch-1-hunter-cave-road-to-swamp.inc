
IF !DEF(SKETCH_1_HUNTER_CAVE_ROAD_TO_SWAMP_INC)
SKETCH_1_HUNTER_CAVE_ROAD_TO_SWAMP_INC = 1

Section "Sketch_1_hunter_cave_road_to_swamp", ROMX, BANK[1]
  db NO_ENCOUNTERS
Sketch_1_hunter_cave_road_to_swamp:
  db 9, 8, 
  db HIGH(Sketch_1_hunter_cave_road_to_swampAutoEvents), LOW(Sketch_1_hunter_cave_road_to_swampAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_hunter_cave_road_to_swampBumpEvents), LOW(Sketch_1_hunter_cave_road_to_swampBumpEvents)
  db HIGH(Sketch_1_hunter_cave_road_to_swampEntities), LOW(Sketch_1_hunter_cave_road_to_swampEntities)
  db $22, $22, $22, $22, 
  db $22, $aa, $aa, $22, 
  db $2a, $00, $00, $a2, 
  db $a0, $09, $00, $0a, 
  db $a0, $0f, $00, $0a, 
  db $a0, $00, $0a, $0a, 
  db $2a, $00, $00, $0a, 
  db $22, $a0, $0a, $a2, 
  db $22, $a0, $a2, $22, 

Sketch_1_hunter_cave_road_to_swampAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 3, HIGH(Overworld), LOW(Overworld), 115, 71
  EndList

Sketch_1_hunter_cave_road_to_swampBumpEvents:
  AllocateCheckpointEvent 4, 3, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 3, 3, HIGH(HunterCaveRoadToSwampNPC), LOW(HunterCaveRoadToSwampNPC)
  EndList

Sketch_1_hunter_cave_road_to_swampEntities:
  ret

ENDC