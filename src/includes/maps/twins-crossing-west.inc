IF !DEF(TWINS_CROSSING_WEST_INC)
TWINS_CROSSING_WEST_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "TwinsCrossingWest", ROM0
TwinsCrossingWest:
  db 9, 10, HIGH(TwinsCrossingWestEvents), LOW(TwinsCrossingWestEvents)
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $06, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $01, $0c, $0c, $0d, $01, $01, $01, 
  db $01, $01, $06, $01, $0c, $01, $01, $01, $06, $01, 
  db $01, $01, $01, $01, $06, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $01, $0c, $01, $01, $01, $01, $01, 
  db $06, $0c, $06, $0c, $06, $01, $01, $01, $06, $01, 
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $01, $01, $01, $06, $01, $01, $01, 

TwinsCrossingWestEvents:
  AllocateTransportEvent 6, 0, HIGH(Overworld), LOW(Overworld), 31, 27
  AllocateTransportEvent 2, 6, HIGH(Underworld), LOW(Underworld), 62, 54
  EndList

ENDC