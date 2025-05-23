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
; node ./src/scripts/text-encode.js "you rest by the" "fire"
db 27, 17, 23, 2, 20, 7, 21, 22, 2, 4, 27, 2, 22, 10, 7, LINE_FEED
db 8, 11, 20, 7, NULL

; WARNING this one is special, and is hardcoded somewhere
Silence:
db 29, 29, 29, NULL

OublietteQuestion1:
; node ./src/scripts/text-encode.js "hold B to leave" "if you are trapped"
db 10, 17, 14, 6, 2, 4, 2, 22, 17, 2, 14, 7, 3, 24, 7, LINE_FEED
db 11, 8, 2, 27, 17, 23, 2, 3, 20, 7, 2, 22, 20, 3, 18, 18, 7, 6, NULL

OublietteNPC1:
; node ./src/scripts/text-encode.js "I am trapped." "I cannot leave."
db 11, 2, 3, 15, 2, 22, 20, 3, 18, 18, 7, 6, 29, LINE_FEED
db 11, 2, 5, 3, 16, 16, 17, 22, 2, 14, 7, 3, 24, 7, 29, NULL

OublietteNPC2:
; node ./src/scripts/text-encode.js "I can leave any" "time I want"
db 11, 2, 5, 3, 16, 2, 14, 7, 3, 24, 7, 2, 3, 16, 27, LINE_FEED
db 22, 11, 15, 7, 2, 11, 2, 25, 3, 16, 22, NULL

OublietteNPC3:
; node ./src/scripts/text-encode.js "the walls are soft" "dirt behind a thin" "veneer of rock"
db 22, 10, 7, 2, 25, 3, 14, 14, 21, 2, 3, 20, 7, 2, 21, 17, 8, 22, LINE_FEED
db 6, 11, 20, 22, 2, 4, 7, 10, 11, 16, 6, 2, 3, 2, 22, 10, 11, 16, LINE_FEED
db 24, 7, 16, 7, 7, 20, 2, 17, 8, 2, 20, 17, 5, 13, NULL

OublietteNPC4:
; node ./src/scripts/text-encode.js "so close... The" "air here tastes" "fresh and clean"
db 21, 17, 2, 5, 14, 17, 21, 7, 29, 29, 29, 2, 22, 10, 7, LINE_FEED
db 3, 11, 20, 2, 10, 7, 20, 7, 2, 22, 3, 21, 22, 7, 21, LINE_FEED
db 8, 20, 7, 21, 10, 2, 3, 16, 6, 2, 5, 14, 7, 3, 16, NULL

OublietteNPC5:
; node ./src/scripts/text-encode.js "a tunnel ending" "in light is a" "tunnel nonetheless"
db 3, 2, 22, 23, 16, 16, 7, 14, 2, 7, 16, 6, 11, 16, 9, LINE_FEED
db 11, 16, 2, 14, 11, 9, 10, 22, 2, 11, 21, 2, 3, LINE_FEED
db 22, 23, 16, 16, 7, 14, 2, 16, 17, 16, 7, 22, 10, 7, 14, 7, 21, 21, NULL


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
; node ./src/scripts/text-encode.js "evil beasts wait" "on the far shores" "of our rivers"
db 7, 24, 11, 14, 2, 4, 7, 3, 21, 22, 21, 2, 25, 3, 11, 22, LINE_FEED
db 17, 16, 2, 22, 10, 7, 2, 8, 3, 20, 2, 21, 10, 17, 20, 7, 21, LINE_FEED
db 17, 8, 2, 17, 23, 20, 2, 20, 11, 24, 7, 20, 21, NULL

TwinRiverNPC2:
; node ./src/scripts/text-encode.js "our people live" "on the coast where" "it is still safe"
db 17, 23, 20, 2, 18, 7, 17, 18, 14, 7, 2, 14, 11, 24, 7, LINE_FEED
db 17, 16, 2, 22, 10, 7, 2, 5, 17, 3, 21, 22, 2, 25, 10, 7, 20, 7, LINE_FEED
db 11, 22, 2, 11, 21, 2, 21, 22, 11, 14, 14, 2, 21, 3, 8, 7, NULL
TwinRiverNPC3:
; node ./src/scripts/text-encode.js "to visit our kin" "go east then north" "around the cape"
db 22, 17, 2, 24, 11, 21, 11, 22, 2, 17, 23, 20, 2, 13, 11, 16, LINE_FEED
db 9, 17, 2, 7, 3, 21, 22, 2, 22, 10, 7, 16, 2, 16, 17, 20, 22, 10, LINE_FEED
db 3, 20, 17, 23, 16, 6, 2, 22, 10, 7, 2, 5, 3, 18, 7, NULL

