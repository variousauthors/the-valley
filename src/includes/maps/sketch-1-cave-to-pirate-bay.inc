
IF !DEF(SKETCH_1_CAVE_TO_PIRATE_BAY_INC)
SKETCH_1_CAVE_TO_PIRATE_BAY_INC = 1

Section "Sketch_1_cave_to_pirate_bay", ROMX, BANK[1]
Sketch_1_cave_to_pirate_bay:
  db 40, 24, 
  db HIGH(Sketch_1_cave_to_pirate_bayAutoEvents), LOW(Sketch_1_cave_to_pirate_bayAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(CaveToPirateBayEncounters), LOW(CaveToPirateBayEncounters), 
  db HIGH(Sketch_1_cave_to_pirate_bayBumpEvents), LOW(Sketch_1_cave_to_pirate_bayBumpEvents)
  db HIGH(Sketch_1_cave_to_pirate_bayEntities), LOW(Sketch_1_cave_to_pirate_bayEntities)
  db $2a, $4a, $22, $22, $22, $22, $22, $22, $2a, $aa, $2a, $22, 
  db $2a, $44, $a2, $22, $22, $22, $22, $aa, $a0, $00, $a0, $a2, 
  db $22, $a4, $4a, $22, $22, $22, $2a, $00, $00, $c0, $a0, $a2, 
  db $22, $2a, $44, $a2, $22, $22, $a0, $0a, $a0, $00, $a0, $a2, 
  db $22, $22, $a4, $a2, $22, $2a, $00, $a2, $2a, $aa, $a0, $a2, 
  db $22, $22, $a4, $4a, $aa, $a0, $0a, $22, $22, $22, $a0, $a2, 
  db $22, $22, $2a, $44, $00, $00, $a2, $22, $22, $22, $a0, $a2, 
  db $22, $22, $a0, $05, $00, $0a, $22, $22, $22, $22, $a0, $a2, 
  db $22, $2a, $00, $04, $40, $00, $a2, $22, $22, $22, $a0, $a2, 
  db $22, $2a, $0a, $aa, $44, $a0, $0a, $aa, $22, $22, $a0, $a2, 
  db $22, $2a, $0a, $22, $a4, $4a, $00, $00, $a2, $2a, $00, $a2, 
  db $22, $2a, $0a, $22, $2a, $4a, $aa, $a0, $0a, $2a, $0a, $22, 
  db $22, $2a, $0a, $22, $2a, $44, $a2, $2a, $00, $a0, $0a, $22, 
  db $22, $aa, $00, $a2, $22, $a4, $a2, $22, $a0, $00, $a2, $22, 
  db $2a, $00, $00, $0a, $22, $a4, $4a, $22, $2a, $00, $a2, $22, 
  db $a0, $00, $10, $00, $a2, $2a, $4a, $22, $22, $a0, $0a, $22, 
  db $a0, $04, $40, $00, $a2, $2a, $44, $a2, $22, $a0, $00, $a2, 
  db $a0, $01, $44, $10, $0a, $a2, $a4, $a2, $2a, $00, $00, $a2, 
  db $2a, $00, $44, $40, $00, $0a, $a4, $4a, $a0, $00, $01, $0a, 
  db $22, $a0, $14, $00, $aa, $00, $00, $50, $00, $04, $40, $0a, 
  db $22, $a0, $00, $00, $a2, $aa, $00, $44, $00, $00, $44, $1a, 
  db $22, $a0, $00, $0a, $22, $22, $a0, $04, $a0, $00, $00, $0a, 
  db $22, $2a, $aa, $a2, $2a, $aa, $00, $a4, $4a, $aa, $10, $a2, 
  db $22, $22, $22, $2a, $a0, $00, $0a, $2a, $4a, $22, $aa, $22, 
  db $22, $22, $22, $a0, $00, $aa, $a2, $2a, $44, $a2, $22, $22, 
  db $22, $22, $2a, $00, $aa, $22, $22, $a0, $04, $4a, $22, $22, 
  db $22, $22, $2a, $0a, $22, $2a, $aa, $00, $aa, $44, $a2, $22, 
  db $22, $22, $2a, $0a, $22, $a0, $00, $0a, $22, $a4, $4a, $22, 
  db $22, $22, $2a, $0a, $22, $a0, $aa, $a2, $22, $2a, $44, $a2, 
  db $22, $22, $2a, $0a, $2a, $a0, $a2, $22, $22, $22, $a4, $a2, 
  db $22, $22, $2a, $00, $a0, $00, $a2, $22, $22, $22, $a4, $a2, 
  db $22, $22, $22, $a0, $00, $aa, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $2a, $0a, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $2a, $0a, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $2a, $0a, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $2a, $0a, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $a0, $00, $a2, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $a0, $c0, $a2, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $a0, $00, $a2, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $2a, $aa, $22, $22, $22, $22, $22, $22, $22, 

Sketch_1_cave_to_pirate_bayAutoEvents:
  AllocateTransportEvent 37, 8, HIGH(Overworld), LOW(Overworld), 67, 120
  AllocateTransportEvent 2, 18, HIGH(Overworld), LOW(Overworld), 56, 125
  EndList

Sketch_1_cave_to_pirate_bayBumpEvents:
  EndList

Sketch_1_cave_to_pirate_bayEntities:
  ret

ENDC