IF !DEF(UNDERPASS_ONE_INC)
UNDERPASS_ONE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "UnderpassOne", ROM0
  db HAS_BOUNDS
UnderpassOne:
  db 9, 10, HIGH(UnderpassOneAutoEvents), LOW(UnderpassOneAutoEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, 
  db $b0, $00, $00, $be, $bb, 
  db $b0, $bb, $bb, $b0, $bb, 
  db $b0, $bb, $bb, $b0, $bb, 
  db $b0, $bb, $bb, $b0, $bb, 
  db $b0, $0b, $bb, $b0, $bb, 
  db $be, $00, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, 

UnderpassOneAutoEvents:
  ; underworld
  AllocateTransportEvent 7, 1, HIGH(Underworld), LOW(Underworld), 58, 12
  AllocateTransportEvent 2, 7, HIGH(Underworld), LOW(Underworld), 48, 19

  EndList

UnderpassOneTriggerEvents:
  EndList

ENDC