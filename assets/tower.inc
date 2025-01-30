
IF !DEF(TOWER_INC)
TOWER_INC = 1

Section "Tower", ROMX, BANK[1]
Tower:
  db 27, 30, 
  db HIGH(TowerAutoEvents), LOW(TowerAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(TowerBumpEvents), LOW(TowerBumpEvents)
  db HIGH(TowerEntities), LOW(TowerEntities)
  db $44, $6b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b6, $44, 
  db $44, $6b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b6, $44, 
  db $44, $60, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $06, $44, 
  db $44, $6b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b6, $44, 
  db $44, $6b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b6, $44, 
  db $44, $6b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b6, $44, 
  db $44, $6b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b6, $44, 
  db $44, $6b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b6, $44, 
  db $44, $6b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b6, $44, 
  db $44, $6b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b6, $44, 
  db $44, $6b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b6, $44, 
  db $44, $6b, $bb, $bb, $bb, $bb, $bb, $b9, $bb, $bb, $bb, $bb, $bb, $b6, $44, 
  db $44, $6b, $bb, $b0, $bb, $bb, $bb, $6c, $6b, $bb, $bb, $0b, $bb, $b6, $44, 
  db $44, $66, $64, $66, $61, $11, $14, $6c, $64, $11, $16, $66, $46, $66, $44, 
  db $44, $66, $64, $6c, $61, $11, $14, $6c, $64, $11, $16, $c6, $46, $66, $44, 
  db $44, $6c, $c5, $cc, $61, $11, $15, $cc, $c5, $11, $16, $cc, $5c, $c6, $44, 
  db $44, $6c, $64, $66, $61, $11, $14, $66, $64, $11, $16, $66, $46, $c6, $44, 
  db $44, $6c, $64, $44, $44, $44, $44, $44, $44, $44, $44, $44, $46, $c6, $44, 
  db $44, $6c, $64, $11, $14, $11, $14, $11, $14, $44, $44, $44, $46, $c6, $44, 
  db $44, $6c, $64, $1b, $14, $1b, $14, $1b, $14, $44, $44, $44, $46, $c6, $44, 
  db $44, $6c, $64, $11, $14, $11, $14, $11, $14, $66, $66, $66, $46, $c6, $44, 
  db $44, $6c, $64, $11, $14, $11, $14, $11, $16, $66, $cc, $cc, $5c, $c6, $44, 
  db $44, $6c, $64, $11, $14, $11, $14, $11, $14, $66, $c6, $66, $46, $66, $44, 
  db $44, $6c, $64, $46, $44, $46, $44, $44, $44, $66, $c6, $44, $44, $44, $44, 
  db $44, $6c, $64, $66, $66, $66, $64, $66, $64, $66, $c6, $41, $11, $11, $44, 
  db $44, $6c, $c5, $cc, $cc, $cc, $c5, $6d, $65, $cc, $c6, $61, $11, $b1, $44, 
  db $44, $66, $64, $66, $66, $66, $64, $66, $64, $66, $66, $41, $11, $11, $44, 

TowerAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

TowerBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  EndList

TowerEntities:
  ret

ENDC