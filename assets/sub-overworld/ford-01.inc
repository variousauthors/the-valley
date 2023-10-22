
IF !DEF(FORD_01_INC)
FORD_01_INC = 1

Section "ford_01", ROM0
ford_01:
  db height, width, HIGH(ford_01AutoEvents), LOW($ford_01AutoEvents)
  db $1f, $44, $44, $4f, $41, 
  db $1f, $f4, $44, $ff, $41, 
  db $1f, $4f, $ff, $f4, $66, 
  db $66, $4f, $4f, $44, $61, 
  db $16, $64, $ff, $f6, $61, 
  db $16, $4f, $ff, $4f, $61, 
  db $16, $ff, $4f, $4f, $f1, 
  db $14, $ff, $4f, $ff, $4f, 
  db $14, $44, $44, $f4, $4f, 

ford_01AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        