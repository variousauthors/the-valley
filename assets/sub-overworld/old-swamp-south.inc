
IF !DEF(OLD_SWAMP_SOUTH_INC)
OLD_SWAMP_SOUTH_INC = 1

Section "old_swamp_south", ROM0
old_swamp_south:
db height, width, HIGH(old_swamp_southAutoEvents), LOW($old_swamp_southAutoEvents)
db $01, $01, $01, $0c, $01, $0f, $0f, $01, $01, $01, 
db $01, $0f, $01, $06, $01, $01, $0f, $0f, $01, $0f, 
db $0f, $01, $01, $0c, $01, $01, $0f, $0f, $0f, $01, 
db $01, $0f, $01, $06, $01, $01, $01, $0f, $01, $01, 
db $01, $01, $01, $0c, $01, $01, $01, $01, $0f, $01, 
db $01, $01, $01, $0c, $01, $01, $01, $0f, $01, $01, 
db $02, $01, $01, $06, $0c, $0d, $01, $0f, $01, $02, 
db $02, $01, $0f, $01, $01, $01, $01, $01, $01, $02, 
db $01, $02, $01, $01, $0f, $01, $0f, $01, $02, $01, 

old_swamp_southAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        