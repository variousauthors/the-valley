
IF !DEF(RUINED_STRUCTURE_INC)
RUINED_STRUCTURE_INC = 1

Section "ruined_structure", ROM0
ruined_structure:
  db 9, 10, 
  db HIGH(ruined_structureAutoEvents), LOW(ruined_structureAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(ruined_structureBumpEvents), LOW(ruined_structureBumpEvents)
  db HIGH(ruined_structureEntities), LOW(ruined_structureEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 
  db $11, $16, $61, $11, $66, 
  db $1b, $b6, $b6, $6c, $61, 
  db $1b, $d6, $6b, $6c, $11, 
  db $16, $66, $66, $cc, $11, 
  db $1b, $66, $66, $11, $11, 
  db $11, $bb, $b1, $11, $11, 
  db $11, $11, $11, $11, $11, 

ruined_structureAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruined_structureBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruined_structureEntities:
  ret

ENDC