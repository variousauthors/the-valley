
IF !DEF(RUINS_TWO_INTERIOR_INC)
RUINS_TWO_INTERIOR_INC = 1

Section "ruins_two_interior", ROM0
ruins_two_interior:
  db 18, 20, 
  db HIGH(ruins_two_interiorAutoEvents), LOW(ruins_two_interiorAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(ruins_two_interiorBumpEvents), LOW(ruins_two_interiorBumpEvents)
  db HIGH(ruins_two_interiorEntities), LOW(ruins_two_interiorEntities)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $b0, $00, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $b0, $00, $6b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $b0, $00, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $00, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $d0, $6b, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $00, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

ruins_two_interiorAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruins_two_interiorBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruins_two_interiorEntities:
  ret

ENDC