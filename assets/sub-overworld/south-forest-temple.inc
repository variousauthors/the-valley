
IF !DEF(SOUTH_FOREST_TEMPLE_INC)
SOUTH_FOREST_TEMPLE_INC = 1

Section "south_forest_temple", ROM0
south_forest_temple:
  db height, width, HIGH(south_forest_templeAutoEvents), LOW($south_forest_templeAutoEvents)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $1b, $b1, $b1, 
  db $cc, $1b, $11, $61, $b1, 
  db $16, $1b, $1b, $b6, $b1, 
  db $1c, $6c, $6b, $66, $6b, 
  db $11, $1b, $66, $6d, $1b, 
  db $11, $11, $bb, $16, $11, 
  db $11, $11, $1b, $1b, $bb, 
  db $11, $11, $11, $11, $11, 

south_forest_templeAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        