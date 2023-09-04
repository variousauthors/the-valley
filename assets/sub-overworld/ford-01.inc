
IF !DEF(FORD_01_INC)
FORD_01_INC = 1

Section "ford_01", ROM0
ford_01:
db height, width, HIGH(ford_01AutoEvents), LOW($ford_01AutoEvents)
db $01, $0f, $04, $04, $04, $04, $04, $0f, $04, $01, 
db $01, $0f, $0f, $04, $04, $04, $0f, $0f, $04, $01, 
db $01, $0f, $04, $0f, $0f, $0f, $0f, $04, $06, $06, 
db $06, $06, $04, $0f, $04, $0f, $04, $04, $06, $01, 
db $01, $06, $06, $04, $0f, $0f, $0f, $06, $06, $01, 
db $01, $06, $04, $0f, $0f, $0f, $04, $0f, $06, $01, 
db $01, $06, $0f, $0f, $04, $0f, $04, $0f, $0f, $01, 
db $01, $04, $0f, $0f, $04, $0f, $0f, $0f, $04, $0f, 
db $01, $04, $04, $04, $04, $04, $0f, $04, $04, $0f, 

ford_01AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        