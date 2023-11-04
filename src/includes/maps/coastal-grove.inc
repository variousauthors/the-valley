IF !DEF(COSTAL_GROVE_INC)
COSTAL_GROVE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "CoastalGrove", ROM0
  db NO_BOUNDS
CoastalGrove:
  db 9, 10, HIGH(CoastalGroveEvents), LOW(CoastalGroveEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $11, $11, $11, $11, 
  db $11, $16, $11, $11, $11, 
  db $11, $11, $dc, $c6, $11, 
  db $11, $11, $11, $1c, $11, 
  db $11, $11, $11, $16, $11, 
  db $16, $c6, $cc, $6c, $11, 
  db $11, $c1, $61, $11, $61, 
  db $11, $61, $11, $11, $11, 
  db $11, $c1, $11, $11, $11, 

CoastalGroveEvents:
  AllocateTransportEvent 8, 2, HIGH(Overworld), LOW(Overworld), 29, 1
  AllocateTransportEvent 2, 4, HIGH(Underworld), LOW(Underworld), 58, 2
  EndList

ENDC