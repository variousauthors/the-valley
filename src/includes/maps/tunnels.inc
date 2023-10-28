IF !DEF(TUNNELS_INC)
TUNNELS_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Tunnels", ROMX, BANK[1]
Tunnels:
  db 9, 10, HIGH(TunnelsAutoEvents), LOW(TunnelsAutoEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $b0, $eb, $bb, $bb, $bb, 
  db $b0, $bb, $bb, $bb, $bb, 
  db $be, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $e0, 
  db $bb, $bb, $bb, $bb, $b0, 
  db $bb, $bb, $bb, $bb, $be, 
  db $bb, $bb, $bb, $bb, $bb, 
  db $eb, $bb, $bb, $bb, $bb, 
  db $00, $eb, $bb, $bb, $bb, 

TunnelsAutoEvents:
  ; left
  AllocateTransportEvent 7, 0, HIGH(Underworld), LOW(Underworld), 14, 3
  AllocateTransportEvent 8, 2, HIGH(TunnelsEntrance), LOW(TunnelsEntrance), 2, 2

  ; middle
  AllocateTransportEvent 0, 2, HIGH(Underworld), LOW(Underworld), 23, 68
  AllocateTransportEvent 2, 1, HIGH(TunnelsEntrance), LOW(TunnelsEntrance), 1, 5

  ; right
  AllocateTransportEvent 3, 8, HIGH(TunnelsEntrance), LOW(TunnelsEntrance), 2, 8
  AllocateTransportEvent 5, 9, HIGH(Underworld), LOW(Underworld), 67, 89

  EndList

TunnelsTriggerEvents:
  EndList

ENDC