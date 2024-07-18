
IF !DEF(TINY_MAP_INC)
TINY_MAP_INC = 1

Section "tiny_map", ROM0
tiny_map:
  db height, width, HIGH(tiny_mapAutoEvents), LOW($tiny_mapAutoEvents)
  db $36, $66, 
  db $66, $66, 
  db $66, $66, 
  db $66, $66, 
  db $66, $66, 

tiny_mapAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        