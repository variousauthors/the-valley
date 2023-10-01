IF !DEF(RUINED_TEMPLE_INC)
RUINED_TEMPLE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "RuinedTemple", ROM0
RuinedTemple:
  db 9, 10, HIGH(RuinedTempleEvents), LOW(RuinedTempleEvents)
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $06, $0c, $0c, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $06, $01, $01, $01, $01, $0b, $0b, $01, 
  db $01, $01, $0c, $01, $01, $0b, $06, $00, $06, $01, 
  db $01, $01, $0c, $06, $0c, $06, $00, $0d, $0b, $01, 
  db $01, $06, $06, $01, $01, $0b, $00, $06, $0b, $01, 
  db $01, $06, $04, $04, $01, $01, $0b, $0b, $06, $01, 
  db $01, $04, $04, $06, $06, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 

RuinedTempleEvents:
  AllocateTransportEvent 1, 0, HIGH(Overworld), LOW(Overworld), 22, 41
  AllocateTransportEvent 4, 7, HIGH(Underworld), LOW(Underworld), 44, 82
  EndList

ENDC