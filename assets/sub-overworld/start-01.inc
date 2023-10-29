
IF !DEF(START_01_INC)
START_01_INC = 1

Section "start_01", ROM0
start_01:
  db height, width, HIGH(start_01AutoEvents), LOW($start_01AutoEvents)
  db $11, $11, $11, $11, $16, 
  db $11, $66, $11, $66, $61, 
  db $16, $6b, $b6, $b6, $61, 
  db $66, $6b, $66, $db, $16, 
  db $66, $66, $66, $bb, $61, 
  db $66, $6b, $66, $66, $61, 
  db $16, $66, $b6, $6b, $66, 
  db $11, $66, $6b, $b6, $61, 
  db $11, $11, $66, $66, $11, 

start_01AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        