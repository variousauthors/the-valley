IF !DEF(OLD_SWAMP_SOUTH_INC)
OLD_SWAMP_SOUTH_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "OldSwampSouth", ROM0
OldSwampSouth:
  db 9, 10, HIGH(OldSwampSouthEvents), LOW(OldSwampSouthEvents)
  db $01, $01, $01, $0c, $01, $0f, $0f, $01, $01, $01, 
  db $01, $0f, $01, $06, $01, $01, $0f, $0f, $01, $0f, 
  db $0f, $01, $01, $0c, $01, $01, $0f, $0f, $0f, $01, 
  db $01, $0f, $01, $06, $01, $01, $01, $0f, $01, $01, 
  db $01, $01, $01, $0c, $01, $01, $01, $01, $0f, $01, 
  db $01, $01, $01, $0c, $01, $01, $01, $0f, $01, $01, 
  db $02, $01, $01, $06, $0c, $0d, $01, $0f, $01, $02, 
  db $02, $01, $0f, $01, $01, $01, $01, $01, $01, $02, 
  db $01, $02, $01, $01, $0f, $01, $0f, $01, $02, $01, 

OldSwampSouthEvents:
  AllocateTransportEvent 0, 3, HIGH(Overworld), LOW(Overworld), 6, 33
  AllocateTransportEvent 6, 5, HIGH(Underworld), LOW(Underworld), 12, 66
  EndList

ENDC