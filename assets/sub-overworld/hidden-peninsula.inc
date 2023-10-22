
IF !DEF(HIDDEN_PENINSULA_INC)
HIDDEN_PENINSULA_INC = 1

Section "hidden_peninsula", ROM0
hidden_peninsula:
  db height, width, HIGH(hidden_peninsulaAutoEvents), LOW($hidden_peninsulaAutoEvents)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 
  db $11, $cc, $66, $c6, $c6, 
  db $11, $c1, $11, $11, $11, 
  db $1b, $6b, $bb, $b1, $11, 
  db $1b, $66, $66, $b1, $11, 
  db $1b, $6d, $61, $11, $11, 
  db $11, $16, $11, $b1, $11, 
  db $11, $bb, $bb, $b1, $11, 

hidden_peninsulaAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        