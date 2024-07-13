IF !DEF(ENTITY_UTILS_INC)
ENTITY_UTILS_INC = 1

; @param hl - entity
; @param b - size
resetEntity:
  ld a, 0
.write
  ld [hl+], a
  dec b
  jr nz, .write

  ret


ENDC