IF !DEF(UNDERWORLD_INC)
UNDERWORLD_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Underworld", ROMX, BANK[1]
Underworld:
  db 72, 100, HIGH(UnderworldAutoEvents), LOW(UnderworldAutoEvents), HIGH(UnderworldTileset), LOW(UnderworldTileset)
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
  db $bb, $0b, $00, $33, $33, $00, $b0, $00, $b0, $b0, $b0, $b0, $b0, $00, $b0, $b0, $e0, $b0, $00, $eb, $bb, $d0, $bb, $bb, $bb, $d0, $bb, $b0, $b0, $bb, $bb, $bb, $bb, $bb, $0b, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $bb, $bb, $bb, 
  db $bb, $00, $0b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $b0, $b0, $00, $00, $00, $00, $0b, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $0b, $00, $00, $0b, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $b0, $00, $00, $00, $00, $eb, $b0, $b0, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $0b, $0b, $bb, $0b, 
  db $bb, $00, $0b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $b0, $b0, $00, $00, $00, $0b, $0b, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $0b, $0b, $bb, $0b, 
  db $00, $0b, $00, $33, $33, $00, $b0, $00, $e0, $00, $b0, $00, $b0, $b0, $e0, $b0, $b0, $00, $b0, $bb, $bb, $00, $bb, $b0, $00, $00, $00, $b0, $b0, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $0b, $0b, $bb, $0b, 
  db $0b, $00, $0b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $b0, $b0, $b0, $00, $00, $00, $0b, $0b, $0b, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $0b, $bb, $0b, 
  db $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $b0, $b0, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $0b, $00, $0b, $0b, 
  db $0b, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $b0, $b0, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $0b, $bb, $0b, $0b, 
  db $0b, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $b0, $b0, $b0, $b0, $b0, $00, $0b, $bb, $0b, $e0, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $db, $b0, $b0, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $00, $0b, $0b, $0b, 
  db $0b, $bb, $00, $00, $00, $0b, $bb, $b0, $00, $b0, $00, $b0, $00, $bb, $0b, $bb, $0b, $b0, $00, $0b, $bb, $0b, $bb, $b0, $0b, $00, $00, $b0, $bb, $bb, $bb, $bb, $0b, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $b0, $00, $00, $00, $00, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $e0, $00, $00, $0b, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $0b, $bb, $b0, $b0, $03, $33, $30, $00, $00, $00, $0b, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $eb, $0b, $0b, 
  db $0b, $b0, $00, $00, $00, $00, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $bb, $00, $00, $00, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $0b, $0b, 
  db $0b, $e0, $00, $00, $00, $00, $00, $00, $0b, $bb, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $bb, $bb, $bb, $bb, $00, $db, $b0, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $bb, $b0, $bb, $bb, $00, $eb, $0b, $bb, $bb, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $b0, $00, $00, $00, $00, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $0b, $0b, $0b, $0b, $bb, 
  db $0b, $b0, $00, $00, $00, $00, $b0, $00, $b0, $00, $00, $00, $00, $00, $db, $0b, $d0, $00, $00, $00, $00, $00, $00, $bb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $0b, $bb, $eb, $0b, $0b, $0b, $00, $bb, 
  db $0b, $b0, $00, $00, $00, $00, $b0, $b0, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $00, $00, $00, $00, $00, $0b, $bb, $0b, $bb, $00, $0b, $0b, $0b, $b0, $bb, 
  db $0b, $b0, $00, $00, $00, $00, $b0, $00, $b0, $0d, $bb, $b0, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $b0, $bb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $0b, $0b, $0b, $e0, $bb, 
  db $0b, $b0, $00, $00, $00, $00, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $b0, $bb, $0b, $bb, $b0, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $00, $00, $00, $0b, $0b, $0b, $b0, $bb, 
  db $0b, $b0, $00, $00, $00, $00, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $00, $00, $00, $eb, $bb, $bb, $bb, $bb, $b0, $b0, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $0b, $00, $00, $0b, 
  db $0b, $b0, $00, $00, $00, $00, $bb, $00, $00, $0b, $00, $b0, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b3, $bb, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $00, $0b, $0b, $0b, $bb, $bb, $0b, 
  db $0b, $b0, $00, $00, $00, $00, $bb, $0b, $bb, $eb, $b0, $b0, $bb, $0b, $00, $0b, $bb, $bb, $bb, $b0, $00, $00, $00, $00, $00, $00, $00, $bb, $bb, $bb, $bb, $b3, $bb, $bb, $0b, $00, $00, $00, $00, $00, $0b, $bb, $b0, $bb, $00, $0b, $0b, $bb, $bb, $0b, 
  db $0b, $b0, $00, $00, $00, $00, $bb, $0b, $bb, $bb, $b0, $b0, $bb, $0b, $0b, $0b, $bb, $bb, $bb, $b0, $b0, $b0, $b0, $b0, $b0, $b0, $b0, $bb, $00, $0b, $bb, $b3, $bb, $bb, $0b, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $b3, $bb, $bb, $bb, $0b, $bb, $bb, $0b, 
  db $0b, $b0, $00, $00, $00, $00, $bb, $0b, $bb, $bb, $b0, $b0, $00, $00, $0b, $00, $03, $33, $33, $00, $00, $00, $00, $00, $00, $00, $00, $bb, $0b, $0b, $bb, $b3, $bb, $bb, $0b, $bb, $bb, $b3, $bb, $bb, $bb, $bb, $b3, $bb, $bb, $00, $00, $00, $00, $0b, 
  db $0b, $b0, $00, $00, $00, $00, $bb, $0b, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $b0, $d0, $b0, $d0, $b0, $d0, $b0, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $b3, $bb, $bb, $bb, $bb, $b3, $bb, $bb, $0b, $bb, $bb, $bb, $0b, 
  db $0b, $bb, $00, $00, $00, $0b, $bb, $00, $00, $00, $00, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $00, $00, $00, $00, $00, $00, $00, $bb, $3b, $0b, $be, $b0, $00, $0b, $0b, $bb, $bb, $b3, $bb, $bb, $bb, $bb, $b3, $bb, $bb, $0b, $00, $00, $00, $0b, 
  db $0b, $bb, $bb, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $b0, $bb, $00, $00, $bb, $bb, $bb, $bb, $bb, $b0, $b0, $b0, $b0, $b0, $b0, $b0, $b0, $bb, $3b, $0b, $b0, $bb, $bb, $0b, $00, $00, $00, $b3, $bb, $b0, $00, $00, $b0, $bb, $bb, $0b, $0b, $bb, $bb, $0b, 
  db $0b, $e0, $00, $00, $00, $bb, $db, $0b, $eb, $bb, $b0, $bb, $0c, $c0, $bb, $bb, $bb, $bb, $bb, $b0, $00, $00, $00, $00, $00, $00, $00, $bb, $3b, $00, $00, $bb, $bb, $0b, $bb, $bb, $b0, $b0, $bb, $b0, $bb, $b0, $b0, $bb, $bb, $0b, $0b, $bb, $bb, $0b, 
  db $0b, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $bb, $b0, $bb, $0c, $c0, $33, $33, $30, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $3b, $bb, $bb, $bb, $bb, $0b, $00, $00, $00, $00, $00, $00, $b0, $00, $b0, $bb, $bb, $0b, $00, $00, $0b, $0b, 
  db $00, $00, $00, $00, $00, $00, $0b, $00, $00, $00, $00, $bb, $e0, $00, $bb, $bb, $bb, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $b0, $03, $33, $00, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $b0, $b0, $b0, $b0, $bb, $bb, $0b, $bb, $bb, $0b, $0b, 
  db $0b, $0b, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $b0, $bb, $bb, $b0, $b0, $00, $00, $00, $00, $00, $00, $0b, $00, $00, $b0, $b0, $b0, $bb, $bb, $00, $0b, $0b, $0b, $0b, 
  db $0b, $00, $00, $00, $00, $b0, $eb, $00, $00, $0b, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $00, $00, $0b, $eb, $0b, $b0, $eb, $0b, $e0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $00, $bb, $bb, $bb, $bb, $0b, $0b, $0b, 
  db $0b, $0b, $bb, $bb, $0b, $b0, $bb, $bb, $bb, $0b, $0b, $bb, $bb, $b0, $00, $00, $00, $00, $0b, $bb, $0b, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $00, $00, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $0b, 
  db $0b, $0b, $b0, $eb, $0b, $00, $00, $00, $00, $0b, $0b, $bb, $b0, $00, $bb, $bb, $bb, $bb, $00, $0b, $0b, $00, $0b, $00, $00, $0b, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $bb, $bb, $00, $00, $00, $0b, $0b, $bb, $0b, 
  db $0b, $0b, $b0, $bb, $bb, $b0, $bb, $0b, $bb, $bb, $3b, $bb, $b0, $bb, $b0, $00, $00, $0b, $bb, $0b, $0b, $0b, $0b, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $00, $00, $00, $0b, $0b, $0b, $0b, $00, $00, $0b, 
  db $0b, $0b, $b0, $b0, $00, $00, $bb, $0b, $bb, $bb, $3b, $bb, $00, $b0, $00, $bb, $bb, $00, $bb, $0b, $0b, $0b, $0b, $0b, $00, $33, $33, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $bb, $bb, $0b, $0b, $0b, $0b, $bb, $00, $00, $00, $0b, $bb, $bb, $0b, 
  db $0b, $0b, $b0, $bb, $bb, $b0, $bb, $0b, $bb, $bb, $3b, $bb, $0b, $b0, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $0b, $0b, $0b, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $0b, $0b, $0b, $0b, $0d, $0b, $0b, $0b, $bb, $0b, 
  db $0b, $00, $b0, $00, $00, $00, $bb, $0b, $bb, $bb, $3b, $bb, $0b, $e0, $0b, $bb, $bd, $00, $bb, $00, $00, $0b, $00, $0b, $00, $00, $0b, $00, $eb, $bb, $d0, $00, $bb, $bb, $e0, $0b, $bb, $bb, $00, $00, $0b, $0b, $0b, $00, $00, $00, $0b, $0b, $bb, $0b, 
  db $0b, $bb, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $bb, $0b, $bb, $0b, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $bb, $0b, 
  db $03, $33, $30, $00, $00, $00, $00, $0b, $bb, $bb, $00, $00, $0b, $b0, $00, $00, $00, $00, $33, $33, $30, $00, $00, $00, $00, $00, $0b, $00, $00, $00, $00, $00, $00, $00, $00, $03, $33, $33, $00, $00, $0b, $00, $0b, $00, $00, $00, $0b, $00, $00, $0b, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

