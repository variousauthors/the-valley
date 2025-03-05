
IF !DEF(SKETCH_1_EAST_WEST_SAGES_INC)
SKETCH_1_EAST_WEST_SAGES_INC = 1

Section "Sketch_1_east_west_sages", ROMX, BANK[1]
  db NO_ENCOUNTERS
Sketch_1_east_west_sages:
  db 25, 34, 
  db HIGH(Sketch_1_east_west_sagesAutoEvents), LOW(Sketch_1_east_west_sagesAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_east_west_sagesBumpEvents), LOW(Sketch_1_east_west_sagesBumpEvents)
  db HIGH(Sketch_1_east_west_sagesEntities), LOW(Sketch_1_east_west_sagesEntities)
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $0a, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $aa, $a2, $22, $2a, $0a, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $d0, $a2, $22, $2a, $0a, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $a0, $aa, $aa, $aa, $9a, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a0, $a0, $00, $00, $0a, $22, $22, 
  db $22, $22, $22, $aa, $aa, $aa, $a2, $22, $22, $22, $a0, $a0, $00, $00, $00, $a2, $22, 
  db $22, $22, $aa, $aa, $aa, $aa, $aa, $a2, $22, $22, $a0, $00, $08, $07, $00, $a2, $22, 
  db $22, $22, $aa, $00, $00, $00, $0a, $a2, $22, $22, $2a, $a0, $00, $f0, $0a, $22, $22, 
  db $22, $2a, $a0, $a0, $00, $00, $a0, $aa, $22, $22, $22, $a0, $00, $00, $a2, $22, $22, 
  db $22, $2a, $a0, $00, $00, $00, $00, $aa, $22, $22, $22, $2a, $a0, $00, $a2, $22, $22, 
  db $22, $2a, $a0, $00, $e0, $e9, $00, $aa, $22, $22, $22, $22, $aa, $0a, $a2, $22, $22, 
  db $2a, $aa, $a0, $00, $00, $00, $00, $aa, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $aa, $a0, $a0, $00, $00, $a0, $aa, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $a0, $00, $00, $00, $00, $00, $00, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $a0, $44, $40, $a0, $a0, $10, $10, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $a0, $48, $50, $00, $00, $07, $00, $aa, $22, $22, $22, $2a, $0a, $22, $22, $22, 
  db $2a, $a0, $44, $40, $a0, $a0, $10, $10, $aa, $22, $22, $22, $2a, $0a, $22, $22, $22, 
  db $2a, $a0, $00, $00, $00, $00, $00, $00, $aa, $22, $22, $22, $2a, $0a, $22, $22, $22, 
  db $2a, $aa, $a0, $aa, $aa, $aa, $a0, $aa, $aa, $22, $22, $2a, $aa, $9a, $aa, $22, $22, 
  db $2a, $aa, $a0, $aa, $aa, $aa, $a0, $aa, $aa, $22, $22, $a0, $00, $00, $00, $a2, $22, 
  db $aa, $00, $00, $00, $00, $00, $00, $00, $0a, $a2, $22, $a0, $a8, $07, $a0, $0a, $22, 
  db $aa, $0c, $00, $00, $00, $00, $00, $0c, $0a, $a2, $22, $a0, $00, $f0, $0a, $0a, $22, 
  db $aa, $00, $0a, $aa, $aa, $aa, $aa, $00, $0a, $a2, $22, $a0, $00, $00, $0a, $da, $22, 
  db $aa, $aa, $aa, $aa, $aa, $aa, $aa, $aa, $aa, $a2, $22, $2a, $a0, $00, $00, $a2, $22, 
  db $aa, $aa, $a2, $22, $22, $22, $22, $aa, $aa, $a2, $22, $22, $2a, $0a, $aa, $22, $22, 

Sketch_1_east_west_sagesAutoEvents:
  ; overworld
  AllocateTransportEvent 24, 26, HIGH(Overworld), LOW(Overworld), 97, 73
  AllocateTransportEvent 10, 26, HIGH(Overworld), LOW(Overworld), 97, 70

  ; stairs
  AllocateTransportEvent 22, 30, HIGH(Sketch_1_east_west_sages), LOW(Sketch_1_east_west_sages), 21, 15
  AllocateTransportEvent 21, 15, HIGH(Sketch_1_east_west_sages), LOW(Sketch_1_east_west_sages), 22, 30
  AllocateTransportEvent 2, 20, HIGH(Sketch_1_east_west_sages), LOW(Sketch_1_east_west_sages), 21, 3
  AllocateTransportEvent 21, 3, HIGH(Sketch_1_east_west_sages), LOW(Sketch_1_east_west_sages), 2, 20

  EndList

Sketch_1_east_west_sagesBumpEvents:
  AllocateCheckpointEvent 21, 26, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateCheckpointEvent 7, 26, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)

  ; east sages
  AllocateNPCDialogEvent 20, 27, HIGH(EastSageNPC1), LOW(EastSageNPC1)
  AllocateNPCDialogEvent 20, 25, HIGH(EastSageNPC2), LOW(EastSageNPC2)

  ; west sages
  AllocateNPCDialogEvent 6, 27, HIGH(WestSageNPC1), LOW(WestSageNPC1)
  AllocateNPCDialogEvent 6, 25, HIGH(WestSageNPC2), LOW(WestSageNPC2)

  ; guards
  AllocateNPCDialogEvent 18, 26, HIGH(NorthRoadGuard), LOW(NorthRoadGuard)
  AllocateNPCDialogEvent 3, 28, HIGH(NorthRoadGuard), LOW(NorthRoadGuard)

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