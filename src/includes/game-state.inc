IF !DEF(GAME_STATE_INC)
GAME_STATE_INC = 1

SECTION "GAME_STATE", WRAM0

GAME_STATE_LOW_BYTE: ds 1
GAME_STATE_HIGH_BYTE: ds 1
ENCOUNTER_SPRITE_TILES: ds 4

SECTION "GameState", ROM0

/** we want to add a fade out / fade in over 3 frames 
 * fade out, then draw the new screen, then fade in
 * this means the screen transition event should
 * end by setting the game state to fade out
 * and then that should transition to a "draw" state
 * and then fade in 
 * lets do this in 2 states: exit state and enter state
 * exit state runs the fade out and then transitions
 * to enter state, which runs the draw and then fades in */

initGameState:
  ; initialize the game state to overworld
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(enterState)
  ld [hl+], a
  ld a, HIGH(enterState)
  ld [hl], a

  ret

exitState:
  call waitForVBlank

  ; fade out the screen slowly
  call count4In8Frames

  ld hl, FadeOutPalettes
  push af

  ; add a to hl
  add l
	ld l, a
	adc h
	sub l
	ld h, a

  ; get the next palette
  ld a, [hl]

  ld [rBGP], a
  ld [rOBP0], a
  
  pop af
  cp a, 3 ; are we done fading out?
  jp nz, .continue

  ; get the transition event
  call getCurrentEvent
  call doTransportRedraw
  call resetTime
  call toEnterState

  ret

.continue

  ret

enterState:
  call waitForVBlank

  ; fade in the screen slowly
  call count4In8Frames

  ld hl, FadeInPalettes
  push af

  ; add a to hl
  add l
	ld l, a
	adc h
	sub l
	ld h, a

  ; get the next palette
  ld a, [hl]

  ld [rBGP], a
  ld [rOBP0], a
  
  pop af
  cp a, 3 ; are we done fading out?
  jp nz, .continue

  ; transition to overworld state
  call toOverworldGameState
  ret

.continue

  ret

; sets a to 0 if a is negative
wholeA:
  bit 7, a
  jr z, .done
  ; negative
  ld a, 0
.done
  ret

/** random encounter */
randomEncounterGameState:
  ; if we are in a steady state and either
  ; combatant is dead, we are done
  ld a, [PLAYER_CURRENT_HP]
  cp a, 0
  jr z, .playerDead

  ld a, [ENCOUNTER_CURRENT_HP]
  cp a, 0
  jr z, .monsterDead

  ; -- INPUT PHASE JUST RECORDS ACTIONS --

  call readInput

  ; if A button was up last frame then we won't do anything
  ; regardless
  ld a, [_PREV_PAD]
  and a, A_BUTTON
  ret nz ; if A button is still UP return

  ; if A button was down, and they pressed A, then we have
  ; disco party time
  ld a, [_PAD]
  and a, A_BUTTON
  ret z

  ; otherwise there was input
  ; so apply player and monster damage

  ld a, [PLAYER_DEF]
  ld b, a
  ld a, [ENCOUNTER_ATT]
  sub a, b ; damage = att - def
  call wholeA
  ld b, a
  ld a, [PLAYER_CURRENT_HP]
  sub a, b ; next = hp - damage

  call wholeA
  ld [PLAYER_NEXT_CURRENT_HP], a

  ld a, [ENCOUNTER_DEF]
  ld b, a
  ld a, [PLAYER_ATT]
  sub a, b ; damage = att - def
  call wholeA
  ld b, a
  ld a, [ENCOUNTER_CURRENT_HP]
  sub a, b ; next = hp - damage

  call wholeA
  ld [ENCOUNTER_NEXT_CURRENT_HP], a

  call resetInput

  ; the encounter continues
  ret

.playerDead
  call turnOffWindow
  call resetInput
  call toGameOverState
  ret

.monsterDead
  ld a, [ENCOUNTER_XP]
  ld b, a
  ld a, [PLAYER_XP]
  add a, b
  ld [PLAYER_XP], a

  ; check for level
  ld a, [PLAYER_XP_TARGET]
  ld b, a
  ld a, [PLAYER_XP]
  cp a, b
  jr c, .doneLevel ; xp < target => done

  ; apply level
  ld a, 0
  ld [PLAYER_XP], a ; for now we are resetting XP

  ld b, 10
  ld a, [PLAYER_XP_TARGET]
  add a, b
  ld [PLAYER_XP_TARGET], a ; next level is 10 harder

  ; update state
  ld a, [PLAYER_ATT]
  inc a
  ld [PLAYER_ATT], a

  ld a, [PLAYER_DEF]
  inc a
  ld [PLAYER_DEF], a

  ld a, [PLAYER_MAX_HP]
  add a, 4
  ld [PLAYER_MAX_HP], a

