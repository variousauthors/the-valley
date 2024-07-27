
IF !DEF(DARK_LORD_F1_INC)
DARK_LORD_F1_INC = 1

Section "dark_lord_f1", ROM0
dark_lord_f1:
  db 18, 20, 
  db HIGH(dark_lord_f1AutoEvents), LOW(dark_lord_f1AutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(dark_lord_f1BumpEvents), LOW(dark_lord_f1BumpEvents)
  db HIGH(dark_lord_f1Entities), LOW(dark_lord_f1Entities)
  db $bb, $b0, $00, $00, $00, $00, $00, $00, $0b, $bb, 
  db $00, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $00, 
  db $d0, $00, $bb, $bb, $bb, $bb, $bb, $bb, $00, $0e, 
  db $00, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $00, $00, $00, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $00, $0b, $0b, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $00, $00, $00, $00, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $0e, $cc, $cc, $cc, $cc, $cc, $cc, 
  db $bb, $bb, $bb, $00, $00, $00, $00, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $00, $0b, $0b, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $00, $00, $00, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

dark_lord_f1AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

dark_lord_f1BumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

dark_lord_f1Entities:
  ret

ENDC