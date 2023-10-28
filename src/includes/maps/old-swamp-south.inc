IF !DEF(OLD_SWAMP_SOUTH_INC)
OLD_SWAMP_SOUTH_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "OldSwampSouth", ROM0
OldSwampSouth:
  db 9, 10, HIGH(OldSwampSouthEvents), LOW(OldSwampSouthEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $1c, $1f, $f1, $11, 
  db $1f, $16, $11, $ff, $1f, 
  db $f1, $1c, $11, $ff, $f1, 
  db $1f, $16, $11, $1f, $11, 
  db $11, $1c, $11, $11, $f1, 
  db $11, $1c, $11, $1f, $11, 
  db $21, $16, $cd, $1f, $12, 
  db $21, $f1, $11, $11, $12, 
  db $12, $11, $f1, $f1, $21, 

OldSwampSouthEvents:
  AllocateTransportEvent 0, 3, HIGH(Overworld), LOW(Overworld), 6, 33
  AllocateTransportEvent 6, 5, HIGH(Underworld), LOW(Underworld), 12, 66
  EndList

ENDC