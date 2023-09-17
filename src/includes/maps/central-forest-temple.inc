IF !DEF(CENTRAL_FOREST_TEMPLE_INC)
CENTRAL_FOREST_TEMPLE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "CentralForestTemple", ROM0
CentralForestTemple:
  db 9, 10, HIGH(CentralForestTempleEvents), LOW(CentralForestTempleEvents)
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 
  db $06, $0c, $0c, $06, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $06, $01, $01, $0b, $01, $0b, $01, $01, 
  db $01, $01, $0c, $01, $0b, $06, $06, $06, $0b, $01, 
  db $01, $01, $0c, $06, $0c, $06, $0d, $06, $01, $01, 
  db $01, $01, $01, $01, $0b, $06, $06, $06, $0b, $01, 
  db $01, $06, $01, $01, $01, $0b, $01, $0b, $01, $01, 
  db $01, $04, $04, $01, $01, $01, $01, $01, $01, $01, 
  db $01, $01, $01, $01, $01, $01, $01, $01, $01, $01, 

CentralForestTempleEvents:
  AllocateTransportEvent 1, 0, HIGH(Overworld), LOW(Overworld), 12, 8
  AllocateTransportEvent 4, 6, HIGH(Underworld), LOW(Underworld), 24, 16
  EndList

ENDC