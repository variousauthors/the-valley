IF !DEF(OVERWORLD_INC)
OVERWORLD_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Overworld", ROM0
Overworld:
  db 16, 16, HIGH(OverworldAutoEvents), LOW(OverworldAutoEvents)
  db 1, 1, 2, 2, 2, 2, 0, 2,  0,  2, 2, 2, 2, 0, 2, 2
  db 1, 2, 1, 1, 0, 0, 1, 1,  1,  1, 1, 1, 1, 1, 0, 2
  db 2, 1, 0, 1, 1, 0, 1, 1,  1,  1, 1, 0, 1, 2, 0, 2
  db 2, 1, 1, 2, 1, 1, 1, 0,  1,  1, 1, 1, 0, 0, 0, 0
  db 0, 1, 1, 1, 0, 1, 1, 1,  1,  1, 0, 0, 0, 0, 1, 2
  db 0, 0, 1, 1, 1, 0, 1, 1,  1,  1, 2, 0, 0, 1, 1, 2
  db 0, 0, 0, 1, 1, 1, 0, 0,  1,  0, 1, 0, 1, 1, 1, 2
  db 0, 0, 0, 0, 0, 1, 1, 2,  0,  0, 0, 1, 0, 1, 0, 2

  db 2, 1, 0, 0, 0, 0, 1, 0,  0,  1, 1, 0, 1, 0, 1, 2

  db 2, 1, 1, 0, 0, 0, 0, 0,  1,  2, 1, 0, 1, 1, 1, 2
  db 0, 0, 1, 1, 1, 0, 0, 1,  1,  1, 0, 0, 1, 1, 0, 2
  db 2, 1, 0, 0, 0, 1, 1, 1,  1,  1, 1, 0, 1, 0, 1, 2
  db 0, 1, 1, 0, 1, 1, 0, 1,  0,  1, 1, 1, 2, 1, 1, 2
  db 2, 1, 2, 1, 1, 1, 1, 1,  1,  1, 0, 0, 1, 2, 1, 2
  db 2, 2, 1, 1, 1, 0, 1, 1,  0,  1, 0, 1, 0, 1, 2, 2
  db 2, 2, 0, 2, 0, 2, 2, 0,  2,  0, 2, 2, 2, 2, 2, 2

OverworldAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList

OverworldTriggerEvents:
  EndList

ENDC