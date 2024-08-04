
IF !DEF(PENINSULA_FORT_INC)
PENINSULA_FORT_INC = 1

Section "peninsula_fort", ROM0
peninsula_fort:
  db 21, 20, 
  db HIGH(peninsula_fortAutoEvents), LOW(peninsula_fortAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(peninsula_fortBumpEvents), LOW(peninsula_fortBumpEvents)
  db HIGH(peninsula_fortEntities), LOW(peninsula_fortEntities)
  db $41, $11, $11, $11, $11, $11, $11, $11, $11, $11, 
  db $41, $11, $11, $11, $11, $11, $11, $11, $11, $11, 
  db $44, $11, $11, $11, $11, $11, $11, $11, $11, $11, 
  db $44, $11, $11, $11, $11, $11, $11, $11, $11, $14, 
  db $bb, $bb, $bb, $bb, $b6, $bb, $bb, $bb, $bb, $bb, 
  db $44, $b1, $b1, $b1, $1c, $1a, $b1, $b1, $b1, $14, 
  db $44, $11, $11, $11, $6c, $66, $11, $11, $11, $14, 
  db $44, $11, $bb, $b6, $6c, $66, $61, $11, $11, $14, 
  db $44, $1b, $00, $0b, $6c, $6b, $bb, $11, $11, $11, 
  db $41, $1b, $00, $00, $cc, $6b, $00, $b1, $11, $11, 
  db $41, $1b, $00, $0b, $6c, $c0, $00, $8b, $61, $11, 
  db $41, $16, $bb, $bb, $6c, $6b, $00, $0b, $66, $11, 
  db $46, $66, $66, $66, $6c, $66, $bb, $b1, $11, $11, 
  db $46, $66, $bb, $bb, $6c, $66, $66, $66, $11, $14, 
  db $41, $6b, $09, $0b, $6c, $66, $44, $46, $11, $14, 
  db $11, $6b, $00, $00, $cc, $66, $44, $41, $11, $14, 
  db $11, $10, $90, $0b, $6c, $61, $44, $41, $11, $14, 
  db $11, $1b, $bb, $bb, $66, $66, $11, $11, $11, $14, 
  db $11, $16, $66, $66, $66, $61, $11, $11, $11, $14, 
  db $41, $11, $16, $61, $11, $11, $11, $11, $11, $44, 
  db $44, $11, $11, $11, $11, $11, $11, $11, $44, $44, 

peninsula_fortAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

peninsula_fortBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

peninsula_fortEntities:
  ret

ENDC