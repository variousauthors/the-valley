
IF !DEF(THE_CATACOMBS_INC)
THE_CATACOMBS_INC = 1

Section "the_catacombs", ROM0
the_catacombs:
  db height, width, HIGH(the_catacombsAutoEvents), LOW($the_catacombsAutoEvents)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $e0, $00, $b0, $00, $b0, $b0, $e0, $00, $b0, $00, $b0, $b0, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $b0, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $b0, $e0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $00, $b0, $b0, $e0, $00, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $b0, $b0, $00, $b0, $00, $b0, $b0, $e0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $e0, $00, $b0, $b0, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $b0, $b0, $00, $e0, $b0, $b0, $b0, $e0, $00, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $b0, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $e0, $00, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $b0, $b0, $00, $b0, $00, $b0, $00, $e0, $00, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

the_catacombsAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        