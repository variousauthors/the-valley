
IF !DEF(SKETCH_1_FOREST_CAVE_LOBBY_INC)
SKETCH_1_FOREST_CAVE_LOBBY_INC = 1

Section "Sketch_1_forest_cave_lobby", ROMX, BANK[1]
  db NO_BOUNDS | NO_ENCOUNTERS
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
  AllocateTransportEvent 0, 5, HIGH(Overworld), LOW(Overworld),  8, 99
  EndList

Sketch_1_forest_cave_lobbyBumpEvents:
  EndList

Sketch_1_forest_cave_lobbyEntities:
  ret

ENDC