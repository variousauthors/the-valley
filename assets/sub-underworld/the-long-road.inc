
IF !DEF(THE_LONG_ROAD_INC)
THE_LONG_ROAD_INC = 1

Section "the_long_road", ROM0
the_long_road:
  db height, width, HIGH(the_long_roadAutoEvents), LOW($the_long_roadAutoEvents)
  db $bb, $bb, $bb, $bb, $bb, 
  db $b0, $00, $00, $00, $0b, 
  db $b0, $b0, $bb, $bb, $0b, 
  db $bb, $b0, $bb, $bb, $0b, 
  db $be, $b0, $bb, $bb, $eb, 
  db $b0, $b0, $bb, $bb, $bb, 
  db $b0, $b0, $bb, $bb, $b0, 
  db $b0, $00, $00, $00, $00, 
  db $bb, $bb, $bb, $bb, $bb, 

the_long_roadAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        