IF !DEF(OLD_SWAMP_INC)
OLD_SWAMP_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "OldSwamp", ROM0
OldSwamp:
  db 9, 10, HIGH(OldSwampEvents), LOW(OldSwampEvents)
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $0d, $01, $0f, $0f, $01, $01, $01, $01, 
  db $01, $01, $0c, $01, $04, $04, $04, $0f, $01, $01, 
  db $01, $01, $0c, $0f, $04, $04, $0f, $01, $01, $01, 
  db $01, $01, $06, $01, $0f, $0f, $06, $00, $06, $06, 
  db $01, $01, $00, $06, $01, $06, $00, $01, $01, $01, 
  db $01, $01, $06, $06, $00, $06, $06, $01, $01, $01, 
  db $01, $01, $01, $01, $06, $06, $01, $01, $01, $01, 
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 

OldSwampEvents:
  AllocateTransportEvent 4, 9, HIGH(Overworld), LOW(Overworld), 2, 31
  AllocateTransportEvent 1, 2, HIGH(Underworld), LOW(Underworld), 6, 64
  EndList

ENDC