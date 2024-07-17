IF !DEF(TEXT_DATABASE_INC)
TEXT_DATABASE_INC = 1

Section "TEXT_DATABASE", ROMX, BANK[1]

LINE_FEED EQU 1
NULL EQU 0

; we are not bounds checking, the author must be
; careful to ensure each text is < 54 chars and null terminated
; with each line being < 18 char and line feed terminated

TestDialog:
  db 18, 45, 22, 61, 45, 49, 62, 35, 81, 22, 73, 30, 3, 41, 72, LINE_FEED
  db 63, 18, 5, 45, 39, 5, 55, 3, 34, 30, 58, 5, 11, 3, 3, LINE_FEED, NULL

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
