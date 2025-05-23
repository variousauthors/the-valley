
IF !DEF(OUBLIETTE_INC)
OUBLIETTE_INC = 1

Section "Oubliette", ROMX, BANK[1]
db NO_ENCOUNTERS
Oubliette:
  db 30, 30, 
  db HIGH(OublietteAutoEvents), LOW(OublietteAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(OublietteBumpEvents), LOW(OublietteBumpEvents)
  db HIGH(OublietteEntities), LOW(OublietteEntities)
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $aa, $aa, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $00, $0a, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $07, $0a, $aa, $aa, $a2, $22, $2a, $aa, $aa, $a2, $22, $22, $22, $22, 
  db $2a, $0f, $00, $00, $00, $36, $66, $63, $00, $00, $a2, $22, $22, $22, $22, 
  db $2a, $00, $00, $0a, $aa, $a2, $22, $2a, $00, $90, $a2, $22, $22, $22, $22, 
  db $2a, $a0, $00, $0a, $22, $22, $22, $2a, $00, $00, $a2, $22, $22, $22, $22, 
  db $22, $a0, $00, $0a, $22, $22, $22, $2a, $00, $00, $a2, $22, $22, $22, $22, 
  db $22, $aa, $ba, $aa, $22, $22, $22, $2a, $ab, $aa, $a2, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $aa, $aa, $aa, $a2, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $00, $00, $00, $a2, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $00, $0f, $70, $a2, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $00, $00, $00, $a2, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $a0, $00, $a0, $a2, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $00, $00, $a0, $a2, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $2a, $ab, $aa, $aa, $a2, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 

OublietteAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 0, 0, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

OublietteBumpEvents:
  AllocateCheckpointEvent 4, 3, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateCheckpointEvent 21, 23, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)

  AllocateNPCDialogEvent 21, 24, HIGH(OublietteNPC1), LOW(OublietteNPC1)
  AllocateNPCDialogEvent 3, 3, HIGH(OublietteNPC1), LOW(OublietteNPC1)
  AllocateNPCDialogEvent 5, 18, HIGH(OublietteNPC2), LOW(OublietteNPC2)
  EndList

OublietteEntities:
  ret

ENDC