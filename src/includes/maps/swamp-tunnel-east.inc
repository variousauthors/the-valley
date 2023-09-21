IF !DEF(SWAMP_TUNNEL_EAST_INC)
SWAMP_TUNNEL_EAST_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "SwampTunnelEast", ROM0
SwampTunnelEast:
  db 9, 10, HIGH(SwampTunnelEastEvents), LOW(SwampTunnelEastEvents)
  db $01, $01, $0f, $01, $0f, $04, $04, $04, $0f, $0f, 
  db $01, $0f, $01, $0d, $0c, $0c, $01, $0f, $01, $01, 
  db $01, $01, $01, $01, $01, $0c, $01, $01, $01, $01, 
  db $01, $0f, $01, $01, $01, $0c, $01, $01, $01, $01, 
  db $04, $0f, $0f, $01, $01, $06, $01, $01, $01, $01, 
  db $04, $04, $0f, $01, $01, $0c, $06, $01, $01, $01, 
  db $04, $0f, $01, $01, $0f, $06, $06, $06, $06, $06, 
  db $0f, $01, $01, $0f, $01, $01, $01, $0f, $0f, $01, 
  db $04, $04, $04, $01, $01, $0f, $04, $04, $04, $01, 

SwampTunnelEastEvents:
  AllocateTransportEvent 6, 9, HIGH(Overworld), LOW(Overworld), 1, 39
  AllocateTransportEvent 1, 3, HIGH(Underworld), LOW(Underworld), 2, 78
  EndList

ENDC