
IF !DEF(SKETCH_1_EAST_WEST_SAGES_INC)
SKETCH_1_EAST_WEST_SAGES_INC = 1

Section "Sketch_1_east_west_sages", ROMX, BANK[1]
  db NO_ENCOUNTERS
Start:
Sketch_1_east_west_sages:
  db 36, 34, 
  db HIGH(Sketch_1_east_west_sagesAutoEvents), LOW(Sketch_1_east_west_sagesAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_east_west_sagesBumpEvents), LOW(Sketch_1_east_west_sagesBumpEvents)
  db HIGH(Sketch_1_east_west_sagesEntities), LOW(Sketch_1_east_west_sagesEntities)
  db $2a, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a0, $a2, 
  db $ad, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a0, $a2, 
  db $a0, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a0, $a2, 
  db $20, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $aa, $a9, $a2, 
  db $26, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a2, $22, $22, $ad, $00, $00, $a2, 
  db $26, $22, $22, $aa, $aa, $aa, $a2, $22, $22, $2a, $da, $22, $22, $aa, $a0, $00, $0a, 
  db $26, $22, $aa, $aa, $aa, $aa, $aa, $a2, $22, $22, $02, $22, $22, $a0, $80, $70, $0a, 
  db $26, $22, $aa, $00, $00, $00, $0a, $a2, $22, $22, $62, $22, $22, $a0, $0f, $00, $a2, 
  db $26, $2a, $a0, $a0, $00, $00, $a0, $aa, $22, $22, $62, $22, $22, $a0, $00, $0a, $22, 
  db $26, $63, $00, $00, $00, $00, $00, $aa, $22, $22, $62, $22, $22, $aa, $00, $0a, $22, 
  db $22, $2a, $a0, $00, $e0, $e9, $00, $a3, $66, $66, $62, $22, $22, $2a, $a0, $aa, $22, 
  db $2a, $aa, $a0, $00, $00, $00, $00, $a3, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $aa, $a0, $a0, $00, $00, $a0, $a0, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $a0, $00, $00, $00, $00, $00, $00, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $a0, $44, $40, $a0, $a0, $10, $10, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $a0, $48, $50, $00, $00, $07, $00, $aa, $22, $22, $22, $2a, $0a, $22, $22, $22, 
  db $2a, $a0, $44, $40, $a0, $a0, $10, $10, $aa, $22, $22, $22, $2a, $0a, $22, $22, $22, 
  db $2a, $a0, $00, $00, $00, $00, $00, $00, $aa, $22, $22, $22, $2a, $0a, $22, $22, $22, 
  db $2a, $aa, $a0, $00, $a0, $a0, $00, $aa, $aa, $22, $22, $2a, $aa, $9a, $aa, $22, $22, 
  db $2a, $aa, $a0, $00, $00, $00, $00, $aa, $aa, $22, $22, $a0, $00, $00, $00, $a2, $22, 
  db $aa, $aa, $a0, $00, $a0, $a0, $00, $aa, $aa, $a2, $22, $a0, $a8, $07, $a0, $0a, $22, 
  db $aa, $aa, $aa, $00, $00, $00, $0a, $aa, $aa, $a2, $22, $a0, $00, $f0, $0a, $0a, $22, 
  db $aa, $aa, $aa, $aa, $00, $0a, $aa, $aa, $aa, $a2, $22, $a0, $00, $00, $0a, $da, $22, 
  db $aa, $aa, $aa, $aa, $a0, $aa, $aa, $aa, $aa, $a2, $22, $2a, $a0, $00, $00, $a2, $22, 
  db $aa, $aa, $a0, $00, $00, $00, $00, $aa, $aa, $a2, $22, $22, $2a, $0a, $aa, $22, $22, 
  db $44, $44, $00, $10, $0b, $00, $10, $04, $44, $42, $22, $22, $22, $22, $22, $22, $22, 
  db $44, $44, $40, $01, $0b, $01, $00, $44, $44, $42, $22, $22, $22, $22, $22, $22, $22, 
  db $44, $44, $44, $00, $0b, $00, $04, $44, $44, $42, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $aa, $aa, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $00, $0a, $22, $22, $22, 
  db $2a, $aa, $aa, $aa, $aa, $aa, $aa, $a2, $22, $2a, $aa, $aa, $0a, $0a, $aa, $aa, $a2, 
  db $2a, $c0, $00, $0a, $00, $00, $00, $a2, $22, $2a, $00, $00, $0a, $0a, $00, $0c, $a2, 
  db $2a, $aa, $0a, $aa, $a0, $aa, $a0, $a2, $22, $2a, $0a, $aa, $aa, $0a, $0a, $aa, $a2, 
  db $22, $2a, $00, $00, $00, $a2, $ac, $a2, $22, $2a, $ca, $22, $2a, $00, $0a, $22, $22, 
  db $22, $2a, $aa, $aa, $aa, $a2, $aa, $a2, $22, $2a, $aa, $22, $2a, $aa, $aa, $22, $22, 

Sketch_1_east_west_sagesAutoEvents:
  ; east sage entrance
  AllocateTransportEvent 10, 29, HIGH(Overworld), LOW(Overworld), 100, 73
  ; west sage entrance
  AllocateTransportEvent 24, 26, HIGH(Overworld), LOW(Overworld), 100, 70
  ; temple entrance
  AllocateTransportEvent 23, 9, HIGH(Overworld), LOW(Overworld), 104, 71

  ; stairs to passages
  ; east sage stairs
  AllocateIntraTransportEvent 4, 27, Sketch_1_east_west_sages, 32, 31
  AllocateIntraTransportEvent 34, 20, Sketch_1_east_west_sages, 5, 20

  ; west sage stairs
  AllocateIntraTransportEvent 22, 30, Sketch_1_east_west_sages, 32, 2
  AllocateIntraTransportEvent 34, 13, Sketch_1_east_west_sages, 1, 1

  EndList

Sketch_1_east_west_sagesBumpEvents:
  AllocateCheckpointEvent 21, 26, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateCheckpointEvent 7, 26, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)

  ; east sages
  AllocateNPCDialogEvent 6, 30, HIGH(EastSageNPC1), LOW(EastSageNPC1)
  AllocateNPCDialogEvent 6, 28, HIGH(EastSageNPC2), LOW(EastSageNPC2)

  ; west sages
  AllocateNPCDialogEvent 20, 27, HIGH(WestSageNPC1), LOW(WestSageNPC1)
  AllocateNPCDialogEvent 20, 25, HIGH(WestSageNPC2), LOW(WestSageNPC2)

  ; guards
  AllocateNPCDialogEvent 18, 26, HIGH(NorthRoadGuard), LOW(NorthRoadGuard)
  AllocateNPCDialogEvent 3, 31, HIGH(NorthRoadGuard), LOW(NorthRoadGuard)

  ; pilgrims
  AllocateNPCDialogEvent 15, 5, HIGH(PilgrimNPC1), LOW(PilgrimNPC1)
  AllocateNPCDialogEvent 10, 11, HIGH(PilgrimNPC2), LOW(PilgrimNPC2)
  AllocateNPCDialogEvent 15, 13, HIGH(PilgrimNPC3), LOW(PilgrimNPC3)

  ; scriptures
  AllocateNPCDialogEvent 10, 8, HIGH(StoneScripture1), LOW(StoneScripture1)
  AllocateNPCDialogEvent 10, 10, HIGH(StoneScripture2), LOW(StoneScripture2)

  EndList

Sketch_1_east_west_sagesEntities:
  ret

ENDC