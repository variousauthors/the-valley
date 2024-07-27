
IF !DEF(RUINS_ONE_INTERIOR_INC)
RUINS_ONE_INTERIOR_INC = 1

Section "ruins_one_interior", ROM0
ruins_one_interior:
  db 18, 20, 
  db HIGH(ruins_one_interiorAutoEvents), LOW(ruins_one_interiorAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(ruins_one_interiorBumpEvents), LOW(ruins_one_interiorBumpEvents)
  db HIGH(ruins_one_interiorEntities), LOW(ruins_one_interiorEntities)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $d0, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $b6, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $6b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

ruins_one_interiorAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruins_one_interiorBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruins_one_interiorEntities:
  ret

ENDC