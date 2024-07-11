
IF !DEF(NORTH_GROVE_EXIT_INC)
NORTH_GROVE_EXIT_INC = 1

Section "north_grove_exit", ROM0
north_grove_exit:
  db height, width, HIGH(north_grove_exitAutoEvents), LOW($north_grove_exitAutoEvents)
  db $11, $11, $11, $11, $11, $11, $11, 
  db $11, $11, $16, $b6, $bb, $11, $11, 
  db $11, $11, $61, $00, $0b, $66, $11, 
  db $11, $10, $b0, $00, $11, $66, $11, 
  db $11, $66, $60, $0c, $cc, $6c, $c6, 
  db $11, $66, $b0, $00, $0b, $66, $16, 
  db $16, $16, $b6, $6b, $b6, $61, $11, 
  db $16, $61, $66, $66, $66, $16, $66, 
  db $61, $61, $64, $46, $66, $66, $16, 
  db $11, $66, $64, $44, $46, $66, $10, 
  db $11, $16, $66, $44, $46, $06, $16, 
  db $61, $16, $61, $06, $60, $61, $66, 
  db $16, $11, $66, $66, $16, $bb, $61, 
  db $11, $11, $11, $10, $61, $60, $11, 

north_grove_exitAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        