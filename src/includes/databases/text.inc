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

ElderOne:
  ; node ./src/scripts/text-encode.js "the world aches" "no kings remain" "and the dead stir"
  db 22, 10, 7, 2, 25, 17, 20, 14, 6, 2, 3, 5, 10, 7, 21, LINE_FEED 
  db 16, 17, 2, 13, 11, 16, 9, 21, 2, 20, 7, 15, 3, 11, 16, LINE_FEED 
  db 3, 16, 6, 2, 22, 10, 7, 2, 6, 7, 3, 6, 2, 21, 22, 11, 20, NULL

ElderTwo:
  ; node ./src/scripts/text-encode.js "a deep wrongness" "goes unanswered" "I know you see it"
  db 3, 2, 6, 7, 7, 18, 2, 25, 20, 17, 16, 9, 16, 7, 21, 21, LINE_FEED 
  db 9, 17, 7, 21, 2, 23, 16, 3, 16, 21, 25, 7, 20, 7, 6, LINE_FEED 
  db 11, 2, 13, 16, 17, 25, 2, 27, 17, 23, 2, 21, 7, 7, 2, 11, 22, LINE_FEED , NULL

ElderThree:
  ; node ./src/scripts/text-encode.js "heed our words" "seek the sages" "heal this world"
  db 10, 7, 7, 6, 2, 17, 23, 20, 2, 25, 17, 20, 6, 21 , LINE_FEED 
  db 21, 7, 7, 13, 2, 22, 10, 7, 2, 21, 3, 9, 7, 21 , LINE_FEED 
  db 10, 7, 3, 14, 2, 22, 10, 11, 21, 2, 25, 17, 20, 14, 6 , LINE_FEED , NULL

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
