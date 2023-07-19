IF !DEF(SMALLWORLD_INC)
SMALLWORLD_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Smallworld", ROM0
Smallworld:
  db 10, 4, HIGH(SmallworldEvents), LOW(SmallworldEvents)
  db 2, 1, 1, 1
  db 1, 1, 1, 1
  db 1, 1, 1, 1
  db 1, 1, 0, 1
  db 1, 0, 0, 1
  db 1, 0, 1, 1
  db 1, 1, 1, 1
  db 1, 1, 1, 1
  db 1, 1, 1, 1
  db 1, 1, 1, 1
  db 1, 1, 1, 1

SmallworldEvents:
  AllocateTransportEvent 4, 1, HIGH(Overworld), LOW(Overworld), 4, 4
  EndList

ENDC