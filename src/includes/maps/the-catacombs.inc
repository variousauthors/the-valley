IF !DEF(THE_CATACOMBS_INC)
THE_CATACOMBS_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "TheCatacombs", ROM0
  db HAS_BOUNDS
TheCatacombs:
  db 45, 30, HIGH(TheCatacombsAutoEvents), LOW(TheCatacombsAutoEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $e0, $00, $b0, $00, $b0, $b0, $e0, $00, $b0, $00, $b0, $b0, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $b0, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $b0, $e0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $00, $b0, $b0, $e0, $00, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $b0, $b0, $00, $b0, $00, $b0, $b0, $e0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $e0, $00, $b0, $b0, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $b0, $b0, $00, $e0, $b0, $b0, $b0, $e0, $00, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $b0, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $0b, $bb, $0b, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $e0, $00, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $b0, $b0, $b0, $b0, $00, $b0, $00, $b0, $00, $e0, $00, $b0, $00, $b0, $bb, 
  db $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 

TheCatacombsAutoEvents:
  ; underworld
  AllocateTransportEvent 2, 2, HIGH(Underworld), LOW(Underworld), 4, 34
  AllocateTransportEvent 2, 14, HIGH(Underworld), LOW(Underworld), 4, 46
  AllocateTransportEvent 14, 6, HIGH(Underworld), LOW(Underworld), 16, 38
  AllocateTransportEvent 18, 18, HIGH(Underworld), LOW(Underworld), 20, 50
  AllocateTransportEvent 22, 26, HIGH(Underworld), LOW(Underworld), 24, 58
  AllocateTransportEvent 26, 18, HIGH(Underworld), LOW(Underworld), 28, 50
  AllocateTransportEvent 30, 10, HIGH(Underworld), LOW(Underworld), 32, 42
  AllocateTransportEvent 30, 18, HIGH(Underworld), LOW(Underworld), 32, 50
  AllocateTransportEvent 38, 18, HIGH(Underworld), LOW(Underworld), 40, 50
  AllocateTransportEvent 42, 18, HIGH(Underworld), LOW(Underworld), 44, 50

  EndList


TheCatacombsTriggerEvents:
  EndList

ENDC