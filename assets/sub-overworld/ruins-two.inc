
IF !DEF(RUINS_TWO_INC)
RUINS_TWO_INC = 1

Section "ruins_two", ROM0
ruins_two:
  db 18, 20, 
  db HIGH(ruins_twoAutoEvents), LOW(ruins_twoAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(ruins_twoBumpEvents), LOW(ruins_twoBumpEvents)
  db HIGH(ruins_twoEntities), LOW(ruins_twoEntities)
  db $14, $44, $bb, $bb, $b1, $6c, $61, $11, $11, $11, 
  db $44, $44, $bb, $bb, $b6, $6c, $61, $bb, $b1, $11, 
  db $44, $44, $bb, $bb, $6c, $cc, $61, $b4, $b1, $11, 
  db $44, $44, $bb, $bb, $b6, $6c, $61, $bb, $b1, $11, 
  db $44, $44, $bb, $bb, $b1, $6c, $61, $11, $11, $11, 
  db $44, $44, $11, $11, $11, $6c, $61, $44, $41, $11, 
  db $44, $44, $11, $11, $11, $6c, $64, $46, $44, $41, 
  db $44, $44, $11, $bb, $bb, $bc, $64, $66, $64, $44, 
  db $44, $44, $11, $bb, $bb, $bc, $64, $1d, $11, $44, 
  db $44, $44, $11, $bb, $bb, $6c, $64, $11, $11, $44, 
  db $44, $44, $11, $bb, $bb, $b6, $64, $11, $14, $44, 
  db $44, $44, $11, $bb, $bb, $b1, $14, $11, $44, $44, 
  db $44, $44, $11, $11, $11, $11, $14, $14, $44, $44, 
  db $44, $44, $41, $11, $11, $11, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, $44, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, $44, $44, $44, $44, $44, 

ruins_twoAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruins_twoBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruins_twoEntities:
  ret

ENDC