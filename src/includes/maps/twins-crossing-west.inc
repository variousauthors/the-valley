IF !DEF(TWINS_CROSSING_WEST_INC)
TWINS_CROSSING_WEST_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "TwinsCrossingWest", ROM0
  db NO_BOUNDS
TwinsCrossingWest:
  db 9, 10, HIGH(TwinsCrossingWestEvents), LOW(TwinsCrossingWestEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $11, $11, $11, $11, 
  db $16, $11, $11, $11, $11, 
  db $11, $11, $cc, $d1, $11, 
  db $11, $61, $c1, $11, $61, 
  db $11, $11, $61, $11, $11, 
  db $11, $11, $c1, $11, $11, 
  db $6c, $6c, $61, $11, $61, 
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $61, $11, 

TwinsCrossingWestEvents:
  AllocateTransportEvent 6, 0, HIGH(Overworld), LOW(Overworld), 31, 27
  AllocateTransportEvent 2, 6, HIGH(Underworld), LOW(Underworld), 62, 54
  EndList

ENDC