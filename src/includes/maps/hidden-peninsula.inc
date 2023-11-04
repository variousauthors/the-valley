IF !DEF(HIDDEN_PENINSULA_INC)
HIDDEN_PENINSULA_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "HiddenPeninsula", ROM0
  db NO_BOUNDS
HiddenPeninsula:
  db 9, 10, HIGH(HiddenPeninsulaAutoEvents), LOW(HiddenPeninsulaAutoEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 
  db $11, $cc, $66, $c6, $c6, 
  db $11, $c1, $11, $11, $11, 
  db $1b, $6b, $bb, $b1, $11, 
  db $1b, $66, $66, $b1, $11, 
  db $1b, $6d, $61, $11, $11, 
  db $11, $16, $11, $b1, $11, 
  db $11, $bb, $bb, $b1, $11, 

HiddenPeninsulaAutoEvents:
  ; overworld
  AllocateTransportEvent 2, 9, HIGH(Overworld), LOW(Overworld), 23, 44

  ; underworld
  AllocateTransportEvent 6, 3, HIGH(Underworld), LOW(Underworld), 46, 88

  EndList

HiddenPeninsulaTriggerEvents:
  EndList

ENDC