TwinRiverNPC4:
; node ./src/scripts/text-encode.js "avoid the woods" "they are home to" "terrible monsters"
db 3, 24, 17, 11, 6, 2, 22, 10, 7, 2, 25, 17, 17, 6, 21, LINE_FEED
db 22, 10, 7, 27, 2, 3, 20, 7, 2, 10, 17, 15, 7, 2, 22, 17, LINE_FEED
db 22, 7, 20, 20, 11, 4, 14, 7, 2, 15, 17, 16, 21, 22, 7, 20, 21, NULL

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

TwinRiverNPC7:
; node ./src/scripts/text-encode.js "bad water befouls" "these caves. cross" "at your peril..."
db 4, 3, 6, 2, 25, 3, 22, 7, 20, 2, 4, 7, 8, 17, 23, 14, 21, LINE_FEED
db 22, 10, 7, 21, 7, 2, 5, 3, 24, 7, 21, 29, 2, 5, 20, 17, 21, 21, LINE_FEED
db 3, 22, 2, 27, 17, 23, 20, 2, 18, 7, 20, 11, 14, 29, 29, 29, NULL

/* North River Folk */
NorthRiverNPC1:
; node ./src/scripts/text-encode.js "it is quite rare" "to meet folk from" "the south"
db 11, 22, 2, 11, 21, 2, 19, 23, 11, 22, 7, 2, 20, 3, 20, 7, LINE_FEED
db 22, 17, 2, 15, 7, 7, 22, 2, 8, 17, 14, 13, 2, 8, 20, 17, 15, LINE_FEED
db 22, 10, 7, 2, 21, 17, 23, 22, 10, NULL

NorthRiverNPC2:
; node ./src/scripts/text-encode.js "welcome to" "north river"
db 25, 7, 14, 5, 17, 15, 7, 2, 22, 17, LINE_FEED
db 16, 17, 20, 22, 10, 2, 20, 11, 24, 7, 20, NULL

NorthRiverNPC3:
; node ./src/scripts/text-encode.js "the north coast of" "old was plagued by" "dangerous pirates"
db 22, 10, 7, 2, 16, 17, 20, 22, 10, 2, 5, 17, 3, 21, 22, 2, 17, 8, LINE_FEED
db 17, 14, 6, 2, 25, 3, 21, 2, 18, 14, 3, 9, 23, 7, 6, 2, 4, 27, LINE_FEED
db 6, 3, 16, 9, 7, 20, 17, 23, 21, 2, 18, 11, 20, 3, 22, 7, 21, NULL

NorthRiverNPC4:
; node ./src/scripts/text-encode.js "we traded pirates" "for the beasts of" "the river kings"
db 25, 7, 2, 22, 20, 3, 6, 7, 6, 2, 18, 11, 20, 3, 22, 7, 21, LINE_FEED
db 8, 17, 20, 2, 22, 10, 7, 2, 4, 7, 3, 21, 22, 21, 2, 17, 8, LINE_FEED
db 22, 10, 7, 2, 20, 11, 24, 7, 20, 2, 13, 11, 16, 9, 21, NULL

NorthRiverNPC5:
; node ./src/scripts/text-encode.js "my grandmother was" "a pirate before" "she married gramps"
db 15, 27, 2, 9, 20, 3, 16, 6, 15, 17, 22, 10, 7, 20, 2, 25, 3, 21, LINE_FEED
db 3, 2, 18, 11, 20, 3, 22, 7, 2, 4, 7, 8, 17, 20, 7, LINE_FEED
db 21, 10, 7, 2, 15, 3, 20, 20, 11, 7, 6, 2, 9, 20, 3, 15, 18, 21, NULL

NorthRiverNPC6:
; node ./src/scripts/text-encode.js "i found a tablet" "but the words were" "not for me..."
db 11, 2, 8, 17, 23, 16, 6, 2, 3, 2, 22, 3, 4, 14, 7, 22, LINE_FEED
db 4, 23, 22, 2, 22, 10, 7, 2, 25, 17, 20, 6, 21, 2, 25, 7, 20, 7, LINE_FEED
db 16, 17, 22, 2, 8, 17, 20, 2, 15, 7, 29, 29, 29, NULL

