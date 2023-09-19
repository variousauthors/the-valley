
IF !DEF(UNDERPASS_TWO_INC)
UNDERPASS_TWO_INC = 1

Section "underpass_two", ROM0
underpass_two:
db height, width, HIGH(underpass_twoAutoEvents), LOW($underpass_twoAutoEvents)
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, 
db $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, 
db $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $00, $0e, $0b, $0e, $00, $00, $00, $00, $00, $0b, 
db $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, 
db $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, 
db $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, 
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 

underpass_twoAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        