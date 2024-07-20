IF !DEF(RANDOM_ENCOUNTER_GAME_STATE_INC)
RANDOM_ENCOUNTER_GAME_STATE_INC = 1

SECTION "ENCOUNTER_STATE", WRAM0

/** check encounters will decrement this
 * and when it hits zero we have an encounter 
 * this is to prevent the immediate encounter */
ENCOUNTER_HITS: ds 1

/** this gets populated from the encounter
 * stats */
ENCOUNTER_MAX_HP: ds 1
ENCOUNTER_CURRENT_HP: ds 1
ENCOUNTER_CURRENT_SUB_HP: ds 1
ENCOUNTER_CURRENT_HP_BCD: ds 2
ENCOUNTER_NEXT_CURRENT_HP: ds 1
ENCOUNTER_XP: ds 1
ENCOUNTER_ATT: ds 1
ENCOUNTER_DEF: ds 1

; a fake event we call when the player retreats
; to move them back to the boat
RETREAT_TRANSPORT_EVENT: ds 7 ; EVENT_SIZE

/** holds the sprite tiles we intend 
 * to render */
CURRENT_ENCOUNTER_SPRITE_TILES: ds 4

SECTION "RandomEncounterGameState", ROM0

populateRetreatEvent:
  ; they are running away so send them to the boat
  ld hl, RETREAT_TRANSPORT_EVENT
  ld a, TRANSPORT_EVENT
  ld [hl+], a
  ld a, [PLAYER_WORLD_Y]
  ld [hl+], a
  ld a, [PLAYER_WORLD_X]
  ld [hl+], a
  ld a, HIGH(Overworld)
  ld [hl+], a
  ld a, LOW(Overworld)
  ld [hl+], a
  ld a, [BOAT_WORLD_Y]
  ld [hl+], a
  ld a, [BOAT_WORLD_X]
  ld [hl+], a
  ret

/** we could use "away" for retreat 
 * but it didn't feel amazing? felt too risky 
 * maybe if there was a "confirm" like require
 * one press to prime and one press to execute 
 **/
getRetreatButton:
  call getAwayButton
  ret

/** we could use "away" for retreat 
 * but it didn't feel amazing? felt too risky 
 * maybe if there was a "confirm" like require
 * one press to prime and one press to execute 
 **/
getAttackButton:
  call getTowardsButton
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

  ; first check for "run away"
  ; if the player is running away, send them to the boat

  call getRetreatButton
  ld b, a

  ; if retreat button was down last frame then we won't do anything
  ; regardless
  ld a, [_PREV_PAD]
  and a, b
  jr nz, .noRetreat ; if B button is still DOWN return

  ; if retreat button was up, and they pressed B, then retreat
  ld a, [_PAD]
  and a, b
  jr z, .noRetreat

  ; tidy up
  ; @TODO this should send you to the boat state
  ; the full heal should happen there
  call playerFullHeal
  call fromRandomEncounterGameState
  call initEventEncounterTable ; reset to null
  call populateRetreatEvent

  ld de, RETREAT_TRANSPORT_EVENT
  call handleTransportEvent

  ret

.noRetreat
  ; then check for attack

  call getAttackButton
  ld b, a

  ; if attack button was down last frame then we won't do anything
  ; regardless
  ld a, [_PREV_PAD]
  and a, b
  jr nz, .noInput ; if A button is still DOWN return

  ; if attack button was up, and they pressed A, then we have
  ; disco party time
  ld a, [_PAD]
  and a, b
  jr z, .noInput

  ; there was an A press that started this frame
  call resolveAttack
  call resetInput

  ; the encounter continues
  ret

.noInput
  ld a, 1
  or a ; nz indicates nothing happened
  ret

.playerDead
  call fromRandomEncounterGameState
  call init ; ha, if this works
  ret

.monsterDead
  call applyXP

  ; we only need to redraw everything if they win
  ; if they flee we do a full transition
  call turnOffLCD
  call drawFreshNewMap
  call turnOnLCD

.doneLevel

  ; transition back to whatever state we were in
  call fromRandomEncounterGameState

  ret

