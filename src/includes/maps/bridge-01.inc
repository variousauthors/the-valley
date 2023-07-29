IF !DEF(BRIDGE_01_INC)
BRIDGE_01_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Bridge01", ROM0
Bridge01:
  db 9, 14, HIGH(Bridge01Events), LOW(Bridge01Events)
  db $01, $01, $01, $01, $08, $04, $04, $04, $06, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $06, $08, $04, $04, $04, $08, $08, $01, $01, $01, $01, 
  db $01, $01, $06, $06, $08, $04, $04, $04, $08, $06, $06, $06, $01, $01, 
  db $01, $06, $06, $0b, $0b, $04, $04, $0b, $0b, $0b, $06, $06, $06, $06, 
  db $0c, $0c, $00, $0c, $0c, $04, $04, $0c, $0c, $0c, $0c, $0c, $0c, $0c, 
  db $0c, $06, $0c, $00, $0c, $0c, $04, $04, $0c, $0c, $0c, $0c, $0c, $0c, 
  db $01, $06, $06, $06, $0b, $04, $0b, $04, $0b, $0b, $06, $01, $06, $06, 
  db $01, $01, $01, $06, $08, $04, $04, $04, $08, $06, $01, $06, $01, $01, 
  db $01, $01, $01, $01, $08, $04, $04, $04, $06, $01, $01, $01, $01, $01, 

Bridge01Events:
  AllocateTransportEvent 4, 13, HIGH(Overworld), LOW(Overworld), 17, 14
  AllocateTransportEvent 5, 13, HIGH(Overworld), LOW(Overworld), 17, 14
  AllocateTransportEvent 4, 0, HIGH(Overworld), LOW(Overworld), 17, 10
  AllocateTransportEvent 5, 0, HIGH(Overworld), LOW(Overworld), 17, 10
  EndList

ENDC