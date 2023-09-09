
IF !DEF(OLD_POND_INC)
OLD_POND_INC = 1

Section "old_pond", ROM0
old_pond:
db height, width, HIGH(old_pondAutoEvents), LOW($old_pondAutoEvents)
db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
db $01, $01, $01, $01, $01, $0d, $01, $01, $01, $01, 
db $01, $01, $01, $06, $0c, $0c, $0c, $06, $01, $01, 
db $01, $01, $01, $01, $04, $04, $04, $06, $01, $01, 
db $01, $01, $01, $06, $04, $04, $04, $06, $01, $01, 
db $01, $01, $06, $01, $06, $06, $06, $01, $01, $01, 
db $01, $01, $01, $06, $01, $06, $01, $01, $01, $01, 
db $01, $01, $01, $01, $01, $0c, $01, $01, $01, $01, 
db $01, $01, $01, $01, $01, $0c, $01, $01, $01, $01, 

old_pondAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        