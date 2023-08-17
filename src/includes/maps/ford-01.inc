IF !DEF(FORD_01_INC)
FORD_01_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Ford01", ROM0
Ford01:
  db 9, 10, HIGH(Ford01Events), LOW(Ford01Events)
  db $01, $0f, $04, $04, $04, $04, $04, $0f, $04, $01, 
  db $01, $0f, $0f, $04, $04, $04, $0f, $0f, $04, $01, 
  db $01, $0f, $04, $0f, $0f, $0f, $0f, $04, $06, $06, 
  db $06, $06, $04, $0f, $04, $0f, $04, $04, $06, $01, 
  db $01, $06, $06, $04, $0f, $0f, $0f, $06, $06, $01, 
  db $01, $06, $04, $0f, $0f, $0f, $04, $0f, $06, $01, 
  db $01, $06, $0f, $0f, $04, $0f, $04, $0f, $0f, $01, 
  db $01, $04, $0f, $0f, $04, $0f, $0f, $0f, $04, $0f, 
  db $01, $04, $04, $04, $04, $04, $0f, $04, $04, $0f, 

Ford01Events:
  AllocateTransportEvent 3, 0, HIGH(Overworld), LOW(Overworld), 34, 6
  AllocateTransportEvent 2, 9, HIGH(Overworld), LOW(Overworld), 34, 8
  EndList

ENDC