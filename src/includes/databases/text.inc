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

CheckpointSetMessage:
  ; node ./src/scripts/text-encode.js "checkpoint set"
  db 5, 10, 7, 5, 13, 18, 17, 11, 16, 22, 2, 21, 7, 22, NULL

ElderOne:
; node ./src/scripts/text-encode.js "urgod has returned" "and evil spreads." "you must stop him."
db 23, 20, 9, 17, 6, 2, 10, 3, 21, 2, 20, 7, 22, 23, 20, 16, 7, 6, LINE_FEED
db 3, 16, 6, 2, 7, 24, 11, 14, 2, 21, 18, 20, 7, 3, 6, 21, 29, LINE_FEED
db 27, 17, 23, 2, 15, 23, 21, 22, 2, 21, 22, 17, 18, 2, 10, 11, 15, 29, NULL

ElderTwo:
; node ./src/scripts/text-encode.js "Urgod fears only" "the lance of heros"
db 23, 20, 9, 17, 6, 2, 8, 7, 3, 20, 21, 2, 17, 16, 14, 27, LINE_FEED
db 22, 10, 7, 2, 14, 3, 16, 5, 7, 2, 17, 8, 2, 10, 7, 20, 17, 21, NULL

ElderThree:
  ; node ./src/scripts/text-encode.js "heed our words" "seek the sages" "heal this world"
  db 10, 7, 7, 6, 2, 17, 23, 20, 2, 25, 17, 20, 6, 21 , LINE_FEED 
  db 21, 7, 7, 13, 2, 22, 10, 7, 2, 21, 3, 9, 7, 21 , LINE_FEED 
  db 10, 7, 3, 14, 2, 22, 10, 11, 21, 2, 25, 17, 20, 14, 6 , LINE_FEED , NULL

StartCampOne:
; node ./src/scripts/text-encode.js "There is a camp" "to the east if you" "follow the coast"
db 22, 10, 7, 20, 7, 2, 11, 21, 2, 3, 2, 5, 3, 15, 18, LINE_FEED
db 22, 17, 2, 22, 10, 7, 2, 7, 3, 21, 22, 2, 11, 8, 2, 27, 17, 23, LINE_FEED
db 8, 17, 14, 14, 17, 25, 2, 22, 10, 7, 2, 5, 17, 3, 21, 22, NULL

StartCampTwo:
; node ./src/scripts/text-encode.js "the flood plains" "to the north are" "well travelled"
db 22, 10, 7, 2, 8, 14, 17, 17, 6, 2, 18, 14, 3, 11, 16, 21, LINE_FEED
db 22, 17, 2, 22, 10, 7, 2, 16, 17, 20, 22, 10, 2, 3, 20, 7, LINE_FEED
db 25, 7, 14, 14, 2, 22, 20, 3, 24, 7, 14, 14, 7, 6, NULL

StartCampThree:
; node ./src/scripts/text-encode.js "the flood plains" "to the north are" "well travelled"
db 22, 10, 7, 2, 8, 14, 17, 17, 6, 2, 18, 14, 3, 11, 16, 21, LINE_FEED
db 22, 17, 2, 22, 10, 7, 2, 16, 17, 20, 22, 10, 2, 3, 20, 7, LINE_FEED
db 25, 7, 14, 14, 2, 22, 20, 3, 24, 7, 14, 14, 7, 6, NULL

; ## Rumors 

; ### FIRST TOWN
; - north past the mountains the monsters are more dangerous
; - there is a fishing village east along the coast
; - the road to the fishing village is long

; ### Nearby Clearing
; - I am trying to decipher the words written on this old stone
; - enciphered script on old stones
; - a hermit lives on the island north of here

; ### FISHING TOWN
; - a hermit lives on the island north of here
; - beware the swamp it is full of beasts


DarkLordSays:
  db 27, 17, 23, 2, 3, 20, 7, 2, 16, 17, 2, 10, 7, 20, 17 , LINE_FEED
  db 12, 23, 21, 22, 2, 3, 2, 5, 10, 11, 14, 6, 2, 21, 7, 16, 22 , LINE_FEED
  db 22, 17, 2, 6, 20, 17, 25, 16, 2, 11, 16, 2, 10, 17, 18, 7 , LINE_FEED, NULL

ENDC
