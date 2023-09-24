IF !DEF(MEDITATION_ROOM_INC)
MEDITATION_ROOM_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "MeditationRoom", ROMX, BANK[1]
MeditationRoom:
  db 9, 10, HIGH(MeditationRoomAutoEvents), LOW(MeditationRoomAutoEvents)
  db $0b, $0c, $0c, $06, $06, $06, $0c, $0c, $0b, $0b, 
  db $0c, $0c, $0b, $01, $06, $01, $0b, $0c, $0c, $0b, 
  db $0c, $0b, $04, $04, $04, $04, $04, $0b, $0c, $0b, 
  db $0c, $01, $04, $06, $06, $01, $04, $01, $0c, $0b, 
  db $01, $06, $05, $06, $0e, $06, $05, $06, $01, $0b, 
  db $06, $06, $04, $01, $06, $06, $04, $01, $06, $0b, 
  db $0c, $0b, $04, $04, $04, $04, $04, $0b, $0c, $0b, 
  db $0c, $0c, $0b, $06, $01, $01, $0b, $0c, $0c, $0b, 
  db $0b, $0c, $0c, $06, $06, $06, $0c, $0c, $0b, $0b, 

MeditationRoomAutoEvents:
  ; underworld
  AllocateTransportEvent 4, 4, HIGH(Underworld), LOW(Underworld), 28, 32

  EndList

MeditationRoomTriggerEvents:
  EndList

ENDC