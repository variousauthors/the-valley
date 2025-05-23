
IF !DEF(OUBLIETTE_INC)
OUBLIETTE_INC = 1

Section "Oubliette", ROMX, BANK[1]
Oubliette:
  db 30, 30, 
  db HIGH(OublietteAutoEvents), LOW(OublietteAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(OublietteBumpEvents), LOW(OublietteBumpEvents)
  db HIGH(OublietteEntities), LOW(OublietteEntities)
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $aa, $aa, $aa, $aa, $aa, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $00, $0a, $00, $0a, $00, $0a, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $07, $0a, $00, $0a, $09, $0a, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $0f, $0a, $ab, $aa, $a5, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $00, $00, $00, $00, $00, $0a, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $2a, $a0, $00, $00, $00, $00, $0a, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $a0, $00, $0a, $aa, $aa, $aa, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $aa, $ba, $aa, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $aa, $aa, $aa, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $a0, $00, $0a, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $23, $66, $66, $63, $00, $f7, $0a, $22, $22, 
  db $22, $22, $22, $22, $2a, $aa, $a0, $aa, $22, $22, $a0, $00, $0a, $22, $22, 
  db $22, $22, $22, $22, $aa, $00, $00, $0a, $22, $22, $aa, $aa, $aa, $22, $22, 
  db $22, $22, $2a, $aa, $a0, $0a, $00, $0a, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $aa, $00, $00, $aa, $ab, $aa, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $a0, $00, $00, $00, $00, $a2, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $23, $00, $00, $aa, $0a, $00, $a2, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $26, $a0, $00, $00, $aa, $aa, $a2, $22, $22, $2a, $aa, $aa, $a2, $22, 
  db $22, $26, $aa, $5a, $a0, $a0, $00, $a2, $22, $22, $aa, $00, $00, $a2, $22, 
  db $22, $26, $a0, $90, $a0, $00, $00, $a2, $22, $2a, $a0, $0f, $70, $a2, $22, 
  db $22, $26, $a0, $00, $a0, $a0, $00, $a2, $22, $2a, $00, $00, $00, $a2, $22, 
  db $22, $26, $a0, $00, $aa, $aa, $ba, $a2, $22, $2a, $a0, $00, $a0, $a2, $22, 
  db $22, $26, $aa, $0a, $a2, $22, $22, $22, $22, $2a, $00, $00, $a0, $a2, $22, 
  db $22, $26, $66, $32, $22, $22, $62, $22, $22, $2a, $ab, $aa, $aa, $a2, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 

OublietteAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

OublietteBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

OublietteEntities:
  ret

ENDC