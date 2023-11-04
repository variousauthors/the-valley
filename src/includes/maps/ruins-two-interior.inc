IF !DEF(RUNS_TWO_INTERIOR_INC)
RUNS_TWO_INTERIOR_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "RuinsTwoInterior", ROM0
  db HAS_BOUNDS
RuinsTwoInterior:
  db 18, 20, HIGH(RuinsTwoInteriorEvents), LOW(RuinsTwoInteriorEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $b0, $00, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $b0, $00, $6b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $b0, $00, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $00, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $d0, $6b, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $00, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

RuinsTwoInteriorEvents:
  ; doors
  AllocateTransportEvent 2, 8, HIGH(RuinsTwo), LOW(RuinsTwo), 2, 8
  AllocateTransportEvent 9, 10, HIGH(RuinsTwo), LOW(RuinsTwo), 9, 10

  ; final maze
  AllocateTransportEvent 9, 8, HIGH(FinalMaze), LOW(FinalMaze), 1, 4

  EndList

ENDC