NorthRiverNPC7:
; node ./src/scripts/text-encode.js "the coast north of" "here is dangerous" "traveller"
db 22, 10, 7, 2, 5, 17, 3, 21, 22, 2, 16, 17, 20, 22, 10, 2, 17, 8, LINE_FEED
db 10, 7, 20, 7, 2, 11, 21, 2, 6, 3, 16, 9, 7, 20, 17, 23, 21, LINE_FEED
db 22, 20, 3, 24, 7, 14, 14, 7, 20, NULL

/* Little Valley Folk */
LittleValleyNPC1:
; node ./src/scripts/text-encode.js "welcome to little" "valley. visitors" "are so rare now"
db 25, 7, 14, 5, 17, 15, 7, 2, 22, 17, 2, 14, 11, 22, 22, 14, 7, LINE_FEED
db 24, 3, 14, 14, 7, 27, 29, 2, 24, 11, 21, 11, 22, 17, 20, 21, LINE_FEED
db 3, 20, 7, 2, 21, 17, 2, 20, 3, 20, 7, 2, 16, 17, 25, NULL

;LittleValleyNPC2:
; node ./src/scripts/text-encode.js "it has been a long" "while since I met" "northern folk"
;db 11, 22, 2, 10, 3, 21, 2, 4, 7, 7, 16, 2, 3, 2, 14, 17, 16, 9, LINE_FEED
;db 25, 10, 11, 14, 7, 2, 21, 11, 16, 5, 7, 2, 11, 2, 15, 7, 22, LINE_FEED
;db 16, 17, 20, 22, 10, 7, 20, 16, 2, 8, 17, 14, 13, NULL

LittleValleyNPC3:
; node ./src/scripts/text-encode.js "there is a tower" "on the plateau"
db 22, 10, 7, 20, 7, 2, 11, 21, 2, 3, 2, 22, 17, 25, 7, 20, LINE_FEED
db 17, 16, 2, 22, 10, 7, 2, 18, 14, 3, 22, 7, 3, 23, NULL

LittleValleyNPC4:
; node ./src/scripts/text-encode.js "only a fool would" "set foot in the" "swamps"
db 17, 16, 14, 27, 2, 3, 2, 8, 17, 17, 14, 2, 25, 17, 23, 14, 6, LINE_FEED
db 21, 7, 22, 2, 8, 17, 17, 22, 2, 11, 16, 2, 22, 10, 7, LINE_FEED
db 21, 25, 3, 15, 18, 21, NULL

LittleValleyNPC5:
; node ./src/scripts/text-encode.js "boats once sailed" "between our valley" "and north river"
db 4, 17, 3, 22, 21, 2, 17, 16, 5, 7, 2, 21, 3, 11, 14, 7, 6, LINE_FEED
db 4, 7, 22, 25, 7, 7, 16, 2, 17, 23, 20, 2, 24, 3, 14, 14, 7, 27, LINE_FEED
db 3, 16, 6, 2, 16, 17, 20, 22, 10, 2, 20, 11, 24, 7, 20, NULL

LittleValleyNPC6:
; node ./src/scripts/text-encode.js "the source of our" "river is untouched" "by the river kings"
db 22, 10, 7, 2, 21, 17, 23, 20, 5, 7, 2, 17, 8, 2, 17, 23, 20, LINE_FEED
db 20, 11, 24, 7, 20, 2, 11, 21, 2, 23, 16, 22, 17, 23, 5, 10, 7, 6, LINE_FEED
db 4, 27, 2, 22, 10, 7, 2, 20, 11, 24, 7, 20, 2, 13, 11, 16, 9, 21, NULL

TellingStones1:
; node ./src/scripts/text-encode.js "river kings feared" "the pirates of old"
db 20, 11, 24, 7, 20, 2, 13, 11, 16, 9, 21, 2, 8, 7, 3, 20, 7, 6, LINE_FEED
db 22, 10, 7, 2, 18, 11, 20, 3, 22, 7, 21, 2, 17, 8, 2, 17, 14, 6, NULL

TellingStones2:
; node ./src/scripts/text-encode.js "to slay the river" "kings first seek" "their blessing"
db 22, 17, 2, 21, 14, 3, 27, 2, 22, 10, 7, 2, 20, 11, 24, 7, 20, LINE_FEED
db 13, 11, 16, 9, 21, 2, 8, 11, 20, 21, 22, 2, 21, 7, 7, 13, LINE_FEED
db 22, 10, 7, 11, 20, 2, 4, 14, 7, 21, 21, 11, 16, 9, NULL

