
IF !DEF(TINY_MAP_INC)
TINY_MAP_INC = 1

Section "tiny_map", ROM0
tiny_map:
  db 5, 4, 
  db HIGH(tiny_mapAutoEvents), LOW(tiny_mapAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(tiny_mapBumpEvents), LOW(tiny_mapBumpEvents)
  db HIGH(tiny_mapEntities), LOW(tiny_mapEntities)
  db $36, $66, 
  db $66, $66, 
  db $66, $66, 
  db $66, $66, 
  db $66, $66, 

tiny_mapAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

tiny_mapBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

tiny_mapEntities:
  ret

ENDC