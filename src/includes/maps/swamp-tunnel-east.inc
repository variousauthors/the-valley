IF !DEF(SWAMP_TUNNEL_EAST_INC)
SWAMP_TUNNEL_EAST_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "SwampTunnelEast", ROM0
SwampTunnelEast:
  db 9, 10, HIGH(SwampTunnelEastEvents), LOW(SwampTunnelEastEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $f1, $f4, $44, $ff, 
  db $1f, $1d, $cc, $1f, $11, 
  db $11, $11, $1c, $11, $11, 
  db $1f, $11, $1c, $11, $11, 
  db $4f, $f1, $16, $11, $11, 
  db $44, $f1, $1c, $61, $11, 
  db $4f, $11, $f6, $66, $66, 
  db $f1, $1f, $11, $1f, $f1, 
  db $44, $41, $1f, $44, $41, 

SwampTunnelEastEvents:
  AllocateTransportEvent 6, 9, HIGH(Overworld), LOW(Overworld), 1, 39
  AllocateTransportEvent 1, 3, HIGH(Underworld), LOW(Underworld), 2, 78
  EndList

ENDC