UnderworldTileset:
  db $00, $01, $02, $09, $03, $04, $05, $06,
  db $08, $07, $0E, $09, $0A, $0B, $0C, $0D,

; swap s/ (\d+, \d+)(.*,)(\d+, \d+)/\3\2\1
UnderworldAutoEvents:
  ; overworld
  AllocateTransportEvent 68, 26, HIGH(Overworld), LOW(Overworld), 34, 13
  AllocateTransportEvent 68, 56, HIGH(Overworld), LOW(Overworld), 34, 28
  AllocateTransportEvent 68, 68, HIGH(Overworld), LOW(Overworld), 34, 34
  AllocateTransportEvent 64, 6, HIGH(Overworld), LOW(Overworld), 32, 3
  AllocateTransportEvent 62, 12, HIGH(Overworld), LOW(Overworld), 31, 6
  AllocateTransportEvent 62, 48, HIGH(Overworld), LOW(Overworld), 31, 24
  AllocateTransportEvent 58, 16, HIGH(Overworld), LOW(Overworld), 29, 8
  AllocateTransportEvent 52, 18, HIGH(Overworld), LOW(Overworld), 26, 9
  AllocateTransportEvent 50, 32, HIGH(Overworld), LOW(Overworld), 25, 16
  AllocateTransportEvent 48, 96, HIGH(Overworld), LOW(Overworld), 24, 48
  AllocateTransportEvent 44, 2, HIGH(Overworld), LOW(Overworld), 22, 1
  AllocateTransportEvent 42, 26, HIGH(Overworld), LOW(Overworld), 21, 13
  AllocateTransportEvent 42, 94, HIGH(Overworld), LOW(Overworld), 21, 47
  AllocateTransportEvent 40, 34, HIGH(Overworld), LOW(Overworld), 20, 17
  AllocateTransportEvent 36, 28, HIGH(Overworld), LOW(Overworld), 18, 14
  AllocateTransportEvent 34, 52, HIGH(Overworld), LOW(Overworld), 17, 26
  AllocateTransportEvent 30, 62, HIGH(Overworld), LOW(Overworld), 15, 31
  AllocateTransportEvent 12, 34, HIGH(Overworld), LOW(Overworld), 6, 17
  AllocateTransportEvent 8, 12, HIGH(Overworld), LOW(Overworld), 4, 6
  AllocateTransportEvent 8, 56, HIGH(Overworld), LOW(Overworld), 4, 28
  AllocateTransportEvent 6, 74, HIGH(Overworld), LOW(Overworld), 3, 37
  AllocateTransportEvent 4, 18, HIGH(Overworld), LOW(Overworld), 2, 9

  ; sub-overworld
  AllocateTransportEvent 2, 78, HIGH(SwampTunnelEast), LOW(SwampTunnelEast), 1, 3
  AllocateTransportEvent 6, 74, HIGH(SwampTunnelWest), LOW(SwampTunnelWest), 6, 6
  AllocateTransportEvent 6, 64, HIGH(OldSwamp), LOW(OldSwamp), 1, 2
  AllocateTransportEvent 12, 66, HIGH(OldSwampSouth), LOW(OldSwampSouth), 6, 5
  AllocateTransportEvent 16, 90, HIGH(PeninsulaRuins), LOW(PeninsulaRuins), 1, 4
  AllocateTransportEvent 18, 20, HIGH(NorthForestTemple), LOW(NorthForestTemple), 3, 5
  AllocateTransportEvent 24, 16, HIGH(CentralForestTemple), LOW(CentralForestTemple), 4, 6
  AllocateTransportEvent 28, 16, HIGH(SouthForestTemple), LOW(SouthForestTemple), 5, 7
  AllocateTransportEvent 36, 16, HIGH(OldPond), LOW(OldPond), 1, 5
  AllocateTransportEvent 44, 82, HIGH(RuinedTemple), LOW(RuinedTemple), 4, 7
  AllocateTransportEvent 58, 2, HIGH(CoastalGrove), LOW(CoastalGrove), 2, 4
  AllocateTransportEvent 60, 24, HIGH(Start), LOW(Start), 3, 6
  AllocateTransportEvent 62, 58, HIGH(TwinsCrossingEast), LOW(TwinsCrossingEast), 6, 3
  AllocateTransportEvent 62, 54, HIGH(TwinsCrossingWest), LOW(TwinsCrossingWest), 2, 6
  AllocateTransportEvent 32, 32, HIGH(TowerApproach), LOW(TowerApproach), 3, 4
  AllocateTransportEvent 28, 32, HIGH(Tower), LOW(Tower), 25, 15
  AllocateTransportEvent 46, 88, HIGH(HiddenPeninsula), LOW(HiddenPeninsula), 6, 3
  AllocateTransportEvent 56, 61, HIGH(DesertTown), LOW(DesertTown), 11, 7

  ; sub-underworld short-cuts
  AllocateTransportEvent 68, 33, HIGH(TheLongRoad), LOW(TheLongRoad), 4, 1
  AllocateTransportEvent 68, 60, HIGH(TheLongRoad), LOW(TheLongRoad), 4, 8
  ; underpass 1
  AllocateTransportEvent 58, 12, HIGH(UnderpassOne), LOW(UnderpassOne), 7, 1
  AllocateTransportEvent 48, 19, HIGH(UnderpassOne), LOW(UnderpassOne), 2, 7
  ; underpass 2
  AllocateTransportEvent 46, 28, HIGH(UnderpassTwo), LOW(UnderpassTwo), 4, 1
  AllocateTransportEvent 46, 32, HIGH(UnderpassTwo), LOW(UnderpassTwo), 4, 3

  ; tunnels entrance
  AllocateTransportEvent 55, 42, HIGH(TunnelsEntrance), LOW(TunnelsEntrance), 7, 3
  AllocateTransportEvent 55, 46, HIGH(TunnelsEntrance), LOW(TunnelsEntrance), 7, 5
  AllocateTransportEvent 55, 50, HIGH(TunnelsEntrance), LOW(TunnelsEntrance), 7, 7

  ; tunnels exits
  ; left
  AllocateTransportEvent 14, 3, HIGH(Tunnels), LOW(Tunnels), 7, 0
  ; middle
  AllocateTransportEvent 23, 68, HIGH(Tunnels), LOW(Tunnels), 0, 2
  ; right
  AllocateTransportEvent 67, 89, HIGH(Tunnels), LOW(Tunnels), 5, 9

  ; sub-underworld the catacombs
  AllocateTransportEvent 4, 34, HIGH(TheCatacombs), LOW(TheCatacombs), 2, 2
  AllocateTransportEvent 4, 46, HIGH(TheCatacombs), LOW(TheCatacombs), 2, 14
  AllocateTransportEvent 16, 38, HIGH(TheCatacombs), LOW(TheCatacombs), 14, 6
  AllocateTransportEvent 20, 50, HIGH(TheCatacombs), LOW(TheCatacombs), 18, 18
  AllocateTransportEvent 24, 58, HIGH(TheCatacombs), LOW(TheCatacombs), 22, 26
  AllocateTransportEvent 28, 50, HIGH(TheCatacombs), LOW(TheCatacombs), 26, 18
  AllocateTransportEvent 32, 42, HIGH(TheCatacombs), LOW(TheCatacombs), 30, 10
  AllocateTransportEvent 32, 50, HIGH(TheCatacombs), LOW(TheCatacombs), 30, 18
  AllocateTransportEvent 40, 50, HIGH(TheCatacombs), LOW(TheCatacombs), 38, 18
  AllocateTransportEvent 44, 50, HIGH(TheCatacombs), LOW(TheCatacombs), 42, 18

  ; ruins
  AllocateTransportEvent 28, 24, HIGH(RuinsOne), LOW(RuinsOne), 4, 2
  AllocateTransportEvent 20, 28, HIGH(RuinsTwo), LOW(RuinsTwo), 8, 15
  AllocateTransportEvent 32, 38, HIGH(RuinsThree), LOW(RuinsThree), 13, 5


  EndList


UnderworldTriggerEvents:
  EndList

ENDC