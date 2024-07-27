
IF !DEF(TWINS_CROSSING_WEST_INC)
TWINS_CROSSING_WEST_INC = 1

Section "twins_crossing_west", ROM0
twins_crossing_west:
  db 9, 10, 
  db HIGH(twins_crossing_westAutoEvents), LOW(twins_crossing_westAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(twins_crossing_westBumpEvents), LOW(twins_crossing_westBumpEvents)
  db HIGH(twins_crossing_westEntities), LOW(twins_crossing_westEntities)
  db $11, $11, $11, $11, $11, 
  db $16, $11, $11, $11, $11, 
  db $11, $11, $cc, $d1, $11, 
  db $11, $61, $c1, $11, $61, 
  db $11, $11, $61, $11, $11, 
  db $11, $11, $c1, $11, $11, 
  db $6c, $6c, $61, $11, $61, 
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $61, $11, 

twins_crossing_westAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

twins_crossing_westBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

twins_crossing_westEntities:
  ret

ENDC