IF !DEF(SMALLWORLD_INC)
SMALLWORLD_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Smallworld", ROM0
Smallworld:
  db 4, 2, HIGH(SmallworldEvents), LOW(SmallworldEvents)
  db 1, 2, 2, 2
  db 2, 2, 1, 2
  db 2, 1, 2, 2
  db 2, 1, 0, 2
  db 2, 0, 0, 2
  db 2, 0, 1, 2
  db 2, 1, 1, 2
  db 2, 2, 1, 2
  db 2, 1, 2, 2
  db 2, 2, 2, 2

SmallworldEvents:
  EndList

ENDC