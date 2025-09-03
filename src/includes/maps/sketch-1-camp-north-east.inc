
IF !DEF(SKETCH_1_CAMP_NORTH_EAST_INC)
SKETCH_1_CAMP_NORTH_EAST_INC = 1

Section "Sketch_1_camp_north_east", ROMX, BANK[1]
  db NO_BOUNDS | NO_ENCOUNTERS
Sketch_1_camp_north_east:
  db 9, 10, 
  db HIGH(Sketch_1_camp_north_eastAutoEvents), LOW(Sketch_1_camp_north_eastAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_camp_north_eastBumpEvents), LOW(Sketch_1_camp_north_eastBumpEvents)
  db HIGH(Sketch_1_camp_north_eastEntities), LOW(Sketch_1_camp_north_eastEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $10, $11, $11, $11, 
  db $11, $01, $00, $10, $11, 
  db $11, $00, $00, $01, $11, 
  db $10, $00, $90, $00, $11, 
  db $10, $10, $f0, $00, $11, 
  db $11, $00, $00, $10, $11, 
  db $11, $11, $01, $01, $11, 
  db $11, $11, $11, $11, $11, 

Sketch_1_camp_north_eastAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 4, 9, HIGH(Overworld), LOW(Overworld), 51, 119
  EndList

Sketch_1_camp_north_eastBumpEvents:
  AllocateCheckpointEvent 5, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 4, 4, HIGH(CampNorthEastNPC), LOW(CampNorthEastNPC)
  EndList

Sketch_1_camp_north_eastEntities:
  ret

ENDC