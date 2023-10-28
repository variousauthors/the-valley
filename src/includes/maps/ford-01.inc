IF !DEF(FORD_01_INC)
FORD_01_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Ford01", ROM0
Ford01:
  db 9, 10, HIGH(Ford01Events), LOW(Ford01Events), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $1f, $44, $44, $4f, $41, 
  db $1f, $f4, $44, $ff, $41, 
  db $1f, $4f, $ff, $f4, $66, 
  db $66, $4f, $4f, $44, $61, 
  db $16, $64, $ff, $f6, $61, 
  db $16, $4f, $ff, $4f, $61, 
  db $16, $ff, $4f, $4f, $f1, 
  db $14, $ff, $4f, $ff, $4f, 
  db $14, $44, $44, $f4, $4f, 

Ford01Events:
  AllocateTransportEvent 3, 0, HIGH(Overworld), LOW(Overworld), 34, 6
  AllocateTransportEvent 2, 9, HIGH(Overworld), LOW(Overworld), 34, 8
  EndList

ENDC