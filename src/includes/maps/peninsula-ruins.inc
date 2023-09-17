IF !DEF(PENINSULA_RUINS)
PENINSULA_RUINS = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "PeninsulaRuins", ROM0
PeninsulaRuins:
  db 9, 10, HIGH(PeninsulaRuinsEvents), LOW(PeninsulaRuinsEvents)
  db $01, $01, $0b, $01, $01, $01, $0b, $01, $01, $01, 
  db $01, $01, $01, $01, $0d, $01, $01, $01, $01, $01, 
  db $01, $01, $0b, $01, $06, $01, $0b, $04, $04, $01, 
  db $0f, $04, $04, $0f, $0c, $0f, $04, $04, $04, $01, 
  db $04, $04, $0b, $01, $0c, $01, $0b, $0f, $0f, $01, 
  db $0f, $04, $04, $01, $0c, $01, $01, $01, $01, $01, 
  db $01, $0f, $0b, $01, $0f, $0f, $0b, $04, $04, $01, 
  db $01, $01, $01, $01, $0c, $01, $0f, $01, $01, $01, 
  db $01, $01, $01, $01, $06, $01, $01, $01, $01, $01, 

PeninsulaRuinsEvents:
  AllocateTransportEvent 8, 4, HIGH(Overworld), LOW(Overworld), 8, 45
  AllocateTransportEvent 1, 4, HIGH(Underworld), LOW(Underworld), 16, 90
  EndList

ENDC