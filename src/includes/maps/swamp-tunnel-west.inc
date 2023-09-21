IF !DEF(SWAMP_TUNNEL_WEST_INC)
SWAMP_TUNNEL_WEST_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "SwampTunnelWest", ROM0
SwampTunnelWest:
  db 9, 10, HIGH(SwampTunnelWestEvents), LOW(SwampTunnelWestEvents)
  db $01, $04, $04, $01, $0f, $04, $04, $04, $01, $04, 
  db $01, $0f, $0f, $01, $01, $0f, $01, $0f, $01, $04, 
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $0f, 
  db $06, $06, $06, $06, $01, $01, $01, $01, $01, $0f, 
  db $01, $01, $01, $0c, $06, $0c, $0c, $01, $01, $01, 
  db $01, $01, $01, $01, $01, $01, $0c, $01, $0f, $01, 
  db $01, $01, $01, $01, $01, $01, $0d, $01, $01, $0f, 
  db $01, $01, $01, $0f, $0f, $01, $01, $01, $0f, $04, 
  db $01, $0f, $04, $04, $04, $0f, $0f, $04, $04, $04, 

SwampTunnelWestEvents:
  AllocateTransportEvent 3, 0, HIGH(Overworld), LOW(Overworld), 3, 37
  AllocateTransportEvent 6, 6, HIGH(Underworld), LOW(Underworld), 6, 74

  EndList

ENDC