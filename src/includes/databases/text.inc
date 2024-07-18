IF !DEF(TEXT_DATABASE_INC)
TEXT_DATABASE_INC = 1

Section "TEXT_DATABASE", ROMX, BANK[1]

LINE_FEED EQU 1
NULL EQU 0

; we are not bounds checking, the author must be
; careful to ensure each text is < 54 chars and null terminated
; with each line being < 18 char and line feed terminated

TestDialog:
  db 22, 10, 7, 20, 7, 2, 11, 21, 2, 16, 17, 2, 21, 10, 3, 15, 7 , LINE_FEED
  db 11, 16, 2, 10, 11, 6, 11, 16, 9, 2, 10, 7, 20, 7 , LINE_FEED
  db 3, 15, 17, 16, 9, 2, 22, 10, 7, 2, 20, 23, 11, 16, 21 , LINE_FEED, NULL

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
