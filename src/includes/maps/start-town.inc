
IF !DEF(START_TOWN_INC)
START_TOWN_INC = 1

Section "StartTown", ROMX, BANK[1]
  db NO_BOUNDS | NO_ENCOUNTERS
StartTown:
  db 11, 12, 
  db HIGH(StartTownAutoEvents), LOW(StartTownAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(StartTownBumpEvents), LOW(StartTownBumpEvents)
  db HIGH(StartTownEntities), LOW(StartTownEntities)
  db $10, $00, $00, $00, $00, $00, 
  db $00, $10, $01, $00, $10, $10, 
  db $10, $01, $10, $13, $11, $01, 
  db $01, $00, $00, $00, $31, $00, 
  db $01, $30, $07, $00, $30, $10, 
  db $13, $00, $00, $00, $00, $00, 
  db $00, $07, $0f, $07, $00, $00, 
  db $01, $00, $00, $00, $00, $10, 
  db $00, $00, $00, $00, $01, $03, 
  db $01, $00, $10, $01, $00, $30, 
  db $01, $01, $00, $00, $11, $01, 

StartTownAutoEvents:
  AllocateTransportEvent 11, 5, HIGH(Overworld), LOW(Overworld), 93, 53
  EndList

StartTownBumpEvents:
  AllocateNPCDialogEvent 6, 3, HIGH(StartCampOne), LOW(StartCampOne)
  AllocateNPCDialogEvent 4, 5, HIGH(StartCampTwo), LOW(StartCampTwo)
  AllocateNPCDialogEvent 6, 7, HIGH(Silence), LOW(Silence)

  /** checkpoints */
  AllocateCheckpointEvent 6, 5, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  EndList

StartTownEntities:
  ret

ENDC