
IF !DEF(MAP_ROOM_EAST_INC)
MAP_ROOM_EAST_INC = 1

Section "map_room_east", ROM0
map_room_east:
  db height, width, HIGH(map_room_eastAutoEvents), LOW($map_room_eastAutoEvents)
  db $bb, $b1, $24, $bb, $bb, 
  db $b0, $b5, $6c, $b0, $bb, 
  db $b0, $b8, $9a, $b0, $bb, 
  db $b0, $0b, $bb, $00, $bb, 
  db $bb, $00, $00, $0b, $bb, 
  db $bb, $0b, $0b, $0b, $bb, 
  db $bb, $00, $00, $0b, $bb, 
  db $bb, $0b, $0b, $0b, $bb, 
  db $bb, $00, $e0, $0b, $bb, 

map_room_eastAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        