
IF !DEF(PENINSULA_RUINS_INC)
PENINSULA_RUINS_INC = 1

Section "peninsula_ruins", ROM0
peninsula_ruins:
db height, width, HIGH(peninsula_ruinsAutoEvents), LOW($peninsula_ruinsAutoEvents)
db $01, $01, $0b, $01, $01, $01, $0b, $01, $01, $01, 
db $01, $01, $01, $01, $0d, $01, $01, $01, $01, $01, 
db $01, $01, $0b, $01, $06, $01, $0b, $04, $04, $01, 
db $0f, $04, $04, $0f, $0c, $0f, $04, $04, $04, $01, 
db $04, $04, $0b, $01, $0c, $01, $0b, $0f, $0f, $01, 
db $0f, $04, $04, $01, $0c, $01, $01, $01, $01, $01, 
db $01, $0f, $0b, $01, $0f, $0f, $0b, $04, $04, $01, 
db $01, $01, $01, $01, $0c, $01, $0f, $01, $01, $01, 
db $01, $01, $01, $01, $06, $01, $01, $01, $01, $01, 

peninsula_ruinsAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        