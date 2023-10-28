IF !DEF(RUINED_TEMPLE_INC)
RUINED_TEMPLE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "RuinedTemple", ROM0
RuinedTemple:
  db 9, 10, HIGH(RuinedTempleEvents), LOW(RuinedTempleEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $11, $11, $11, $11, 
  db $6c, $c1, $11, $11, $11, 
  db $11, $61, $11, $1b, $b1, 
  db $11, $c1, $1b, $60, $61, 
  db $11, $c6, $c6, $0d, $b1, 
  db $16, $61, $1b, $06, $b1, 
  db $16, $44, $11, $bb, $61, 
  db $14, $46, $61, $11, $11, 
  db $11, $11, $11, $11, $11, 

RuinedTempleEvents:
  AllocateTransportEvent 1, 0, HIGH(Overworld), LOW(Overworld), 22, 41
  AllocateTransportEvent 4, 7, HIGH(Underworld), LOW(Underworld), 44, 82
  EndList

ENDC