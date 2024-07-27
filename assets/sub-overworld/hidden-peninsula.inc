
IF !DEF(HIDDEN_PENINSULA_INC)
HIDDEN_PENINSULA_INC = 1

Section "hidden_peninsula", ROM0
hidden_peninsula:
  db 9, 10, 
  db HIGH(hidden_peninsulaAutoEvents), LOW(hidden_peninsulaAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(hidden_peninsulaBumpEvents), LOW(hidden_peninsulaBumpEvents)
  db HIGH(hidden_peninsulaEntities), LOW(hidden_peninsulaEntities)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 
  db $11, $cc, $66, $c6, $c6, 
  db $11, $c1, $11, $11, $11, 
  db $1b, $6b, $bb, $b1, $11, 
  db $1b, $66, $66, $b1, $11, 
  db $1b, $6d, $61, $11, $11, 
  db $11, $16, $11, $b1, $11, 
  db $11, $bb, $bb, $b1, $11, 

hidden_peninsulaAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

hidden_peninsulaBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

hidden_peninsulaEntities:
  ret

ENDC