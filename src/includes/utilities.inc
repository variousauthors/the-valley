IF !DEF(UTILITIES_INC)
UTILITIES_INC = 1

waitForVBlank:
.loop
  ld a, [rLY]
  cp 145
  jr nz, .loop

  ret

ENDC