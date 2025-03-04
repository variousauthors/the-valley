
IF !DEF(SKETCH_1_LITTLE_VALLEY_CAVES_INC)
SKETCH_1_LITTLE_VALLEY_CAVES_INC = 1

Section "Sketch_1_little_valley_caves", ROMX, BANK[1]
Sketch_1_little_valley_caves:
  db 26, 22, 
  db HIGH(Sketch_1_little_valley_cavesAutoEvents), LOW(Sketch_1_little_valley_cavesAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_little_valley_cavesBumpEvents), LOW(Sketch_1_little_valley_cavesBumpEvents)
  db HIGH(Sketch_1_little_valley_cavesEntities), LOW(Sketch_1_little_valley_cavesEntities)
  db $22, $2a, $aa, $aa, $aa, $aa, $22, $22, $22, $22, $22, 
  db $22, $a0, $00, $00, $00, $00, $a2, $22, $22, $22, $22, 
  db $2a, $00, $aa, $aa, $aa, $a0, $ca, $22, $22, $22, $22, 
  db $a0, $0a, $22, $22, $22, $2a, $a2, $22, $22, $22, $22, 
  db $a0, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $a0, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $a0, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $a0, $a2, $22, $22, $22, $aa, $aa, $aa, $22, $22, $22, 
  db $a0, $a2, $22, $22, $2a, $00, $00, $00, $a2, $22, $22, 
  db $a0, $0a, $22, $22, $a0, $00, $70, $00, $a2, $22, $22, 
  db $2a, $ca, $22, $22, $a0, $00, $f0, $00, $a2, $22, $22, 
  db $22, $a2, $22, $22, $2a, $00, $00, $0a, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $aa, $a0, $a2, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $2a, $aa, $aa, $a2, $22, $22, $22, $22, $2a, $a2, 
  db $22, $a0, $00, $a0, $0a, $22, $22, $22, $aa, $ad, $0a, 
  db $2a, $01, $00, $00, $d0, $a2, $22, $2a, $00, $00, $0a, 
  db $2a, $10, $07, $00, $00, $a2, $22, $a0, $00, $00, $a2, 
  db $a0, $00, $0f, $70, $0a, $a2, $22, $a0, $70, $0a, $22, 
  db $a0, $00, $00, $00, $00, $a2, $22, $a0, $f0, $0a, $22, 
  db $a0, $17, $00, $0a, $aa, $22, $22, $2a, $00, $0a, $22, 
  db $a0, $00, $00, $a2, $22, $22, $22, $2a, $00, $0a, $22, 
  db $2a, $00, $00, $a2, $22, $22, $22, $2a, $00, $0a, $22, 
  db $22, $aa, $0a, $22, $22, $22, $22, $22, $a0, $a2, $22, 

Sketch_1_little_valley_cavesAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_little_valley_cavesBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Sketch_1_little_valley_cavesEntities:
  ret

ENDC