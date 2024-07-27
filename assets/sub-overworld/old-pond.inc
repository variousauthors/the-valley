
IF !DEF(OLD_POND_INC)
OLD_POND_INC = 1

Section "old_pond", ROM0
old_pond:
  db 9, 10, 
  db HIGH(old_pondAutoEvents), LOW(old_pondAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(old_pondBumpEvents), LOW(old_pondBumpEvents)
  db HIGH(old_pondEntities), LOW(old_pondEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $1d, $11, $11, 
  db $11, $16, $cc, $c6, $11, 
  db $11, $11, $44, $46, $11, 
  db $11, $16, $44, $46, $11, 
  db $11, $61, $66, $61, $11, 
  db $11, $16, $16, $11, $11, 
  db $11, $11, $1c, $11, $11, 
  db $11, $11, $1c, $11, $11, 

old_pondAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

old_pondBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

old_pondEntities:
  ret

ENDC