IF !DEF(TEXT_DATABASE_INC)
TEXT_DATABASE_INC = 1

Section "TEXT_DATABASE", ROMX, BANK[1]

LINE_FEED EQU 1
NULL EQU 0

; we are not bounds checking, the author must be
; careful to ensure each text is < 54 chars and null terminated
; with each line being < 18 char and line feed terminated

Silence:
  db 29, 29, 29, NULL

TestDialog:
  db 22, 10, 7, 20, 7, 2, 11, 21, 2, 16, 17, 2, 21, 10, 3, 15, 7 , LINE_FEED
  db 11, 16, 2, 10, 11, 6, 11, 16, 9, 2, 10, 7, 20, 7 , LINE_FEED
  db 3, 15, 17, 16, 9, 2, 22, 10, 7, 2, 20, 23, 11, 16, 21 , LINE_FEED, NULL

;|                 |LINE_FEED
; CHILD IT IS FOLLY
; TO STAND AGAINST
; THE DARK LORD
ElderWarning:
  db 5, 10, 11, 14, 6, 2, 11, 22, 2, 11, 21, 2, 8, 17, 14, 14, 27 , LINE_FEED
  db 22, 17, 2, 21, 22, 3, 16, 6, 2, 3, 9, 3, 11, 16, 21, 22 , LINE_FEED
  db 22, 10, 7, 2, 6, 3, 20, 13, 2, 14, 17, 20, 6 , LINE_FEED, NULL

;|                 |LINE_FEED
; IF YOU LEAVE NOW
; I FORBID YOU TO
; EVER RETURN HERE
LastChance:
  db 11, 8, 2, 27, 17, 23, 2, 14, 7, 3, 24, 7, 2, 16, 17, 25 , LINE_FEED
  db 11, 2, 8, 17, 20, 4, 11, 6, 2, 27, 17, 23, 2, 22, 17 , LINE_FEED
  db 7, 24, 7, 20, 2, 20, 7, 22, 23, 20, 16, 2, 10, 7, 20, 7 , LINE_FEED, NULL

DarkLordSays:
  ; YOU ARE NO HERO | JUST A CHILD SENT | TO SLAY A GOD
  db 27, 17, 23, 2, 3, 20, 7, 2, 16, 17, 2, 10, 7, 20, 17 , LINE_FEED
  db 12, 23, 21, 22, 2, 3, 2, 5, 10, 11, 14, 6, 2, 21, 7, 16, 22 , LINE_FEED
  db 22, 17, 2, 6, 20, 17, 25, 16, 2, 11, 16, 2, 10, 17, 18, 7 , LINE_FEED, NULL

; 17 chars + line feed
; null terminated
; In the north is  |
; a cave where some|
; creatures lurk   |
ExampleMaxDialog:
  db 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, LINE_FEED
  db 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, LINE_FEED
  db 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, NULL

ENDC
