
IF !DEF(TWINS_CROSSING_EAST_INC)
TWINS_CROSSING_EAST_INC = 1

Section "twins_crossing_east", ROM0
twins_crossing_east:
db height, width, HIGH(twins_crossing_eastAutoEvents), LOW($twins_crossing_eastAutoEvents)
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $01, $06, $01, $01, $01, $01, $06, $01, 
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $01, $01, $0c, $06, $0c, $01, $0c, $06, 
db $06, $01, $01, $06, $01, $01, $0c, $01, $01, $01, 
db $01, $01, $01, $0c, $01, $01, $0c, $01, $01, $01, 
db $01, $01, $01, $0d, $01, $01, $06, $06, $06, $01, 
db $01, $06, $01, $01, $01, $01, $06, $04, $06, $01, 
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 

twins_crossing_eastAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        