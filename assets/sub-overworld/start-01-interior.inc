
IF !DEF(START_01_INTERIOR_INC)
START_01_INTERIOR_INC = 1

Section "start_01_interior", ROM0
start_01_interior:
db height, width, HIGH(start_01_interiorAutoEvents), LOW($start_01_interiorAutoEvents)
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $0b, $0b, $0b, $0b, $00, $00, $0d, $0b, $0b, $0b, 
db $0b, $0b, $0b, $06, $00, $00, $0b, $0b, $0b, $0b, 
db $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, 
db $0b, $0b, $0b, $0b, $0b, $00, $00, $0b, $0b, $0b, 
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 

start_01_interiorAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        