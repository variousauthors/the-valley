
IF !DEF(SOUTH_GROVE_EXIT_INC)
SOUTH_GROVE_EXIT_INC = 1

Section "south_grove_exit", ROM0
south_grove_exit:
  db 12, 12, 
  db HIGH(south_grove_exitAutoEvents), LOW(south_grove_exitAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(south_grove_exitBumpEvents), LOW(south_grove_exitBumpEvents)
  db HIGH(south_grove_exitEntities), LOW(south_grove_exitEntities)
  db $11, $11, $11, $11, $61, $11, 
  db $11, $b1, $0b, $b1, $11, $61, 
  db $1b, $66, $60, $61, $11, $11, 
  db $1b, $0d, $66, $06, $b1, $11, 
  db $11, $16, $06, $66, $b6, $11, 
  db $61, $16, $60, $11, $b6, $61, 
  db $11, $b1, $c1, $1b, $66, $41, 
  db $11, $11, $c6, $66, $64, $41, 
  db $11, $11, $c1, $44, $44, $41, 
  db $11, $61, $c0, $64, $46, $41, 
  db $11, $66, $66, $60, $61, $11, 
  db $11, $11, $c1, $11, $11, $11, 

south_grove_exitAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

south_grove_exitBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

south_grove_exitEntities:
  ret

ENDC