IF !DEF(STARTING_CAVE_INC)
STARTING_CAVE_INC = 1

Section "StartingCave", ROM0
  db NO_ENCOUNTERS
StartingCave:
  db 9, 8, 
  db HIGH(StartingCaveAutoEvents), LOW(StartingCaveAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(StartingCaveBumpEvents), LOW(StartingCaveBumpEvents)
  db HIGH(StartingCaveEntities), LOW(StartingCaveEntities)
  db $bb, $bb, $bb, $bb, 
  db $bb, $00, $00, $bb, 
  db $b0, $00, $b0, $0b, 
  db $b0, $00, $00, $0b, 
  db $cc, $cc, $00, $0b, 
  db $b0, $00, $00, $0b, 
  db $b0, $00, $b0, $0b, 
  db $bb, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, 

StartingCaveAutoEvents:
  /** entrance */
  AllocateTransportEvent 4, 0, HIGH(Overworld), LOW(Overworld), 28, 46
  AllocateNPCDialogEvent 4, 1, HIGH(LastChance), LOW(LastChance)

  EndList

StartingCaveBumpEvents:
  AllocateNPCDialogEvent 4, 5, HIGH(ElderWarning), LOW(ElderWarning)

  EndList

StartingCaveEntities:
  ld b, 4
  ld c, 5
  call initElder
  ret

ENDC