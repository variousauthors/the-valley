
IF !DEF(HIDDEN_PENINSULA_INC)
HIDDEN_PENINSULA_INC = 1

Section "hidden_peninsula", ROM0
hidden_peninsula:
db height, width, HIGH(hidden_peninsulaAutoEvents), LOW($hidden_peninsulaAutoEvents)
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $0c, $0c, $06, $06, $0c, $06, $0c, $06, 
db $01, $01, $0c, $01, $01, $01, $01, $01, $01, $01, 
db $01, $0b, $06, $0b, $0b, $0b, $0b, $01, $01, $01, 
db $01, $0b, $06, $06, $06, $06, $0b, $01, $01, $01, 
db $01, $0b, $06, $0d, $06, $01, $01, $01, $01, $01, 
db $01, $01, $01, $06, $01, $01, $0b, $01, $01, $01, 
db $01, $01, $0b, $0b, $0b, $0b, $0b, $01, $01, $01, 

hidden_peninsulaAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        