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

/** plan: 
 * two groups of sages guard the road to the north on opposite banks of the river
 * the east bank sages say that only one who has made the hero's pilgrimage in the valley could defeat the dark lord 
 * the west bank sages sat that only one who has the blade of light can defeat the dark lord
 *
 * someone says "the blade of light was stolen long ago"
 * elsewhere "at least the darklord drove the pirates away"
 * elsewhere "the coast was once full of with pirates"
 *
 * the idea here is:
 * - you can go to the darklord any time, but the way is high level
 * - having the blade of light makes this easier
 * - the hero's pilgrimage has a nice difficulty curve, so you can level up
 * - after doing the hero's pilgrimage you are high enough level to do the pirate
 *   dungeon
 * - after doing both you are high enough level to fight the dark lord (maybe the sword give you bonus damage)
 *
 * You don't _need_ the boat to get to the valley, you can fight through the swamp
 * but there are no checkpoints along the hero's pilgrimage
 * 
 * You also don't need the blade of light or anything to fight the dark lord but
 * you would have to grind your ass of

 1. hero's pilgrimage
 2. blade of light
 3. calm moon
 */

/** start in town
 * head north get to the next town
 * get high enough level to go through the shortcut
 * notice the cave there
 * read the telling stones 
 *
 * head south and get to the valley with the swamp 
 * folks in the south town warn of the swamp 
 *
 * the player has to choose to explore north and find the boat 
 **/

/* Twin River */
TwinRiverNPC1:
; node ./src/scripts/text-encode.js "child it is folly" "to stand against" "the river kings"
db 5, 10, 11, 14, 6, 2, 11, 22, 2, 11, 21, 2, 8, 17, 14, 14, 27, LINE_FEED
db 22, 17, 2, 21, 22, 3, 16, 6, 2, 3, 9, 3, 11, 16, 21, 22, LINE_FEED
db 22, 10, 7, 2, 20, 11, 24, 7, 20, 2, 13, 11, 16, 9, 21, NULL

TwinRiverNPC2:
; node ./src/scripts/text-encode.js "our people live" "on the coast where" "it is still safe"
db 17, 23, 20, 2, 18, 7, 17, 18, 14, 7, 2, 14, 11, 24, 7, LINE_FEED
db 17, 16, 2, 22, 10, 7, 2, 5, 17, 3, 21, 22, 2, 25, 10, 7, 20, 7, LINE_FEED
db 11, 22, 2, 11, 21, 2, 21, 22, 11, 14, 14, 2, 21, 3, 8, 7, NULL
TwinRiverNPC3:
; node ./src/scripts/text-encode.js "to visit our kin" "head east past the" "cape then north"
db 22, 17, 2, 24, 11, 21, 11, 22, 2, 17, 23, 20, 2, 13, 11, 16, LINE_FEED
db 10, 7, 3, 6, 2, 7, 3, 21, 22, 2, 18, 3, 21, 22, 2, 22, 10, 7, LINE_FEED
db 5, 3, 18, 7, 2, 22, 10, 7, 16, 2, 16, 17, 20, 22, 10, NULL
TwinRiverNPC4:
; node ./src/scripts/text-encode.js "avoid the woods" "they are home to" "terrible beasts"
db 3, 24, 17, 11, 6, 2, 22, 10, 7, 2, 25, 17, 17, 6, 21, LINE_FEED
db 22, 10, 7, 27, 2, 3, 20, 7, 2, 10, 17, 15, 7, 2, 22, 17, LINE_FEED
db 22, 7, 20, 20, 11, 4, 14, 7, 2, 4, 7, 3, 21, 22, 21, NULL

TwinRiverNPC5:
; node ./src/scripts/text-encode.js "the river kings" "flood the valleys" "with angry beasts"
db 22, 10, 7, 2, 20, 11, 24, 7, 20, 2, 13, 11, 16, 9, 21, LINE_FEED
db 8, 14, 17, 17, 6, 2, 22, 10, 7, 2, 24, 3, 14, 14, 7, 27, 21, LINE_FEED
db 25, 11, 22, 10, 2, 3, 16, 9, 20, 27, 2, 4, 7, 3, 21, 22, 21, NULL
TwinRiverNPC6:
; node ./src/scripts/text-encode.js "i heard the river" "kings are barely" "human anymore"
db 11, 2, 10, 7, 3, 20, 6, 2, 22, 10, 7, 2, 20, 11, 24, 7, 20, LINE_FEED
db 13, 11, 16, 9, 21, 2, 3, 20, 7, 2, 4, 3, 20, 7, 14, 27, LINE_FEED
db 10, 23, 15, 3, 16, 2, 3, 16, 27, 15, 17, 20, 7, NULL

/* North River Folk */
; node ./src/scripts/text-encode.js "the north coast of" "old was plagued by" "dangerous pirates"
; node ./src/scripts/text-encode.js "we traded pirates" "for the beasts of" "the river kings"

; node ./src/scripts/text-encode.js "it is quite" "rare to meet folk" "from down south"
; node ./src/scripts/text-encode.js "welcome to north" "river" ""

; node ./src/scripts/text-encode.js "we once lived all" "happily along the" "north river"
; node ./src/scripts/text-encode.js "the further you go" "up river the more" "dangerous it is"

/* Little Valley Folk */
; node ./src/scripts/text-encode.js "hello and welcome" "to little valley"
; node ./src/scripts/text-encode.js "it has been a long" "while since I met" "norther folk"
; node ./src/scripts/text-encode.js "my grandmother was" "a pirate before" "she married gramps"
; node ./src/scripts/text-encode.js "the source of our" "river is untouched" "by the river kings"
; node ./src/scripts/text-encode.js "further west lies" "the greater valley" "and the old road"
; node ./src/scripts/text-encode.js "i am told swamps" "are deadly though" "i have not been"

ENDC
