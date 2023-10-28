IF !DEF(SOUTH_FOREST_TEMPLE_INC)
SOUTH_FOREST_TEMPLE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "SouthForestTemple", ROM0
SouthForestTemple:
  db 9, 10, HIGH(SouthForestTempleEvents), LOW(SouthForestTempleEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $1b, $b1, $b1, 
  db $cc, $1b, $11, $61, $b1, 
  db $16, $1b, $1b, $b6, $b1, 
  db $1c, $6c, $6b, $66, $6b, 
  db $11, $1b, $66, $6d, $1b, 
  db $11, $11, $bb, $16, $11, 
  db $11, $11, $1b, $1b, $bb, 
  db $11, $11, $11, $11, $11, 

SouthForestTempleEvents:
  AllocateTransportEvent 2, 0, HIGH(Overworld), LOW(Overworld), 14, 8
  AllocateTransportEvent 5, 7, HIGH(Underworld), LOW(Underworld), 28, 16
  EndList

ENDC