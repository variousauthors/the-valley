IF !DEF(TUNNELS_INC)
TUNNELS_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Tunnels", ROMX, BANK[1]
Tunnels:
  db 9, 10, HIGH(TunnelsAutoEvents), LOW(TunnelsAutoEvents)
  db $0b, $00, $0e, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $00, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0e, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0e, $00, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $00, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0e, 
  db $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $0e, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 
  db $00, $00, $0e, $0b, $0b, $0b, $0b, $0b, $0b, $0b, 

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