IF !DEF(OLD_SWAMP_INC)
OLD_SWAMP_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "OldSwamp", ROMX
  db NO_BOUNDS
OldSwamp:
  db 9, 10, HIGH(OldSwampEvents), LOW(OldSwampEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $11, $11, $11, $11, 
  db $11, $d1, $ff, $11, $11, 
  db $11, $c1, $44, $4f, $11, 
  db $11, $cf, $44, $f1, $11, 
  db $11, $61, $ff, $60, $66, 
  db $11, $06, $16, $01, $11, 
  db $11, $66, $06, $61, $11, 
  db $11, $11, $66, $11, $11, 
  db $11, $11, $11, $11, $11, 

OldSwampEvents:
  AllocateTransportEvent 4, 9, HIGH(Overworld), LOW(Overworld), 2, 31
  AllocateTransportEvent 1, 2, HIGH(Underworld), LOW(Underworld), 6, 64
  EndList

ENDC