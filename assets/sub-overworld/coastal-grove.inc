
IF !DEF(COASTAL_GROVE_INC)
COASTAL_GROVE_INC = 1

Section "coastal_grove", ROM0
coastal_grove:
  db 9, 10, 
  db HIGH(coastal_groveAutoEvents), LOW(coastal_groveAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(coastal_groveBumpEvents), LOW(coastal_groveBumpEvents)
  db HIGH(coastal_groveEntities), LOW(coastal_groveEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $16, $11, $11, $11, 
  db $11, $11, $dc, $c6, $11, 
  db $11, $11, $11, $1c, $11, 
  db $11, $11, $11, $16, $11, 
  db $16, $c6, $cc, $6c, $11, 
  db $11, $c1, $61, $11, $61, 
  db $11, $61, $11, $11, $11, 
  db $11, $c1, $11, $11, $11, 

coastal_groveAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

coastal_groveBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

coastal_groveEntities:
  ret

ENDC