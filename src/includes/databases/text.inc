IF !DEF(TEXT_DATABASE_INC)
TEXT_DATABASE_INC = 1

Section "TEXT_DATABASE", ROMX, BANK[1]

LINE_FEED EQU 1
NULL EQU 0

; we are not bounds checking, the author must be
; careful to ensure each text is < 54 chars and null terminated
; with each line being < 18 char and line feed terminated

TestDialog:
  ;  I  u  U  e             E  o  O  O 
  db 3, 4, 5, 6, LINE_FEED, 7, 8, 9, 9, LINE_FEED, 10, 11, 12, 13, NULL

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
