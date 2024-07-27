
IF !DEF(RUINS_ONE_INC)
RUINS_ONE_INC = 1

Section "ruins_one", ROM0
ruins_one:
  db 18, 20, 
  db HIGH(ruins_oneAutoEvents), LOW(ruins_oneAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(ruins_oneBumpEvents), LOW(ruins_oneBumpEvents)
  db HIGH(ruins_oneEntities), LOW(ruins_oneEntities)
  db $14, $44, $11, $44, $44, $11, $11, $11, $11, $11, 
  db $44, $4b, $bb, $4b, $b4, $11, $1b, $bb, $bb, $b1, 
  db $41, $44, $44, $41, $14, $11, $1b, $bb, $bb, $b1, 
  db $b6, $11, $16, $61, $14, $11, $1b, $bb, $bb, $b1, 
  db $b6, $d6, $66, $14, $b1, $6c, $c6, $bb, $bb, $b1, 
  db $6b, $66, $61, $44, $b1, $66, $6b, $bb, $bb, $b1, 
  db $1b, $66, $14, $4b, $11, $6c, $6b, $bb, $bb, $b1, 
  db $b6, $66, $b4, $bb, $11, $6c, $6b, $bb, $bb, $b1, 
  db $1b, $66, $b1, $11, $11, $6c, $61, $11, $ff, $11, 
  db $66, $bb, $66, $66, $66, $6c, $61, $ff, $ff, $f1, 
  db $cc, $cc, $6c, $cc, $c6, $cc, $6f, $fb, $4b, $ff, 
  db $66, $66, $66, $66, $66, $6c, $6f, $b4, $44, $bf, 
  db $11, $1b, $bb, $6b, $bb, $66, $6f, $44, $b4, $4f, 
  db $11, $1b, $bb, $bb, $bb, $6c, $ff, $b4, $44, $bf, 
  db $11, $1b, $bb, $bb, $bb, $6c, $ff, $fb, $4b, $f1, 
  db $11, $1b, $bb, $bb, $bb, $6f, $ff, $ff, $ff, $f1, 
  db $11, $1b, $bb, $bb, $bb, $6c, $61, $ff, $f1, $11, 
  db $11, $11, $11, $11, $11, $6c, $61, $11, $11, $11, 

ruins_oneAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruins_oneBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruins_oneEntities:
  ret

ENDC