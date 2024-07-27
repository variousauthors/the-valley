
IF !DEF(DARK_LORD_APPROACH_INC)
DARK_LORD_APPROACH_INC = 1

Section "dark_lord_approach", ROM0
  db NO_ENCOUNTERS
dark_lord_approach:
  db 18, 20, 
  db HIGH(dark_lord_approachAutoEvents), LOW(dark_lord_approachAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(dark_lord_approachBumpEvents), LOW(dark_lord_approachBumpEvents)
  db HIGH(dark_lord_approachEntities), LOW(dark_lord_approachEntities)
  db $4b, $bb, $bb, $44, $44, $44, $44, $44, $44, $44, 
  db $bb, $bb, $bb, $44, $44, $44, $44, $44, $44, $44, 
  db $bb, $bb, $bb, $44, $44, $44, $44, $4f, $44, $b4, 
  db $bb, $bb, $bb, $44, $ff, $44, $b4, $ff, $44, $44, 
  db $bb, $bb, $bb, $4f, $f4, $44, $44, $f4, $ff, $44, 
  db $bb, $bb, $bb, $ff, $44, $ff, $44, $ff, $4f, $f4, 
  db $bb, $bb, $bb, $ff, $0f, $f0, $f0, $ff, $00, $ff, 
  db $bb, $bb, $bb, $60, $bf, $0b, $00, $0b, $f0, $ff, 
  db $bb, $bb, $bb, $00, $60, $60, $00, $60, $06, $f6, 
  db $bb, $bb, $bc, $cc, $cc, $cc, $fc, $cc, $cc, $cc, 
  db $bb, $bb, $bb, $60, $60, $0f, $60, $60, $06, $0c, 
  db $bb, $bb, $bb, $00, $b6, $fb, $00, $0b, $06, $fc, 
  db $bb, $bb, $bb, $ff, $0f, $ff, $f0, $6f, $6f, $ff, 
  db $bb, $bb, $bb, $f4, $4b, $ff, $44, $44, $ff, $44, 
  db $bb, $bb, $bb, $ff, $44, $4f, $fb, $44, $ff, $44, 
  db $bb, $bb, $bb, $4f, $f4, $44, $44, $4f, $f4, $44, 
  db $bb, $bb, $bb, $44, $44, $44, $44, $44, $44, $44, 
  db $bb, $bb, $bb, $44, $44, $44, $44, $44, $44, $44, 

dark_lord_approachAutoEvents:
  AllocateTransportEvent 9, 19, HIGH(Overworld), LOW(Overworld), 28, 48
  AllocateTransportEvent 9, 5, HIGH(dark_lord_f1), LOW(dark_lord_f1), 9, 19
  EndList

dark_lord_approachBumpEvents:
  EndList

dark_lord_approachEntities:
  ret
        
ENDC