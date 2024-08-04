
IF !DEF(DARK_LORD_B1_INC)
DARK_LORD_B1_INC = 1

Section "dark_lord_b1", ROM0
dark_lord_b1:
  db 18, 20, 
  db HIGH(dark_lord_b1AutoEvents), LOW(dark_lord_b1AutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(dark_lord_b1BumpEvents), LOW(dark_lord_b1BumpEvents)
  db HIGH(dark_lord_b1Entities), LOW(dark_lord_b1Entities)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, 
  db $b0, $00, $00, $00, $00, $00, $08, $08, $00, $0b, 
  db $b0, $00, $a0, $0a, $00, $a0, $00, $00, $80, $0b, 
  db $b0, $00, $00, $00, $00, $00, $00, $00, $bb, $0b, 
  db $b0, $ec, $0c, $cc, $cc, $cc, $cc, $c0, $0b, $0b, 
  db $b0, $00, $00, $00, $00, $00, $00, $00, $bb, $0b, 
  db $b0, $00, $a0, $0a, $00, $a0, $00, $00, $80, $0b, 
  db $b0, $00, $00, $00, $00, $00, $08, $08, $00, $0b, 
  db $bb, $0b, $0b, $0b, $0b, $0b, $00, $00, $00, $0b, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

dark_lord_b1AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

dark_lord_b1BumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

dark_lord_b1Entities:
  ret

ENDC