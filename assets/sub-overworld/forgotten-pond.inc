
IF !DEF(FORGOTTEN_POND_INC)
FORGOTTEN_POND_INC = 1

Section "forgotten_pond", ROM0
forgotten_pond:
  db 9, 10, 
  db HIGH(forgotten_pondAutoEvents), LOW(forgotten_pondAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(forgotten_pondBumpEvents), LOW(forgotten_pondBumpEvents)
  db HIGH(forgotten_pondEntities), LOW(forgotten_pondEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $1b, $1d, $1b, $11, 
  db $11, $16, $66, $61, $11, 
  db $11, $16, $44, $46, $11, 
  db $11, $66, $44, $46, $11, 
  db $11, $66, $66, $66, $11, 
  db $11, $6b, $66, $6b, $11, 
  db $11, $11, $66, $11, $11, 
  db $11, $11, $16, $11, $11, 

forgotten_pondAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

forgotten_pondBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

forgotten_pondEntities:
  ret

ENDC