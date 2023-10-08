IF !DEF(HIDDEN_PENINSULA_INC)
HIDDEN_PENINSULA_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "HiddenPeninsula", ROM0
HiddenPeninsula:
  db 9, 10, HIGH(HiddenPeninsulaAutoEvents), LOW(HiddenPeninsulaAutoEvents)
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $0c, $0c, $06, $06, $0c, $06, $0c, $06, 
  db $01, $01, $0c, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $0b, $06, $0b, $0b, $0b, $0b, $01, $01, $01, 
  db $01, $0b, $06, $06, $06, $06, $0b, $01, $01, $01, 
  db $01, $0b, $06, $0d, $06, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $06, $01, $01, $0b, $01, $01, $01, 
  db $01, $01, $0b, $0b, $0b, $0b, $0b, $01, $01, $01, 

HiddenPeninsulaAutoEvents:
  ; overworld
  AllocateTransportEvent 2, 9, HIGH(Overworld), LOW(Overworld), 23, 44

  ; underworld
  AllocateTransportEvent 6, 3, HIGH(Underworld), LOW(Underworld), 46, 88

  EndList

HiddenPeninsulaTriggerEvents:
  EndList

ENDC