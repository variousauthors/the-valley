IF !DEF(START_INC)
START_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Start", ROM0
Start:
  db 9, 10, HIGH(StartAutoEvents), LOW(StartAutoEvents)
  db $11, $11, $11, $11, $16, $00, $00, $00, $00, $00
  db $01, $01, $06, $06, $01, $01, $06, $06, $06, $01, 
  db $01, $06, $06, $0b, $0b, $06, $0b, $06, $06, $01, 
  db $01, $06, $06, $0b, $06, $06, $0d, $0b, $01, $06, 
  db $0c, $0c, $0c, $06, $06, $06, $0b, $0b, $06, $01, 
  db $01, $06, $06, $0b, $06, $06, $06, $06, $06, $01, 
  db $01, $01, $06, $06, $0b, $06, $06, $0b, $06, $06, 
  db $01, $01, $01, $06, $06, $0b, $0b, $06, $06, $01, 
  db $01, $01, $01, $01, $06, $06, $06, $06, $01, $01, 

StartAutoEvents:
  ; overworld
  AllocateTransportEvent 4, 0, HIGH(Overworld), LOW(Overworld), 30, 12

  ; underworld
  AllocateTransportEvent 3, 6, HIGH(Underworld), LOW(Underworld), 60, 24

  EndList

StartTriggerEvents:
  EndList

ENDC