
IF !DEF(CAVE_PASSAGE_INC)
CAVE_PASSAGE_INC = 1

Section "Cave_passage", ROMX, BANK[1]
Cave_passage:
  db 18, 20, 
  db HIGH(Cave_passageAutoEvents), LOW(Cave_passageAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Cave_passageBumpEvents), LOW(Cave_passageBumpEvents)
  db HIGH(Cave_passageEntities), LOW(Cave_passageEntities)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $4b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $b0, $4b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $b0, $4b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $4b, $bb, $bb, 
  db $bb, $bb, $bb, $be, $00, $0b, $bb, $4b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $0b, $bb, $40, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $0b, $bb, $40, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $0b, $b4, $4b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $0b, $b4, $bb, $bb, $bb, 
  db $bb, $bb, $00, $00, $00, $00, $05, $00, $0b, $bb, 
  db $bb, $bb, $0b, $bb, $bb, $0b, $b4, $bb, $00, $bb, 
  db $bb, $bb, $0b, $bb, $bb, $0b, $44, $4b, $b0, $0e, 
  db $bb, $bb, $0b, $bb, $bb, $0b, $44, $4b, $b0, $bb, 
  db $bb, $bb, $0b, $bb, $bb, $0b, $4b, $bb, $00, $bb, 
  db $bb, $bb, $eb, $d0, $00, $00, $50, $00, $0b, $bb, 
  db $00, $bb, $bb, $bb, $bb, $bb, $40, $bb, $bb, $bb, 
  db $44, $44, $44, $44, $44, $44, $40, $bb, $bb, $bb, 
  db $bb, $bb, $b0, $0b, $bb, $bb, $00, $bb, $bb, $bb, 

Cave_passageAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Cave_passageBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Cave_passageEntities:
  ret

ENDC