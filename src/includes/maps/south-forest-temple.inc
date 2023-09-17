IF !DEF(SOUTH_FOREST_TEMPLE_INC)
SOUTH_FOREST_TEMPLE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "SouthForestTemple", ROM0
SouthForestTemple:
  db 9, 10, HIGH(SouthForestTempleEvents), LOW(SouthForestTempleEvents)
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $01, $01, $0b, $0b, $01, $0b, $01, 
  db $0c, $0c, $01, $0b, $01, $01, $06, $01, $0b, $01, 
  db $01, $06, $01, $0b, $01, $0b, $0b, $06, $0b, $01, 
  db $01, $0c, $06, $0c, $06, $0b, $06, $06, $06, $0b, 
  db $01, $01, $01, $0b, $06, $06, $06, $0d, $01, $0b, 
  db $01, $01, $01, $01, $0b, $0b, $01, $06, $01, $01, 
  db $01, $01, $01, $01, $01, $0b, $01, $0b, $0b, $0b, 
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 

SouthForestTempleEvents:
  AllocateTransportEvent 2, 0, HIGH(Overworld), LOW(Overworld), 14, 9
  AllocateTransportEvent 5, 7, HIGH(Underworld), LOW(Underworld), 28, 18
  EndList

ENDC