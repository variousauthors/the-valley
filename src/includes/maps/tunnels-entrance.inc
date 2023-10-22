IF !DEF(TUNNELS_ENTRANCE_INC)
TUNNELS_ENTRANCE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "TunnelsEntrance", ROMX, BANK[1]
TunnelsEntrance:
  db 9, 10, HIGH(TunnelsEntranceAutoEvents), LOW(TunnelsEntranceAutoEvents)
  db $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bd, $bb, $bb, 
  db $bb, $d0, $b0, $b0, $db, 
  db $bb, $b0, $b0, $b0, $bb, 
  db $bb, $b0, $b0, $b0, $bb, 
  db $bb, $b0, $b0, $b0, $bb, 
  db $bb, $b0, $b0, $b0, $bb, 
  db $bb, $be, $be, $be, $bb, 
  db $bb, $bb, $bb, $bb, $bb, 

TunnelsEntranceAutoEvents:
  ; underworld
  AllocateTransportEvent 7, 3, HIGH(Underworld), LOW(Underworld), 55, 42
  AllocateTransportEvent 7, 5, HIGH(Underworld), LOW(Underworld), 55, 46
  AllocateTransportEvent 7, 7, HIGH(Underworld), LOW(Underworld), 55, 50

  ; tunnels
  AllocateTransportEvent 2, 2, HIGH(Tunnels), LOW(Tunnels), 8, 2
  AllocateTransportEvent 1, 5, HIGH(Tunnels), LOW(Tunnels), 2, 1
  AllocateTransportEvent 2, 8, HIGH(Tunnels), LOW(Tunnels), 3, 8

  EndList

TunnelsEntranceTriggerEvents:
  EndList

ENDC