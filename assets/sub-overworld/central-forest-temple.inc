
IF !DEF(CENTRAL_FOREST_TEMPLE_INC)
CENTRAL_FOREST_TEMPLE_INC = 1

Section "central_forest_temple", ROM0
central_forest_temple:
db height, width, HIGH(central_forest_templeAutoEvents), LOW($central_forest_templeAutoEvents)
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $06, $0c, $0c, $06, $01, $01, $01, $01, $01, $01, 
db $01, $01, $06, $01, $01, $0b, $01, $0b, $01, $01, 
db $01, $01, $0c, $01, $0b, $06, $06, $06, $0b, $01, 
db $01, $01, $0c, $06, $0c, $06, $0d, $06, $01, $01, 
db $01, $01, $01, $01, $0b, $06, $06, $06, $0b, $01, 
db $01, $06, $01, $01, $01, $0b, $01, $0b, $01, $01, 
db $01, $04, $04, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 

central_forest_templeAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        