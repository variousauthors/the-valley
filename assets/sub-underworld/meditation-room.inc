
IF !DEF(MEDITATION_ROOM_INC)
MEDITATION_ROOM_INC = 1

Section "meditation_room", ROM0
meditation_room:
db height, width, HIGH(meditation_roomAutoEvents), LOW($meditation_roomAutoEvents)
db $0b, $0c, $0c, $06, $06, $06, $0c, $0c, $0b, $0b, 
db $0c, $0c, $0b, $01, $06, $01, $0b, $0c, $0c, $0b, 
db $0c, $0b, $04, $04, $04, $04, $04, $0b, $0c, $0b, 
db $0c, $01, $04, $06, $06, $01, $04, $01, $0c, $0b, 
db $01, $06, $05, $06, $0e, $06, $05, $06, $01, $0b, 
db $06, $06, $04, $01, $06, $06, $04, $01, $06, $0b, 
db $0c, $0b, $04, $04, $04, $04, $04, $0b, $0c, $0b, 
db $0c, $0c, $0b, $06, $01, $01, $0b, $0c, $0c, $0b, 
db $0b, $0c, $0c, $06, $06, $06, $0c, $0c, $0b, $0b, 

meditation_roomAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        