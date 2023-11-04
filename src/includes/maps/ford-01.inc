IF !DEF(FORD_01_INC)
FORD_01_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Ford01", ROM0
  db NO_BOUNDS
Ford01:
  db 18, 10, HIGH(Ford01Events), LOW(Ford01Events), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $14, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $46, 
  db $44, $44, $44, $44, $66, 
  db $1f, $f4, $44, $ff, $44, 
  db $1f, $4f, $ff, $f4, $6f, 
  db $66, $4f, $4f, $44, $f4, 
  db $16, $64, $ff, $f6, $f4, 
  db $16, $4f, $ff, $4f, $46, 
  db $16, $ff, $46, $44, $64, 
  db $16, $ff, $4f, $f6, $64, 
  db $16, $44, $44, $f6, $4f, 
  db $64, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, 

Ford01Events:
  AllocateTransportEvent 7, 0, HIGH(Overworld), LOW(Overworld), 34, 6
  AllocateTransportEvent 6, 9, HIGH(Overworld), LOW(Overworld), 34, 8
  EndList

ENDC