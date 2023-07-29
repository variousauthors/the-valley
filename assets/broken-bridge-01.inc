
IF !DEF(BROKEN_BRIDGE_01_INC)
BROKEN_BRIDGE_01_INC = 1

Section "broken_bridge_01", ROM0
broken_bridge_01:
db height, width, HIGH(broken_bridge_01AutoEvents), LOW($broken_bridge_01AutoEvents)
db $06, $06, $08, $04, $04, $04, $06, $06, $06, $06, $06, $06, 
db $06, $06, $08, $04, $04, $04, $08, $08, $01, $01, $06, $06, 
db $06, $06, $08, $04, $04, $04, $08, $06, $06, $06, $01, $01, 
db $06, $0b, $0b, $04, $04, $0b, $0b, $0b, $06, $06, $06, $06, 
db $00, $0c, $0c, $04, $04, $0c, $0c, $0c, $0c, $0c, $0c, $0c, 
db $0c, $00, $0c, $0c, $04, $04, $0c, $0c, $0c, $0c, $0c, $0c, 
db $06, $06, $0b, $04, $0b, $04, $0b, $0b, $06, $01, $06, $06, 
db $06, $06, $08, $04, $04, $04, $08, $06, $01, $06, $01, $01, 
db $06, $06, $08, $04, $04, $04, $06, $06, $06, $06, $06, $06, 

broken_bridge_01AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        