drawEncounterWindow:
  call ENCOUNTER_STATUS_DRAW_TEMPLATE

  call disabledEncounterTemplateDraw

  ret

resolveAttack:
  ; so apply player and monster damage
  ; do player damage first and bail if the enemy dies

  call calculatePlayerDamage

  ld b, a
  ld a, [ENCOUNTER_CURRENT_HP]
  call minAB
  sub a, b ; next = hp - damage

  ld [ENCOUNTER_NEXT_CURRENT_HP], a

  call calculateEncounterDamage

  ld b, a
  ld a, [PLAYER_CURRENT_HP]
  call minAB
  sub a, b ; next = hp - damage

  ld [PLAYER_NEXT_CURRENT_HP], a

  ret

; adds a random amount to a up to half of a
; @param a - whole number
; @return a - some value with 1 fewer bits than a
; like if you give it a 5 bit number it gives you a random 4 bit number
; so for a lot of numbers in a given bit range that is going to be roughly
; less than half
twiddle:
  ; no need to work if incoming damage is zero
  cp a, 0
  ret z

  ld b, a
  ld a, 0

  ; build up a byte
  ; less than b/2 but with as
  ; many bits as possible set
  ; eg 00110101 -> 00011111
  srl b
  .loop
    or a, b
    srl b
    jr nz, .loop

  ; and with rand to twiddle some bits
  ld hl, Rand
  and a, [hl]

  ret

/** damage is always 
 * 
 * examples
 * att def dm
 * 4   2   1 - 3
 * 5   2   2 - 4
 * 6   3   2 - 4
 * 9   3   3 - 9 
 * 4   0   2 - 6*/
; @param a - ATT
; @param b - DEF
; @return a - damage
calculateDamage:
  ; this will fail if a - b > 127
  ; because wholeA will call the result negative
  sub a, b ; damage = att - def
  call wholeA

  cp a, 0
  jr .nonZero
  ld a, 1 ; we never do zero damage
  ret
.nonZero

  ; a has incoming damage
  ; now twiddle it
  ld c, a
  call twiddle
  add a, c

  ret

; @return a - damage
calculateEncounterDamage:
  ld a, [PLAYER_DEF]
  ld b, a
  ld a, [ENCOUNTER_ATT]

  call calculateDamage

  ret

; @return a - damage
calculatePlayerDamage:
  ld a, [ENCOUNTER_DEF]
  ld b, a
  ld a, [PLAYER_ATT]

  call calculateDamage

  ret

