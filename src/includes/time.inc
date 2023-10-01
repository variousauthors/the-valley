
IF !DEF(TIME_INC)
TIME_INC = 1

SECTION "TIMER", WRAM0

Timer: ds 1

SECTION "TIME", ROM0

resetTime:
  ld hl, Timer
  ld [hl], 0

  ret

; gonna tick every frame
tick:
  ld hl, Timer
  ld a, [Timer]
  inc a

  ld [hl], a

  ret

; returns a zero or a one
; changing every 32 ticks
; @return a - one or zero
twoIn64Timer:
  ld a, [Timer]

  srl a
  srl a
  srl a
  srl a
  srl a ; divide by 32 

  and a, $01 ; mod 2

  ret

ENDC