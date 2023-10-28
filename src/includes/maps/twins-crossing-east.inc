IF !DEF(TWINS_CROSSING_EAST_INC)
TWINS_CROSSING_EAST_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "TwinsCrossingEast", ROM0
TwinsCrossingEast:
  db 9, 10, HIGH(TwinsCrossingEastEvents), LOW(TwinsCrossingEastEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 
  db $11, $11, $c6, $cc, $c6, 
  db $11, $16, $11, $16, $11, 
  db $11, $1c, $11, $16, $11, 
  db $11, $1d, $11, $44, $41, 
  db $11, $11, $11, $44, $41, 
  db $11, $11, $11, $11, $11, 

TwinsCrossingEastEvents:
  AllocateTransportEvent 3, 9, HIGH(Overworld), LOW(Overworld), 31, 29
  AllocateTransportEvent 6, 3, HIGH(Underworld), LOW(Underworld), 62, 58
  EndList

ENDC