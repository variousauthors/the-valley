
IF !DEF(TWINS_CROSSING_WEST_INC)
TWINS_CROSSING_WEST_INC = 1

Section "twins_crossing_west", ROM0
twins_crossing_west:
db height, width, HIGH(twins_crossing_westAutoEvents), LOW($twins_crossing_westAutoEvents)
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $06, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $01, $01, $0c, $0c, $0d, $01, $01, $01, 
db $01, $01, $06, $01, $0c, $01, $01, $01, $06, $01, 
db $01, $01, $01, $01, $06, $01, $01, $01, $01, $01, 
db $01, $01, $01, $01, $0c, $01, $01, $01, $01, $01, 
db $06, $0c, $06, $0c, $06, $01, $01, $01, $06, $01, 
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $01, $01, $01, $01, $06, $01, $01, $01, 

twins_crossing_westAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        