
IF !DEF(CAVE_01_INC)
CAVE_01_INC = 1

Section "cave_01", ROM0
cave_01:
db height, width, HIGH(cave_01AutoEvents), LOW($cave_01AutoEvents)
db $0b, $0b, $09, $0b, $08, $08, $08, $08, 
db $0b, $08, $08, $0b, $08, $0b, $0b, $08, 
db $08, $08, $0b, $0b, $08, $08, $0b, $08, 
db $08, $0b, $04, $08, $08, $04, $0b, $08, 
db $08, $0b, $04, $04, $04, $04, $0b, $08, 
db $08, $0b, $0b, $0b, $0b, $08, $0b, $08, 
db $08, $08, $08, $08, $08, $08, $08, $08, 
db $0b, $08, $0b, $08, $0b, $0b, $0b, $0b, 
db $0b, $08, $0b, $08, $08, $08, $08, $0b, 
db $08, $08, $0b, $0b, $08, $0b, $08, $08, 
db $08, $08, $08, $08, $08, $0b, $0b, $08, 
db $0b, $09, $0b, $0b, $08, $08, $08, $08, 

cave_01AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        