IF !DEF(MOUNTAIN_PASS_01_INC)
MOUNTAIN_PASS_01_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "MountainPass01", ROM0
MountainPass01:
  db 14, 10, HIGH(MountainPass01Events), LOW(MountainPass01Events)
  db $02, $02, $01, $02, $04, $04, $02, $01, $01, $02, 
  db $02, $02, $01, $02, $04, $04, $02, $01, $01, $02, 
  db $02, $01, $01, $02, $04, $02, $01, $07, $02, $02, 
  db $07, $07, $01, $07, $08, $06, $06, $02, $02, $02, 
  db $07, $02, $02, $02, $04, $02, $06, $06, $02, $02, 
  db $07, $07, $02, $01, $04, $04, $02, $02, $01, $02, 
  db $07, $07, $07, $02, $02, $04, $04, $02, $02, $02, 
  db $07, $07, $07, $06, $02, $02, $04, $02, $02, $02, 
  db $02, $07, $06, $06, $06, $02, $04, $02, $02, $01, 
  db $02, $07, $06, $06, $06, $06, $08, $06, $02, $01, 
  db $02, $06, $06, $06, $06, $02, $04, $06, $02, $02, 
  db $02, $06, $06, $06, $04, $04, $04, $06, $01, $02, 
  db $02, $06, $06, $04, $04, $04, $06, $01, $02, $02, 
  db $02, $01, $07, $04, $04, $02, $07, $02, $01, $02, 

MountainPass01Events:
  AllocateTransportEvent 13, 2, HIGH(Overworld), LOW(Overworld), 10, 14
  AllocateTransportEvent 13, 6, HIGH(Overworld), LOW(Overworld), 11, 16
  AllocateTransportEvent 0, 8, HIGH(Overworld), LOW(Overworld), 9, 16
  EndList

ENDC