
IF !DEF(UNDERPASS_TWO_INC)
UNDERPASS_TWO_INC = 1

Section "underpass_two", ROM0
underpass_two:
  db height, width, HIGH(underpass_twoAutoEvents), LOW($underpass_twoAutoEvents)
  db $bb, $bb, $bb, $bb, $bb, 
  db $00, $00, $00, $00, $0b, 
  db $0b, $bb, $bb, $bb, $0b, 
  db $0b, $bb, $bb, $bb, $bb, 
  db $0e, $be, $00, $00, $0b, 
  db $0b, $bb, $bb, $bb, $0b, 
  db $0b, $bb, $bb, $bb, $0b, 
  db $00, $00, $00, $00, $0b, 
  db $bb, $bb, $bb, $bb, $bb, 

underpass_twoAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        