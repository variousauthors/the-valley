
IF !DEF(OLD_SWAMP_INC)
OLD_SWAMP_INC = 1

Section "old_swamp", ROM0
old_swamp:
  db height, width, HIGH(old_swampAutoEvents), LOW($old_swampAutoEvents)
  db $11, $11, $11, $11, $11, 
  db $11, $d1, $ff, $11, $11, 
  db $11, $c1, $44, $4f, $11, 
  db $11, $cf, $44, $f1, $11, 
  db $11, $61, $ff, $60, $66, 
  db $11, $06, $16, $01, $11, 
  db $11, $66, $06, $61, $11, 
  db $11, $11, $66, $11, $11, 
  db $11, $11, $11, $11, $11, 

old_swampAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        