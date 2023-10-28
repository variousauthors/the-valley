IF !DEF(FINAL_MAZE_INC)
FINAL_MAZE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "FinalMaze", ROM0
FinalMaze:
  db 18, 50, HIGH(FinalMazeAutoEvents), LOW(FinalMazeAutoEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
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