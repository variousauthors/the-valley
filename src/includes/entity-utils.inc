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

/** resets all entities, this is called on transport
  * to give each map a clean slate */
resetEntities:
  call undrawElder
  call undrawCultist
  call resetElder

  ret

ENDC