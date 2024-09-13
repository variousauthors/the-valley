
IF !DEF(START_INC)
START_INC = 1

Section "Start", ROMX, BANK[1]
Start:
  db 18, 20, 
  db HIGH(StartAutoEvents), LOW(StartAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(StartBumpEvents), LOW(StartBumpEvents)
  db HIGH(StartEntities), LOW(StartEntities)
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $33, $33, $33, $33, $32, $22, $22, 
  db $22, $23, $33, $30, $00, $00, $00, $03, $22, $22, 
  db $22, $33, $00, $00, $08, $00, $00, $00, $33, $22, 
  db $22, $30, $00, $08, $00, $08, $00, $00, $03, $22, 
  db $23, $00, $00, $00, $00, $00, $00, $00, $03, $32, 
  db $23, $00, $00, $30, $00, $00, $30, $00, $00, $32, 
  db $23, $30, $00, $00, $00, $00, $00, $00, $00, $32, 
  db $22, $30, $00, $30, $00, $00, $30, $00, $00, $32, 
  db $22, $33, $00, $00, $00, $00, $00, $00, $03, $32, 
  db $22, $23, $00, $00, $0c, $00, $00, $00, $33, $22, 
  db $22, $22, $30, $00, $0c, $00, $00, $03, $32, $22, 
  db $22, $22, $23, $30, $0c, $00, $00, $33, $22, $22, 
  db $22, $22, $22, $33, $3c, $33, $33, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 
  db $22, $22, $22, $22, $22, $22, $22, $22, $22, $22, 

StartAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

StartBumpEvents:
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

StartEntities:
  ret

ENDC