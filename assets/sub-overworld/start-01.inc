
IF !DEF(START_01_INC)
START_01_INC = 1

Section "start_01", ROM0
start_01:
  db 9, 10, 
  db HIGH(start_01AutoEvents), LOW(start_01AutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(start_01BumpEvents), LOW(start_01BumpEvents)
  db HIGH(start_01Entities), LOW(start_01Entities)
  db $11, $11, $11, $11, $16, 
  db $11, $66, $11, $66, $61, 
  db $16, $6b, $b6, $b6, $61, 
  db $66, $6b, $66, $db, $16, 
  db $66, $66, $66, $bb, $61, 
  db $66, $6b, $66, $66, $61, 
  db $16, $66, $b6, $6b, $66, 
  db $11, $66, $6b, $b6, $61, 
  db $11, $11, $66, $66, $11, 

start_01AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

start_01BumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

start_01Entities:
  ret

ENDC