
IF !DEF(TOWER_APPROACH_INC)
TOWER_APPROACH_INC = 1

Section "tower_approach", ROM0
tower_approach:
  db 18, 10, 
  db HIGH(tower_approachAutoEvents), LOW(tower_approachAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(tower_approachBumpEvents), LOW(tower_approachBumpEvents)
  db HIGH(tower_approachEntities), LOW(tower_approachEntities)
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
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

tower_approachBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

tower_approachEntities:
  ret

ENDC