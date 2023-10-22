IF !DEF(RUINS_ONE_INTERIOR_INC)
RUINS_ONE_INTERIOR_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "RuinsOneInterior", ROMX, BANK[1]
RuinsOneInterior:
  db 18, 20, HIGH(RuinsOneInteriorEvents), LOW(RuinsOneInteriorEvents)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $d0, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $b6, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $6b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

RuinsOneInteriorEvents:
  ; doors
  AllocateTransportEvent 12, 6, HIGH(RuinsOne), LOW(RuinsOne), 12, 6
  AllocateTransportEvent 4, 13, HIGH(RuinsOne), LOW(RuinsOne), 4, 13

  ; final maze
  AllocateTransportEvent 3, 16, HIGH(FinalMaze), LOW(FinalMaze), 9, 0

  EndList

ENDC