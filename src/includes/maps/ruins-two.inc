IF !DEF(RUINS_TWO_INC)
RUINS_TWO_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "RuinsTwo", ROM0
  db NO_BOUNDS
RuinsTwo:
  db 18, 20, HIGH(RuinsTwoEvents), LOW(RuinsTwoEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $14, $44, $bb, $bb, $b1, $6c, $61, $11, $11, $11, 
  db $44, $44, $bb, $bb, $b6, $6c, $61, $bb, $b1, $11, 
  db $44, $44, $bb, $bb, $6c, $cc, $61, $b4, $b1, $11, 
  db $44, $44, $bb, $bb, $b6, $6c, $61, $bb, $b1, $11, 
  db $44, $44, $bb, $bb, $b1, $6c, $61, $11, $11, $11, 
  db $44, $44, $11, $11, $11, $6c, $61, $44, $41, $11, 
  db $44, $44, $11, $11, $11, $6c, $64, $46, $44, $41, 
  db $44, $44, $11, $bb, $bb, $bc, $64, $66, $64, $44, 
  db $44, $44, $11, $bb, $bb, $bc, $64, $1d, $11, $44, 
  db $44, $44, $11, $bb, $bb, $6c, $64, $11, $11, $44, 
  db $44, $44, $11, $bb, $bb, $b6, $64, $11, $14, $44, 
  db $44, $44, $11, $bb, $bb, $b1, $14, $11, $44, $44, 
  db $44, $44, $11, $11, $11, $11, $14, $14, $44, $44, 
  db $44, $44, $41, $11, $11, $11, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, $44, $44, $44, $44, $44, 

RuinsTwoEvents:
  AllocateTransportEvent 0, 11, HIGH(Overworld), LOW(Overworld), 10, 14

  ; interior
  AllocateTransportEvent 2, 8, HIGH(RuinsTwoInterior), LOW(RuinsTwoInterior), 2, 8
  AllocateTransportEvent 9, 10, HIGH(RuinsTwoInterior), LOW(RuinsTwoInterior), 9, 10

  ; underworld
  AllocateTransportEvent 8, 15, HIGH(Underworld), LOW(Underworld), 20, 28

  EndList

ENDC