
IF !DEF(SWAMP_TUNNEL_WEST_INC)
SWAMP_TUNNEL_WEST_INC = 1

Section "swamp_tunnel_west", ROM0
swamp_tunnel_west:
  db height, width, HIGH(swamp_tunnel_westAutoEvents), LOW($swamp_tunnel_westAutoEvents)
  db $14, $41, $f4, $44, $14, 
  db $1f, $f1, $1f, $1f, $14, 
  db $11, $11, $11, $11, $1f, 
  db $66, $66, $11, $11, $1f, 
  db $11, $1c, $6c, $c1, $11, 
  db $11, $11, $11, $c1, $f1, 
  db $11, $11, $11, $d1, $1f, 
  db $11, $1f, $f1, $11, $f4, 
  db $1f, $44, $4f, $f4, $44, 

swamp_tunnel_westAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        