applyXP: 
  ld a, [ENCOUNTER_XP]
  ld b, a
  ld a, [PLAYER_XP]
  add a, b
  ld [PLAYER_XP], a

  ; we don't want to check for level until the xp has animated
  ; we don't want to exit this state until the xp has animated

  ; check for level
  ld a, [PLAYER_XP_TARGET]
  ld b, a
  ld a, [PLAYER_XP]
  cp a, b
  ret c ; xp < target => done

  ; apply level
  ld a, [PLAYER_XP_TARGET]
  ld b, a
  ld a, [PLAYER_XP]
  sub a, b
  ld [PLAYER_XP], a

  ; calculate next level target xp
  ld b, PLAYER_XP_PER_LEVEL
  ld a, [PLAYER_XP_TARGET]
  add a, b
  ld [PLAYER_XP_TARGET], a 

  ; update BCD
  ld hl, PLAYER_XP_TARGET
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [PLAYER_XP_TARGET_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [PLAYER_XP_TARGET_BCD + 1], a

  ; update stats

  ; hp goes up (hp / 16) + ([0, 7])
  ld a, [PLAYER_MAX_HP]
  srl a
  srl a
  srl a
  srl a ; divide by 16
  ld b, a
  ld a, [Rand]
  and a, %00000111
  add a, b
  ld b, a

  ld a, [PLAYER_MAX_HP]
  add a, b
  ld [PLAYER_MAX_HP], a

  ; att and def goes up 0 or 1
  ld a, [Rand]
  and a, %00000001
  ld b, a

  ld a, [PLAYER_ATT]
  add a, b
  ld [PLAYER_ATT], a

  ld a, [Rand]
  and a, %00000010
  sra a
  ld b, a

  ld a, [PLAYER_DEF]
  add a, b
  ; NO DEF INCREASE FOR NOW
  ; open ended it is too strong
  ; ld [PLAYER_DEF], a

  ; done updating

  call playerFullHeal

  ; update BCD
  ld hl, PLAYER_MAX_HP
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [PLAYER_MAX_HP_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [PLAYER_MAX_HP_BCD + 1], a

  ret

OVERWORLD_ENCOUNTER_THRESHOLD EQU 2
INTERIOR_ENCOUNTER_THRESHOLD EQU 4

initEncounterSystem:
  ld hl, ENCOUNTER_HITS
  ld [hl], OVERWORLD_ENCOUNTER_THRESHOLD

  ret

resetEncounterHits:
  ; reset the hits
  call getEncounterHitsThreshold
  ld [ENCOUNTER_HITS], a

  ret

getEncounterHitsThreshold:
  call getCurrentMap
  call isOverworld
  jr nz, .overworld

  ld a, INTERIOR_ENCOUNTER_THRESHOLD
  ret

.overworld
  ld a, OVERWORLD_ENCOUNTER_THRESHOLD

  ret

; @return c - random encounter!
checkForRandomEncounter:
  call getCurrentMap
  call isSafeArea
  jr nz, .abortEncounter

  ; get the random number
  ld a, [Rand]
  ; compare it to 128 (50/50)
  and a, %00000001 ; 0 - 3
  cp a, 1 ; 1/2 chance
  jr nc, .done ; no random encounter

  ; count down to encounter
  ld a, [ENCOUNTER_HITS]
  dec a
  ld [ENCOUNTER_HITS], a

  cp a, 1
  jr nc, .done ; if we have less than 2 hits we're done

  call resetEncounterHits

  ; detected a random enconter, but we might abort
  ; if it is an auto event tile
  call getNextWorldPosition

  /** safe tiles like bridge or boat */
  call isTileSafe
  jr nz, .abortEncounter

  /** auto events also cancel random encounters 
   * @TODO this is because of the bridge problem
   * there is an auto event on either side of the
   * bridge and when crossing back over, it is
   * possible to encounter an enemy from the wrong
   * side of the bridge. Tried to fix this with
   * isTileSafe above but that just changes the 
   * problem */
  call checkForAutoEvent
  jr nz, .abortEncounter

  ; ensure c is set
  ld a, 0
  ld b, 1
  cp a, b

  ret

.abortEncounter
  ; clear c
  cp a
.done

  ret

initEncounterSprite:
  ; get the current encounter sprite
  call getCurrentEncounterSprite

  ; init encounter sprite tiles
  ; this will be used later to draw the sprite
  ld hl, CURRENT_ENCOUNTER_SPRITE_TILES
  ld [hl+], a
  inc a
  ld [hl+], a
  inc a
  ld [hl+], a
  inc a
  ld [hl+], a

  ret

undrawEncounterSprite:
  ld a, ENCOUNTER_SPRITE_INDEX
  call undrawSprite

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

  ld hl, CURRENT_ENCOUNTER_SPRITE_TILES
  ld a, [hl]
  ld d, ENCOUNTER_SPRITE_INDEX
  call drawSprite

  ret

WINDOW_FRAME_TILE_BASE EQU 80
WINDOW_FRAME_TOP EQU WINDOW_FRAME_TILE_BASE + 0
WINDOW_FRAME_BOTTOM EQU WINDOW_FRAME_TILE_BASE + 1
WINDOW_FRAME_BLANK EQU 0

MONSTER_STATS_PANEL_TOP EQU _SCRN0 + 0
MONSTER_STATS_PANEL_BOTTOM EQU _SCRN0 + 128

PLAYER_STATS_PANEL_TOP EQU _SCRN0 + 416
PLAYER_STATS_PANEL_BODY EQU _SCRN0 + 448

drawEncounterWindowFrame:
  ; draw MONSTER encounter stats panel
  ld hl, MONSTER_STATS_PANEL_TOP
  ld a, WINDOW_FRAME_BLANK
  ld b, SCRN_WIDTH
  ld c, 4 ; draw 4 blank rows of window
.loop1
  ld [hl+], a
  dec b
  jr nz, .loop1

  dec c
  jr z, .done1
  ld b, SCRN_WIDTH
  ld de, 12
  add hl, de

  jr .loop1
.done1

  ; draw bottom border of window
  ld hl, MONSTER_STATS_PANEL_BOTTOM
  ld a, WINDOW_FRAME_BOTTOM
  ld b, SCRN_WIDTH
.loop2
  ld [hl+], a
  dec b
  jr nz, .loop2

  ; draw HERO encounter stats panel
  ld hl, PLAYER_STATS_PANEL_BODY
  ld a, WINDOW_FRAME_BLANK
  ld b, SCRN_WIDTH
  ld c, 4 ; draw 4 blank rows of window
.loop3
  ld [hl+], a
  dec b
  jr nz, .loop3

  dec c
  jr z, .done2
  ld b, SCRN_WIDTH
  ld de, 12
  add hl, de

  jr .loop3
.done2

  ; draw top border of window
  ld hl, PLAYER_STATS_PANEL_TOP
  ld a, WINDOW_FRAME_TOP
  ld b, SCRN_WIDTH
.loop4
  ld [hl+], a
  dec b
  jr nz, .loop4

  ret

ENCOUNTER_WINDOW_TILE_BASE EQU 64
PLAYER_STATS_HP EQU ENCOUNTER_WINDOW_TILE_BASE + 10
PLAYER_STATS_SPACE EQU 0
PLAYER_STATS_XP EQU ENCOUNTER_WINDOW_TILE_BASE + 24
PLAYER_STATS_SLASH EQU ENCOUNTER_WINDOW_TILE_BASE + 25

ENCOUNTER_WINDOW_TEXT_BASE EQU _SCRN0 + 449
ENCOUNTER_WINDOW_TEXT_ROW_ONE EQU ENCOUNTER_WINDOW_TEXT_BASE
ENCOUNTER_WINDOW_TEXT_ROW_TWO EQU ENCOUNTER_WINDOW_TEXT_ROW_ONE + 32
ENCOUNTER_WINDOW_TEXT_ROW_THREE EQU ENCOUNTER_WINDOW_TEXT_ROW_TWO + 32

; @pre b - should start at 0
; @param de - template
; @param hl - BCD to render
; @return b - digits we rendered
renderBCD:
  ; convert BCD to digit tile by using
  ; bcd as offset into window tiles

  ; draw each of those into VRAM
.bcdHundreds
  ld a, [hl+]
  and %00001111
  cp a, 0
  jr z, .bcdTensNoHundreds
  add ENCOUNTER_WINDOW_TILE_BASE

  call fillTileSlot
  inc b

.bcdTensAfterHundreds
  ld a, [hl]
  and %11110000
  srl a
  srl a
  srl a
  srl a
  add ENCOUNTER_WINDOW_TILE_BASE

  call fillTileSlot
  inc b
jr .bcdOnes

  ; draw each of those into VRAM
.bcdTensNoHundreds
  ld a, [hl]
  and %11110000
  srl a
  srl a
  srl a
  srl a
  cp a, 0
  jr z, .bcdOnes
  add ENCOUNTER_WINDOW_TILE_BASE

  call fillTileSlot
  inc b

.bcdOnes
  ; draw each of those into VRAM
  ld a, [hl]
  and %00001111
  add ENCOUNTER_WINDOW_TILE_BASE

  call fillTileSlot
  inc b
  ret

updateRandomEncounterWindow:
  call enableEncounterStatusTemplateDraw
  call resetEncounterStatusTemplateDrawPointer
  call getEncounterStatusTemplatePointer

  ; the template is in order
  ; so we have to draw all the text in order
  ; starting with HP 20/20     HP  etc...

  ld a, PLAYER_STATS_HP
  call fillTileSlot
  ld a, PLAYER_STATS_SPACE
  call fillTileSlot

  ; potentially we could blank the template
  ; each frame

  ; convert BCD to digit tile by using
  ; bcd as offset into window tiles

  ; draw each of those into VRAM
  ld b, 0
  ld hl, PLAYER_CURRENT_HP_BCD
  call renderBCD

  ; slash
  ld a, PLAYER_STATS_SLASH
  call fillTileSlot
  inc b

  ld hl, PLAYER_MAX_HP_BCD
  call renderBCD

  ld a, 11
  sub a, b ; sub off what we wrote
  or a
  jr z, .donePlayerHP ; nothing to draw
  ld b, a ; remaining spaces to draw

  ; decrement through the white space
.loopPlayerHP
  ld a, 0
  call fillTileSlot
  dec b
  jr nz, .loopPlayerHP
.donePlayerHP

  ; now we should be ready to draw monster HP

  ; MONSTER HP

  ld a, PLAYER_STATS_HP
  call fillTileSlot
  ld a, PLAYER_STATS_SPACE
  call fillTileSlot

  ld b, 0
  ld hl, ENCOUNTER_CURRENT_HP_BCD
  call renderBCD

  ld a, 3
  sub a, b
  or a
  jr z, .doneEncounterHP ; nothing to draw
  ld b, a ; white spaces to draw

  ; decrement through the white space
.loopEncounterHP
  ld a, 0
  call fillTileSlot
  dec b
  jr nz, .loopEncounterHP
.doneEncounterHP

  ; XP

  ld a, PLAYER_STATS_XP
  call fillTileSlot
  ld a, PLAYER_STATS_SPACE
  call fillTileSlot

  ld b, 0
  ld hl, PLAYER_XP_BCD
  call renderBCD

  ; slash
  ld a, PLAYER_STATS_SLASH
  call fillTileSlot
  inc b

  ld hl, PLAYER_XP_TARGET_BCD
  call renderBCD

  ld a, 7
  sub a, b
  or a
  jr z, .doneXP ; nothing to draw
  ld b, a ; number of whitespace to draw

  ; decrement through the white space
.loopXP
  ld a, 0
  call fillTileSlot
  dec b
  jr nz, .loopXP
.doneXP

  call resetEncounterStatusTemplateDrawPointer

  ret

randomEncounterGameStateDraw:
  ; we are no longer using the window
  ; for now we are just redrawing everything in VRAM
  ; but later we might use the window again if we can
  ; figure out a nice way to draw the overworld band
  ; call turnOnWindow
  call drawEncounterWindow

  ret

randomEncounterGameStateUpdate:
  call updatePlayerStats
  call updateMonsterStats

  /** @TODO this updates everything every time
   * but we can update only as needed 
   * ie if the above has changed? */
  call updateRandomEncounterWindow

  ret

; @return z - yes, we are in a steady state
randomEncounterGameStateIsSteady:
  ; PLAYER STATE
  ld a, [PLAYER_NEXT_CURRENT_HP]
  ld b, a
  ld a, [PLAYER_CURRENT_HP]
  cp a, b
  ret nz

  ; ENCOUNTER STATE
  ld a, [ENCOUNTER_NEXT_CURRENT_HP]
  ld b, a
  ld a, [ENCOUNTER_CURRENT_HP]
  cp a, b
  ret nz

  ret

initEncounter:
  ; get the random number
  ld a, [Rand]
  ; mod ENCOUNTER_TABLE_LENGTH
  and a, ENCOUNTER_TABLE_MASK

  call setCurrentEncounterIndex

  ; get the monster
  call getCurrentEncounterStats

  ; now hl has the encounter stats

  ; initialize the encounter
  ld a, [hl+]
  ld [ENCOUNTER_CURRENT_HP], a
  ld [ENCOUNTER_NEXT_CURRENT_HP], a
  ld [ENCOUNTER_MAX_HP], a

  ld a, [hl+]
  ld [ENCOUNTER_ATT], a
  ld a, [hl+]
  ld [ENCOUNTER_DEF], a
  ld a, [hl+]
  ld [ENCOUNTER_XP], a

  ; should this data also be in the encounter stats?
  call initEncounterSprite

  ; init BCDs
  ld hl, ENCOUNTER_CURRENT_HP
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [ENCOUNTER_CURRENT_HP_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [ENCOUNTER_CURRENT_HP_BCD + 1], a

  ret

fromRandomEncounterGameState:
  call turnOffWindow
  call resetInput
  call disabledEncounterTemplateDraw
  call undrawEncounterSprite
  ; we don't know which state to return to
  ; so we do the PrevTransition
  call performPrevTransition

  ret

toRandomEncounterGameState:
  ; back up previous game state
  call bookmarkGameState

  ld hl, GAME_STATE_LOW_BYTE
  ld a, LOW(randomEncounterGameState)
  ld [hl+], a
  ld a, HIGH(randomEncounterGameState)
  ld [hl], a

  ld hl, GAME_STATE_DRAW_LOW_BYTE
  ld a, LOW(randomEncounterGameStateDraw)
  ld [hl+], a
  ld a, HIGH(randomEncounterGameStateDraw)
  ld [hl], a

  ld hl, GAME_STATE_UPDATE_LOW_BYTE
  ld a, LOW(randomEncounterGameStateUpdate)
  ld [hl+], a
  ld a, HIGH(randomEncounterGameStateUpdate)
  ld [hl], a

  ld hl, GAME_STATE_IS_STEADY_LOW_BYTE
  ld a, LOW(randomEncounterGameStateIsSteady)
  ld [hl+], a
  ld a, HIGH(randomEncounterGameStateIsSteady)
  ld [hl], a

  ld hl, GAME_STATE_TRANSITION_FN_LOW_BYTE
  ld a, LOW(toRandomEncounterGameState)
  ld [hl+], a
  ld a, HIGH(toRandomEncounterGameState)
  ld [hl], a

  call initEncounter
  /** @TODO move this to drawRandomEncounterState 
   * well actually it does not manipulate VRAM so
   * move it to update */

  
  ; use _SCRN0 instead of window
  ; just reset scroll position
  ; redraw the scene
  ; draw the UI over top
  ; when encounter is done go back to previous way
  call turnOffLCD
  call drawFreshNewMap

  call drawEncounterWindowFrame

  ; position the window for encounter UI
  ld a, 14 * (META_TILE_ROWS_PER_SCRN - 1) - 8
  ld [rWY], a

  ld a, 7
  ld [rWX], a

  ; set the compare to that y value for interupts
  ld a, [rWY]
  ld [rLYC], a
  call turnOnLCD

  ; initialize the template
  call clearEncounterStatusTemplate

  ld b, ENCOUNTER_STATUS_DRAW_TEMPLATE_SIZE
  ld hl, ENCOUNTER_STATUS_DRAW_TEMPLATE
  call makeVRAMTemplate
  call prefillVRAMAddresses

  ; dabble all the latest stats
  call updatePlayerStats
  call updateMonsterStats
  call updateRandomEncounterWindow

  call drawEncounterSprite

  ret

copyOverworldBand:
  ; SO!
  ; we need to copy a band of the viewport
  ; rSCY tells us the y coord in pixels
  ; rSCX tells us where to start copying
  ; then we need to copy 20 tiles and mod around
  ; and do this for 8 rows

  ; if rSCY 40, rSCX E0 that's 64, 224
  ; divide by 8 we get 8, 28
  ; so we start at that tile
  ; increment x, mod 32
  ; so we copy 28, 29, 30, 31, 0, 1, 2, ...

  ; jump down 1 row after each 20 tiles

  ; we still copy the window straight though with no wrap
  ; so start at $9CA0 and go 20 tiles at a time
 
  ret

updatePlayerStats:
  ld hl, PLAYER_XP
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [PLAYER_XP_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [PLAYER_XP_BCD + 1], a

  ; HP
  ld a, [PLAYER_NEXT_CURRENT_HP]
  ld b, a
  ld a, [PLAYER_CURRENT_HP]
  ld c, a
  push bc
  ld hl, PLAYER_CURRENT_HP
  ld [hl], b ; full update instead of calling updateStat
  pop bc

  ; if new is same as old do not double dabble
  ld a, [PLAYER_CURRENT_HP]
  cp a, c
  ret z

  ld hl, PLAYER_CURRENT_HP
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [PLAYER_CURRENT_HP_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [PLAYER_CURRENT_HP_BCD + 1], a

  ret

updateMonsterStats: 
  ld a, [ENCOUNTER_NEXT_CURRENT_HP]
  ld b, a
  ld a, [ENCOUNTER_CURRENT_HP]
  ld c, a
  push bc
  ld hl, ENCOUNTER_CURRENT_HP
  ld [hl], b ; full update instead of calling updateStat
  pop bc

  ; if new is same as old do not double dabble
  ld a, [ENCOUNTER_CURRENT_HP]
  cp a, c
  ret z

  ld hl, ENCOUNTER_CURRENT_HP
  call doubleDabble

  ld a, [DoubleDabbleByte2]
  ld [ENCOUNTER_CURRENT_HP_BCD], a
  ld a, [DoubleDabbleByte1]
  ld [ENCOUNTER_CURRENT_HP_BCD + 1], a

  ret

SECTION "_ENCOUNTER_STATUS_DRAW_TEMPLATE", ROM0

/** call this on entering a state that uses the template */
clearEncounterStatusTemplate:
  call resetEncounterStatusTemplateDrawPointer
  call getEncounterStatusTemplatePointer

  ld a, 0
  ld b, ONE_ROW_OF_TEXT * 3
.loop
  call fillTileSlot
  dec b
  jr nz, .loop
.done

  ret

prefillVRAMAddresses:
  ; we know where we want to draw each tile
  ; so we can pre-fill that part of the template

  ; it is the whole 3 rows of VRAM

  call getEncounterStatusTemplatePointer
  ld hl, ENCOUNTER_WINDOW_TEXT_ROW_ONE

  ld b, ONE_ROW_OF_TEXT
.loop1
  call fillVRAMAddressSlot
  inc hl
  dec b
  jr nz, .loop1
.done1

  ld hl, ENCOUNTER_WINDOW_TEXT_ROW_TWO
  ld b, ONE_ROW_OF_TEXT
.loop2
  call fillVRAMAddressSlot
  inc hl
  dec b
  jr nz, .loop2
.done2

  ld hl, ENCOUNTER_WINDOW_TEXT_ROW_THREE
  ld b, ONE_ROW_OF_TEXT
.loop3
  call fillVRAMAddressSlot
  inc hl
  dec b
  jr nz, .loop3
.done3

  ret

getEncounterStatusTemplatePointer:
  ld a, [ENCOUNTER_STATUS_DRAW_TEMPLATE_POINTER]
  ld d, a
  ld a, [ENCOUNTER_STATUS_DRAW_TEMPLATE_POINTER + 1]
  ld e, a

  ret

resetEncounterStatusTemplateDrawPointer:
  ld a, high(ENCOUNTER_STATUS_DRAW_TEMPLATE + 1)
  ld h, a
  ld [ENCOUNTER_STATUS_DRAW_TEMPLATE_POINTER], a
  ld a, low(ENCOUNTER_STATUS_DRAW_TEMPLATE + 1)
  ld l, a
  ld [ENCOUNTER_STATUS_DRAW_TEMPLATE_POINTER + 1], a
  ret

; sets the initial instructions to ret
disabledEncounterTemplateDraw:
  ld hl, ENCOUNTER_STATUS_DRAW_TEMPLATE
  ld [hl], RET_OP

  ret

  ; sets the initial instructions to nop
enableEncounterStatusTemplateDraw:
  ld hl, ENCOUNTER_STATUS_DRAW_TEMPLATE
  ld [hl], NO_OP_OP
  ret

; these guys get filled as we go
SECTION "ENCOUNTER_STATUS_DRAW_TEMPLATE", WRAM0

ONE_ROW_OF_TEXT EQU 18
ENCOUNTER_STATUS_DRAW_TEMPLATE_SIZE EQU 3 * 18

ENCOUNTER_STATUS_DRAW_TEMPLATE_POINTER: ds 2
ENCOUNTER_STATUS_DRAW_TEMPLATE: ds START_TEMPLATE + (TEMPLATE_SLOT * ENCOUNTER_STATUS_DRAW_TEMPLATE_SIZE) + END_TEMPLATE

ENDC