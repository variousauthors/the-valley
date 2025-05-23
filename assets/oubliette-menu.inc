
IF !DEF(OUBLIETTE_MENU_INC)
OUBLIETTE_MENU_INC = 1

Section "Oubliette_menu", ROMX, BANK[1]
Oubliette_menu:
  db 9, 10, 
  db HIGH(Oubliette_menuAutoEvents), LOW(Oubliette_menuAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Oubliette_menuBumpEvents), LOW(Oubliette_menuBumpEvents)
  db HIGH(Oubliette_menuEntities), LOW(Oubliette_menuEntities)
  db $2a, $aa, $aa, $aa, $a2, 
  db $a0, $00, $00, $00, $0a, 
  db $a0, $d0, $00, $00, $0a, 
  db $a0, $00, $00, $00, $0a, 
  db $a0, $d0, $00, $00, $0a, 
  db $a0, $00, $00, $00, $0a, 
  db $a0, $d0, $00, $00, $0a, 
  db $a0, $00, $00, $00, $0a, 
  db $2a, $aa, $aa, $aa, $a2, 

Oubliette_menuAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Oubliette_menuBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Oubliette_menuEntities:
  ret

ENDC