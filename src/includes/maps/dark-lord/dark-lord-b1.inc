
IF !DEF(DARK_LORD_B1_INC)
DARK_LORD_B1_INC = 1

Section "dark_lord_b1", ROM0
  db NO_ENCOUNTERS
dark_lord_b1:
  db 18, 20, 
  db HIGH(dark_lord_b1AutoEvents), LOW(dark_lord_b1AutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(DarkLordTowerEncounters), LOW(DarkLordTowerEncounters), 
  db HIGH(dark_lord_b1BumpEvents), LOW(dark_lord_b1BumpEvents)
  db HIGH(dark_lord_b1Entities), LOW(dark_lord_b1Entities)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, 
  db $b0, $00, $00, $00, $00, $00, $0b, $b0, $00, $0b, 
  db $b0, $00, $80, $08, $00, $80, $0b, $b0, $00, $0b, 
  db $b0, $00, $00, $00, $00, $00, $00, $00, $bb, $0b, 
  db $b0, $ec, $cc, $cc, $cc, $cc, $cc, $c0, $0b, $0b, 
  db $b0, $00, $00, $00, $00, $00, $00, $00, $bb, $0b, 
  db $b0, $00, $80, $08, $00, $80, $0b, $b0, $00, $0b, 
  db $b0, $00, $00, $00, $00, $00, $0b, $b0, $00, $0b, 
  db $bb, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

dark_lord_b1AutoEvents:
  AllocateTransportEvent 8, 2, HIGH(dark_lord_f1), LOW(dark_lord_f1), 2, 0
  EndList

dark_lord_b1BumpEvents:
  AllocateNPCDialogEvent 6, 4, HIGH(Silence), LOW(Silence)
  AllocateNPCDialogEvent 6, 7, HIGH(Silence), LOW(Silence)
  AllocateNPCDialogEvent 6, 10, HIGH(Silence), LOW(Silence)
  AllocateNPCDialogEvent 10, 4, HIGH(Silence), LOW(Silence)
  AllocateNPCDialogEvent 10, 7, HIGH(Silence), LOW(Silence)
  AllocateNPCDialogEvent 10, 10, HIGH(Silence), LOW(Silence)
  EndList

dark_lord_b1Entities:
  ret
        
ENDC