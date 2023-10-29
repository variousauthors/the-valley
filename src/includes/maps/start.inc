IF !DEF(START_INC)
START_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Start", ROM0
Start:
  db 9, 10, HIGH(StartAutoEvents), LOW(StartAutoEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $11, $11, $11, $16, 
  db $11, $66, $11, $66, $61, 
  db $16, $6b, $b6, $b6, $61, 
  db $66, $6b, $66, $db, $16, 
  db $66, $66, $66, $bb, $61, 
  db $66, $6b, $66, $66, $61, 
  db $16, $66, $b6, $6b, $66, 
  db $11, $66, $6b, $b6, $61, 
  db $11, $11, $66, $66, $11, 

StartAutoEvents:
  ; overworld
  AllocateTransportEvent 4, 0, HIGH(Overworld), LOW(Overworld), 30, 12

  ; underworld
  AllocateTransportEvent 3, 6, HIGH(Underworld), LOW(Underworld), 60, 24

  EndList

StartTriggerEvents:
  EndList

ENDC