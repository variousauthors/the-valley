
IF !DEF(RUINS_THREE_INTERIOR_INC)
RUINS_THREE_INTERIOR_INC = 1

Section "ruins_three_interior", ROM0
ruins_three_interior:
  db height, width, HIGH(ruins_three_interiorAutoEvents), LOW($ruins_three_interiorAutoEvents)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $db, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $06, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $b6, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

ruins_three_interiorAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        