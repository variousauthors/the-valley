IF !DEF(HIDEY_HOLE_INC)
HIDEY_HOLE_INC = 1

Section "hidey_hole", ROM0
hidey_hole:
  db 9, 10, 
  db HIGH(hidey_holeAutoEvents), LOW(hidey_holeAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(hidey_holeBumpEvents), LOW(hidey_holeBumpEvents)
  db HIGH(hidey_holeEntities), LOW(hidey_holeEntities)
  db $bb, $00, $00, $66, $bb, 
  db $b0, $01, $10, $06, $0b, 
  db $00, $00, $00, $b0, $00, 
  db $44, $00, $00, $00, $00, 
  db $44, $00, $d0, $00, $00, 
  db $44, $00, $00, $00, $00, 
  db $00, $00, $00, $b6, $00, 
  db $b6, $60, $00, $00, $0b, 
  db $bb, $60, $00, $06, $bb, 

hidey_holeAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

hidey_holeBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

hidey_holeEntities:
  ret

ENDC