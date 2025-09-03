
IF !DEF(SKETCH_1_CAMP_SOUTH_TWIN_RIVER_INC)
SKETCH_1_CAMP_SOUTH_TWIN_RIVER_INC = 1

Section "Sketch_1_camp_south_twin_river", ROMX, BANK[1]
  db NO_BOUNDS | NO_ENCOUNTERS
Sketch_1_camp_south_twin_river:
  db 9, 10, 
  db HIGH(Sketch_1_camp_south_twin_riverAutoEvents), LOW(Sketch_1_camp_south_twin_riverAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_camp_south_twin_riverBumpEvents), LOW(Sketch_1_camp_south_twin_riverBumpEvents)
  db HIGH(Sketch_1_camp_south_twin_riverEntities), LOW(Sketch_1_camp_south_twin_riverEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $10, $11, $11, $11, 
  db $11, $01, $00, $10, $11, 
  db $11, $00, $00, $01, $11, 
  db $10, $00, $90, $00, $11, 
  db $10, $10, $f0, $00, $11, 
  db $11, $00, $00, $10, $11, 
  db $11, $11, $01, $01, $11, 
  db $11, $11, $11, $11, $11, 

Sketch_1_camp_south_twin_riverAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 108, 97
  EndList

Sketch_1_camp_south_twin_riverBumpEvents:
  AllocateCheckpointEvent 5, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 4, 4, HIGH(CampSouthTwinRiverNPC), LOW(CampSouthTwinRiverNPC)
  EndList

Sketch_1_camp_south_twin_riverEntities:
  ret

ENDC