
IF !DEF(OLD_POND_INC)
OLD_POND_INC = 1

Section "old_pond", ROM0
old_pond:
  db height, width, HIGH(old_pondAutoEvents), LOW($old_pondAutoEvents)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $1d, $11, $11, 
  db $11, $16, $cc, $c6, $11, 
  db $11, $11, $44, $46, $11, 
  db $11, $16, $44, $46, $11, 
  db $11, $61, $66, $61, $11, 
  db $11, $16, $16, $11, $11, 
  db $11, $11, $1c, $11, $11, 
  db $11, $11, $1c, $11, $11, 

old_pondAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        