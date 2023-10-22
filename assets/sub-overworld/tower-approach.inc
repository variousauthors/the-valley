
IF !DEF(TOWER_APPROACH_INC)
TOWER_APPROACH_INC = 1

Section "tower_approach", ROM0
tower_approach:
  db height, width, HIGH(tower_approachAutoEvents), LOW($tower_approachAutoEvents)
  db $11, $11, $b1, $11, $11, 
  db $11, $b6, $c6, $b1, $11, 
  db $11, $6c, $cc, $61, $11, 
  db $1b, $cc, $dc, $cb, $11, 
  db $11, $6c, $cc, $61, $11, 
  db $11, $b6, $c6, $b1, $11, 
  db $11, $16, $c6, $11, $11, 
  db $11, $b6, $c6, $b1, $11, 
  db $11, $16, $c6, $11, $11, 
  db $11, $b6, $c6, $b1, $11, 
  db $11, $16, $c6, $11, $11, 
  db $11, $b6, $c6, $b1, $11, 
  db $11, $16, $c6, $11, $11, 
  db $11, $b6, $c6, $b1, $11, 
  db $11, $16, $c6, $11, $11, 
  db $11, $b6, $c6, $b1, $11, 
  db $11, $16, $c6, $11, $11, 
  db $11, $b6, $c6, $b1, $11, 

tower_approachAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        