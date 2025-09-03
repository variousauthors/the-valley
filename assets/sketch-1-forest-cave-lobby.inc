
IF !DEF(SKETCH_1_FOREST_CAVE_LOBBY_INC)
SKETCH_1_FOREST_CAVE_LOBBY_INC = 1

Section "Sketch_1_forest_cave_lobby", ROMX, BANK[1]
Sketch_1_forest_cave_lobby:
  db 9, 10, 
  db HIGH(Sketch_1_forest_cave_lobbyAutoEvents), LOW(Sketch_1_forest_cave_lobbyAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Sketch_1_forest_cave_lobbyBumpEvents), LOW(Sketch_1_forest_cave_lobbyBumpEvents)
  db HIGH(Sketch_1_forest_cave_lobbyEntities), LOW(Sketch_1_forest_cave_lobbyEntities)
  db $11, $11, $10, $11, $11, 
  db $11, $11, $10, $11, $11, 
  db $11, $11, $00, $11, $11, 
  db $11, $30, $00, $00, $01, 
  db $13, $00, $03, $0f, $01, 
  db $13, $0d, $03, $09, $01, 
  db $13, $00, $13, $00, $01, 
  db $11, $33, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 

Sketch_1_forest_cave_lobbyAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Sketch_1_forest_cave_lobbyBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Sketch_1_forest_cave_lobbyEntities:
  ret

ENDC