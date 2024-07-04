IF !DEF(GROVE_SHORTCUT)
GROVE_SHORTCUT = 1

Section "GroveShortcut", ROM0
  db HAS_BOUNDS
GroveShortcut:
  db 4, 6, 
  db HIGH(GroveShortcutAutoEvents), LOW(GroveShortcutAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(CavePassageEncounters), LOW(CavePassageEncounters), 
  db HIGH(GroveShortcutBumpEvents), LOW(GroveShortcutBumpEvents)
  db $bb, $00, $eb, 
  db $bb, $0b, $bb, 
  db $bb, $0b, $bb, 
  db $e0, $0b, $bb, 

GroveShortcutAutoEvents:
  /** entrance */
  AllocateTransportEvent 0, 4, HIGH(NorthGroveExit), LOW(NorthGroveExit), 3, 3
  AllocateTransportEvent 3, 0, HIGH(SouthGroveExit), LOW(SouthGroveExit), 5, 6

  EndList

GroveShortcutBumpEvents:
  EndList

ENDC