IF !DEF(INPUT_INC)
INPUT_INC = 1

SECTION "InputState", WRAM0

; all the bits we need for inputs 
_PAD: ds 2
_PREV_PAD: ds 2
; this is a bit of a hack
; the main loop uses the presence of input to signal "we
; are still working on this step". So for example if we
; have moved the player and want to check for auto events,
; if we find an auto event we clear the _PAD to indicate
; that we no longer want to continue thinking about this
; update, we can wait for another input now
; this is not great, there is a refactor coming, but for
; now I will just duplicate _PAD for that purpose
_PROCESSING: ds 2

; directions
RIGHT EQU %00010000
LEFT  EQU %00100000
UP    EQU %01000000
DOWN  EQU %10000000

A_BUTTON EQU %00000001
B_BUTTON EQU %00000010

SECTION "Input", ROM0

resetInput:
  ld a, 0
  ld [_PROCESSING], a
  ret

; @param a - the inputs from readInput
; @return a - the inputs we care about
getInput:
  and a, UP | DOWN | LEFT | RIGHT ; the buttons we care about

  ret

readInput:
  ; record the previous input
  ld a, [_PAD]
  ld [_PREV_PAD], a

  ; read the cruzeta (the d-pad)
  ld a, %00100000 ; select the d-pad
  ld [rP1], a

  ; read the d-pad several times to avoid bouncing
  ld a, [rP1] ; could also do
  ld a, [rP1] ; rept 4
  ld a, [rP1] ; ld a, [rP1]
  ld a, [rP1] ; endr

  and $0F
  swap a
  ld b, a

  ; we go for the buttons
  ld a, %00010000 ; bit 4 to 1 bit 5 to 0 (enable buttons, disable d-pad)
  ld [rP1], a

  ; read the buttons several times to avoid bouncing
  ld a, [rP1] ; could also do
  ld a, [rP1] ; rept 4
  ld a, [rP1] ; ld a, [rP1]
  ld a, [rP1] ; endr

  and $0F
  or b

  ; we now have a with 0 for down and 1 for up
  cpl ; complement so 1 means down :D
  ld [_PAD], a
  ld [_PROCESSING], a
.done
  ret

ENDC