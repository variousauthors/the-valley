
IF !DEF(RUINS_ONE_INTERIOR_INC)
RUINS_ONE_INTERIOR_INC = 1

Section "ruins_one_interior", ROM0
ruins_one_interior:
  db height, width, HIGH(ruins_one_interiorAutoEvents), LOW($ruins_one_interiorAutoEvents)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $d0, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $b6, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $6b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

ruins_one_interiorAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        