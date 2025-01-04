IF !DEF(TEXT_DATABASE_INC)
TEXT_DATABASE_INC = 1

Section "TEXT_DATABASE", ROMX, BANK[1]

LINE_FEED EQU 1
NULL EQU 0

; WARNING this one is special, and is hardcoded somewhere
DarkLordSays:
  db 27, 17, 23, 2, 3, 20, 7, 2, 16, 17, 2, 10, 7, 20, 17 , LINE_FEED
  db 12, 23, 21, 22, 2, 3, 2, 5, 10, 11, 14, 6, 2, 21, 7, 16, 22 , LINE_FEED
  db 22, 17, 2, 6, 20, 17, 25, 16, 2, 11, 16, 2, 10, 17, 18, 7 , LINE_FEED, NULL

; WARNING this one is special, and is hardcoded somewhere
CheckpointSetMessage:
  ; node ./src/scripts/text-encode.js "checkpoint set"
  db 5, 10, 7, 5, 13, 18, 17, 11, 16, 22, 2, 21, 7, 22, NULL

; WARNING this one is special, and is hardcoded somewhere
Silence:
  db 29, 29, 29, NULL

; we are not bounds checking, the author must be
; careful to ensure each text is < 54 chars and null terminated
; with each line being < 18 char and line feed terminated

StartCave:
; node ./src/scripts/text-encode.js "Bevin is still not" "home. Go see if he" "is alright"
db 4, 7, 24, 11, 16, 2, 11, 21, 2, 21, 22, 11, 14, 14, 2, 16, 17, 22, LINE_FEED
db 10, 17, 15, 7, 29, 2, 9, 17, 2, 21, 7, 7, 2, 11, 8, 2, 10, 7, LINE_FEED
db 11, 21, 2, 3, 14, 20, 11, 9, 10, 22, NULL

StartSouth:
; node ./src/scripts/text-encode.js "I saw Bevin run" "off to the east"
db 11, 2, 21, 3, 25, 2, 4, 7, 24, 11, 16, 2, 20, 23, 16, LINE_FEED
db 17, 8, 8, 2, 22, 17, 2, 22, 10, 7, 2, 7, 3, 21, 22, NULL

ForestCaveLobby:
; node ./src/scripts/text-encode.js "there are ruins" "hidden all around" "the valley"
db 22, 10, 7, 20, 7, 2, 3, 20, 7, 2, 20, 23, 11, 16, 21, LINE_FEED
db 10, 11, 6, 6, 7, 16, 2, 3, 14, 14, 2, 3, 20, 17, 23, 16, 6, LINE_FEED
db 22, 10, 7, 2, 24, 3, 14, 14, 7, 27, NULL

ForestCave:
; node ./src/scripts/text-encode.js "there are caves" "for those with" "eyes to see them"
db 22, 10, 7, 20, 7, 2, 3, 20, 7, 2, 5, 3, 24, 7, 21, LINE_FEED
db 8, 17, 20, 2, 22, 10, 17, 21, 7, 2, 25, 11, 22, 10, LINE_FEED
db 7, 27, 7, 21, 2, 22, 17, 2, 21, 7, 7, 2, 22, 10, 7, 15, NULL

HoleCave:
; node ./src/scripts/text-encode.js "the cave yawned" "and trapped bevin" "down below..."
db 22, 10, 7, 2, 5, 3, 24, 7, 2, 27, 3, 25, 16, 7, 6, LINE_FEED
db 3, 16, 6, 2, 22, 20, 3, 18, 18, 7, 6, 2, 4, 7, 24, 11, 16, LINE_FEED
db 6, 17, 25, 16, 2, 4, 7, 14, 17, 25, 29, 29, 29, NULL

ENDC
