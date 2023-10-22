
IF !DEF(TUNNELS_ENTRANCE_INC)
TUNNELS_ENTRANCE_INC = 1

Section "tunnels_entrance", ROM0
tunnels_entrance:
  db height, width, HIGH(tunnels_entranceAutoEvents), LOW($tunnels_entranceAutoEvents)
  db $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bd, $bb, $bb, 
  db $bb, $d0, $b0, $b0, $db, 
  db $bb, $b0, $b0, $b0, $bb, 
  db $bb, $b0, $b0, $b0, $bb, 
  db $bb, $b0, $b0, $b0, $bb, 
  db $bb, $b0, $b0, $b0, $bb, 
  db $bb, $be, $be, $be, $bb, 
  db $bb, $bb, $bb, $bb, $bb, 

tunnels_entranceAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        