IF !DEF(THE_LONG_ROAD_INC)
THE_LONG_ROAD_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "TheLongRoad", ROM0
TheLongRoad:
  db 9, 10, HIGH(TheLongRoadAutoEvents), LOW(TheLongRoadAutoEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $bb, $bb, $bb, $bb, $bb, 
  db $b0, $00, $00, $00, $0b, 
  db $b0, $b0, $bb, $bb, $0b, 
  db $bb, $b0, $bb, $bb, $0b, 
  db $be, $b0, $bb, $bb, $eb, 
  db $b0, $b0, $bb, $bb, $bb, 
  db $b0, $b0, $bb, $bb, $b0, 
  db $b0, $00, $00, $00, $00, 
  db $bb, $bb, $bb, $bb, $bb, 

TheLongRoadAutoEvents:
  AllocateTransportEvent 4, 1, HIGH(Underworld), LOW(Underworld), 68, 33
  AllocateTransportEvent 4, 8, HIGH(Underworld), LOW(Underworld), 68, 60
  EndList

TheLongRoadTriggerEvents:
  EndList

ENDC