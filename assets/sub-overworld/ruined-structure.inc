
IF !DEF(RUINED_STRUCTURE_INC)
RUINED_STRUCTURE_INC = 1

Section "ruined_structure", ROM0
ruined_structure:
  db height, width, HIGH(ruined_structureAutoEvents), LOW($ruined_structureAutoEvents)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 
  db $11, $16, $61, $11, $66, 
  db $1b, $b6, $b6, $6c, $61, 
  db $1b, $d6, $6b, $6c, $11, 
  db $16, $66, $66, $cc, $11, 
  db $1b, $66, $66, $11, $11, 
  db $11, $bb, $b1, $11, $11, 
  db $11, $11, $11, $11, $11, 

ruined_structureAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        