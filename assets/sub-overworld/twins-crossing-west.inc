
IF !DEF(TWINS_CROSSING_WEST_INC)
TWINS_CROSSING_WEST_INC = 1

Section "twins_crossing_west", ROM0
twins_crossing_west:
  db height, width, HIGH(twins_crossing_westAutoEvents), LOW($twins_crossing_westAutoEvents)
  db $11, $11, $11, $11, $11, 
  db $16, $11, $11, $11, $11, 
  db $11, $11, $cc, $d1, $11, 
  db $11, $61, $c1, $11, $61, 
  db $11, $11, $61, $11, $11, 
  db $11, $11, $c1, $11, $11, 
  db $6c, $6c, $61, $11, $61, 
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $61, $11, 

twins_crossing_westAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        