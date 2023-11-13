IF !DEF(FORGOTTEN_POND_INC)
FORGOTTEN_POND_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "ForgottenPond", ROM0
  db NO_BOUNDS ; metadata flags
ForgottenPond:
  db 9, 10, HIGH(ForgottenPondAutoEvents), LOW(ForgottenPondAutoEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $11, $11, $11, $11, 
  db $11, $1b, $1d, $1b, $11, 
  db $11, $16, $66, $61, $11, 
  db $11, $16, $44, $46, $11, 
  db $11, $66, $44, $46, $11, 
  db $11, $66, $66, $66, $11, 
  db $11, $6b, $66, $6b, $11, 
  db $11, $11, $66, $11, $11, 
  db $11, $11, $16, $11, $11, 

ForgottenPondAutoEvents:
  ; overworld
  AllocateTransportEvent 8, 5, HIGH(Overworld), LOW(Overworld), 25, 16

  ; underworld
  AllocateTransportEvent 1, 5, HIGH(Underworld), LOW(Underworld), 50, 32

  EndList

ForgottenPondTriggerEvents:
  EndList

ENDC