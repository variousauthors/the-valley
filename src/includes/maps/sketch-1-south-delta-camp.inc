
IF !DEF(SKETCH_1_SOUTH_DELTA_CAMP_INC)
SKETCH_1_SOUTH_DELTA_CAMP_INC = 1

Section "Sketch_1_south_delta_camp", ROMX, BANK[1]
  db NO_BOUNDS | NO_ENCOUNTERS
Sketch_1_south_delta_camp:
  db 9, 10, 
  db HIGH(Sketch_1_south_delta_campAutoEvents), LOW(Sketch_1_south_delta_campAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_south_delta_campBumpEvents), LOW(Sketch_1_south_delta_campBumpEvents)
  db HIGH(Sketch_1_south_delta_campEntities), LOW(Sketch_1_south_delta_campEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $10, $11, $11, $11, 
  db $11, $01, $00, $10, $11, 
  db $11, $00, $00, $01, $11, 
  db $10, $00, $90, $00, $11, 
  db $10, $10, $f0, $00, $11, 
  db $11, $00, $00, $10, $11, 
  db $11, $11, $01, $01, $11, 
  db $11, $11, $11, $11, $11, 

Sketch_1_south_delta_campAutoEvents:
  EndList

Sketch_1_south_delta_campBumpEvents:
  AllocateCheckpointEvent 5, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 4, 4, HIGH(SouthDeltaCampNPC), LOW(SouthDeltaCampNPC)
  EndList

Sketch_1_south_delta_campEntities:
  ret

ENDC