
IF !DEF(DARK_LORD_F2_INC)
DARK_LORD_F2_INC = 1

Section "dark_lord_f2", ROM0
dark_lord_f2:
  db 18, 20, 
  db HIGH(dark_lord_f2AutoEvents), LOW(dark_lord_f2AutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(DarkLordTowerEncounters), LOW(DarkLordTowerEncounters), 
  db HIGH(dark_lord_f2BumpEvents), LOW(dark_lord_f2BumpEvents)
  db HIGH(dark_lord_f2Entities), LOW(dark_lord_f2Entities)
  db $b0, $00, $0b, $b0, $00, $00, $03, $33, $33, $00, 
  db $b0, $bb, $0b, $b0, $bb, $bb, $bb, $bb, $bb, $b0, 
  db $bb, $bb, $0b, $b0, $bb, $bb, $bb, $bb, $bb, $bd, 
  db $00, $0b, $00, $00, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $0b, $0b, $b0, $b0, $b0, $00, $bb, $bb, $bb, $bb, 
  db $0b, $0b, $b0, $b0, $b0, $b0, $bb, $bb, $bb, $bb, 
  db $0b, $0b, $b0, $00, $00, $b0, $bb, $bb, $b0, $00, 
  db $0b, $bb, $bb, $b0, $bb, $be, $bb, $bb, $b0, $b0, 
  db $00, $00, $0b, $00, $0b, $bb, $bb, $bb, $b0, $b0, 
  db $0b, $bb, $00, $0d, $00, $0b, $bb, $bb, $bb, $b0, 
  db $0b, $eb, $bb, $00, $0b, $0b, $b0, $00, $00, $00, 
  db $0b, $0b, $bb, $b0, $bb, $00, $00, $bb, $bb, $bb, 
  db $0b, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $00, $0b, $00, $00, $00, $00, $00, $00, $be, $0b, 
  db $bb, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $00, $00, $0b, $0b, $00, $00, $00, $00, $00, $0b, 
  db $0b, $bb, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, 
  db $00, $00, $0b, $00, $00, $b0, $00, $00, $bb, $bb, 

dark_lord_f2AutoEvents:
  AllocateTransportEvent 9, 7, HIGH(dark_lord_f1), LOW(dark_lord_f1), 9, 7
  AllocateTransportEvent 2, 19, HIGH(dark_lord_f1), LOW(dark_lord_f1), 2, 19

  AllocateTransportEvent 10, 2, HIGH(dark_lord_f3), LOW(dark_lord_f3), 10, 2
  AllocateTransportEvent 13, 17, HIGH(dark_lord_f3), LOW(dark_lord_f3), 13, 17
  AllocateTransportEvent 7, 11, HIGH(dark_lord_f3), LOW(dark_lord_f3), 7, 11
  EndList

dark_lord_f2BumpEvents:
  EndList

dark_lord_f2Entities:
  ret
        
ENDC