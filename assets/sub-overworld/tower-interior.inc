
IF !DEF(TOWER_INTERIOR_INC)
TOWER_INTERIOR_INC = 1

Section "tower_interior", ROM0
tower_interior:
  db 18, 30, 
  db HIGH(tower_interiorAutoEvents), LOW(tower_interiorAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(tower_interiorBumpEvents), LOW(tower_interiorBumpEvents)
  db HIGH(tower_interiorEntities), LOW(tower_interiorEntities)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $00, $bb, $bb, 
  db $bb, $b0, $00, $00, $00, $00, $0b, $bb, $bb, $00, $00, $00, $00, $0b, $bb, 
  db $bb, $bb, $00, $0b, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $b0, $00, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $b0, $00, $00, $00, $00, $00, $0b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $0b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $0b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $00, $0b, $b0, $bb, $b0, $bb, $bb, $b0, $00, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $00, $00, $00, $bb, $b0, $bb, $bb, $b0, $00, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $00, $0b, $bb, $bb, $b0, $bb, $bb, $b0, $00, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $0b, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0d, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

tower_interiorAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

tower_interiorBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

tower_interiorEntities:
  ret

ENDC