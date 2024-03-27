IF !DEF(RANDOM_ENCOUNTER_GAME_STATE_INC)
RANDOM_ENCOUNTER_GAME_STATE_INC = 1

SECTION "ENCOUNTER_STATE", WRAM0

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

  ; if B button was down last frame then we won't do anything
  ; regardless
  ld a, [_PREV_PAD]
  and a, B_BUTTON
  jr nz, .noRetreat ; if B button is still DOWN return

  ; if B button was up, and they pressed B, then retreat
  ld a, [_PAD]
  and a, B_BUTTON
  jr z, .noRetreat

  ; tidy up
  call playerFullHeal
  call fromRandomEncounterGameState
  call populateRetreatEvent

  ld de, RETREAT_TRANSPORT_EVENT
  call handleTransportEvent

  ret

.noRetreat
  ; then check for attack

  ; if A button was down last frame then we won't do anything
  ; regardless
  ld a, [_PREV_PAD]
  and a, A_BUTTON
  ret nz ; if A button is still DOWN return

  ; if A button was up, and they pressed A, then we have
  ; disco party time
  ld a, [_PAD]
  and a, A_BUTTON
  ret z

  ; there was an A press that started this frame
  ; so apply player and monster damage
  ; do player damage first and bail if the enemy dies

  call calculatePlayerDamage

  ld b, a
  ld a, [ENCOUNTER_CURRENT_HP]
  sub a, b ; next = hp - damage

  call wholeA
  ld [ENCOUNTER_NEXT_CURRENT_HP], a

  ld a, [ENCOUNTER_NEXT_CURRENT_HP]
  cp a, 0

  call calculateEncounterDamage

  ld b, a
  ld a, [PLAYER_CURRENT_HP]
  sub a, b ; next = hp - damage

  call wholeA
  ld [PLAYER_NEXT_CURRENT_HP], a

  call resetInput

  ; the encounter continues
  ret

.playerDead
  call turnOffWindow
  call resetInput
  call toGameOverState
  ret

.monsterDead
  call doLevelUp

.doneLevel

  ; transition back to whatever state we were in
  call fromRandomEncounterGameState

  ret

; adds a random amount to a up to half of a
; @param a - whole number
; @return a - a + RND
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
srl b ; start at b/2
.loop
  or a, b
  srl b
  jr nz, .loop

  ; and with rand to twiddle some bits
  ld hl, Rand
  and a, [hl]

  ret

; @param a - ATT
; @param b - DEF
; @return a - damage
calculateDamage:
  sub a, b ; damage = att - def
  call wholeA

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

doLevelUp: 
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
  ld a, 0
  ld [PLAYER_XP], a ; for now we are resetting XP

  ld b, PLAYER_XP_PER_LEVEL
  ld a, [PLAYER_XP_TARGET]
  add a, b
  ld [PLAYER_XP_TARGET], a 

  ; update stats

  ; hp goes up 0 - 7
  ld a, [Rand]
  and a, %00000111
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

  ld a, [PLAYER_DEF]
  add a, b
  ld [PLAYER_DEF], a

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

  ld hl, CURRENT_ENCOUNTER_SPRITE_TILES

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

WINDOW_FRAME_TILE_BASE EQU 80
WINDOW_FRAME_TL EQU WINDOW_FRAME_TILE_BASE + 0
WINDOW_FRAME_TR EQU WINDOW_FRAME_TILE_BASE + 2
WINDOW_FRAME_BL EQU WINDOW_FRAME_TILE_BASE + 5
WINDOW_FRAME_BR EQU WINDOW_FRAME_TILE_BASE + 7
WINDOW_FRAME_LEFT EQU WINDOW_FRAME_TILE_BASE + 3
WINDOW_FRAME_RIGHT EQU WINDOW_FRAME_TILE_BASE + 4
WINDOW_FRAME_TOP EQU WINDOW_FRAME_TILE_BASE + 1
WINDOW_FRAME_BOTTOM EQU WINDOW_FRAME_TILE_BASE + 6

ENCOUNTER_WINDOW_TL EQU _SCRN1 + 0
ENCOUNTER_WINDOW_TR EQU _SCRN1 + 19
ENCOUNTER_WINDOW_BL EQU _SCRN1 + 96 ; 64
ENCOUNTER_WINDOW_BR EQU _SCRN1 + 115 ; 83
ENCOUNTER_WINDOW_LEFT EQU _SCRN1 + 32
ENCOUNTER_WINDOW_RIGHT EQU _SCRN1 + 51
ENCOUNTER_WINDOW_TOP EQU _SCRN1 + 1
ENCOUNTER_WINDOW_BOTTOM EQU _SCRN1 + 96 + 1

