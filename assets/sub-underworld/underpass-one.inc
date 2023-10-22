
IF !DEF(UNDERPASS_ONE_INC)
UNDERPASS_ONE_INC = 1

Section "underpass_one", ROM0
underpass_one:
  db height, width, HIGH(underpass_oneAutoEvents), LOW($underpass_oneAutoEvents)
  db $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $bb, $bb, 
  db $b0, $00, $00, $be, $bb, 
  db $b0, $bb, $bb, $b0, $bb, 
  db $b0, $bb, $bb, $b0, $bb, 
  db $b0, $bb, $bb, $b0, $bb, 
  db $b0, $0b, $bb, $b0, $bb, 
  db $be, $00, $00, $00, $bb, 
  db $bb, $bb, $bb, $bb, $bb, 

underpass_oneAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        