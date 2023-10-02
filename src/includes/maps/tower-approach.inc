IF !DEF(TOWER_APPROACH)
TOWER_APPROACH = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "TowerApproach", ROM0
TowerApproach:
  db 18, 10, HIGH(TowerApproachAutoEvents), LOW(TowerApproachAutoEvents)
  db $01, $01, $01, $01, $0b, $01, $01, $01, $01, $01, 
  db $01, $01, $0b, $06, $0c, $06, $0b, $01, $01, $01, 
  db $01, $01, $06, $0c, $0c, $0c, $06, $01, $01, $01, 
  db $01, $0b, $0c, $0c, $0d, $0c, $0c, $0b, $01, $01, 
  db $01, $01, $06, $0c, $0c, $0c, $06, $01, $01, $01, 
  db $01, $01, $0b, $06, $0c, $06, $0b, $01, $01, $01, 
  db $01, $01, $01, $06, $0c, $06, $01, $01, $01, $01, 
  db $01, $01, $0b, $06, $0c, $06, $0b, $01, $01, $01, 
  db $01, $01, $01, $06, $0c, $06, $01, $01, $01, $01, 
  db $01, $01, $0b, $06, $0c, $06, $0b, $01, $01, $01, 
  db $01, $01, $01, $06, $0c, $06, $01, $01, $01, $01, 
  db $01, $01, $0b, $06, $0c, $06, $0b, $01, $01, $01, 
  db $01, $01, $01, $06, $0c, $06, $01, $01, $01, $01, 
  db $01, $01, $0b, $06, $0c, $06, $0b, $01, $01, $01, 
  db $01, $01, $01, $06, $0c, $06, $01, $01, $01, $01, 
  db $01, $01, $0b, $06, $0c, $06, $0b, $01, $01, $01, 
  db $01, $01, $01, $06, $0c, $06, $01, $01, $01, $01, 
  db $01, $01, $0b, $06, $0c, $06, $0b, $01, $01, $01, 

TowerApproachAutoEvents:
  ; overworld
  AllocateTransportEvent 17, 4, HIGH(Overworld), LOW(Overworld), 16, 16

  ; underworld
  AllocateTransportEvent 3, 4, HIGH(Underworld), LOW(Underworld), 32, 32

  EndList

TowerApproachTriggerEvents:
  EndList

ENDC