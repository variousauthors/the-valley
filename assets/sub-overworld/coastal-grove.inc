
IF !DEF(COASTAL_GROVE_INC)
COASTAL_GROVE_INC = 1

Section "coastal_grove", ROM0
coastal_grove:
db height, width, HIGH(coastal_groveAutoEvents), LOW($coastal_groveAutoEvents)
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $01, $06, $01, $01, $01, $01, $01, $01, 
db $01, $01, $01, $01, $0d, $0c, $0c, $06, $01, $01, 
db $01, $01, $01, $01, $01, $01, $01, $0c, $01, $01, 
db $01, $01, $01, $01, $01, $01, $01, $06, $01, $01, 
db $01, $06, $0c, $06, $0c, $0c, $06, $0c, $01, $01, 
db $01, $01, $0c, $01, $06, $01, $01, $01, $06, $01, 
db $01, $01, $06, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $0c, $01, $01, $01, $01, $01, $01, $01, 

coastal_groveAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        