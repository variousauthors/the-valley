IF !DEF(FINAL_MAZE_INC)
FINAL_MAZE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "FinalMaze", ROMX, BANK[1]
FinalMaze:
  db 18, 50, HIGH(FinalMazeAutoEvents), LOW(FinalMazeAutoEvents)
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $06, $06, $0b, $0b, $0b, $0b, $0b, $06, $06, $06, $0b, $0b, $0b, $0b, $0b, $06, $06, $06, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0e, $00, $00, $00, $0b, $00, $00, $00, $0d, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $01, $06, $0b, $0b, $0b, $0b, $0b, $06, $01, $06, $0b, $0b, $0b, $0b, $0b, $06, $01, $06, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $00, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $06, $06, $0b, $0b, $0b, $0b, $0b, $06, $06, $06, $0b, $0b, $0b, $0b, $0b, $06, $06, $06, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $00, $00, $00, $0b, $0b, $0b, $00, $0b, $00, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $0b, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $0b, $0b, $0b, $0b, 
  db $0b, $00, $0d, $00, $00, $00, $0b, $00, $0b, $00, $0b, $00, $00, $00, $0d, $00, $0b, $0b, $0b, $0b, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $0b, $0b, $0b, 
  db $0b, $00, $00, $00, $0b, $00, $0b, $00, $00, $00, $0b, $00, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $00, $00, $00, $00, $00, $00, $0b, $06, $06, $06, $0b, $00, $00, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $00, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $0b, $0b, 
  db $0e, $0b, $0b, $0b, $0b, $0b, $0b, $06, $0e, $06, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $00, $00, $00, $0b, $00, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $06, $06, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $06, $06, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $0e, $06, $0b, $0b, $0b, $0b, $0e, $00, $0b, $0b, $0b, $0b, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $06, $06, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $00, $0b, $0b, $00, $00, $0b, $00, $00, $00, $0b, $00, $00, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $00, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $00, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0e, $0b, $0b, $0b, $0e, $0b, $0b, $0b, $0e, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 

; swap s/ (\d+, \d+)(.*,)(\d+, \d+)/\3\2\1
FinalMazeAutoEvents:
  ; intra
  AllocateTransportEvent 5, 2, HIGH(FinalMaze), LOW(FinalMaze), 17, 29
  AllocateTransportEvent 17, 29, HIGH(FinalMaze), LOW(FinalMaze), 5, 2
  AllocateTransportEvent 1, 12, HIGH(FinalMaze), LOW(FinalMaze), 17, 33
  AllocateTransportEvent 17, 33, HIGH(FinalMaze), LOW(FinalMaze), 1, 12
  AllocateTransportEvent 5, 14, HIGH(FinalMaze), LOW(FinalMaze), 17, 37
  AllocateTransportEvent 17, 37, HIGH(FinalMaze), LOW(FinalMaze), 5, 14

  ; ruins interior
  AllocateTransportEvent 9, 0, HIGH(RuinsOneInterior), LOW(RuinsOneInterior), 3, 16
  AllocateTransportEvent 1, 4, HIGH(RuinsTwoInterior), LOW(RuinsTwoInterior), 9, 8
  AllocateTransportEvent 13, 14, HIGH(RuinsThreeInterior), LOW(RuinsThreeInterior), 1, 4

  EndList

FinalMazeTriggerEvents:
  EndList

ENDC