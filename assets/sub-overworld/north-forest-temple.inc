
IF !DEF(NORTH_FOREST_TEMPLE_INC)
NORTH_FOREST_TEMPLE_INC = 1

Section "north_forest_temple", ROM0
north_forest_temple:
  db height, width, HIGH(north_forest_templeAutoEvents), LOW($north_forest_templeAutoEvents)
  db $11, $11, $11, $11, $11, 
  db $11, $1b, $11, $1b, $11, 
  db $11, $11, $11, $11, $11, 
  db $1c, $c6, $cd, $11, $11, 
  db $1c, $11, $11, $11, $11, 
  db $16, $1b, $11, $1b, $11, 
  db $1c, $11, $11, $11, $11, 
  db $16, $11, $11, $11, $11, 
  db $1c, $11, $11, $11, $11, 

north_forest_templeAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        