IF !DEF(DESERT_TOWN_INC)
DESERT_TOWN_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "DesertTown", ROM0
DesertTown:
  db 18, 20, HIGH(DesertTownEvents), LOW(DesertTownEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $24, $44, $22, $22, $22, $24, $44, $42, $22, $22, 
  db $44, $44, $22, $27, $77, $74, $44, $42, $22, $22, 
  db $44, $44, $22, $77, $22, $22, $24, $27, $77, $77, 
  db $44, $44, $2b, $bb, $bb, $b2, $24, $77, $76, $66, 
  db $44, $44, $6b, $66, $00, $b7, $74, $76, $66, $77, 
  db $44, $44, $66, $60, $00, $b6, $64, $66, $67, $22, 
  db $44, $44, $6b, $b6, $bb, $b6, $44, $66, $72, $22, 
  db $44, $44, $66, $66, $66, $66, $56, $66, $72, $22, 
  db $44, $44, $46, $66, $66, $66, $46, $67, $22, $22, 
  db $44, $44, $46, $bb, $6b, $b6, $44, $67, $22, $72, 
  db $44, $44, $46, $b0, $00, $b6, $64, $62, $22, $72, 
  db $44, $44, $46, $bd, $00, $b6, $64, $42, $27, $72, 
  db $44, $44, $46, $6b, $bb, $b6, $46, $42, $27, $22, 
  db $44, $44, $44, $66, $66, $64, $44, $44, $22, $22, 
  db $44, $44, $44, $44, $44, $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, $44, $44, $44, $44, $44, 

DesertTownEvents:
  ; overworld
  AllocateTransportEvent 3, 19, HIGH(Overworld), LOW(Overworld), 28, 28

  ; underworld
  AllocateTransportEvent 11, 7, HIGH(Underworld), LOW(Underworld), 56, 61

  EndList

ENDC