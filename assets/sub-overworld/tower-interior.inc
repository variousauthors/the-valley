
IF !DEF(TOWER_INTERIOR_INC)
TOWER_INTERIOR_INC = 1

Section "tower_interior", ROM0
tower_interior:
  db height, width, HIGH(tower_interiorAutoEvents), LOW($tower_interiorAutoEvents)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $00, $bb, $bb, 
  db $bb, $b0, $00, $00, $00, $00, $0b, $bb, $bb, $00, $00, $00, $00, $0b, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $b0, $00, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $b0, $00, $00, $00, $00, $00, $0b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $0b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $0b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $00, $0b, $b0, $bb, $b0, $bb, $bb, $b0, $00, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $00, $00, $00, $bb, $b0, $bb, $bb, $b0, $00, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $00, $0b, $bb, $bb, $b0, $bb, $bb, $b0, $00, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $0b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0d, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

tower_interiorAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        