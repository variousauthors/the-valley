IF !DEF(RAND_INC)
RAND_INC = 1

; Linear-feedback shift register

SECTION "RNGState", WRAM0

RNG: ds 1 ; a byte that is always changing

Rand: ds 1 ; a byte that is probably random number evey 8 tics or so

SECTION "RNG", ROM0

setSeed:
  ld a, %00101101
  ld [RNG], a
  ret

/** call this every tick to keep rand random */
updateRand:
  ld a, [Rand]
  ld b, a ; get the old rand

  call sampleRNG ; get the new bit

  ld a, 0
  adc a ; put the new bit in a

  sla b ; shift off the end of old rand
  or a, b ; slip the new bit in there

  ld [Rand], a ; boom

  call updateRNG ; make sure RNG is ready for next call

  ret

/** sets c to the random bit 
 * you must call update after sample
 * but you should use the carry first ;)
 */
sampleRNG:
  ld a, [RNG]
  rra
  ret

/** updates the RNG with next bit */
updateRNG:
  ld a, [RNG]
  rrca ; get bit 8 into position
  ld b, a
  ld a, [RNG]
  rrca
  rrca
  rrca ; get bit 6 into position
  xor a, b
  ld b, a
  ld a, [RNG]
  rrca
  rrca
  rrca
  rrca ; get bit 5 into position
  xor a, b
  ld b, a
  ld a, [RNG]
  sla a
  sla a
  sla a ; get bit 4 into position
  xor a, b ; now the leading bit is our nice new bit
  and a, %10000000 ; select it out
  ld b, a ; store it for later
  ld a, [RNG]

  srl a ; lose the last bit
  or a, b ; set the new first bit
  ld [RNG], a

  ret

/**
get the next bit and appends it to a
so if a has 0100
after this call a has 1010
rra sets bit 7 to carry
*/
buildUp:
  ret

ENDC