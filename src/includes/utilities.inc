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

; sets b to min(a, b)
; useful if you are about to
; subtract whole numbers
; with sub a, b
minAB:
  cp a, b
  jr c, .aLessB
  ret

.aLessB
  ld b, a

  ret

; sets a to 0 if a is negative
wholeA:
  bit 7, a
  jr z, .done
  ; negative
  ld a, 0
.done
  ret

WhiteOutPalettes:
  db %11100100
  db %10010000
  db %01000000
  db %00000000

FadeOutPalettes:
  db %11100100
  db %10010000
  db %01000000
  db %00000000

FadeInPalettes:
  db %00000000
  db %01000000
  db %10010000
  db %11100100

; @param - hl the address of some subroutie to call
indirectCall:
  jp hl

; @param a, b
; @return a = Math.min(a + b, 255)
add255:
  add a, b
  ret nc

  ld a, 255

  ret

; @param a - a
; @param hl - hl
; @return hl - hl + a
addAToHL:
  add l ; a = a + l
	ld l, a ; l' = a'
	adc h ; a'' = a' + h + c ; what!?
	sub l ; l' here is a + l
	ld h, a ; so h is getting h + c yikes!

  ret

addAToDE:
  add e ; a = a + e
	ld e, a ; e' = a'
	adc d ; a'' = a' + d + c ; what!?
	sub e ; l' here is a + e
	ld d, a ; so d is getting d + c yikes!

  ret

; @param a - number
; @return |a|
absA:
  bit 7, a
  jr z, .skipNegate
  dec a
  cpl
.skipNegate

  ret

; @param hl - out
; @param de - unchanged
; @return hl = hl - de
sub16bit:
  ld a, l
	sub e
	ld l, a
	ld a, h
	sbc d
	ld h, a

  ret

; returns the direction directly away from
; the player's current move direction
; @return a - the away button UP, LEFT, RIGHT, DOWN
getAwayButton:
  ld a, [PLAYER_MOVE_DIRECTION]

.right
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .left
  ld a, LEFT
  ret

.left
  cp a, PLAYER_MOVE_LEFT
  jr nz, .up
  ld a, RIGHT
  ret

.up
  cp a, PLAYER_MOVE_UP
  jr nz, .down
  ld a, DOWN
  ret

.down
  ld a, UP

  ret

; @pre this is for testing cardinal directions only
; if you pass in bc diagonal from de then you get garbage
; @param bc - y,x we want the away of
; @return a - the towards button UP, LEFT, RIGHT, DOWN
getPositionalTowardsButton:
  ; calculate the direction from the player to this bc
  ; then get towards button as usually, noting that "0000" means
  ; no direction is towards (ie we are there) and we can xor this
  ; to get 1111 meaning any direction is away
  ld d, b
  ld e, c

  call getWorldPosition

  ; de - bc the point in question is the origin
.testY
  ld a, d
  sub a, b
  jr z, .testX
  jr c, .up
  jr nc, .down

.testX
  ld a, e
  sub a, c
  jr z, .identical
  jr c, .left
  jr nc, .right

.up
  ld a, UP
  ret
.down
  ld a, DOWN
  ret
.left
  ld a, LEFT
  ret
.right
  ld a, RIGHT
  ret
.identical
  ld a, 0
  ret

; returns the direction directly towards
; the player's current move direction
; @return a - the towards button UP, LEFT, RIGHT, DOWN
getTowardsButton:
  ld a, [PLAYER_MOVE_DIRECTION]

.right
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .left
  ld a, RIGHT
  ret

.left
  cp a, PLAYER_MOVE_LEFT
  jr nz, .up
  ld a, LEFT
  ret

.up
  cp a, PLAYER_MOVE_UP
  jr nz, .down
  ld a, UP
  ret

.down
  ld a, DOWN

  ret



ENDC