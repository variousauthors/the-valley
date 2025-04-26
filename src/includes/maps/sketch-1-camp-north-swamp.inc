
IF !DEF(SKETCH_1_CAMP_NORTH_SWAMP_INC)
SKETCH_1_CAMP_NORTH_SWAMP_INC = 1

Section "Sketch_1_camp_north_swamp", ROMX, BANK[1]
  db NO_BOUNDS | NO_ENCOUNTERS
Sketch_1_camp_north_swamp:
  db 9, 10, 
  db HIGH(Sketch_1_camp_north_swampAutoEvents), LOW(Sketch_1_camp_north_swampAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_camp_north_swampBumpEvents), LOW(Sketch_1_camp_north_swampBumpEvents)
  db HIGH(Sketch_1_camp_north_swampEntities), LOW(Sketch_1_camp_north_swampEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $10, $11, $11, $11, 
  db $11, $01, $00, $10, $11, 
  db $11, $00, $00, $01, $11, 
  db $10, $00, $90, $00, $11, 
  db $10, $10, $f0, $00, $11, 
  db $11, $00, $00, $10, $11, 
  db $11, $11, $01, $01, $11, 
  db $11, $11, $11, $11, $11, 

Sketch_1_camp_north_swampAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 91, 56
  EndList

Sketch_1_camp_north_swampBumpEvents:
  AllocateCheckpointEvent 5, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 4, 4, HIGH(CampNorthSwampNPC), LOW(CampNorthSwampNPC)
  EndList

Sketch_1_camp_north_swampEntities:
  ret

ENDC