IF !DEF(RUINS_THREE_INC)
RUINS_THREE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "RuinsThree", ROM0
RuinsThree:
  db 18, 20, HIGH(RuinsThreeEvents), LOW(RuinsThreeEvents)
  db $01, $01, $01, $0b, $0b, $0b, $01, $01, $06, $0c, $06, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $0b, $0b, $0b, $01, $01, $06, $06, $06, $01, $01, $01, $06, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $0b, $0b, $0b, $0b, $0b, $06, $0c, $06, $0b, $01, $0b, $01, $0b, $06, $0b, $06, $01, 
  db $01, $01, $01, $0b, $0b, $0b, $0b, $0b, $06, $0c, $06, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $0b, $0b, $0b, $0b, $06, $06, $0c, $0c, $0c, $0c, $06, $0c, $0c, $01, $0b, $01, $01, 
  db $01, $01, $01, $0b, $0b, $0b, $0b, $0b, $06, $0c, $06, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $0b, $0b, $0b, $0b, $0b, $06, $06, $06, $0b, $01, $0b, $01, $0b, $01, $0b, $06, $01, 
  db $0f, $0f, $01, $0b, $0b, $0b, $0b, $0b, $06, $0c, $06, $01, $01, $01, $01, $01, $01, $06, $01, $01, 
  db $04, $0f, $0f, $0b, $01, $01, $01, $01, $06, $0c, $06, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $04, $04, $04, $0b, $0b, $01, $01, $0b, $06, $06, $06, $0b, $0b, $0b, $0b, $0b, $01, $01, $01, $01, 
  db $04, $04, $04, $04, $0f, $0b, $01, $01, $06, $0c, $06, $0b, $0b, $0b, $0b, $0b, $01, $01, $01, $01, 
  db $01, $04, $04, $0b, $0f, $0f, $04, $0b, $06, $0c, $06, $06, $0b, $0b, $0b, $0b, $01, $01, $01, $01, 
  db $01, $04, $0b, $04, $0f, $0f, $0f, $04, $06, $0c, $06, $0b, $0b, $0b, $0b, $0b, $01, $01, $01, $01, 
  db $01, $01, $04, $04, $0f, $0d, $0b, $0b, $06, $06, $06, $0b, $0b, $0b, $0b, $0b, $01, $01, $01, $01, 
  db $01, $01, $04, $0b, $0f, $0f, $0b, $01, $06, $0c, $06, $0b, $0b, $0b, $0b, $0b, $01, $01, $01, $01, 
  db $01, $01, $04, $04, $0f, $0b, $01, $01, $06, $0c, $06, $0b, $0b, $0b, $0b, $0b, $01, $01, $01, $01, 
  db $01, $01, $01, $04, $04, $04, $01, $01, $06, $0c, $06, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $01, $01, $04, $04, $01, $06, $0c, $06, $01, $01, $01, $01, $01, $01, $01, $01, $01, 

RuinsThreeEvents:
  AllocateTransportEvent 0, 9, HIGH(Overworld), LOW(Overworld), 16, 19
  AllocateTransportEvent 17, 9, HIGH(Overworld), LOW(Overworld), 16, 19

  ; interior
  AllocateTransportEvent 4, 7, HIGH(RuinsThreeInterior), LOW(RuinsThreeInterior), 4, 7
  AllocateTransportEvent 11, 11, HIGH(RuinsThreeInterior), LOW(RuinsThreeInterior), 11, 11

  ; underworld
  AllocateTransportEvent 13, 5, HIGH(Underworld), LOW(Underworld), 32, 38

  EndList

ENDC