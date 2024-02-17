IF !DEF(UNDERWORLD_INC)
UNDERWORLD_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Underworld", ROMX, BANK[1]
  db HAS_BOUNDS
Underworld:
  db 72, 100, HIGH(UnderworldAutoEvents), LOW(UnderworldAutoEvents), HIGH(InteriorTileset), LOW(InteriorTileset)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $00, $00, $00, $00, $00, $00, $b0, $00, $00, $00, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $0b, $0b, $bb, $bb, $bb, $0b, $00, $00, $00, $00, $00, $00, $0b, 
  db $bb, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $00, $00, $0b, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $bb, $bb, $bb, $0b, $eb, $b0, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $bb, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $00, $00, $00, $bb, $bb, $b0, $bb, $0b, $0b, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $03, $33, $30, $00, $0b, $0b, $b0, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $bb, $bb, $00, $00, $00, $00, $00, $00, $00, $eb, $00, $0b, $bb, $b0, $bb, $bb, $0b, $db, $b0, $bb, $bb, $00, $bb, $db, $0b, $0b, $00, $00, $00, $33, $33, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, $0b, $b0, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $00, $00, $0b, $bb, $bb, $bb, $0b, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $00, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $0b, $bb, $b0, $00, $00, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $bb, $0b, $0b, $bb, $bb, $bb, $bb, $bb, $eb, $b0, $bb, $bb, $b0, $eb, $bb, $0b, $b0, $bb, $0b, $00, $00, $00, $00, $bb, $bb, $0b, 
  db $bb, $bb, $0b, $00, $00, $0b, $bb, $00, $00, $00, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $b0, $00, $0b, $bb, $bb, $bb, $0b, $0b, $bb, $bb, $bb, $bb, $bb, $0b, $b0, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $bb, $bb, $0b, $0b, $bb, $0b, $eb, $0b, $b0, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $00, $00, $00, $b0, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $00, $eb, $bb, $bb, $bb, $00, $b0, $00, $00, $b0, $00, $00, $00, $b0, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $bb, $bb, $00, $0b, $00, $00, $00, $0b, $b0, $b0, $00, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $b0, $b0, $03, $33, $33, $00, $0b, $0b, $0b, $bb, $00, $00, $bb, $b0, $bb, $bb, $b0, $b0, $bb, $bb, $bb, $b0, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $bb, $bb, $bb, $bb, $0b, $b0, $bb, $bb, $b3, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $00, $00, $00, $b0, $b0, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $00, $0b, $b0, $0b, $b0, $00, $00, $00, $b0, $b0, $00, $00, $00, $bb, $0b, $0b, $bb, $00, $00, $00, $00, $0b, 
  db $00, $00, $00, $0b, $0b, $b0, $b0, $00, $b3, $bb, $bb, $bb, $bb, $b0, $00, $bb, $0b, $bb, $b0, $b0, $b0, $bb, $bb, $00, $00, $00, $0b, $0b, $bb, $bb, $00, $0b, $bb, $bb, $0b, $b0, $b0, $b0, $bb, $bb, $b0, $bb, $0b, $0b, $bb, $0b, $bb, $bb, $bb, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $b0, $b0, $b0, $b3, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $0b, $e0, $00, $b0, $b0, $bb, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $0b, $00, $eb, $0b, $b0, $b0, $bb, $bb, $bb, $b0, $bb, $0b, $0b, $bb, $0b, $bb, $bb, $bb, $0b, 
  db $00, $00, $00, $0b, $0b, $b0, $b0, $b0, $b3, $bb, $bb, $bb, $bb, $b0, $00, $bb, $0b, $bb, $bb, $b0, $b0, $bb, $bb, $03, $33, $30, $00, $00, $0b, $b0, $0b, $0b, $0b, $bb, $0b, $b0, $b0, $00, $00, $00, $00, $b0, $0b, $0b, $bb, $0b, $bb, $bb, $bb, $0b, 
  db $0b, $0d, $0b, $0b, $0b, $b0, $b0, $b0, $b0, $bb, $00, $33, $33, $00, $b0, $00, $00, $00, $00, $00, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $b0, $bb, $0b, $00, $00, $0b, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $0b, 
  db $00, $00, $00, $0b, $00, $b0, $b0, $b0, $b0, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $00, $00, $b0, $0b, $0b, $bb, $bb, $b3, $b0, $00, $00, $00, $00, $00, $00, $b0, $00, $00, $0b, $bb, $bb, $0b, 
  db $0b, $0b, $0b, $0b, $bb, $b0, $b0, $bb, $b0, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $d0, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $0b, $b0, $bb, $0b, $bb, $bb, $b3, $b0, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $eb, $0b, $bb, $bb, $0b, 
  db $00, $00, $00, $0b, $bb, $b0, $b0, $00, $00, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $00, $b0, $0b, $bb, $bb, $b3, $b0, $b0, $00, $00, $00, $00, $b0, $bb, $bb, $bb, $0b, $bb, $bb, $0b, 
  db $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $eb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $00, $bb, $bb, $00, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b3, $b0, $b0, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $0b, $bb, $bb, $0b, 
  db $bb, $00, $0b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $bb, $bb, $bb, $b0, $00, $00, $0b, $bb, $bb, $00, $00, $00, $00, $00, $0b, $bb, $bb, $bb, $b0, $b0, $b0, $b0, $00, $00, $00, $00, $00, $00, $0b, $00, $00, $00, $0b, 
  db $bb, $0b, $00, $33, $33, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $e0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $db, $0b, $bb, $bb, $bb, $bb, $0b, $b0, $00, $00, $00, $b0, $b0, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $0b, 
  db $bb, $00, $0b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $0b, $0b, $00, $00, $00, $00, $0b, $b0, $b0, $b0, $b0, $b0, $b0, $00, $bb, $bb, $bb, $b0, $b0, $00, $00, $0b, $bb, $bb, $3b, 
  db $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $0b, $0b, $bb, $bb, $0b, $bb, $b0, $00, $00, $00, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $b0, $bb, $bb, $0b, $bb, $bb, $3b, 
  db $bb, $00, $0b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $b0, $b0, $d0, $b0, $b0, $00, $b0, $bb, $bb, $bb, $b0, $b0, $bb, $bb, $0b, $bb, $bb, $3b, 
  db $bb, $0b, $00, $33, $33, $00, $b0, $00, $e0, $00, $b0, $b0, $b0, $b0, $b0, $00, $b0, $03, $33, $30, $00, $00, $bb, $bb, $00, $00, $00, $0b, $bb, $d0, $0b, $bb, $b0, $00, $00, $00, $b0, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $0b, $bb, $bb, $3b, 
  db $bb, $00, $0b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $b0, $b0, $b0, $b0, $b0, $b0, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $bb, $bb, $0b, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $00, $00, $00, $0b, $bb, $b0, $00, $00, $00, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $00, $0b, 
  db $bb, $00, $0b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $bb, $bb, 
  db $bb, $0b, $00, $33, $33, $00, $b0, $b0, $e0, $00, $b0, $b0, $e0, $00, $b0, $b0, $e0, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $0b, $db, $b0, $bb, $bb, $bb, $00, $00, $0b, $bb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $3b, $bb, $bb, $bb, 
  db $bb, $00, $0b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $00, $00, $00, $b0, $00, $00, $0b, $bb, $00, $00, $00, $0b, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $3b, $bb, $bb, $bb, 
  db $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $eb, $bb, $bb, $bb, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $3b, $bb, $bb, $bb, 
  db $bb, $00, $0b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $b0, $b0, $00, $00, $00, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $3b, $bb, $bb, $bb, 
  db $bb, $0b, $00, $33, $33, $00, $b0, $00, $b0, $b0, $b0, $b0, $b0, $00, $b0, $b0, $e0, $b0, $00, $eb, $bb, $d0, $bb, $bb, $bb, $d0, $bb, $b0, $b0, $bb, $bb, $bb, $bb, $bb, $0b, $00, $00, $00, $00, $b0, $00, $b0, $00, $00, $00, $0b, $0b, $bb, $bb, $bb, 
  db $bb, $00, $0b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $b0, $b0, $00, $00, $00, $00, $0b, $0b, $0b, $bb, $b0, $00, $b0, $d0, $b0, $00, $bb, $bb, $0b, $0b, $00, $00, $0b, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $b0, $00, $00, $00, $00, $eb, $b0, $b0, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $bb, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $0b, $0b, $0b, $bb, $0b, 
  db $bb, $00, $0b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $b0, $b0, $00, $00, $00, $0b, $0b, $0b, $0b, $bb, $b0, $00, $bb, $cb, $b0, $00, $bb, $bb, $0b, $0b, $0b, $bb, $0b, 
  db $00, $0b, $00, $33, $33, $00, $b0, $00, $e0, $00, $b0, $00, $b0, $b0, $e0, $b0, $b0, $00, $b0, $bb, $bb, $00, $bb, $b0, $00, $00, $00, $b0, $b0, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $bb, $b0, $00, $b0, $c0, $b0, $00, $bb, $bb, $0b, $0b, $0b, $bb, $0b, 
  db $0b, $00, $0b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $b0, $b0, $b0, $00, $00, $00, $0b, $0b, $0b, $00, $00, $00, $00, $00, $c0, $00, $00, $00, $00, $0b, $0b, $0b, $bb, $0b, 
  db $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $b0, $b0, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $0b, $bb, $b0, $00, $b0, $c0, $b0, $00, $bb, $bb, $0b, $0b, $00, $0b, $0b, 
  db $0b, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $b0, $b0, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $0b, $bb, $b0, $00, $00, $c0, $00, $00, $bb, $bb, $0b, $0b, $bb, $0b, $0b, 
  db $0b, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $b0, $b0, $b0, $b0, $b0, $00, $0b, $bb, $0b, $e0, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $db, $b0, $b0, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $0b, $bb, $b0, $00, $b0, $c0, $b0, $00, $bb, $bb, $0b, $00, $0b, $0b, $0b, 
  db $0b, $bb, $0b, $00, $0b, $0b, $bb, $b0, $00, $b0, $00, $b0, $00, $bb, $0b, $bb, $0b, $b0, $00, $0b, $bb, $0b, $bb, $b0, $0b, $00, $00, $b0, $bb, $bb, $bb, $bb, $0b, $bb, $0b, $0b, $bb, $b0, $00, $00, $c0, $00, $00, $bb, $bb, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $b0, $0b, $0d, $0b, $00, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $e0, $00, $00, $0b, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $0b, $bb, $b0, $b0, $03, $33, $30, $00, $00, $00, $0b, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $eb, $0b, $0b, 
  db $0b, $b0, $0b, $00, $0b, $00, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $bb, $00, $00, $00, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $0b, $0b, 
  db $0b, $e0, $0b, $bc, $bb, $00, $00, $00, $0b, $bb, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $bb, $bb, $bb, $bb, $00, $db, $b0, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $bb, $b0, $bb, $bb, $00, $eb, $0b, $bb, $bb, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $b0, $0b, $0c, $0b, $00, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $0b, $0b, $0b, $0b, $bb, 
  db $0b, $b0, $00, $0c, $00, $00, $b0, $00, $b0, $00, $00, $00, $00, $00, $db, $0b, $d0, $00, $00, $00, $00, $00, $00, $bb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $0b, $bb, $eb, $0b, $0b, $0b, $00, $bb, 
  db $0b, $b0, $0b, $0c, $0b, $00, $b0, $b0, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $00, $00, $00, $00, $00, $0b, $bb, $0b, $bb, $00, $0b, $0b, $0b, $b0, $bb, 
  db $0b, $b0, $00, $0c, $00, $00, $b0, $00, $b0, $0d, $bb, $b0, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $b0, $bb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $0b, $0b, $0b, $e0, $bb, 
  db $0b, $b0, $0b, $0c, $0b, $00, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $b0, $bb, $0b, $bb, $b0, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $00, $00, $00, $0b, $0b, $0b, $b0, $bb, 
  db $0b, $b0, $00, $0c, $00, $00, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $00, $00, $00, $eb, $bb, $bb, $bb, $bb, $b0, $b0, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $0b, $00, $00, $0b, 
  db $0b, $b0, $0b, $0c, $0b, $00, $bb, $00, $00, $0b, $00, $b0, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $00, $0b, $0b, $0b, $bb, $bb, $0b, 
  db $0b, $b0, $00, $0c, $00, $00, $bb, $0b, $bb, $eb, $b0, $b0, $bb, $0b, $00, $0b, $bb, $bb, $bb, $b0, $00, $00, $00, $00, $00, $00, $00, $bb, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $00, $00, $00, $00, $00, $0b, $bb, $b0, $bb, $00, $0b, $0b, $bb, $bb, $0b, 
  db $0b, $b0, $0b, $0c, $0b, $00, $bb, $0b, $bb, $bb, $b0, $b0, $bb, $0b, $0b, $0b, $bb, $bb, $bb, $b0, $b0, $b0, $b0, $b0, $b0, $b0, $b0, $bb, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $b3, $bb, $bb, $bb, $00, $00, $00, $0b, 
  db $0b, $b0, $00, $0c, $00, $00, $bb, $0b, $bb, $bb, $b0, $b0, $00, $00, $0b, $00, $03, $33, $33, $00, $00, $00, $00, $00, $00, $00, $00, $33, $33, $00, $00, $b0, $bb, $0b, $bb, $bb, $b0, $b3, $bb, $bb, $bb, $bb, $b3, $bb, $bb, $bb, $bb, $bb, $bb, $0b, 
  db $0b, $b0, $0b, $0c, $0b, $00, $bb, $0b, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $b0, $d0, $b0, $d0, $b0, $d0, $b0, $bb, $bb, $bb, $b0, $b0, $bb, $0b, $bb, $bb, $b0, $b3, $bb, $bb, $bb, $bb, $b3, $bb, $bb, $00, $00, $00, $bb, $0b, 
  db $0b, $bb, $00, $00, $00, $0b, $bb, $00, $00, $00, $00, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $00, $00, $00, $00, $00, $00, $00, $bb, $bb, $bb, $be, $b0, $00, $00, $00, $bb, $b0, $b3, $bb, $bb, $bb, $bb, $b3, $bb, $bb, $0b, $bb, $b0, $bb, $0b, 
  db $0b, $bb, $bb, $b0, $bb, $bb, $bb, $0b, $bb, $bb, $b0, $bb, $00, $00, $bb, $bb, $bb, $bb, $bb, $b0, $b0, $b0, $b0, $b0, $b0, $b0, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $b0, $bb, $b0, $b3, $bb, $b0, $00, $00, $b0, $bb, $bb, $3b, $bb, $b0, $bb, $0b, 
  db $0b, $e0, $00, $00, $00, $bb, $db, $0b, $eb, $bb, $b0, $bb, $0c, $c0, $bb, $bb, $bb, $bb, $bb, $b0, $00, $00, $00, $00, $00, $00, $00, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $b0, $bb, $b0, $b0, $bb, $b0, $bb, $b0, $b0, $bb, $bb, $3b, $bb, $b0, $00, $0b, 
  db $0b, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $bb, $b0, $bb, $0c, $c0, $33, $33, $30, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $b0, $bb, $b0, $b0, $00, $00, $b0, $00, $b0, $bb, $bb, $3b, $bb, $b0, $bb, $0b, 
  db $00, $00, $00, $00, $00, $00, $0b, $00, $00, $00, $00, $bb, $e0, $00, $bb, $bb, $bb, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $b0, $03, $33, $00, $bb, $bb, $bb, $0b, $b0, $eb, $b0, $bb, $bb, $bb, $bb, $b0, $00, $bb, $bb, $3b, $bb, $b0, $bb, $0b, 
  db $0b, $0b, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $b0, $bb, $bb, $b0, $b0, $00, $00, $0b, $bb, $bb, $b0, $00, $00, $00, $00, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $0b, 
  db $0b, $00, $00, $00, $00, $b0, $eb, $00, $00, $0b, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $00, $00, $0b, $eb, $0b, $b0, $eb, $0b, $e0, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $00, $00, $00, $0b, $bb, $b0, $bb, $0b, 
  db $0b, $0b, $bb, $bb, $0b, $b0, $bb, $bb, $bb, $0b, $0b, $bb, $bb, $b0, $00, $00, $00, $00, $0b, $bb, $0b, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $0b, $bb, $b0, $00, $00, $00, $00, $00, $03, $33, $33, $00, $00, $00, $0b, $bb, $bb, $bb, $bb, $b0, $bb, $0b, 
  db $0b, $0b, $b0, $eb, $0b, $00, $00, $00, $00, $0b, $0b, $bb, $b0, $00, $bb, $bb, $bb, $bb, $00, $0b, $0b, $00, $0b, $00, $00, $0b, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $0b, $b0, $bb, $0b, 
  db $0b, $0b, $b0, $bb, $bb, $b0, $bb, $0b, $bb, $bb, $3b, $bb, $b0, $bb, $b0, $00, $00, $0b, $bb, $0b, $0b, $0b, $0b, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $00, $00, $0b, 
  db $0b, $0b, $b0, $b0, $00, $00, $bb, $0b, $bb, $bb, $3b, $bb, $00, $b0, $00, $bb, $bb, $00, $bb, $0b, $0b, $0b, $0b, $0b, $00, $33, $33, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $bb, $bb, $0b, $0b, $0b, $0b, $bb, $00, $00, $00, $0b, $0b, $bb, $0b, 
  db $0b, $0b, $b0, $bb, $bb, $b0, $bb, $0b, $bb, $bb, $3b, $bb, $0b, $b0, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $0b, $0b, $0b, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $0b, $0b, $0b, $0b, $0b, $0d, $0b, $0b, $0b, $bb, $0b, 
  db $0b, $00, $b0, $00, $00, $00, $bb, $0b, $bb, $bb, $3b, $bb, $0b, $e0, $0b, $bb, $bd, $00, $bb, $00, $00, $0b, $00, $0b, $00, $00, $0b, $00, $eb, $bb, $d0, $00, $bb, $bb, $e0, $0b, $bb, $bb, $0b, $00, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $bb, $0b, 
  db $0b, $bb, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $bb, $0b, $bb, $0b, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $bb, $0b, 
  db $03, $33, $30, $00, $00, $00, $00, $0b, $bb, $bb, $00, $00, $0b, $b0, $00, $00, $00, $00, $33, $33, $30, $00, $00, $00, $00, $00, $0b, $00, $00, $00, $00, $00, $00, $00, $00, $03, $33, $33, $00, $00, $0b, $00, $0b, $00, $00, $00, $0b, $00, $00, $0b, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

; swap s/ (\d+, \d+)(.*,)(\d+, \d+)/\3\2\1
UnderworldAutoEvents:
  ; overworld
  AllocateTransportEvent 58, 16, HIGH(Overworld), LOW(Overworld), 73, 48

  EndList


UnderworldTriggerEvents:
  EndList

ENDC