drawEncounterWindowFrame:
  ; draw the frame around the window
  ld a, WINDOW_FRAME_TL
  ld [ENCOUNTER_WINDOW_TL], a
  ld a, WINDOW_FRAME_TR
  ld [ENCOUNTER_WINDOW_TR], a
  ld a, WINDOW_FRAME_BL
  ld [ENCOUNTER_WINDOW_BL], a
  ld a, WINDOW_FRAME_BR
  ld [ENCOUNTER_WINDOW_BR], a

  ld a, WINDOW_FRAME_LEFT
  ld [ENCOUNTER_WINDOW_LEFT], a
  ld [ENCOUNTER_WINDOW_LEFT + 32], a
  ld a, WINDOW_FRAME_RIGHT
  ld [ENCOUNTER_WINDOW_RIGHT], a
  ld [ENCOUNTER_WINDOW_RIGHT + 32], a

  ; draw top
  ld hl, ENCOUNTER_WINDOW_TOP
  ld a, WINDOW_FRAME_TOP
  ld b, SCRN_WIDTH - 2
.loop
  ld [hl+], a
  dec b
  jr nz, .loop

  ; draw bottom
  ld hl, ENCOUNTER_WINDOW_BOTTOM
  ld a, WINDOW_FRAME_BOTTOM
  ld b, SCRN_WIDTH - 2
.loop2
  ld [hl+], a
  dec b
  jr nz, .loop2

  ret

ENCOUNTER_WINDOW_TILE_BASE EQU 64
PLAYER_STATS_H EQU ENCOUNTER_WINDOW_TILE_BASE + 10
PLAYER_STATS_P EQU ENCOUNTER_WINDOW_TILE_BASE + 11
PLAYER_STATS_SPACE EQU 0
PLAYER_STATS_X EQU ENCOUNTER_WINDOW_TILE_BASE + 24

ENCOUNTER_WINDOW_TEXT_BASE EQU _SCRN1 + 33

drawRandomEncounterWindow:
  /**
   * @TODO now we have a method for printing texts 
   * to the screen so we could instead build up
   * the string to display during update and then
   * pass that to our text rendering subroutine
   * since it renders text into the window just like this
   */
  call drawEncounterWindowFrame

  ld a, PLAYER_STATS_H
  ld [ENCOUNTER_WINDOW_TEXT_BASE], a

  ld a, PLAYER_STATS_P
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 1], a

  ld a, PLAYER_STATS_SPACE
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 2], a

  ; convert BCD to digit tile by using
  ; bcd as offset into window tiles

  ; draw each of those into VRAM
  ld a, [PLAYER_CURRENT_HP_BCD]
  and %00001111
  add ENCOUNTER_WINDOW_TILE_BASE
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 3], a

  ; draw each of those into VRAM
  ld a, [PLAYER_CURRENT_HP_BCD + 1]
  and %11110000
  srl a
  srl a
  srl a
  srl a
  add ENCOUNTER_WINDOW_TILE_BASE
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 4], a

  ; draw each of those into VRAM
  ld a, [PLAYER_CURRENT_HP_BCD + 1]
  and %00001111
  add ENCOUNTER_WINDOW_TILE_BASE
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 5], a

  ; MONSTER HP

  ld a, PLAYER_STATS_H
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 12], a

  ld a, PLAYER_STATS_P
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 13], a

  ld a, PLAYER_STATS_SPACE
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 14], a

  ; draw each of those into VRAM
  ld a, [ENCOUNTER_CURRENT_HP_BCD]
  and %00001111
  add ENCOUNTER_WINDOW_TILE_BASE
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 15], a

  ; draw each of those into VRAM
  ld a, [ENCOUNTER_CURRENT_HP_BCD + 1]
  and %11110000
  srl a
  srl a
  srl a
  srl a
  add ENCOUNTER_WINDOW_TILE_BASE
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 16], a

  ; draw each of those into VRAM
  ld a, [ENCOUNTER_CURRENT_HP_BCD + 1]
  and %00001111
  add ENCOUNTER_WINDOW_TILE_BASE
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 17], a

  ; XP

  ld a, PLAYER_STATS_X
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 32], a

  ld a, PLAYER_STATS_P
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 33], a

  ld a, PLAYER_STATS_SPACE
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 34], a

  ; draw each of those into VRAM
  ld a, [PLAYER_XP_BCD]
  and %00001111
  add ENCOUNTER_WINDOW_TILE_BASE
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 35], a

  ; draw each of those into VRAM
  ld a, [PLAYER_XP_BCD + 1]
  and %11110000
  srl a
  srl a
  srl a
  srl a
  add ENCOUNTER_WINDOW_TILE_BASE
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 36], a

  ; draw each of those into VRAM
  ld a, [PLAYER_XP_BCD + 1]
  and %00001111
  add ENCOUNTER_WINDOW_TILE_BASE
  ld [ENCOUNTER_WINDOW_TEXT_BASE + 37], a

  ret

randomEncounterGameStateDraw:
  call turnOnWindow
  call drawRandomEncounterWindow

  ret

randomEncounterGameStateUpdate:
  call updatePlayerStats
  call updateMonsterStats

  ret

; @return z - yes, we are in a steady state
randomEncounterGameStateIsSteady:
  ; ENCOUNTER STATE
  ld a, [PLAYER_NEXT_CURRENT_HP]
  ld b, a
  ld a, [PLAYER_CURRENT_HP]
  cp a, b
  ret nz

  ret

initEncounter:
  ; get the random number
  ld a, [Rand]
  ; mod 16
  and a, %00001111

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
  call drawEncounterSprite

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

ENDC