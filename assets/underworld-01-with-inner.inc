
IF !DEF(UNDERWORLD_01_WITH_INNER_INC)
UNDERWORLD_01_WITH_INNER_INC = 1

Section "Underworld_01_with_inner", ROMX, BANK[1]
Underworld_01_with_inner:
  db 72, 100, 
  db HIGH(Underworld_01_with_innerAutoEvents), LOW(Underworld_01_with_innerAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(Underworld_01_with_innerBumpEvents), LOW(Underworld_01_with_innerBumpEvents)
  db HIGH(Underworld_01_with_innerEntities), LOW(Underworld_01_with_innerEntities)
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bf, $ff, $ff, $ff, $fb, $00, $00, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, 
  db $bb, $bb, $bb, $b0, $00, $00, $00, $00, $00, $00, $b0, $00, $00, $00, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $44, $44, $44, $4b, $0b, $bb, $bb, $bb, $0b, $00, $00, $00, $00, $00, $00, $0b, 
  db $bb, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $00, $00, $0b, $44, $44, $44, $44, $44, $44, $44, $44, $44, $4b, $bb, $bb, $bb, $0b, $eb, $b0, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $bb, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $00, $00, $00, $bb, $bb, $b0, $bb, $0b, $0b, $4f, $ff, $ff, $ff, $ff, $bb, $bb, $bb, $bb, $43, $33, $30, $00, $0b, $0b, $b0, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $bb, $bb, $00, $00, $00, $00, $00, $00, $00, $eb, $00, $0b, $bb, $b0, $bb, $bb, $0b, $db, $b0, $bb, $bb, $00, $bb, $db, $0b, $4f, $44, $44, $44, $33, $33, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, $0b, $b0, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $00, $00, $0b, $bb, $bb, $bf, $4f, $4b, $bb, $bb, $bb, $bb, $bb, $bb, $00, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $0b, $bb, $b0, $00, $00, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $bf, $4f, $4b, $bb, $bb, $bb, $bb, $bb, $eb, $b0, $bb, $bb, $b0, $eb, $bb, $0b, $b0, $bb, $0b, $00, $00, $00, $00, $bb, $bb, $0b, 
  db $bb, $bb, $0b, $00, $00, $0b, $bb, $00, $00, $00, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $b0, $00, $0b, $bb, $bb, $bf, $4f, $4b, $bb, $bb, $bb, $bb, $bb, $0b, $b0, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $bb, $bb, $0b, $0b, $bb, $0b, $eb, $0b, $b0, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $00, $00, $00, $b0, $bb, $bb, $bb, $bb, $ff, $4f, $4b, $00, $eb, $bb, $bb, $bb, $00, $b0, $00, $00, $b0, $00, $00, $00, $b0, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $bb, $bb, $00, $0b, $00, $00, $00, $0b, $b0, $b0, $00, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $b0, $b0, $03, $33, $33, $44, $4f, $4b, $0b, $bb, $00, $00, $bb, $b0, $bb, $bb, $b0, $b0, $bb, $bb, $bb, $b0, $bb, $0b, $0b, $bb, $bb, $b0, $bb, $bb, $0b, 
  db $ff, $ff, $bb, $bb, $0b, $b0, $bb, $bb, $b3, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $00, $00, $00, $b0, $b0, $bb, $bb, $bb, $ff, $ff, $4b, $0b, $00, $0b, $b0, $0b, $b0, $00, $00, $00, $b0, $b0, $00, $00, $00, $bb, $0b, $0b, $bb, $00, $00, $00, $00, $0b, 
  db $44, $44, $44, $4b, $0b, $b0, $b4, $44, $b3, $bb, $bb, $bb, $bb, $b0, $00, $bb, $0b, $bb, $b0, $b0, $b0, $bb, $bf, $44, $44, $44, $4b, $0b, $bb, $bb, $00, $0b, $bb, $bb, $0b, $b0, $b0, $b0, $bb, $bb, $b0, $bb, $0b, $0b, $bb, $0b, $bb, $bb, $bb, $0b, 
  db $4f, $4f, $4f, $4b, $0b, $b0, $b4, $f4, $b3, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $0b, $e0, $00, $b0, $b0, $bb, $bf, $4b, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $0b, $00, $eb, $0b, $b0, $b0, $bb, $bb, $bb, $b0, $bb, $0b, $0b, $bb, $0b, $bb, $bb, $bb, $0b, 
  db $44, $44, $44, $4b, $0b, $b0, $b4, $f4, $b3, $bf, $ff, $bb, $bb, $b0, $00, $bb, $0b, $bb, $bb, $b0, $b0, $bb, $bf, $43, $33, $30, $00, $00, $0b, $b0, $0b, $0b, $0b, $bb, $0b, $b0, $b0, $00, $00, $00, $00, $b0, $0b, $0b, $bb, $0b, $bb, $bb, $bb, $0b, 
  db $4f, $4d, $4f, $4b, $0b, $b0, $b4, $f4, $f4, $ff, $44, $33, $33, $00, $b0, $00, $00, $00, $00, $00, $b0, $bb, $bb, $fb, $bb, $bb, $bb, $0b, $0b, $b0, $bb, $0b, $00, $00, $0b, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $0b, 
  db $44, $44, $44, $4b, $00, $b0, $b4, $f4, $f4, $ff, $4f, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $00, $00, $b0, $0b, $0b, $bb, $bb, $b3, $b4, $44, $44, $44, $44, $44, $44, $b0, $00, $00, $0b, $bb, $bb, $0b, 
  db $4f, $4f, $4f, $4f, $bb, $b0, $b4, $ff, $f4, $44, $4f, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $d0, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $0b, $b0, $bb, $0b, $bb, $bb, $b3, $b4, $ff, $ff, $ff, $ff, $ff, $f4, $fb, $bb, $eb, $0b, $bb, $bb, $0b, 
  db $44, $44, $44, $4f, $bb, $b0, $b4, $44, $44, $fb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $00, $b0, $0b, $bb, $bb, $b3, $b4, $f4, $44, $44, $44, $44, $f4, $fb, $bb, $bb, $0b, $bb, $bb, $0b, 
  db $ff, $f4, $ff, $fb, $bb, $bb, $bb, $bb, $bb, $bb, $eb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $00, $bb, $bb, $00, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b3, $b4, $f4, $ff, $ff, $ff, $ff, $f4, $ff, $ff, $fb, $0b, $bb, $bb, $0b, 
  db $bf, $44, $4f, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $bb, $bb, $bb, $b0, $00, $00, $0b, $bb, $bb, $00, $00, $00, $00, $00, $0b, $ff, $ff, $ff, $f4, $f4, $f4, $f4, $44, $44, $44, $44, $44, $44, $4b, $00, $00, $00, $0b, 
  db $bf, $4b, $44, $33, $33, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $e0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $db, $0b, $bb, $bb, $bb, $bb, $0b, $f4, $44, $44, $44, $f4, $f4, $ff, $ff, $ff, $ff, $f4, $ff, $ff, $fb, $bb, $bb, $bb, $0b, 
  db $bf, $44, $4f, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $0b, $0b, $00, $00, $00, $00, $0b, $f4, $b4, $b4, $b4, $f4, $f4, $44, $fb, $bb, $bb, $f4, $f4, $44, $44, $4f, $bb, $bb, $3b, 
  db $bb, $f4, $fb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $00, $00, $00, $0b, $0b, $bb, $bb, $0b, $bb, $f4, $44, $44, $44, $ff, $ff, $f4, $fb, $bb, $bb, $f4, $f4, $ff, $ff, $4f, $bb, $bb, $3b, 
  db $bf, $44, $4f, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b4, $44, $b4, $44, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $f4, $b4, $d4, $b4, $f4, $44, $f4, $fb, $bb, $bb, $f4, $f4, $fb, $bf, $4f, $bb, $bb, $3b, 
  db $bf, $4f, $44, $33, $33, $00, $b0, $00, $e0, $00, $b0, $b0, $b0, $b4, $b4, $44, $b4, $43, $33, $30, $00, $00, $bb, $bb, $00, $00, $00, $0b, $bb, $d0, $0b, $bb, $f4, $44, $44, $44, $f4, $ff, $f4, $ff, $ff, $ff, $f4, $ff, $ff, $ff, $4f, $bb, $bb, $3b, 
  db $bf, $44, $4f, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b4, $44, $b4, $44, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $0b, $bb, $f4, $b4, $b4, $b4, $f4, $f4, $44, $44, $44, $44, $44, $44, $44, $4f, $4f, $ff, $ff, $4f, 
  db $bb, $ff, $fb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $4b, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $00, $00, $00, $0b, $bb, $f4, $44, $44, $44, $f4, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $44, $44, $44, $44, $4f, 
  db $bf, $44, $4f, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b4, $44, $b4, $44, $b0, $00, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $0b, $bb, $bb, $bb, $ff, $ff, $ff, $4f, $ff, $f4, $fb, $bb, $bb, $bb, $bb, $bb, $bb, $bf, $4f, $4f, $ff, $ff, $ff, 
  db $bf, $4f, $44, $33, $33, $00, $b0, $b0, $e0, $00, $b0, $b4, $e4, $44, $b4, $b0, $e0, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $0b, $db, $b0, $bb, $ff, $ff, $44, $44, $4f, $ff, $4f, $ff, $f4, $fb, $bb, $bb, $bb, $bb, $bb, $bb, $bf, $4b, $3b, $bb, $bb, $bb, 
  db $bf, $44, $4f, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b4, $44, $b4, $44, $b0, $00, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $00, $00, $00, $b4, $44, $44, $4b, $bb, $44, $44, $44, $4f, $f4, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $4b, $3b, $bb, $bb, $bb, 
  db $bf, $f4, $fb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $4b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $b4, $bb, $bb, $bb, $eb, $bb, $bb, $bb, $44, $44, $44, $44, $44, $44, $44, $44, $44, $44, $4b, $3b, $bb, $bb, $bb, 
  db $bf, $44, $4f, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b4, $44, $b4, $44, $b0, $00, $b0, $00, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $f4, $b0, $00, $00, $00, $00, $00, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $3b, $bb, $bb, $bb, 
  db $bf, $4f, $44, $33, $33, $00, $b0, $00, $b0, $b0, $b0, $b4, $b4, $44, $b4, $b0, $e0, $b0, $00, $eb, $bb, $d0, $bb, $bb, $bb, $d0, $bb, $f4, $b0, $bb, $bb, $bb, $bb, $bb, $0b, $00, $00, $00, $00, $b0, $00, $b0, $00, $00, $00, $0b, $0b, $bb, $bb, $bb, 
  db $bf, $44, $4b, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b4, $44, $b4, $44, $b0, $00, $b0, $00, $bb, $bb, $b0, $bb, $bb, $bb, $b0, $bb, $f4, $b0, $00, $00, $00, $00, $0b, $0b, $0b, $bb, $b0, $00, $b0, $d0, $b0, $00, $bb, $bb, $0b, $0b, $00, $00, $0b, 
  db $bf, $ff, $fb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $4b, $bb, $bb, $bb, $0b, $bb, $bb, $b0, $00, $00, $00, $00, $eb, $f4, $b0, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $bb, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $0b, $0b, $0b, $bb, $0b, 
  db $ff, $44, $4f, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b4, $44, $b0, $00, $b0, $00, $bb, $bb, $b0, $bb, $b0, $bb, $bb, $bb, $b4, $b0, $00, $00, $00, $0b, $0b, $0b, $0b, $bb, $b0, $00, $bb, $cb, $b0, $00, $bb, $bb, $0b, $0b, $0b, $bb, $0b, 
  db $44, $4f, $44, $33, $33, $00, $b0, $00, $e0, $00, $b0, $00, $b0, $b4, $e4, $b0, $b0, $00, $b0, $bb, $bb, $00, $bb, $b0, $00, $00, $00, $b4, $b0, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $bb, $b0, $00, $b0, $c0, $b0, $00, $bb, $bb, $0b, $0b, $0b, $bb, $0b, 
  db $4f, $44, $4f, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $b0, $00, $b4, $44, $b0, $00, $b0, $00, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $b0, $b4, $b0, $00, $00, $00, $0b, $0b, $0b, $00, $00, $00, $00, $00, $c0, $00, $00, $00, $00, $0b, $0b, $0b, $bb, $0b, 
  db $4f, $ff, $fb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $b0, $b4, $bb, $bb, $bb, $bb, $0b, $0b, $0b, $0b, $bb, $b0, $00, $b0, $c0, $b0, $00, $bb, $bb, $0b, $0b, $00, $0b, $0b, 
  db $4f, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $00, $b0, $00, $b0, $00, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $b0, $b4, $fb, $bb, $bb, $bb, $0b, $0b, $0b, $0b, $bb, $b0, $00, $00, $c0, $00, $00, $bb, $bb, $0b, $0b, $bb, $0b, $0b, 
  db $4f, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $b0, $b0, $b0, $b0, $b0, $00, $0b, $bb, $0b, $e0, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $db, $b0, $b4, $fb, $bb, $bb, $bb, $0b, $0b, $0b, $0b, $bb, $b0, $00, $b0, $c0, $b0, $00, $bb, $bb, $0b, $00, $0b, $0b, $0b, 
  db $4f, $bb, $0b, $00, $0b, $0b, $bb, $b0, $00, $b0, $00, $b0, $00, $bb, $0b, $bb, $0b, $b0, $00, $0b, $bb, $0b, $bb, $b0, $0b, $00, $00, $b4, $fb, $bb, $bb, $bb, $0b, $bb, $0b, $0b, $bb, $b0, $00, $00, $c0, $00, $00, $bb, $bb, $0b, $0b, $0b, $0b, $0b, 
  db $4f, $b0, $0b, $0d, $0b, $00, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $e0, $00, $00, $0b, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $0b, $bb, $b0, $b4, $43, $33, $30, $00, $00, $00, $0b, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $eb, $0b, $0b, 
  db $4f, $b0, $0b, $00, $0b, $00, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $bb, $00, $00, $00, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $0b, $0b, 
  db $4b, $e0, $0b, $bc, $bb, $00, $00, $00, $0b, $bb, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $bb, $bb, $bb, $bb, $00, $db, $b0, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $bb, $b0, $bb, $bb, $00, $eb, $0b, $bb, $bb, $0b, $0b, $0b, $0b, $0b, 
  db $4f, $b0, $0b, $0c, $0b, $00, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bf, $ff, $ff, $ff, $fb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $0b, $0b, $0b, $0b, $bb, 
  db $4f, $b0, $00, $0c, $00, $00, $b0, $00, $b0, $00, $00, $00, $00, $00, $db, $0b, $d4, $44, $44, $44, $44, $44, $44, $fb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $0b, $bb, $eb, $0b, $0b, $0b, $00, $bb, 
  db $4f, $b0, $0b, $0c, $0b, $00, $b0, $b0, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $b4, $fb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $00, $00, $00, $00, $00, $0b, $bb, $0b, $bb, $00, $0b, $0b, $0b, $b0, $bb, 
  db $4f, $b0, $00, $0c, $00, $00, $b0, $00, $b0, $0d, $bb, $b0, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $b4, $fb, $0b, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $0b, $bb, $bb, $0b, $0b, $0b, $e0, $bb, 
  db $4f, $b0, $0b, $0c, $0b, $00, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $b4, $fb, $0b, $bb, $b0, $00, $00, $00, $00, $00, $00, $00, $0b, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $00, $00, $00, $0b, $0b, $0b, $b0, $bb, 
  db $4f, $b0, $00, $0c, $00, $00, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $00, $00, $00, $eb, $bb, $bb, $bb, $bb, $b0, $b4, $fb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $0b, $0b, $00, $00, $0b, 
  db $4f, $b0, $0b, $0c, $0b, $00, $bb, $00, $00, $0b, $00, $b0, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $ff, $ff, $fb, $f4, $ff, $ff, $ff, $ff, $fb, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $0b, $bb, $b0, $bb, $bb, $0b, $bb, $b0, $00, $0b, $0b, $0b, $bb, $bb, $0b, 
  db $4f, $b0, $00, $0c, $00, $00, $bb, $0b, $bb, $eb, $b0, $b0, $bb, $0b, $00, $0b, $bb, $bb, $bb, $f4, $44, $44, $44, $44, $44, $44, $44, $bb, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $00, $00, $00, $00, $00, $0b, $bb, $b0, $bb, $00, $0b, $0b, $bb, $bb, $0b, 
  db $4f, $b0, $0b, $0c, $0b, $00, $bb, $0b, $bb, $bb, $b0, $b0, $bb, $0b, $0b, $0b, $bb, $bb, $bb, $f4, $b4, $b4, $b4, $b4, $b4, $b4, $b4, $bb, $bb, $bb, $bb, $b0, $bb, $0b, $bb, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $b3, $bb, $bb, $bb, $00, $00, $00, $0b, 
  db $4f, $b0, $00, $0c, $00, $00, $bb, $0b, $bb, $bb, $b0, $b0, $00, $00, $0b, $00, $03, $33, $33, $44, $44, $44, $44, $44, $44, $44, $44, $33, $33, $00, $00, $b0, $bb, $0b, $bb, $bb, $b4, $b3, $bb, $bb, $bb, $bb, $b3, $bb, $bb, $bb, $bb, $bb, $bb, $0b, 
  db $4f, $b0, $0b, $0c, $0b, $00, $bb, $0b, $bb, $bb, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b4, $b4, $d4, $b4, $d4, $b4, $d4, $b4, $bb, $bb, $bb, $b0, $b0, $bb, $0b, $bb, $bb, $b4, $b3, $bb, $bb, $bb, $bb, $b3, $bb, $bb, $00, $00, $00, $bb, $0b, 
  db $4f, $bb, $00, $00, $00, $0b, $bb, $00, $00, $00, $00, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b4, $44, $44, $44, $44, $44, $44, $44, $fb, $bb, $bb, $be, $b0, $00, $00, $00, $bb, $b4, $b3, $bb, $ff, $ff, $ff, $b3, $bb, $bb, $0b, $bb, $b0, $bb, $0b, 
  db $4f, $bb, $bb, $b0, $bb, $bb, $fb, $0b, $bb, $bb, $b0, $bb, $00, $00, $bb, $bb, $bb, $bb, $bb, $b4, $b4, $b4, $b4, $b4, $b4, $b4, $b4, $fb, $bb, $bb, $bb, $bb, $bb, $0b, $b0, $bb, $b4, $b3, $bb, $f4, $44, $44, $f4, $bb, $bb, $3b, $bb, $b0, $bb, $0b, 
  db $4b, $e0, $00, $00, $00, $bf, $db, $0b, $eb, $bb, $b0, $bb, $0c, $c0, $bb, $bb, $bf, $ff, $bb, $b4, $44, $44, $44, $44, $44, $44, $44, $fb, $bb, $bb, $bb, $bb, $bb, $0b, $b0, $bb, $b4, $f4, $ff, $f4, $ff, $f4, $f4, $bb, $bb, $3b, $bb, $b0, $00, $0b, 
  db $4f, $bb, $bb, $bb, $bb, $ff, $4b, $0b, $0b, $bb, $b0, $bb, $0c, $c0, $33, $33, $34, $4f, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $4f, $fb, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $b0, $bb, $b4, $f4, $44, $44, $f4, $44, $f4, $bb, $bb, $3b, $bb, $b0, $bb, $0b, 
  db $44, $44, $44, $44, $44, $44, $4b, $00, $00, $00, $00, $bb, $e0, $00, $bb, $bb, $bf, $44, $44, $44, $44, $44, $44, $44, $4f, $4f, $b0, $03, $33, $00, $bb, $bb, $bb, $0b, $b0, $eb, $b4, $ff, $ff, $ff, $ff, $f4, $44, $bb, $bb, $3b, $bb, $b0, $bb, $0b, 
  db $4f, $4f, $ff, $ff, $ff, $fb, $bb, $0b, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bf, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $4f, $4f, $b0, $bb, $bb, $b0, $b0, $00, $00, $0b, $bb, $bb, $b4, $44, $44, $44, $44, $ff, $ff, $ff, $ff, $4f, $bb, $b0, $bb, $0b, 
  db $4f, $44, $44, $44, $44, $b0, $eb, $00, $00, $0b, $0b, $bb, $bb, $ff, $ff, $ff, $ff, $ff, $44, $44, $44, $44, $44, $4f, $ef, $4f, $b0, $eb, $0b, $e0, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $b4, $ff, $44, $44, $44, $4f, $bb, $b0, $bb, $0b, 
  db $4f, $4f, $fb, $bf, $4f, $b0, $bb, $bb, $bb, $0b, $0b, $bb, $ff, $f4, $44, $44, $44, $44, $4f, $ff, $4f, $ff, $ff, $4f, $ff, $4b, $bb, $bb, $0b, $bb, $b0, $00, $00, $00, $00, $00, $03, $33, $33, $44, $44, $44, $4f, $ff, $ff, $ff, $bb, $b0, $bb, $0b, 
  db $4f, $4f, $b0, $eb, $4b, $00, $00, $00, $00, $0b, $0b, $bb, $f4, $44, $fb, $bb, $bb, $bf, $44, $4f, $4f, $44, $4f, $44, $44, $4b, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $ff, $ff, $ff, $ff, $44, $44, $44, $4b, $b0, $bb, $0b, 
  db $4f, $4f, $b0, $bb, $bb, $b0, $bb, $0b, $bb, $bb, $3b, $bf, $f4, $fb, $b0, $00, $00, $0b, $bf, $4f, $4f, $4f, $4f, $ff, $ff, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $4b, $4f, $44, $44, $44, $4b, $4b, $4b, $4b, $00, $00, $0b, 
  db $4f, $4f, $b0, $b0, $00, $00, $bb, $0b, $bb, $bb, $3b, $bf, $44, $b0, $00, $bb, $bb, $00, $bf, $4f, $4f, $4f, $4f, $4f, $44, $33, $33, $00, $00, $00, $00, $00, $00, $00, $00, $0b, $bb, $bb, $4b, $4f, $4f, $4f, $ff, $44, $44, $44, $4b, $0b, $bb, $0b, 
  db $4f, $4f, $b0, $bb, $bb, $b0, $bb, $0b, $bb, $bb, $3b, $bf, $4f, $b0, $bb, $bb, $bb, $b0, $bf, $4f, $ff, $4f, $4f, $4f, $4f, $bb, $bb, $bb, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $4f, $4f, $4f, $4f, $4f, $4b, $4d, $4b, $4b, $0b, $bb, $0b, 
  db $4f, $44, $f0, $00, $00, $00, $bb, $0b, $bb, $bb, $3b, $bf, $4f, $e0, $0b, $bb, $bd, $00, $bf, $44, $44, $4f, $44, $4f, $44, $44, $4b, $00, $eb, $bb, $d0, $00, $bb, $bb, $e0, $0b, $bb, $bb, $4f, $44, $4f, $4f, $4f, $44, $44, $44, $4b, $0b, $bb, $0b, 
  db $4f, $ff, $fb, $bb, $bb, $b0, $bb, $0b, $bb, $bf, $4f, $ff, $4f, $b0, $bb, $bb, $bb, $bb, $bb, $bb, $bf, $4f, $ff, $ff, $ff, $ff, $4b, $0b, $bb, $bb, $bb, $0b, $bb, $bb, $bb, $bb, $bb, $bb, $4f, $ff, $4f, $4f, $4f, $4b, $4b, $4b, $4b, $0b, $bb, $0b, 
  db $43, $33, $30, $00, $00, $00, $00, $0b, $bb, $bf, $44, $44, $4f, $b0, $00, $00, $00, $00, $33, $33, $34, $44, $44, $44, $44, $44, $4b, $00, $00, $00, $00, $00, $00, $00, $00, $03, $33, $33, $44, $44, $4f, $44, $4f, $44, $44, $44, $4b, $00, $00, $0b, 
  db $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bf, $ff, $ff, $ff, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bf, $ff, $ff, $ff, $ff, $ff, $fb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $bb, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $ff, $fb, $bb, $bb, $bb, 

Underworld_01_with_innerAutoEvents:
  ; the first auto event is the out of bounds event so every map
  ; with no bounds must have at least one auto event here
  AllocateTransportEvent 8, 7, HIGH(Overworld), LOW(Overworld), 4, 1
  EndList

Underworld_01_with_innerBumpEvents:
  AllocateCheckpointEvent 3, 4, HIGH(CheckpointSetMessage), LOW(CheckpointSetMessage)
  AllocateNPCDialogEvent 17, 22, HIGH(Silence), LOW(Silence)
  EndList

Underworld_01_with_innerEntities:
  ret

ENDC