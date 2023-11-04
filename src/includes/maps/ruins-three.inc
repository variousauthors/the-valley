IF !DEF(RUINS_THREE_INC)
RUINS_THREE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "RuinsThree", ROM0
  db NO_BOUNDS
RuinsThree:
  db 18, 20, HIGH(RuinsThreeEvents), LOW(RuinsThreeEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $1b, $bb, $11, $6c, $61, $11, $11, $11, $11, 
  db $11, $1b, $bb, $11, $66, $61, $11, $61, $11, $11, 
  db $11, $1b, $bb, $bb, $6c, $6b, $1b, $1b, $6b, $61, 
  db $11, $1b, $bb, $bb, $6c, $61, $11, $11, $11, $11, 
  db $11, $1b, $bb, $b6, $6c, $cc, $c6, $cc, $1b, $11, 
  db $11, $1b, $bb, $bb, $6c, $61, $11, $11, $11, $11, 
  db $11, $1b, $bb, $bb, $66, $6b, $1b, $1b, $1b, $61, 
  db $ff, $1b, $bb, $bb, $6c, $61, $11, $11, $16, $11, 
  db $4f, $fb, $11, $11, $6c, $61, $11, $11, $11, $11, 
  db $44, $4b, $b1, $1b, $66, $6b, $bb, $bb, $11, $11, 
  db $44, $44, $fb, $11, $6c, $6b, $bb, $bb, $11, $11, 
  db $14, $4b, $ff, $4b, $6c, $66, $bb, $bb, $11, $11, 
  db $14, $b4, $ff, $f4, $6c, $6b, $bb, $bb, $11, $11, 
  db $11, $44, $fd, $bb, $66, $6b, $bb, $bb, $11, $11, 
  db $11, $4b, $ff, $b1, $6c, $6b, $bb, $bb, $11, $11, 
  db $11, $44, $fb, $11, $6c, $6b, $bb, $bb, $11, $11, 
  db $11, $14, $44, $11, $6c, $61, $11, $11, $11, $11, 
  db $11, $11, $14, $41, $6c, $61, $11, $11, $11, $11, 

RuinsThreeEvents:
  AllocateTransportEvent 0, 9, HIGH(Overworld), LOW(Overworld), 16, 19
  AllocateTransportEvent 17, 9, HIGH(Overworld), LOW(Overworld), 16, 19

  ; interior
  AllocateTransportEvent 4, 7, HIGH(RuinsThreeInterior), LOW(RuinsThreeInterior), 4, 7
  AllocateTransportEvent 11, 11, HIGH(RuinsThreeInterior), LOW(RuinsThreeInterior), 11, 11

  ; underworld
  AllocateTransportEvent 13, 5, HIGH(Underworld), LOW(Underworld), 32, 38

  EndList

ENDC