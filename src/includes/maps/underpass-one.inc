IF !DEF(UNDERPASS_ONE_INC)
UNDERPASS_ONE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "UnderpassOne", ROMX, BANK[1]
UnderpassOne:
  db 9, 10, HIGH(UnderpassOneAutoEvents), LOW(UnderpassOneAutoEvents)
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $00, $00, $00, $00, $00, $0b, $0e, $0b, $0b, 
  db $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, 
  db $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, 
  db $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, $0b, $0b, 
  db $0b, $00, $00, $0b, $0b, $0b, $0b, $00, $0b, $0b, 
  db $0b, $0e, $00, $00, $00, $00, $00, $00, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 

UnderpassOneAutoEvents:
  ; underworld
  AllocateTransportEvent 7, 1, HIGH(Underworld), LOW(Underworld), 58, 12
  AllocateTransportEvent 2, 7, HIGH(Underworld), LOW(Underworld), 48, 19

  EndList

UnderpassOneTriggerEvents:
  EndList

ENDC