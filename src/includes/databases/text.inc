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

; the world aches
; no kings remain
; and the dead stir
ElderOne:
  db 22, 42, 39, 2, 57, 49, 52, 46, 38, 2, 35, 37, 42, 39, 53 , LINE_FEED
  db 48, 49, 2, 45, 43, 48, 41, 53, 2, 52, 39, 47, 35, 43, 48 , LINE_FEED
  db 35, 48, 38, 2, 54, 42, 39, 2, 38, 39, 35, 38, 2, 53, 54, 43, 52 , LINE_FEED, NULL

; a deep wrongness
; goes unanswered
; I know you see it
ElderTwo:
  db 35, 2, 38, 39, 39, 50, 2, 57, 52, 49, 48, 41, 48, 39, 53, 53 , LINE_FEED
  db 41, 49, 39, 53, 2, 55, 48, 35, 48, 53, 57, 39, 52, 39, 38 , LINE_FEED
  db 11, 2, 45, 48, 49, 57, 2, 59, 49, 55, 2, 53, 39, 39, 2, 43, 54 , LINE_FEED, NULL

; head our words
; seek the sages
; heal this world
ElderThree:
  db 42, 39, 39, 38, 2, 49, 55, 52, 2, 57, 49, 52, 38, 53 , LINE_FEED
  db 53, 39, 39, 45, 2, 54, 42, 39, 2, 53, 35, 41, 39, 53 , LINE_FEED
  db 42, 39, 35, 46, 2, 54, 42, 43, 53, 2, 57, 49, 52, 46, 38 , LINE_FEED, NULL

NoShameDialog:
  db 22, 10, 7, 20, 7, 2, 11, 21, 2, 16, 17, 2, 21, 10, 3, 15, 7 , LINE_FEED
  db 11, 16, 2, 10, 11, 6, 11, 16, 9, 2, 10, 7, 20, 7 , LINE_FEED
  db 3, 15, 17, 16, 9, 2, 22, 10, 7, 2, 20, 23, 11, 16, 21 , LINE_FEED, NULL

LegionOfTheFallenDialog:
  db 10, 7, 2, 11, 21, 2, 9, 23, 3, 20, 6, 7, 6, 2, 4, 27 , LINE_FEED
  db 3, 2, 14, 7, 9, 11, 17, 16, 2, 17, 8, 2, 22, 10, 17, 21, 7 , LINE_FEED
  db 25, 10, 17, 2, 17, 18, 18, 17, 21, 7, 6, 2, 10, 11, 15 , LINE_FEED, NULL

; village
ArrowInTheKnee:
  db 15, 27, 2, 4, 17, 21, 17, 15, 2, 14, 7, 8, 22, 2, 22, 17 , LINE_FEED
  db 21, 14, 3, 27, 2, 10, 11, 15, 29, 29, 29, 2, 3, 16, 6 , LINE_FEED
  db 16, 17, 25, 2, 21, 7, 20, 24, 7, 21, 2, 10, 11, 15 , LINE_FEED, NULL

Elder1Dialog:
  db 29, 29, 29, NULL

escapedCultist:
  ; I escaped but I cannot forget
  db 11, 2, 8, 14, 7, 6, 2, 10, 11, 21, 2, 5, 23, 14, 22 , LINE_FEED
  db 11, 8, 2, 17, 16, 14, 27, 2, 11, 2, 5, 17, 23, 14, 6 , LINE_FEED
  db 8, 17, 20, 9, 7, 22, 29, 29, 29 , LINE_FEED, NULL

throneInTheEarth:
  ; his throne is in the earth
  db 22, 10, 7, 2, 22, 17, 25, 7, 20, 2, 11, 21, 2, 22, 3, 14, 14 , LINE_FEED
  db 4, 23, 22, 2, 10, 11, 21, 2, 22, 10, 20, 17, 16, 7, 2, 11, 21 , LINE_FEED
  db 11, 16, 2, 22, 10, 7, 2, 7, 3, 20, 22, 10 , LINE_FEED, NULL

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
  db 27, 17, 23, 2, 3, 20, 7, 2, 16, 17, 2, 10, 7, 20, 17 , LINE_FEED
  db 12, 23, 21, 22, 2, 3, 2, 5, 10, 11, 14, 6, 2, 21, 7, 16, 22 , LINE_FEED
  db 22, 17, 2, 6, 20, 17, 25, 16, 2, 11, 16, 2, 10, 17, 18, 7 , LINE_FEED, NULL

ENDC
