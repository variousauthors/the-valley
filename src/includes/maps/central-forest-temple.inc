IF !DEF(CENTRAL_FOREST_TEMPLE_INC)
CENTRAL_FOREST_TEMPLE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "CentralForestTemple", ROMX
  db NO_BOUNDS
CentralForestTemple:
  db 9, 10, HIGH(CentralForestTempleEvents), LOW(CentralForestTempleEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $11, $11, $11, $11, 
  db $6c, $c6, $11, $11, $11, 
  db $11, $61, $1b, $1b, $11, 
  db $11, $c1, $b6, $66, $b1, 
  db $11, $c6, $c6, $d6, $11, 
  db $11, $11, $b6, $66, $b1, 
  db $16, $11, $1b, $1b, $11, 
  db $14, $41, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 

CentralForestTempleEvents:
  AllocateTransportEvent 1, 0, HIGH(Overworld), LOW(Overworld), 12, 8
  AllocateTransportEvent 4, 6, HIGH(Underworld), LOW(Underworld), 24, 16
  EndList

ENDC