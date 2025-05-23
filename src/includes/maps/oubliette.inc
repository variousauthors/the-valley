
IF !DEF(OUBLIETTE_INC)
OUBLIETTE_INC = 1

Section "Oubliette", ROMX, BANK[1]
db NO_ENCOUNTERS
Oubliette:
  db 40, 30, 
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
  db $22, $26, $66, $32, $22, $22, $22, $22, $22, $2a, $ab, $aa, $aa, $a2, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $2a, $aa, $aa, $22, $22, $aa, $aa, $aa, $aa, 
  db $aa, $aa, $aa, $aa, $a2, $22, $2a, $00, $0a, $22, $22, $a0, $00, $00, $0a, 
  db $a0, $00, $a0, $00, $a2, $22, $2a, $0c, $03, $66, $66, $30, $f7, $00, $0a, 
  db $a0, $90, $00, $d0, $a2, $22, $2a, $00, $0a, $22, $22, $a0, $00, $0a, $0a, 
  db $a0, $00, $a0, $00, $a2, $22, $2a, $aa, $aa, $22, $22, $aa, $00, $0a, $0a, 
  db $aa, $5a, $aa, $aa, $a2, $22, $22, $22, $22, $22, $22, $2a, $00, $0a, $aa, 
  db $a0, $00, $a0, $00, $a2, $22, $22, $22, $22, $22, $22, $2a, $ab, $aa, $22, 
  db $a8, $f0, $00, $c0, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $a0, $00, $a0, $00, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $aa, $aa, $aa, $aa, $a2, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 

OublietteAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 0, 0, HIGH(Overworld), LOW(Overworld), 4, 1

  ; 3.
  AllocateIntraTransportEvent 31, 15, Oubliette, 32, 6
  AllocateTransportEvent 36, 6, HIGH(Overworld), LOW(Overworld), 117, 122

  EndList

OublietteBumpEvents:
  ; 0.
  AllocateCheckpointEvent 21, 23, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 21, 24, HIGH(OublietteQuestion1), LOW(OublietteQuestion1)

  ; 1.
  AllocateCheckpointEvent 4, 3, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 3, 3, HIGH(OublietteQuestion1), LOW(OublietteQuestion1)
  AllocateNPCDialogEvent 4, 11, HIGH(OublietteNPC1), LOW(OublietteNPC1)

  ; 2.
  AllocateCheckpointEvent 12, 22, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 12, 23, HIGH(OublietteQuestion1), LOW(OublietteQuestion1)
  AllocateCheckpointEvent 20, 6, HIGH(OublietteNPC2), LOW(OublietteNPC2)
  AllocateCheckpointEvent 21, 6, HIGH(OublietteNPC3), LOW(OublietteNPC3)

  ; 3. 
  AllocateCheckpointEvent 31, 24, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 31, 25, HIGH(OublietteQuestion1), LOW(OublietteQuestion1)
  AllocateCheckpointEvent 36, 2, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateCheckpointEvent 32, 2, HIGH(OublietteNPC4), LOW(OublietteNPC4)
  AllocateCheckpointEvent 36, 1, HIGH(OublietteNPC5), LOW(OublietteNPC5)

  EndList

OublietteEntities:
  ret

ENDC