.doneLevel

  call turnOffWindow
  call resetInput
  call toOverworldGameState
  call undrawEncounterSprite

  ret


; @TODO ideall I would like no random encounters
; on tiles with AutoEvents, so that we don't get
; the random encounter on a village tile or stairs
; @return c - random encounter!
checkForRandomEncounter:
  ; get the random number
  ld a, [Rand]
  ; compare it to 128 (50/50)
  cp a, 256 / 4
  jr nc, .done ; no random encounter

  ; c is set

  ; detected a random enconter, but we might abort
  ; if it is an auto event tile
  call getNextWorldPosition
  call checkForAutoEvent
  jr nz, .eventFound

  ; ensure c is set
  ld a, 0
  ld b, 1
  cp a, b

  ret

.eventFound
  ; clear c
  cp a
.done

  ret

/** wandering the overworld */
overworldGameState:
  ; -- INPUT PHASE JUST RECORDS ACTIONS --

  call readInput

  ; if there is not input this frame, skip thinking
  call getInput
  and a
  ret z

  ; record intents
  call doPlayerMovement

  ; -- UPDATE STATE BASED ON ACTIONS --

  ; doPlayerMovement puts the requested move somwhere for us
  ; we can use that to get the callback we need to respond to
  ; the movement

  call handlePlayerMovement
  call nz, resetInput ; if there was no move (ie collision, or random encounter)

  ret

/** watching the game over happen */
gameOverGameState:
  call waitForVBlank

  ; hide the player
  ld a, LCDCF_ON|LCDCF_BG8000|LCDCF_BG9800|LCDCF_BGON|LCDCF_OBJ8|LCDCF_OBJOFF
  ld [rLCDC], a

  ; fade out the screen slowly
  call count4In4Seconds

  ld hl, WhiteOutPalettes
  push af

  ; add a to hl
  add l
	ld l, a
	adc h
	sub l
	ld h, a

  ; get the next palette
  ld a, [hl]

  ld [rBGP], a
  ld [rOBP0], a
  
  pop af
  cp a, 3 ; are we done fading out?
  jp nz, .continue

  ld a, 0
  ld [rIE], a
  halt ; forever

.continue

  ret

WhiteOutPalettes:
  db %11100100
  db %10010000
  db %01000000
  db %00000000

FadeOutPalettes:
  db %11100100
  db %10010000
  db %01000000
  db %00000000

FadeInPalettes:
  db %00000000
  db %01000000
  db %10010000
  db %11100100

toExitState:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(exitState)
  ld [hl+], a
  ld a, HIGH(exitState)
  ld [hl], a
  ret

toEnterState:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(enterState)
  ld [hl+], a
  ld a, HIGH(enterState)
  ld [hl], a
  ret

toOverworldGameState:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(overworldGameState)
  ld [hl+], a
  ld a, HIGH(overworldGameState)
  ld [hl], a
  ret

