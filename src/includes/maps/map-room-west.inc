IF !DEF(MAP_ROOM_WEST_INC)
MAP_ROOM_WEST_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "MapRoomWest", ROM0
MapRoomWest:
  db 9, 10, HIGH(MapRoomWestEvents), LOW(MapRoomWestEvents), HIGH(MapRoomTileset), LOW(MapRoomTileset)
  db $bb, $b1, $24, $bb, $bb, 
  db $b0, $bd, $67, $b0, $bb, 
  db $b0, $b8, $9a, $b0, $bb, 
  db $b0, $0b, $bb, $00, $bb, 
  db $bb, $00, $00, $0b, $bb, 
  db $bb, $0b, $0b, $0b, $bb, 
  db $bb, $00, $00, $0b, $bb, 
  db $bb, $0b, $0b, $0b, $bb, 
  db $bb, $00, $e0, $0b, $bb, 

MapRoomWestEvents:
  AllocateTransportEvent 8, 4, HIGH(Underworld), LOW(Underworld), 42, 7
  EndList

ENDC