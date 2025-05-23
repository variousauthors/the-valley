
IF !DEF(OUBLIETTE_MENU_INC)
OUBLIETTE_MENU_INC = 1

Section "Oubliette_menu", ROMX, BANK[1]
  db HAS_BOUNDS | NO_ENCOUNTERS
Start:
Oubliette_menu:
  db 18, 6, 
  db HIGH(Oubliette_menuAutoEvents), LOW(Oubliette_menuAutoEvents), 
  db HIGH(OublietteMenuTileset), LOW(OublietteMenuTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Oubliette_menuBumpEvents), LOW(Oubliette_menuBumpEvents)
  db HIGH(Oubliette_menuEntities), LOW(Oubliette_menuEntities)
  db $22, $22, $22, 
  db $20, $00, $00, 
  db $20, $01, $d0, 
  db $20, $00, $00, 
  db $20, $03, $d0, 
  db $20, $00, $00, 
  db $20, $04, $d0, 
  db $20, $00, $00, 
  db $20, $05, $d0, 
  db $20, $00, $00, 
  db $20, $06, $d0, 
  db $20, $00, $00, 
  db $20, $07, $d0, 
  db $20, $00, $00, 
  db $20, $08, $d0, 
  db $20, $00, $00, 
  db $20, $09, $d0, 
  db $20, $00, $00, 

Oubliette_menuAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 2, 4, HIGH(Oubliette), LOW(Oubliette), 24, 21
  AllocateTransportEvent 4, 4, HIGH(Oubliette), LOW(Oubliette), 7, 4
  AllocateTransportEvent 6, 4, HIGH(Oubliette), LOW(Oubliette), 22, 12
  AllocateTransportEvent 8, 4, HIGH(Oubliette), LOW(Oubliette), 34, 25

  EndList

Oubliette_menuBumpEvents:
  EndList

Oubliette_menuEntities:
  ret

ENDC