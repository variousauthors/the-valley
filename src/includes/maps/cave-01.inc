IF !DEF(CAVE_01_INC)
CAVE_01_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Cave01", ROM0
Cave01:
  db 12, 8, HIGH(Cave01Events), LOW(Cave01Events)
  db $0b, $0b, $09, $0b, $08, $08, $08, $08, 
  db $0b, $08, $08, $0b, $08, $0b, $0b, $08, 
  db $08, $08, $0b, $0b, $08, $08, $0b, $08, 
  db $08, $0b, $04, $08, $08, $04, $0b, $08, 
  db $08, $0b, $04, $04, $04, $04, $0b, $08, 
  db $08, $0b, $0b, $0b, $0b, $08, $0b, $08, 
  db $08, $08, $08, $08, $08, $08, $08, $08, 
  db $0b, $08, $0b, $08, $0b, $0b, $0b, $0b, 
  db $0b, $08, $0b, $08, $08, $08, $08, $0b, 
  db $08, $08, $0b, $0b, $08, $0b, $08, $08, 
  db $08, $08, $08, $08, $08, $0b, $0b, $08, 
  db $0b, $09, $0b, $0b, $08, $08, $08, $08, 

Cave01Events:
  AllocateTransportEvent 11, 1, HIGH(Overworld), LOW(Overworld), 9, 10
  AllocateTransportEvent 0, 2, HIGH(Overworld), LOW(Overworld), 4, 9
  EndList

ENDC