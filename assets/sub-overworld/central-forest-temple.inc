
IF !DEF(CENTRAL_FOREST_TEMPLE_INC)
CENTRAL_FOREST_TEMPLE_INC = 1

Section "central_forest_temple", ROM0
central_forest_temple:
  db height, width, HIGH(central_forest_templeAutoEvents), LOW($central_forest_templeAutoEvents)
  db $11, $11, $11, $11, $11, 
  db $6c, $c6, $11, $11, $11, 
  db $11, $61, $1b, $1b, $11, 
  db $11, $c1, $b6, $66, $b1, 
  db $11, $c6, $c6, $d6, $11, 
  db $11, $11, $b6, $66, $b1, 
  db $16, $11, $1b, $1b, $11, 
  db $14, $41, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 

central_forest_templeAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        