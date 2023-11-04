IF !DEF(TOWER_INC)
TOWER_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Tower", ROM0
  db HAS_BOUNDS
Tower:
  db 27, 30, HIGH(TowerAutoEvents), LOW(TowerAutoEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
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
  ; underworld
  AllocateTransportEvent 25, 15, HIGH(Underworld), LOW(Underworld), 28, 32

  ; interior
  AllocateTransportEvent 12, 7, HIGH(TowerInterior), LOW(TowerInterior), 12, 7
  AllocateTransportEvent 12, 22, HIGH(TowerInterior), LOW(TowerInterior), 12, 22
  AllocateTransportEvent 2, 3, HIGH(TowerInterior), LOW(TowerInterior), 2, 3
  AllocateTransportEvent 2, 26, HIGH(TowerInterior), LOW(TowerInterior), 2, 26

  ; game over
  AllocateGameOverEvent 11, 15

  EndList

TowerTriggerEvents:
  EndList

ENDC