IF !DEF(UNDERPASS_TWO_INC)
UNDERPASS_TWO_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "UnderpassTwo", ROMX, BANK[1]
  db HAS_BOUNDS
UnderpassTwo:
  db 9, 10, HIGH(UnderpassTwoAutoEvents), LOW(UnderpassTwoAutoEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $bb, $bb, $bb, $bb, $bb, 
  db $00, $00, $00, $00, $0b, 
  db $0b, $bb, $bb, $bb, $0b, 
  db $0b, $bb, $bb, $bb, $bb, 
  db $0e, $be, $00, $00, $0b, 
  db $0b, $bb, $bb, $bb, $0b, 
  db $0b, $bb, $bb, $bb, $0b, 
  db $00, $00, $00, $00, $0b, 
  db $bb, $bb, $bb, $bb, $bb, 

UnderpassTwoAutoEvents:
  ; underworld
  AllocateTransportEvent 4, 1, HIGH(Underworld), LOW(Underworld), 46, 28
  AllocateTransportEvent 4, 3, HIGH(Underworld), LOW(Underworld), 46, 32

  EndList

UnderpassTwoTriggerEvents:
  EndList

ENDC