toRandomEncounterGameState:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(randomEncounterGameState)
  ld [hl+], a
  ld a, HIGH(randomEncounterGameState)
  ld [hl], a

  call turnOnWindow

  ; initialize the encounter
  ld a, 10
  ld [ENCOUNTER_CURRENT_HP], a
  ld [ENCOUNTER_NEXT_CURRENT_HP], a
  ld [ENCOUNTER_MAX_HP], a

  ld a, 2
  ld [ENCOUNTER_DEF], a
  ld a, 6
  ld [ENCOUNTER_ATT], a
  ld a, 5
  ld [ENCOUNTER_XP], a

  ; init BCDs
  ld hl, ENCOUNTER_CURRENT_HP
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [ENCOUNTER_CURRENT_HP_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [ENCOUNTER_CURRENT_HP_BCD + 1], a

  call initEncounterSprite
  call drawEncounterSprite
  call resetPlayerMovement

  ret

fadeBackgroundPalette:
  ret

initEncounterSprite:
  ; init encounter sprite tiles
  ld hl, ENCOUNTER_SPRITE_TILES
  ld a, 156
  ld [hl+], a
  ld a, 157
  ld [hl+], a
  ld a, 158
  ld [hl+], a
  ld a, 159
  ld [hl+], a

  ret

undrawEncounterSprite:
  ld a, 0
  ld hl, Sprites + (10 * 4)
  ld [hl+], a
  ld [hl+], a
  ld [hl+], a
  ld [hl], a
  ld hl, Sprites + (27 * 4)
  ld [hl+], a
  ld [hl+], a
  ld [hl+], a
  ld [hl], a
  ld hl, Sprites + (26 * 4)
  ld [hl+], a
  ld [hl+], a
  ld [hl+], a
  ld [hl], a
  ld hl, Sprites + (25 * 4)
  ld [hl+], a
  ld [hl+], a
  ld [hl+], a
  ld [hl], a

  ret

drawEncounterSprite:
  ; draw the sprite (this should go in main)
  ld hl, PLAYER_NEXT_WORLD_Y
  ld de, CAMERA_WORLD_Y
  call pixelDistance
  ld b, a

  ld hl, PLAYER_NEXT_WORLD_X
  ld de, CAMERA_WORLD_X
  call pixelDistance
  ld c, a

  ld hl, ENCOUNTER_SPRITE_TILES

  ; write 4 bytes for each tile
  ld de, Sprites + (10 * 4) ; 8 sprites for the two animation frames, each 4 bytes per sprite
  ld a, 16 - 1 ; offset for niceness
  add a, b ; monster position y
  ld [de], a
  inc de
  ld a, 8
  add a, c ; monster position x
  ld [de], a
  inc de

  ld a, [hl] ; get the tile
  ld [de], a ; draw the tile
  inc de

  ld a, 0 ; attr
  ld [de], a
  inc de

  inc hl

  ; write 4 bytes for each tile
  ld de, Sprites + (27 * 4) ; 8 sprites for the two animation frames, each 4 bytes per sprite
  ld a, 16 + 8 - 1 ; offset for niceness
  add a, b ; monster position y
  ld [de], a
  inc de
  ld a, 8
  add a, c ; monster position x
  ld [de], a
  inc de

  ld a, [hl] ; get the tile
  ld [de], a ; draw the tile
  inc de

  ld a, 0 ; attr
  ld [de], a
  inc de

  inc hl

  ; write 4 bytes for each tile
  ld de, Sprites + (26 * 4) ; 8 sprites for the two animation frames, each 4 bytes per sprite
  ld a, 16 - 1 ; offset for niceness
  add a, b ; monster position y
  ld [de], a
  inc de
  ld a, 8 + 8
  add a, c ; monster position x
  ld [de], a
  inc de

  ld a, [hl] ; get the tile
  ld [de], a ; draw the tile
  inc de

  ld a, 0 ; attr
  ld [de], a
  inc de

  inc hl

  ; write 4 bytes for each tile
  ld de, Sprites + (25 * 4) ; 8 sprites for the two animation frames, each 4 bytes per sprite
  ld a, 16 + 8 - 1 ; offset for niceness
  add a, b ; monster position y
  ld [de], a
  inc de
  ld a, 8 + 8
  add a, c ; monster position x
  ld [de], a
  inc de

  ld a, [hl] ; get the tile
  ld [de], a ; draw the tile
  inc de

  ld a, 0 ; attr
  ld [de], a
  inc de

  inc hl

  ret


toGameOverState:
  ; set the game state to "GAME_OVER"
  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(gameOverGameState)
  ld [hl+], a
  ld a, HIGH(gameOverGameState)
  ld [hl], a
  ret

; @return hl - the handler for the current game state
getGameStateSubroutine:
  ld hl, GAME_STATE_LOW_BYTE
  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ret

drawRandomEncounterWindow:
  ld a, 144 + 10 ; H
  ld [_SCRN1 + 34], a

  ld a, 144 + 11 ; P
  ld [_SCRN1 + 35], a

  ld a, 0 ; _
  ld [_SCRN1 + 36], a

 ; draw each of those into VRAM
 /* just two digits for now
  ld a, [PLAYER_CURRENT_HP_BCD]
  and %00001111
  add 144
  ld [_SCRN1 + 35], a
  */

  ; draw each of those into VRAM
  ld a, [PLAYER_CURRENT_HP_BCD + 1]
  and %11110000
  srl a
  srl a
  srl a
  srl a
  add 144
  ld [_SCRN1 + 37], a

  ; draw each of those into VRAM
  ld a, [PLAYER_CURRENT_HP_BCD + 1]
  and %00001111
  add 144
  ld [_SCRN1 + 38], a

  ; monster
  /* just two digits for now
  ld a, [ENCOUNTER_CURRENT_HP_BCD]
  and %00001111
  add 144
  ld [_SCRN1 + 39], a
  */

  ld a, 144 + 10 ; H
  ld [_SCRN1 + 47], a

  ld a, 144 + 11 ; P
  ld [_SCRN1 + 48], a

  ld a, 0 ; _
  ld [_SCRN1 + 49], a

  ; draw each of those into VRAM
  ld a, [ENCOUNTER_CURRENT_HP_BCD + 1]
  and %11110000
  srl a
  srl a
  srl a
  srl a
  add 144
  ld [_SCRN1 + 50], a

  ; draw each of those into VRAM
  ld a, [ENCOUNTER_CURRENT_HP_BCD + 1]
  and %00001111
  add 144
  ld [_SCRN1 + 51], a


  ret

ENDC