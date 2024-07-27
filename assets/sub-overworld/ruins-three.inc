
IF !DEF(RUINS_THREE_INC)
RUINS_THREE_INC = 1

Section "ruins_three", ROM0
ruins_three:
  db 18, 20, 
  db HIGH(ruins_threeAutoEvents), LOW(ruins_threeAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(ruins_threeBumpEvents), LOW(ruins_threeBumpEvents)
  db HIGH(ruins_threeEntities), LOW(ruins_threeEntities)
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

ruins_threeAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruins_threeBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruins_threeEntities:
  ret

ENDC