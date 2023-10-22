
IF !DEF(TWINS_CROSSING_EAST_INC)
TWINS_CROSSING_EAST_INC = 1

Section "twins_crossing_east", ROM0
twins_crossing_east:
  db height, width, HIGH(twins_crossing_eastAutoEvents), LOW($twins_crossing_eastAutoEvents)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 
  db $11, $11, $c6, $cc, $c6, 
  db $11, $16, $11, $16, $11, 
  db $11, $1c, $11, $16, $11, 
  db $11, $1d, $11, $44, $41, 
  db $11, $11, $11, $44, $41, 
  db $11, $11, $11, $11, $11, 

twins_crossing_eastAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        