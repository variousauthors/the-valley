IF !DEF(UTILITIES_INC)
UTILITIES_INC = 1

SECTION "DoubleDabbleScratch", WRAM0

DoubleDabbleByte2: ds 1
DoubleDabbleByte1: ds 1
DoubleDabbleByte0: ds 1

SECTION "Utilities", ROM0

waitForVBlank:
.loop
  ld a, [rLY]
  cp 145
  jr nz, .loop

  ret

; converts the byte pointed to by hl into BCD
doubleDabble:
  ; copy the byte from hl to scratch
  ld a, [hl]
  ld [DoubleDabbleByte0], a
  ld a, 0
  ld [DoubleDabbleByte1], a
  ld [DoubleDabbleByte2], a

  ld b, 8
.loop
  ld a, 0
  cp b
  jr z, .done
  dec b

  ; check for base-10 overflow and add 3
.hundreds
  ld a, [DoubleDabbleByte2]
  and a, %00001111
  cp a, %00000101 ; a < 5 => c
  jr c, .tens

  ; add 3
  ld a, [DoubleDabbleByte2]
  add %00000011
  ld [DoubleDabbleByte2], a

.tens
  ld a, [DoubleDabbleByte1]
  and a, %11110000
  cp a, %01010000 ; a < 5 => c
  jr c, .ones

  ; add 3
  ld a, [DoubleDabbleByte1]
  add %00110000
  ld [DoubleDabbleByte1], a

.ones
  ld a, [DoubleDabbleByte1]
  and a, %00001111
  cp a, %00000101 ; a < 5 => c
  jr c, .shiftLeft

  ; add 3
  ld a, [DoubleDabbleByte1]
  add %00000011
  ld [DoubleDabbleByte1], a

.shiftLeft

; shift byte 2
  ld a, [DoubleDabbleByte2]
  sla a
  ld [DoubleDabbleByte2], a

; shift byte 1
  ld a, [DoubleDabbleByte1]
  sla a
  ld [DoubleDabbleByte1], a

  ; possible carry into byte 2
  ld a, [DoubleDabbleByte2]
  adc a, 0
  ld [DoubleDabbleByte2], a

; shift byte 0
  ld a, [DoubleDabbleByte0]
  sla a
  ld [DoubleDabbleByte0], a

  ; possible carry into byte 1
  ld a, [DoubleDabbleByte1]
  adc a, 0
  ld [DoubleDabbleByte1], a

  jr .loop
.done

  ret

ENDC