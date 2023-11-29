IF !DEF(NORTH_FOREST_TEMPLE_INC)
NORTH_FOREST_TEMPLE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "NorthForestTemple", ROMX
  db NO_BOUNDS
NorthForestTemple:
  db 9, 10, HIGH(NorthForestTempleEvents), LOW(NorthForestTempleEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $11, $11, $11, $11, 
  db $11, $1b, $11, $1b, $11, 
  db $11, $11, $11, $11, $11, 
  db $1c, $c6, $cd, $11, $11, 
  db $1c, $11, $11, $11, $11, 
  db $16, $1b, $11, $1b, $11, 
  db $1c, $11, $11, $11, $11, 
  db $16, $11, $11, $11, $11, 
  db $1c, $11, $11, $11, $11, 

NorthForestTempleEvents:
  AllocateTransportEvent 8, 1, HIGH(Overworld), LOW(Overworld), 9, 10
  AllocateTransportEvent 3, 5, HIGH(Underworld), LOW(Underworld), 18, 20
  EndList

ENDC