
IF !DEF(SKETCH_1_HUNTER_CAVE_NEAR_BOAT_INC)
SKETCH_1_HUNTER_CAVE_NEAR_BOAT_INC = 1

; currently not actually a cave but that's ok I think
Section "Sketch_1_hunter_cave_near_boat", ROMX, BANK[1]
  db NO_BOUNDS | NO_ENCOUNTERS
Start:
Sketch_1_hunter_cave_near_boat:
  db 9, 10, 
  db HIGH(Sketch_1_hunter_cave_near_boatAutoEvents), LOW(Sketch_1_hunter_cave_near_boatAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_hunter_cave_near_boatBumpEvents), LOW(Sketch_1_hunter_cave_near_boatBumpEvents)
  db HIGH(Sketch_1_hunter_cave_near_boatEntities), LOW(Sketch_1_hunter_cave_near_boatEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $10, $11, $11, $11, 
  db $11, $01, $00, $10, $11, 
  db $11, $00, $00, $01, $11, 
  db $10, $00, $90, $00, $11, 
  db $10, $10, $f0, $00, $11, 
  db $11, $00, $00, $10, $11, 
  db $11, $11, $01, $01, $11, 
  db $11, $11, $11, $11, $11, 

Sketch_1_hunter_cave_near_boatAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 4, 9, HIGH(Overworld), LOW(Overworld), 58, 124
  EndList

Sketch_1_hunter_cave_near_boatBumpEvents:
  AllocateCheckpointEvent 5, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 4, 4, HIGH(HunterCaveNearBoatNPC), LOW(HunterCaveNearBoatNPC)
  EndList

Sketch_1_hunter_cave_near_boatEntities:
  ret

ENDC