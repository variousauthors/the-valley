
IF !DEF(CENTRAL_FOREST_TEMPLE_INC)
CENTRAL_FOREST_TEMPLE_INC = 1

Section "central_forest_temple", ROM0
central_forest_temple:
  db 9, 10, 
  db HIGH(central_forest_templeAutoEvents), LOW(central_forest_templeAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(central_forest_templeBumpEvents), LOW(central_forest_templeBumpEvents)
  db HIGH(central_forest_templeEntities), LOW(central_forest_templeEntities)
  db $11, $11, $11, $11, $11, 
  db $6c, $c6, $11, $11, $11, 
  db $11, $61, $1b, $1b, $11, 
  db $11, $c1, $b6, $66, $b1, 
  db $11, $c6, $c6, $d6, $11, 
  db $11, $11, $b6, $66, $b1, 
  db $16, $11, $1b, $1b, $11, 
  db $14, $41, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 

central_forest_templeAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

central_forest_templeBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

central_forest_templeEntities:
  ret

ENDC