IF !DEF(TOWER_INTERIOR_INC)
TOWER_INTERIOR_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "TowerInterior", ROM0
TowerInterior:
  db 18, 30, HIGH(TowerInteriorAutoEvents), LOW(TowerInteriorAutoEvents)
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $00, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $00, $00, $00, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $0d, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 

TowerInteriorAutoEvents:
  ; underworld, meditation room
  AllocateTransportEvent 14, 15, HIGH(MeditationRoom), LOW(MeditationRoom), 4, 4

  ; interior
  AllocateTransportEvent 12, 7, HIGH(Tower), LOW(Tower), 12, 7
  AllocateTransportEvent 12, 22, HIGH(Tower), LOW(Tower), 12, 22
  AllocateTransportEvent 2, 3, HIGH(Tower), LOW(Tower), 2, 3
  AllocateTransportEvent 2, 26, HIGH(Tower), LOW(Tower), 2, 26

  EndList

TowerInteriorTriggerEvents:
  EndList

ENDC