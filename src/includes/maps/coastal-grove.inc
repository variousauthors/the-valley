IF !DEF(COSTAL_GROVE_INC)
COSTAL_GROVE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "CoastalGrove", ROM0
CoastalGrove:
  db 9, 10, HIGH(CoastalGroveEvents), LOW(CoastalGroveEvents)
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $06, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $01, $0d, $0c, $0c, $06, $01, $01, 
  db $01, $01, $01, $01, $01, $01, $01, $0c, $01, $01, 
  db $01, $01, $01, $01, $01, $01, $01, $06, $01, $01, 
  db $01, $06, $0c, $06, $0c, $0c, $06, $0c, $01, $01, 
  db $01, $01, $0c, $01, $06, $01, $01, $01, $06, $01, 
  db $01, $01, $06, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $0c, $01, $01, $01, $01, $01, $01, $01, 

CoastalGroveEvents:
  AllocateTransportEvent 8, 2, HIGH(Overworld), LOW(Overworld), 29, 1
  AllocateTransportEvent 2, 4, HIGH(Underworld), LOW(Underworld), 58, 2
  EndList

ENDC