TellingStones3:
; node ./src/scripts/text-encode.js "you are pale moon"
db 27, 17, 23, 2, 3, 20, 7, 2, 18, 3, 14, 7, 2, 15, 17, 17, 16, NULL

SouthDeltaCampNPC:
; node ./src/scripts/text-encode.js "the way north is" "blocked by that" "terrible swamp"
db 22, 10, 7, 2, 25, 3, 27, 2, 16, 17, 20, 22, 10, 2, 11, 21, LINE_FEED
db 4, 14, 17, 5, 13, 7, 6, 2, 4, 27, 2, 22, 10, 3, 22, LINE_FEED
db 22, 7, 20, 20, 11, 4, 14, 7, 2, 21, 25, 3, 15, 18, NULL


WestSageNPC1:
; node ./src/scripts/text-encode.js "the eastern sages" "are drunk on tales" "of ancient swords"
db 22, 10, 7, 2, 7, 3, 21, 22, 7, 20, 16, 2, 21, 3, 9, 7, 21, LINE_FEED
db 3, 20, 7, 2, 6, 20, 23, 16, 13, 2, 17, 16, 2, 22, 3, 14, 7, 21, LINE_FEED
db 17, 8, 2, 3, 16, 5, 11, 7, 16, 22, 2, 21, 25, 17, 20, 6, 21, NULL

WestSageNPC2:
; node ./src/scripts/text-encode.js "the blessings of" "the stones lead" "to truth not arms"
db 22, 10, 7, 2, 4, 14, 7, 21, 21, 11, 16, 9, 21, 2, 17, 8, LINE_FEED
db 22, 10, 7, 2, 21, 22, 17, 16, 7, 21, 2, 14, 7, 3, 6, LINE_FEED
db 22, 17, 2, 22, 20, 23, 22, 10, 2, 16, 17, 22, 2, 3, 20, 15, 21, NULL

EastSageNPC1:
; node ./src/scripts/text-encode.js "western sages are" "obsessed with song" "and foolish talk"
db 25, 7, 21, 22, 7, 20, 16, 2, 21, 3, 9, 7, 21, 2, 3, 20, 7, LINE_FEED
db 17, 4, 21, 7, 21, 21, 7, 6, 2, 25, 11, 22, 10, 2, 21, 17, 16, 9, LINE_FEED
db 3, 16, 6, 2, 8, 17, 17, 14, 11, 21, 10, 2, 22, 3, 14, 13, NULL

EastSageNPC2:
; node ./src/scripts/text-encode.js "it is clear the" "only salvation is" "the ancient blade"
db 11, 22, 2, 11, 21, 2, 5, 14, 7, 3, 20, 2, 22, 10, 7, LINE_FEED
db 17, 16, 14, 27, 2, 21, 3, 14, 24, 3, 22, 11, 17, 16, 2, 11, 21, LINE_FEED
db 22, 10, 7, 2, 3, 16, 5, 11, 7, 16, 22, 2, 4, 14, 3, 6, 7, NULL

StoneScripture1:
; node ./src/scripts/text-encode.js "songs of stone" "and ancient steel" "to the river kings"
db 21, 17, 16, 9, 21, 2, 17, 8, 2, 21, 22, 17, 16, 7, LINE_FEED
db 3, 16, 6, 2, 3, 16, 5, 11, 7, 16, 22, 2, 21, 22, 7, 7, 14, LINE_FEED
db 22, 17, 2, 22, 10, 7, 2, 20, 11, 24, 7, 20, 2, 13, 11, 16, 9, 21, NULL

StoneScripture2:
; node ./src/scripts/text-encode.js "then they will" "fall by the light" "of a pale moon"
db 22, 10, 7, 16, 2, 22, 10, 7, 27, 2, 25, 11, 14, 14, LINE_FEED
db 8, 3, 14, 14, 2, 4, 27, 2, 22, 10, 7, 2, 14, 11, 9, 10, 22, LINE_FEED
db 17, 8, 2, 3, 2, 18, 3, 14, 7, 2, 15, 17, 17, 16, NULL

PilgrimNPC1:
; node ./src/scripts/text-encode.js "alas the sages of" "east and west are" "fierce rivals"
db 3, 14, 3, 21, 2, 22, 10, 7, 2, 21, 3, 9, 7, 21, 2, 17, 8, LINE_FEED
db 7, 3, 21, 22, 2, 3, 16, 6, 2, 25, 7, 21, 22, 2, 3, 20, 7, LINE_FEED
db 8, 11, 7, 20, 5, 7, 2, 20, 11, 24, 3, 14, 21, NULL

