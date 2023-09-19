
IF !DEF(TUNNELS_ENTRANCE_INC)
TUNNELS_ENTRANCE_INC = 1

Section "tunnels_entrance", ROM0
tunnels_entrance:
db height, width, HIGH(tunnels_entranceAutoEvents), LOW($tunnels_entranceAutoEvents)
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $0b, $0b, $0b, $0b, $0b, $0d, $0b, $0b, $0b, $0b, 
db $0b, $0b, $0d, $00, $0b, $00, $0b, $00, $0d, $0b, 
db $0b, $0b, $0b, $00, $0b, $00, $0b, $00, $0b, $0b, 
db $0b, $0b, $0b, $00, $0b, $00, $0b, $00, $0b, $0b, 
db $0b, $0b, $0b, $00, $0b, $00, $0b, $00, $0b, $0b, 
db $0b, $0b, $0b, $00, $0b, $00, $0b, $00, $0b, $0b, 
db $0b, $0b, $0b, $0e, $0b, $0e, $0b, $0e, $0b, $0b, 
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 

tunnels_entranceAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        