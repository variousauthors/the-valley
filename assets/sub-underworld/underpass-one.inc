
IF !DEF(UNDERPASS_ONE_INC)
UNDERPASS_ONE_INC = 1

Section "underpass_one", ROM0
underpass_one:
db height, width, HIGH(underpass_oneAutoEvents), LOW($underpass_oneAutoEvents)
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $0b, $00, $00, $00, $00, $00, $0b, $0e, $0b, $0b, 
db $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, 
db $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, 
db $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, 
db $0b, $00, $00, $0b, $0b, $0b, $0b, $00, $0b, $0b, 
db $0b, $0e, $00, $00, $00, $00, $00, $00, $0b, $0b, 
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 

underpass_oneAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        