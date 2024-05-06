IF !DEF(MEDITATION_ROOM_INC)
MEDITATION_ROOM_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "MeditationRoom", ROMX
  db HAS_BOUNDS
MeditationRoom:
  db 9, 10, HIGH(MeditationRoomAutoEvents), LOW(MeditationRoomAutoEvents), HIGH(InteriorTileset), LOW(InteriorTileset), HIGH(MountainPassEncounters), LOW(MountainPassEncounters)
  db $bc, $c6, $66, $cc, $bb, 
  db $cc, $b1, $61, $bc, $cb, 
  db $cb, $44, $44, $4b, $cb, 
  db $c1, $46, $61, $41, $cb, 
  db $16, $56, $e6, $56, $1b, 
  db $66, $41, $66, $41, $6b, 
  db $cb, $44, $44, $4b, $cb, 
  db $cc, $b6, $11, $bc, $cb, 
  db $bc, $c6, $66, $cc, $bb, 

MeditationRoomAutoEvents:
  ; underworld
  AllocateTransportEvent 4, 4, HIGH(Overworld), LOW(Overworld), 111, 43

  EndList

MeditationRoomTriggerEvents:
  EndList

ENDC