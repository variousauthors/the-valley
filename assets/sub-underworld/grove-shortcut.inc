
IF !DEF(GROVE_SHORTCUT_INC)
GROVE_SHORTCUT_INC = 1

Section "grove_shortcut", ROM0
grove_shortcut:
  db height, width, HIGH(grove_shortcutAutoEvents), LOW($grove_shortcutAutoEvents)
  db $bb, $00, $eb, 
  db $bb, $0b, $bb, 
  db $bb, $0b, $bb, 
  db $e0, $0b, $bb, 

grove_shortcutAutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        