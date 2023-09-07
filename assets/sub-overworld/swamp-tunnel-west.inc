
IF !DEF(SWAMP_TUNNEL_WEST_INC)
SWAMP_TUNNEL_WEST_INC = 1

Section "swamp_tunnel_west", ROM0
swamp_tunnel_west:
db height, width, HIGH(swamp_tunnel_westAutoEvents), LOW($swamp_tunnel_westAutoEvents)
db $04, $04, $04, $01, $0f, $04, $04, $04, $01, $04, 
db $01, $0f, $0f, $01, $01, $0f, $01, $0f, $01, $04, 
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $0f, 
db $06, $06, $06, $06, $01, $01, $01, $01, $01, $0f, 
db $01, $01, $01, $0c, $06, $0c, $0c, $01, $01, $01, 
db $01, $01, $01, $01, $01, $01, $0c, $01, $0f, $01, 
db $01, $01, $01, $01, $01, $01, $0d, $01, $01, $0f, 
db $01, $01, $01, $0f, $0f, $01, $01, $01, $0f, $04, 
db $01, $0f, $04, $04, $04, $0f, $0f, $04, $04, $04, 

swamp_tunnel_westAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        