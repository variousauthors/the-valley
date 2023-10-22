
IF !DEF(PENINSULA_RUINS_INC)
PENINSULA_RUINS_INC = 1

Section "peninsula_ruins", ROM0
peninsula_ruins:
  db height, width, HIGH(peninsula_ruinsAutoEvents), LOW($peninsula_ruinsAutoEvents)
  db $11, $b1, $11, $b1, $11, 
  db $11, $11, $d1, $11, $11, 
  db $11, $b1, $61, $b4, $41, 
  db $f4, $4f, $cf, $44, $41, 
  db $44, $b1, $c1, $bf, $f1, 
  db $f4, $41, $c1, $11, $11, 
  db $1f, $b1, $ff, $b4, $41, 
  db $11, $11, $c1, $f1, $11, 
  db $11, $11, $61, $11, $11, 

peninsula_ruinsAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        