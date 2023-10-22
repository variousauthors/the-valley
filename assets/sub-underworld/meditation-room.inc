
IF !DEF(MEDITATION_ROOM_INC)
MEDITATION_ROOM_INC = 1

Section "meditation_room", ROM0
meditation_room:
  db height, width, HIGH(meditation_roomAutoEvents), LOW($meditation_roomAutoEvents)
  db $bc, $c6, $66, $cc, $bb, 
  db $cc, $b1, $61, $bc, $cb, 
  db $cb, $44, $44, $4b, $cb, 
  db $c1, $46, $61, $41, $cb, 
  db $16, $56, $e6, $56, $1b, 
  db $66, $41, $66, $41, $6b, 
  db $cb, $44, $44, $4b, $cb, 
  db $cc, $b6, $11, $bc, $cb, 
  db $bc, $c6, $66, $cc, $bb, 

meditation_roomAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        