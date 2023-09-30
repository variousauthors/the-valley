IF !DEF(RUINS_THREE_INTERIOR_INC)
RUINS_THREE_INTERIOR_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "RuinsThreeInterior", ROM0
RuinsThreeInterior:
  db 18, 20, HIGH(RuinsThreeInteriorEvents), LOW(RuinsThreeInteriorEvents)
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0d, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $00, $00, $00, $06, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 

RuinsThreeInteriorEvents:
  ; door
  AllocateTransportEvent 4, 7, HIGH(RuinsThree), LOW(RuinsThree), 4, 7
  AllocateTransportEvent 11, 11, HIGH(RuinsThree), LOW(RuinsThree), 11, 11

  ; final maze
  AllocateTransportEvent 1, 4, HIGH(FinalMaze), LOW(FinalMaze), 13, 14

  EndList

ENDC