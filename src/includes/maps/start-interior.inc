IF !DEF(START_INTERIOR)
START_INTERIOR = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "StartInterior", ROM0
StartInterior:
  db 9, 10, HIGH(StartInteriorAutoEvents), LOW(StartInteriorAutoEvents)
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $00, $00, $0d, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $06, $00, $00, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $00, $00, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 

StartInteriorAutoEvents:
  ; exterior
  AllocateTransportEvent 4, 3, HIGH(Start), LOW(Start), 4, 3

  ; underworld
  AllocateTransportEvent 3, 6, HIGH(Underworld), LOW(Underworld), 60, 24

  EndList

StartInteriorTriggerEvents:
  EndList

ENDC