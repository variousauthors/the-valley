
IF !DEF(COASTAL_GROVE_INC)
COASTAL_GROVE_INC = 1

Section "coastal_grove", ROM0
coastal_grove:
  db height, width, HIGH(coastal_groveAutoEvents), LOW($coastal_groveAutoEvents)
  db $11, $11, $11, $11, $11, 
  db $11, $16, $11, $11, $11, 
  db $11, $11, $dc, $c6, $11, 
  db $11, $11, $11, $1c, $11, 
  db $11, $11, $11, $16, $11, 
  db $16, $c6, $cc, $6c, $11, 
  db $11, $c1, $61, $11, $61, 
  db $11, $61, $11, $11, $11, 
  db $11, $c1, $11, $11, $11, 

coastal_groveAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        