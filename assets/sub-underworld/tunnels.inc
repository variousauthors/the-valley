
IF !DEF(TUNNELS_INC)
TUNNELS_INC = 1

Section "tunnels", ROM0
tunnels:
db height, width, HIGH(tunnelsAutoEvents), LOW($tunnelsAutoEvents)
db $0b, $00, $0e, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $0b, $0e, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0e, $00, 
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, 
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0e, 
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $0e, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $00, $00, $0e, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 

tunnelsAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        