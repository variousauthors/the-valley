
IF !DEF(SWAMP_TUNNEL_EAST_INC)
SWAMP_TUNNEL_EAST_INC = 1

Section "swamp_tunnel_east", ROM0
swamp_tunnel_east:
  db height, width, HIGH(swamp_tunnel_eastAutoEvents), LOW($swamp_tunnel_eastAutoEvents)
  db $11, $f1, $f4, $44, $ff, 
  db $1f, $1d, $cc, $1f, $11, 
  db $11, $11, $1c, $11, $11, 
  db $1f, $11, $1c, $11, $11, 
  db $4f, $f1, $16, $11, $11, 
  db $44, $f1, $1c, $61, $11, 
  db $4f, $11, $f6, $66, $66, 
  db $f1, $1f, $11, $1f, $f1, 
  db $44, $41, $1f, $44, $41, 

swamp_tunnel_eastAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        