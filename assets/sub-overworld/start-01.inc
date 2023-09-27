
IF !DEF(START_01_INC)
START_01_INC = 1

Section "start_01", ROM0
start_01:
db height, width, HIGH(start_01AutoEvents), LOW($start_01AutoEvents)
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $06, 
db $01, $01, $06, $06, $01, $01, $06, $06, $06, $01, 
db $01, $06, $06, $0b, $0b, $0b, $0b, $0b, $06, $01, 
db $01, $06, $06, $0b, $0b, $0b, $0b, $0b, $01, $06, 
db $0c, $0c, $0c, $06, $0b, $0b, $0b, $0b, $06, $01, 
db $01, $06, $06, $0b, $0b, $0b, $0b, $0b, $06, $01, 
db $01, $01, $06, $0b, $0b, $0b, $0b, $0b, $06, $06, 
db $01, $01, $01, $06, $0b, $0b, $0b, $0b, $06, $01, 
db $01, $01, $01, $01, $06, $06, $06, $06, $01, $01, 

start_01AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        