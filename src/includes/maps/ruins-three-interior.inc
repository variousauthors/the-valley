IF !DEF(RUINS_THREE_INTERIOR_INC)
RUINS_THREE_INTERIOR_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "RuinsThreeInterior", ROMX, BANK[1]
  db HAS_BOUNDS
RuinsThreeInterior:
  db 18, 20, HIGH(RuinsThreeInteriorEvents), LOW(RuinsThreeInteriorEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $db, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $06, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $b6, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

RuinsThreeInteriorEvents:
  ; door
  AllocateTransportEvent 4, 7, HIGH(RuinsThree), LOW(RuinsThree), 4, 7
  AllocateTransportEvent 11, 11, HIGH(RuinsThree), LOW(RuinsThree), 11, 11

  ; final maze
  AllocateTransportEvent 1, 4, HIGH(FinalMaze), LOW(FinalMaze), 13, 14

  EndList

ENDC