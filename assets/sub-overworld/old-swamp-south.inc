
IF !DEF(OLD_SWAMP_SOUTH_INC)
OLD_SWAMP_SOUTH_INC = 1

Section "old_swamp_south", ROM0
old_swamp_south:
  db height, width, HIGH(old_swamp_southAutoEvents), LOW($old_swamp_southAutoEvents)
  db $11, $1c, $1f, $f1, $11, 
  db $1f, $16, $11, $ff, $1f, 
  db $f1, $1c, $11, $ff, $f1, 
  db $1f, $16, $11, $1f, $11, 
  db $11, $1c, $11, $11, $f1, 
  db $11, $1c, $11, $1f, $11, 
  db $21, $16, $cd, $1f, $12, 
  db $21, $f1, $11, $11, $12, 
  db $12, $11, $f1, $f1, $21, 

old_swamp_southAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        