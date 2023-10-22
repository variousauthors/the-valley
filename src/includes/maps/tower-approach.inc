IF !DEF(TOWER_APPROACH)
TOWER_APPROACH = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "TowerApproach", ROM0
TowerApproach:
  db 18, 10, HIGH(TowerApproachAutoEvents), LOW(TowerApproachAutoEvents)
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

TowerApproachAutoEvents:
  ; overworld
  AllocateTransportEvent 17, 4, HIGH(Overworld), LOW(Overworld), 16, 16

  ; underworld
  AllocateTransportEvent 3, 4, HIGH(Underworld), LOW(Underworld), 32, 32

  EndList

TowerApproachTriggerEvents:
  EndList

ENDC