IF !DEF(MAP_ROOM_EAST_INC)
MAP_ROOM_EAST_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "MapRoomEast", ROM0
MapRoomEast:
  db 9, 10, HIGH(MapRoomEastEvents), LOW(MapRoomEastEvents), HIGH(MapRoomTileset), LOW(MapRoomTileset)
  db $bb, $b1, $24, $bb, $bb, 
  db $b0, $b5, $6c, $b0, $bb, 
  db $b0, $b8, $9a, $b0, $bb, 
  db $b0, $0b, $bb, $00, $bb, 
  db $bb, $00, $00, $0b, $bb, 
  db $bb, $0b, $0b, $0b, $bb, 
  db $bb, $00, $00, $0b, $bb, 
  db $bb, $0b, $0b, $0b, $bb, 
  db $bb, $00, $e0, $0b, $bb, 

MapRoomTileset:
  db $00, $13, $14, $09, $15, $16, $17, $18,
  db $19, $1A, $1B, $09, $1C, $1D, $0C, $0D,

MapRoomEastEvents:
  AllocateTransportEvent 8, 4, HIGH(MapRoomEast), LOW(MapRoomEast), 33, 80
  EndList

ENDC