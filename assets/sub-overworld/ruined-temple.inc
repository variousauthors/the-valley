
IF !DEF(RUINED_TEMPLE_INC)
RUINED_TEMPLE_INC = 1

Section "ruined_temple", ROM0
ruined_temple:
  db 9, 10, 
  db HIGH(ruined_templeAutoEvents), LOW(ruined_templeAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(ruined_templeBumpEvents), LOW(ruined_templeBumpEvents)
  db HIGH(ruined_templeEntities), LOW(ruined_templeEntities)
  db $11, $11, $11, $11, $11, 
  db $6c, $c1, $11, $11, $11, 
  db $11, $61, $11, $1b, $b1, 
  db $11, $c1, $1b, $60, $61, 
  db $11, $c6, $c6, $0d, $b1, 
  db $16, $61, $1b, $06, $b1, 
  db $16, $44, $11, $bb, $61, 
  db $14, $46, $61, $11, $11, 
  db $11, $11, $11, $11, $11, 

ruined_templeAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruined_templeBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruined_templeEntities:
  ret

ENDC