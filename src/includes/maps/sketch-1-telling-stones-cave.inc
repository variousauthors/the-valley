
IF !DEF(SKETCH_1_TELLING_STONES_CAVE_INC)
SKETCH_1_TELLING_STONES_CAVE_INC = 1

Section "Sketch_1_telling_stones_cave", ROMX, BANK[1]
  db NO_ENCOUNTERS
Sketch_1_telling_stones_cave:
  db 26, 16, 
  db HIGH(Sketch_1_telling_stones_caveAutoEvents), LOW(Sketch_1_telling_stones_caveAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_telling_stones_caveBumpEvents), LOW(Sketch_1_telling_stones_caveBumpEvents)
  db HIGH(Sketch_1_telling_stones_caveEntities), LOW(Sketch_1_telling_stones_caveEntities)
  db $22, $aa, $aa, $22, $22, $22, $22, $22, 
  db $2a, $00, $00, $aa, $a2, $22, $22, $22, 
  db $a0, $00, $00, $00, $a2, $22, $22, $22, 
  db $a0, $a0, $00, $a0, $a2, $22, $22, $22, 
  db $a0, $00, $e0, $00, $a2, $22, $22, $22, 
  db $2a, $00, $00, $00, $a2, $22, $22, $22, 
  db $22, $a0, $00, $a0, $a2, $22, $22, $22, 
  db $22, $a0, $00, $00, $0a, $22, $22, $22, 
  db $42, $2a, $aa, $00, $00, $a2, $22, $22, 
  db $42, $22, $22, $a0, $00, $0a, $22, $22, 
  db $44, $2a, $aa, $aa, $00, $0a, $22, $22, 
  db $44, $a0, $00, $00, $0a, $a2, $22, $22, 
  db $44, $00, $00, $00, $0a, $22, $22, $22, 
  db $44, $00, $0a, $00, $00, $a2, $22, $22, 
  db $44, $0e, $00, $00, $00, $a2, $22, $22, 
  db $44, $00, $00, $0a, $0a, $22, $22, $22, 
  db $44, $00, $0a, $0a, $0a, $aa, $a2, $22, 
  db $24, $40, $00, $0a, $00, $00, $a2, $22, 
  db $2a, $44, $aa, $aa, $00, $e0, $a2, $22, 
  db $22, $a4, $44, $00, $00, $00, $a2, $22, 
  db $22, $2a, $05, $00, $00, $0a, $a2, $22, 
  db $22, $2a, $04, $44, $40, $0a, $22, $22, 
  db $22, $2a, $0a, $44, $44, $44, $a2, $22, 
  db $22, $a0, $00, $a4, $4a, $44, $4a, $22, 
  db $22, $a0, $00, $aa, $a2, $2a, $44, $22, 
  db $22, $2a, $0a, $22, $22, $22, $a4, $42, 

Sketch_1_telling_stones_caveAutoEvents:
  AllocateTransportEvent 25, 4, HIGH(Overworld), LOW(Overworld), 106, 90
  EndList

Sketch_1_telling_stones_caveBumpEvents:
  ; stones
  AllocateNPCDialogEvent 18, 10, HIGH(TellingStones1), LOW(TellingStones1)
  AllocateNPCDialogEvent 14, 3, HIGH(TellingStones2), LOW(TellingStones2)
  AllocateNPCDialogEvent 4, 4, HIGH(TellingStones3), LOW(TellingStones3)
  EndList

Sketch_1_telling_stones_caveEntities:
  ret

ENDC