PilgrimNPC2:
; node ./src/scripts/text-encode.js "this is the only" "part the sages" "can agree on"
db 22, 10, 11, 21, 2, 11, 21, 2, 22, 10, 7, 2, 17, 16, 14, 27, LINE_FEED
db 18, 3, 20, 22, 2, 22, 10, 7, 2, 21, 3, 9, 7, 21, LINE_FEED
db 5, 3, 16, 2, 3, 9, 20, 7, 7, 2, 17, 16, NULL

PilgrimNPC3:
; node ./src/scripts/text-encode.js "it is said the" "telling stones are" "in a cave nearby"
db 11, 22, 2, 11, 21, 2, 21, 3, 11, 6, 2, 22, 10, 7, LINE_FEED
db 22, 7, 14, 14, 11, 16, 9, 2, 21, 22, 17, 16, 7, 21, 2, 3, 20, 7, LINE_FEED
db 11, 16, 2, 3, 2, 5, 3, 24, 7, 2, 16, 7, 3, 20, 4, 27, NULL

NorthRoadGuard:
; node ./src/scripts/text-encode.js "the road north is" "dangerous i will" "not let you pass"
db 22, 10, 7, 2, 20, 17, 3, 6, 2, 16, 17, 20, 22, 10, 2, 11, 21, LINE_FEED
db 6, 3, 16, 9, 7, 20, 17, 23, 21, 2, 11, 2, 25, 11, 14, 14, LINE_FEED
db 16, 17, 22, 2, 14, 7, 22, 2, 27, 17, 23, 2, 18, 3, 21, 21, NULL

PirateCaveWarning:
; node ./src/scripts/text-encode.js "the cursed ghosts" "of pirate folk" "guard these halls"
db 22, 10, 7, 2, 5, 23, 20, 21, 7, 6, 2, 9, 10, 17, 21, 22, 21, LINE_FEED
db 17, 8, 2, 18, 11, 20, 3, 22, 7, 2, 8, 17, 14, 13, LINE_FEED
db 9, 23, 3, 20, 6, 2, 22, 10, 7, 21, 7, 2, 10, 3, 14, 14, 21, NULL

HunterCaveNearBoatNPC:
db 29, 29, 29, NULL

HunterCaveNorthRiverNPC:
db 29, 29, 29, NULL

HunterCaveRoadToSwampNPC:
; node ./src/scripts/text-encode.js "i like it here. I" "can see a tower" "from the peak"
db 11, 2, 14, 11, 13, 7, 2, 11, 22, 2, 10, 7, 20, 7, 29, 2, 11, LINE_FEED
db 5, 3, 16, 2, 21, 7, 7, 2, 3, 2, 22, 17, 25, 7, 20, LINE_FEED
db 8, 20, 17, 15, 2, 22, 10, 7, 2, 18, 7, 3, 13, NULL

CampNorthEastNPC:
; node ./src/scripts/text-encode.js "i was told there" "was pirate gold" "up north but..."
db 11, 2, 25, 3, 21, 2, 22, 17, 14, 6, 2, 22, 10, 7, 20, 7, LINE_FEED
db 25, 3, 21, 2, 18, 11, 20, 3, 22, 7, 2, 9, 17, 14, 6, LINE_FEED
db 23, 18, 2, 16, 17, 20, 22, 10, 2, 4, 23, 22, 29, 29, 29, NULL

CampNorthSwampNPC:
; node ./src/scripts/text-encode.js "these woods are" "safe relative to" "the swamps"
db 22, 10, 7, 21, 7, 2, 25, 17, 17, 6, 21, 2, 3, 20, 7, LINE_FEED
db 21, 3, 8, 7, 2, 20, 7, 14, 3, 22, 11, 24, 7, 2, 22, 17, LINE_FEED
db 22, 10, 7, 2, 21, 25, 3, 15, 18, 21, NULL

CampSouthTwinRiverNPC:
; node ./src/scripts/text-encode.js "these woods are" "dangerous. best to" "keep out traveller"
db 22, 10, 7, 21, 7, 2, 25, 17, 17, 6, 21, 2, 3, 20, 7, LINE_FEED
db 6, 3, 16, 9, 7, 20, 17, 23, 21, 29, 2, 4, 7, 21, 22, 2, 22, 17, LINE_FEED
db 13, 7, 7, 18, 2, 17, 23, 22, 2, 22, 20, 3, 24, 7, 14, 14, 7, 20, NULL

ENDC
