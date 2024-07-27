
IF !DEF(FORD_01_INC)
FORD_01_INC = 1

Section "ford_01", ROM0
ford_01:
  db 18, 10, 
  db HIGH(ford_01AutoEvents), LOW(ford_01AutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(ford_01BumpEvents), LOW(ford_01BumpEvents)
  db HIGH(ford_01Entities), LOW(ford_01Entities)
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

ford_01AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ford_01BumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ford_01Entities:
  ret

ENDC