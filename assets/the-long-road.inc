
IF !DEF(THE_LONG_ROAD_INC)
THE_LONG_ROAD_INC = 1

Section "the_long_road", ROM0
the_long_road:
db height, width, HIGH(the_long_roadAutoEvents), LOW($the_long_roadAutoEvents)
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
db $0b, $00, $00, $00, $00, $00, $00, $00, $00, $0b, 
db $0b, $00, $0b, $00, $0b, $0b, $0b, $0b, $00, $0b, 
db $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $00, $0b, 
db $0b, $0e, $0b, $00, $0b, $0b, $0b, $0b, $0e, $0b, 
db $0b, $00, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, 
db $0b, $00, $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, 
db $0b, $00, $00, $00, $00, $00, $00, $00, $00, $00, 
db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 

the_long_roadAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        