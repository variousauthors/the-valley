
IF !DEF(STARTING_CAVE_INC)
STARTING_CAVE_INC = 1

Section "starting_cave", ROM0
starting_cave:
  db 9, 8, 
  db HIGH(starting_caveAutoEvents), LOW(starting_caveAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(starting_caveBumpEvents), LOW(starting_caveBumpEvents)
  db HIGH(starting_caveEntities), LOW(starting_caveEntities)
  db $bb, $bb, $bb, $bb, 
  db $bb, $00, $00, $bb, 
  db $b0, $00, $b0, $0b, 
  db $b0, $00, $00, $0b, 
  db $cc, $cc, $00, $0b, 
  db $b0, $00, $00, $0b, 
  db $b0, $00, $b0, $0b, 
  db $bb, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, 

starting_caveAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

starting_caveBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

starting_caveEntities:
  ret

ENDC