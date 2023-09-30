IF !DEF(RUINS_ONE_INC)
RUINS_ONE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "RuinsOne", ROM0
RuinsOne:
  db 18, 20, HIGH(RuinsOneEvents), LOW(RuinsOneEvents)
  db $01, $04, $04, $04, $01, $01, $04, $04, $04, $04, $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $04, $04, $04, $0b, $0b, $0b, $04, $0b, $0b, $04, $01, $01, $01, $0b, $0b, $0b, $0b, $0b, $0b, $01, 
  db $04, $01, $04, $04, $04, $04, $04, $01, $01, $04, $01, $01, $01, $0b, $0b, $0b, $0b, $0b, $0b, $01, 
  db $0b, $06, $01, $01, $01, $06, $06, $01, $01, $04, $01, $01, $01, $0b, $0b, $0b, $0b, $0b, $0b, $01, 
  db $0b, $06, $0d, $06, $06, $06, $01, $04, $0b, $01, $06, $0c, $0c, $06, $0b, $0b, $0b, $0b, $0b, $01, 
  db $06, $0b, $06, $06, $06, $01, $04, $04, $0b, $01, $06, $06, $06, $0b, $0b, $0b, $0b, $0b, $0b, $01, 
  db $01, $0b, $06, $06, $01, $04, $04, $0b, $01, $01, $06, $0c, $06, $0b, $0b, $0b, $0b, $0b, $0b, $01, 
  db $0b, $06, $06, $06, $0b, $04, $0b, $0b, $01, $01, $06, $0c, $06, $0b, $0b, $0b, $0b, $0b, $0b, $01, 
  db $01, $0b, $06, $06, $0b, $01, $01, $01, $01, $01, $06, $0c, $06, $01, $01, $01, $0f, $0f, $01, $01, 
  db $06, $06, $0b, $0b, $06, $06, $06, $06, $06, $06, $06, $0c, $06, $01, $0f, $0f, $0f, $0f, $0f, $01, 
  db $0c, $0c, $0c, $0c, $06, $0c, $0c, $0c, $0c, $06, $0c, $0c, $06, $0f, $0f, $0b, $04, $0b, $0f, $0f, 
  db $06, $06, $06, $06, $06, $06, $06, $06, $06, $06, $06, $0c, $06, $0f, $0b, $04, $04, $04, $0b, $0f, 
  db $01, $01, $01, $0b, $0b, $0b, $06, $0b, $0b, $0b, $06, $06, $06, $0f, $04, $04, $0b, $04, $04, $0f, 
  db $01, $01, $01, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $0c, $0f, $0f, $0b, $04, $04, $04, $0b, $0f, 
  db $01, $01, $01, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $0c, $0f, $0f, $0f, $0b, $04, $0b, $0f, $01, 
  db $01, $01, $01, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $0f, $01, 
  db $01, $01, $01, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $06, $0c, $06, $01, $0f, $0f, $0f, $01, $01, $01, 
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, $06, $0c, $06, $01, $01, $01, $01, $01, $01, $01, 

RuinsOneEvents:
  AllocateTransportEvent 17, 11, HIGH(Overworld), LOW(Overworld), 14, 12
  AllocateTransportEvent 10, 0, HIGH(Overworld), LOW(Overworld), 14, 12

  ; interior
  AllocateTransportEvent 12, 6, HIGH(RuinsOneInterior), LOW(RuinsOneInterior), 12, 6
  AllocateTransportEvent 4, 13, HIGH(RuinsOneInterior), LOW(RuinsOneInterior), 4, 13

  ; underworld
  AllocateTransportEvent 4, 2, HIGH(Underworld), LOW(Underworld), 28, 24

  EndList

ENDC