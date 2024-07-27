
IF !DEF(OLD_SWAMP_INC)
OLD_SWAMP_INC = 1

Section "old_swamp", ROM0
old_swamp:
  db 9, 10, 
  db HIGH(old_swampAutoEvents), LOW(old_swampAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(old_swampBumpEvents), LOW(old_swampBumpEvents)
  db HIGH(old_swampEntities), LOW(old_swampEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $d1, $ff, $11, $11, 
  db $11, $c1, $44, $4f, $11, 
  db $11, $cf, $44, $f1, $11, 
  db $11, $61, $ff, $60, $66, 
  db $11, $06, $16, $01, $11, 
  db $11, $66, $06, $61, $11, 
  db $11, $11, $66, $11, $11, 
  db $11, $11, $11, $11, $11, 

old_swampAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

old_swampBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

old_swampEntities:
  ret

ENDC