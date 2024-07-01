
IF !DEF(CAVE_PASSAGE_INC)
CAVE_PASSAGE_INC = 1

Section "cave_passage", ROM0
cave_passage:
  db height, width, HIGH(cave_passageAutoEvents), LOW($cave_passageAutoEvents)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $4b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $b0, $4b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $b0, $4b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $4b, $bb, $bb, 
  db $bb, $bb, $bb, $be, $00, $0b, $bb, $4b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $0b, $bb, $40, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $0b, $bb, $40, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $0b, $b4, $4b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $0b, $b4, $bb, $bb, $bb, 
  db $bb, $bb, $00, $00, $00, $00, $05, $00, $0b, $bb, 
  db $bb, $bb, $0b, $bb, $bb, $0b, $b4, $bb, $00, $bb, 
  db $bb, $bb, $0b, $bb, $bb, $0b, $44, $4b, $b0, $0e, 
  db $bb, $bb, $0b, $bb, $bb, $0b, $44, $4b, $b0, $bb, 
  db $bb, $bb, $0b, $bb, $bb, $0b, $4b, $bb, $00, $bb, 
  db $bb, $bb, $eb, $00, $00, $00, $50, $00, $0b, $bb, 
  db $00, $bb, $bb, $bb, $bb, $bb, $40, $bb, $bb, $bb, 
  db $44, $44, $44, $44, $44, $44, $40, $bb, $bb, $bb, 
  db $bb, $bb, $b0, $0b, $bb, $bb, $00, $bb, $bb, $bb, 

cave_passageAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        