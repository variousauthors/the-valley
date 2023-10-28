IF !DEF(PENINSULA_RUINS)
PENINSULA_RUINS = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "PeninsulaRuins", ROM0
PeninsulaRuins:
  db 9, 10, HIGH(PeninsulaRuinsEvents), LOW(PeninsulaRuinsEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $b1, $11, $b1, $11, 
  db $11, $11, $d1, $11, $11, 
  db $11, $b1, $61, $b4, $41, 
  db $f4, $4f, $cf, $44, $41, 
  db $44, $b1, $c1, $bf, $f1, 
  db $f4, $41, $c1, $11, $11, 
  db $1f, $b1, $ff, $b4, $41, 
  db $11, $11, $c1, $f1, $11, 
  db $11, $11, $61, $11, $11, 

PeninsulaRuinsEvents:
  AllocateTransportEvent 8, 4, HIGH(Overworld), LOW(Overworld), 8, 45
  AllocateTransportEvent 1, 4, HIGH(Underworld), LOW(Underworld), 16, 90
  EndList

ENDC