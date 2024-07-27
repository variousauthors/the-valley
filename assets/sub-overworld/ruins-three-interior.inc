
IF !DEF(RUINS_THREE_INTERIOR_INC)
RUINS_THREE_INTERIOR_INC = 1

Section "ruins_three_interior", ROM0
ruins_three_interior:
  db 18, 20, 
  db HIGH(ruins_three_interiorAutoEvents), LOW(ruins_three_interiorAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(ruins_three_interiorBumpEvents), LOW(ruins_three_interiorBumpEvents)
  db HIGH(ruins_three_interiorEntities), LOW(ruins_three_interiorEntities)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $db, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $06, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $b6, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

ruins_three_interiorAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruins_three_interiorBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

ruins_three_interiorEntities:
  ret

ENDC