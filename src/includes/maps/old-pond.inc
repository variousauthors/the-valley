IF !DEF(OLD_POND_INC)
OLD_POND_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "OldPond", ROM0
OldPond:
  db 9, 10, HIGH(OldPondEvents), LOW(OldPondEvents)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $1d, $11, $11, 
  db $11, $16, $cc, $c6, $11, 
  db $11, $11, $44, $46, $11, 
  db $11, $16, $44, $46, $11, 
  db $11, $61, $66, $61, $11, 
  db $11, $16, $16, $11, $11, 
  db $11, $11, $1c, $11, $11, 
  db $11, $11, $1c, $11, $11, 

OldPondEvents:
  AllocateTransportEvent 8, 5, HIGH(Overworld), LOW(Overworld), 18, 8
  AllocateTransportEvent 1, 5, HIGH(Underworld), LOW(Underworld), 36, 16
  EndList

ENDC