
IF !DEF(NORTH_FOREST_TEMPLE_INC)
NORTH_FOREST_TEMPLE_INC = 1

Section "north_forest_temple", ROM0
north_forest_temple:
  db 9, 10, 
  db HIGH(north_forest_templeAutoEvents), LOW(north_forest_templeAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(north_forest_templeBumpEvents), LOW(north_forest_templeBumpEvents)
  db HIGH(north_forest_templeEntities), LOW(north_forest_templeEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $1b, $11, $1b, $11, 
  db $11, $11, $11, $11, $11, 
  db $1c, $c6, $cd, $11, $11, 
  db $1c, $11, $11, $11, $11, 
  db $16, $1b, $11, $1b, $11, 
  db $1c, $11, $11, $11, $11, 
  db $16, $11, $11, $11, $11, 
  db $1c, $11, $11, $11, $11, 

north_forest_templeAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

north_forest_templeBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

north_forest_templeEntities:
  ret

ENDC