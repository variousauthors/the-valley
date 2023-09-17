
IF !DEF(SOUTH_FOREST_TEMPLE_INC)
SOUTH_FOREST_TEMPLE_INC = 1

Section "south_forest_temple", ROM0
south_forest_temple:
db height, width, HIGH(south_forest_templeAutoEvents), LOW($south_forest_templeAutoEvents)
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $01, $01, $01, $0b, $0b, $01, $0b, $01, 
db $0c, $0c, $01, $0b, $01, $01, $06, $01, $0b, $01, 
db $01, $06, $01, $0b, $01, $0b, $0b, $06, $0b, $01, 
db $01, $0c, $06, $0c, $06, $0b, $06, $06, $06, $0b, 
db $01, $01, $01, $0b, $06, $06, $06, $0d, $01, $0b, 
db $01, $01, $01, $01, $0b, $0b, $01, $06, $01, $01, 
db $01, $01, $01, $01, $01, $0b, $01, $0b, $0b, $0b, 
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 

south_forest_templeAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        