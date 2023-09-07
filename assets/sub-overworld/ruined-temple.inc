
IF !DEF(RUINED_TEMPLE_INC)
RUINED_TEMPLE_INC = 1

Section "ruined_temple", ROM0
ruined_temple:
db height, width, HIGH(ruined_templeAutoEvents), LOW($ruined_templeAutoEvents)
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $06, $0c, $0c, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $06, $01, $01, $01, $01, $0b, $0b, $01, 
db $01, $01, $0c, $01, $01, $0b, $08, $00, $06, $01, 
db $01, $01, $0c, $06, $0c, $08, $00, $0d, $0b, $01, 
db $01, $06, $06, $01, $01, $0b, $00, $06, $0b, $01, 
db $01, $06, $04, $04, $01, $01, $0b, $0b, $06, $01, 
db $01, $04, $04, $06, $06, $01, $01, $01, $01, $01, 
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 

ruined_templeAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        