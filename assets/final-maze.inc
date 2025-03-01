
IF !DEF(FINAL_MAZE_INC)
FINAL_MAZE_INC = 1

Section "Final_maze", ROMX, BANK[1]
Final_maze:
  db 18, 50, 
  db HIGH(Final_mazeAutoEvents), LOW(Final_mazeAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Final_mazeBumpEvents), LOW(Final_mazeBumpEvents)
  db HIGH(Final_mazeEntities), LOW(Final_mazeEntities)
  db $bb, $bb, $bb, $bb, $bb, $b0, $00, $bb, $bb, $bb, $bb, $bb, $66, $6b, $bb, $bb, $66, $6b, $bb, $bb, $66, $6b, $bb, $bb, $bb, 
  db $bb, $bb, $e0, $00, $b0, $00, $d0, $bb, $bb, $bb, $bb, $bb, $61, $6b, $bb, $bb, $61, $6b, $bb, $bb, $61, $6b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $b0, $b0, $00, $bb, $bb, $bb, $bb, $bb, $66, $6b, $bb, $bb, $66, $6b, $bb, $bb, $66, $6b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b6, $bb, $bb, $bb, $b6, $bb, $bb, $bb, $b6, $bb, $bb, $bb, $bb, 
  db $b0, $00, $bb, $b0, $b0, $bb, $b0, $00, $bb, $bb, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $b0, $0b, $00, $0b, $00, $bb, $bb, 
  db $b0, $d0, $00, $b0, $b0, $b0, $00, $d0, $bb, $bb, $0b, $00, $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $00, $0b, $0b, $bb, 
  db $b0, $00, $b0, $b0, $00, $b0, $b0, $00, $bb, $bb, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $bb, 
  db $bb, $bb, $b0, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $00, $00, $00, $b6, $66, $b0, $00, $00, $bb, $bb, $bb, $bb, $00, $00, $bb, $bb, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $bb, 
  db $eb, $bb, $bb, $b6, $e6, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $bb, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $bb, 
  db $bb, $bb, $bb, $b6, $66, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $00, $0b, $bb, $bb, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $bb, 
  db $bb, $bb, $bb, $bb, $6b, $bb, $bb, $b0, $bb, $bb, $b0, $00, $0b, $bb, $bb, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $bb, 
  db $bb, $bb, $bb, $b6, $66, $bb, $bb, $b0, $bb, $bb, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $bb, 
  db $bb, $bb, $bb, $b6, $e6, $bb, $bb, $e0, $bb, $bb, $0b, $00, $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $00, $0b, $0b, $bb, 
  db $bb, $bb, $bb, $b6, $66, $bb, $bb, $bb, $bb, $bb, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $b0, $0b, $00, $0b, $00, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $be, $bb, $be, $bb, $be, $bb, $bb, $bb, $bb, $bb, $bb, 

Final_mazeAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Final_mazeBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Final_mazeEntities:
  ret

ENDC