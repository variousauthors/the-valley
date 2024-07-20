
IF !DEF(STARTING_CAVE_INC)
STARTING_CAVE_INC = 1

Section "starting_cave", ROM0
starting_cave:
  db height, width, HIGH(starting_caveAutoEvents), LOW($starting_caveAutoEvents)
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
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        