IF !DEF(TOWER_INTERIOR_INC)
TOWER_INTERIOR_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "TowerInterior", ROM0
  db HAS_BOUNDS
TowerInterior:
  db 18, 30, HIGH(TowerInteriorAutoEvents), LOW(TowerInteriorAutoEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $00, $bb, $bb, 
  db $bb, $b0, $00, $00, $00, $00, $0b, $bb, $bb, $00, $00, $00, $00, $0b, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $b0, $00, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $b0, $00, $00, $00, $00, $00, $0b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $0b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $0b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $00, $0b, $b0, $bb, $b0, $bb, $bb, $b0, $00, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $00, $00, $00, $bb, $b0, $bb, $bb, $b0, $00, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $00, $0b, $bb, $bb, $b0, $bb, $bb, $b0, $00, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $0b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0d, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

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