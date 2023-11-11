
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

; returns 0, 1, 2, 3
; over the course of ~4 seconds
; @return a - 0, 1, 2, or 3
count4In4Seconds:
  ld a, [Timer]

  srl a
  srl a
  srl a
  srl a
  srl a
  srl a ; divide by 64

  and a, $03 ; mod 4

  ret

; returns 0, 1, 2, 3
; over the course of 4 frames
; @return a - 0, 1, 2, or 3
count4In8Frames:
  ld a, [Timer]

  and a, $03 ; mod 4

  ret

; returns a zero or a one
; changing every tick
; @return a - one or zero
twoInTwoTicks:
  ld a, [Timer]
  and a, $01 ; mod 2

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