
IF !DEF(SWAMP_TUNNEL_EAST_INC)
SWAMP_TUNNEL_EAST_INC = 1

Section "swamp_tunnel_east", ROM0
swamp_tunnel_east:
db height, width, HIGH(swamp_tunnel_eastAutoEvents), LOW($swamp_tunnel_eastAutoEvents)
db $01, $01, $0f, $01, $0f, $04, $04, $04, $0f, $0f, 
db $01, $0f, $01, $0d, $0c, $0c, $01, $0f, $01, $01, 
db $01, $01, $01, $01, $01, $0c, $01, $01, $01, $01, 
db $01, $0f, $01, $01, $01, $0c, $01, $01, $01, $01, 
db $04, $0f, $0f, $01, $01, $06, $01, $01, $01, $01, 
db $04, $04, $0f, $01, $01, $0c, $06, $01, $01, $01, 
db $04, $0f, $01, $01, $0f, $06, $06, $06, $06, $06, 
db $0f, $01, $01, $0f, $01, $01, $01, $0f, $0f, $01, 
db $04, $04, $04, $01, $01, $0f, $04, $04, $04, $01, 

swamp_tunnel_eastAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        