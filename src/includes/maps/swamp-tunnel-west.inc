IF !DEF(SWAMP_TUNNEL_WEST_INC)
SWAMP_TUNNEL_WEST_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "SwampTunnelWest", ROM0
  db NO_BOUNDS
SwampTunnelWest:
  db 9, 10, HIGH(SwampTunnelWestEvents), LOW(SwampTunnelWestEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $14, $41, $f4, $44, $14, 
  db $1f, $f1, $1f, $1f, $14, 
  db $11, $11, $11, $11, $1f, 
  db $66, $66, $11, $11, $1f, 
  db $11, $1c, $6c, $c1, $11, 
  db $11, $11, $11, $c1, $f1, 
  db $11, $11, $11, $d1, $1f, 
  db $11, $1f, $f1, $11, $f4, 
  db $1f, $44, $4f, $f4, $44, 

SwampTunnelWestEvents:
  AllocateTransportEvent 3, 0, HIGH(Overworld), LOW(Overworld), 3, 37
  AllocateTransportEvent 6, 6, HIGH(Underworld), LOW(Underworld), 6, 74

  EndList

ENDC