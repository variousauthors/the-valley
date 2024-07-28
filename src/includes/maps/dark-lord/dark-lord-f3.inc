
IF !DEF(DARK_LORD_F3_INC)
DARK_LORD_F3_INC = 1

Section "dark_lord_f3", ROM0
dark_lord_f3:
  db 18, 20, 
  db HIGH(dark_lord_f3AutoEvents), LOW(dark_lord_f3AutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(DarkLordTowerEncounters), LOW(DarkLordTowerEncounters), 
  db HIGH(dark_lord_f3BumpEvents), LOW(dark_lord_f3BumpEvents)
  db HIGH(dark_lord_f3Entities), LOW(dark_lord_f3Entities)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $00, $00, $00, $00, $00, $00, $00, $00, $bb, 
  db $bb, $0b, $bb, $bb, $bb, $b0, $bb, $bb, $b0, $bb, 
  db $bb, $0b, $bb, $bb, $bb, $00, $0b, $bb, $b0, $bb, 
  db $bb, $0b, $bb, $bb, $bb, $0d, $0b, $bb, $b0, $bb, 
  db $bb, $0b, $bb, $bb, $bb, $00, $0b, $bb, $b0, $bb, 
  db $b0, $00, $bb, $bb, $bb, $b0, $bb, $bb, $b0, $bb, 
  db $b0, $d0, $00, $00, $00, $00, $0b, $bb, $b0, $bb, 
  db $b0, $00, $bb, $bb, $bb, $b0, $bb, $bb, $b0, $bb, 
  db $bb, $0b, $b0, $00, $00, $b0, $bb, $bb, $00, $0b, 
  db $bb, $0b, $b0, $44, $40, $b0, $00, $00, $0d, $0b, 
  db $bb, $0b, $b0, $44, $40, $bb, $bb, $bb, $00, $0b, 
  db $bb, $00, $00, $44, $40, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $b0, $00, $00, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

dark_lord_f3AutoEvents:
  AllocateTransportEvent 10, 2, HIGH(dark_lord_f2), LOW(dark_lord_f2), 10, 2
  AllocateTransportEvent 13, 17, HIGH(dark_lord_f2), LOW(dark_lord_f2), 13, 17
  AllocateTransportEvent 7, 11, HIGH(dark_lord_f2), LOW(dark_lord_f2), 7, 11
  EndList

dark_lord_f3BumpEvents:
  EndList

dark_lord_f3Entities:
  ret
        
ENDC