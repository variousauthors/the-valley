
IF !DEF(TUNNELS_INC)
TUNNELS_INC = 1

Section "tunnels", ROM0
tunnels:
  db height, width, HIGH(tunnelsAutoEvents), LOW($tunnelsAutoEvents)
  db $b0, $eb, $bb, $bb, $bb, 
  db $b0, $bb, $bb, $bb, $bb, 
  db $be, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $e0, 
  db $bb, $bb, $bb, $bb, $b0, 
  db $bb, $bb, $bb, $bb, $be, 
  db $bb, $bb, $bb, $bb, $bb, 
  db $eb, $bb, $bb, $bb, $bb, 
  db $00, $eb, $bb, $bb, $bb, 

tunnelsAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        