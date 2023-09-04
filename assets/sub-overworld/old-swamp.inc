
IF !DEF(OLD_SWAMP_INC)
OLD_SWAMP_INC = 1

Section "old_swamp", ROM0
old_swamp:
db height, width, HIGH(old_swampAutoEvents), LOW($old_swampAutoEvents)
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $0d, $01, $0f, $0f, $01, $01, $01, $01, 
db $01, $01, $0c, $01, $04, $04, $04, $0f, $01, $01, 
db $01, $01, $0c, $0f, $04, $04, $0f, $01, $01, $01, 
db $01, $01, $06, $01, $0f, $0f, $06, $00, $06, $06, 
db $01, $01, $00, $06, $01, $06, $00, $01, $01, $01, 
db $01, $01, $06, $06, $00, $06, $06, $01, $01, $01, 
db $01, $01, $01, $01, $06, $06, $01, $01, $01, $01, 
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 

old_swampAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        