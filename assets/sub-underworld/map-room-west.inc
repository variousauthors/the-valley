
IF !DEF(MAP_ROOM_WEST_INC)
MAP_ROOM_WEST_INC = 1

Section "map_room_west", ROM0
map_room_west:
  db height, width, HIGH(map_room_westAutoEvents), LOW($map_room_westAutoEvents)
  db $bb, $b1, $24, $bb, $bb, 
  db $b0, $bd, $67, $b0, $bb, 
  db $b0, $b8, $9a, $b0, $bb, 
  db $b0, $0b, $bb, $00, $bb, 
  db $bb, $00, $00, $0b, $bb, 
  db $bb, $0b, $0b, $0b, $bb, 
  db $bb, $00, $00, $0b, $bb, 
  db $bb, $0b, $0b, $0b, $bb, 
  db $bb, $00, $e0, $0b, $bb, 

map_room_westAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        