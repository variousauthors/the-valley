IF !DEF(ENTITY_UTILS_INC)
ENTITY_UTILS_INC = 1

; @param hl - entity
; @param a - size
resetEntity:
.write
  ld [hl], 0
  inc hl
  dec a
  jr nz, .write

  ret


ENDC