IF !DEF(THE_LONG_ROAD_INC)
THE_LONG_ROAD_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "TheLongRoad", ROM0
TheLongRoad:
  db 9, 10, HIGH(TheLongRoadAutoEvents), LOW(TheLongRoadAutoEvents)
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $00, $00, $00, $00, $00, $00, $00, $00, $0b, 
  db $0b, $00, $0b, $00, $0b, $0b, $0b, $0b, $00, $0b, 
  db $0b, $0b, $0b, $00, $0b, $0b, $0b, $0b, $00, $0b, 
  db $0b, $0e, $0b, $00, $0b, $0b, $0b, $0b, $0e, $0b, 
  db $0b, $00, $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $00, $0b, $00, $0b, $0b, $0b, $0b, $0b, $00, 
  db $0b, $00, $00, $00, $00, $00, $00, $00, $00, $00, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 

TheLongRoadAutoEvents:
  AllocateTransportEvent 4, 1, HIGH(Underworld), LOW(Underworld), 68, 33
  AllocateTransportEvent 4, 8, HIGH(Underworld), LOW(Underworld), 68, 60
  EndList

TheLongRoadTriggerEvents:
  EndList

ENDC