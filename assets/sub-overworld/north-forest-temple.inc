
IF !DEF(NORTH_FOREST_TEMPLE_INC)
NORTH_FOREST_TEMPLE_INC = 1

Section "north_forest_temple", ROM0
north_forest_temple:
db height, width, HIGH(north_forest_templeAutoEvents), LOW($north_forest_templeAutoEvents)
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $01, $0b, $01, $01, $01, $0b, $01, $01, 
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $0c, $0c, $06, $0c, $0d, $01, $01, $01, $01, 
db $01, $0c, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $06, $01, $0b, $01, $01, $01, $0b, $01, $01, 
db $01, $0c, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $06, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $0c, $01, $01, $01, $01, $01, $01, $01, $01, 

north_forest_templeAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        