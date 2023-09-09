IF !DEF(OLD_POND_INC)
OLD_POND_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "OldPond", ROM0
OldPond:
  db 9, 10, HIGH(OldPondEvents), LOW(OldPondEvents)
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $01, $01, $0d, $01, $01, $01, $01, 
  db $01, $01, $01, $06, $0c, $0c, $0c, $06, $01, $01, 
  db $01, $01, $01, $01, $04, $04, $04, $06, $01, $01, 
  db $01, $01, $01, $06, $04, $04, $04, $06, $01, $01, 
  db $01, $01, $06, $01, $06, $06, $06, $01, $01, $01, 
  db $01, $01, $01, $06, $01, $06, $01, $01, $01, $01, 
  db $01, $01, $01, $01, $01, $0c, $01, $01, $01, $01, 
  db $01, $01, $01, $01, $01, $0c, $01, $01, $01, $01, 

OldPondEvents:
  AllocateTransportEvent 8, 5, HIGH(Overworld), LOW(Overworld), 18, 8
  AllocateTransportEvent 1, 5, HIGH(Underworld), LOW(Underworld), 36, 16
  EndList

ENDC