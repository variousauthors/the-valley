IF !DEF(EVENTS_INC)
EVENTS_INC = 1

/** for now we will just have a table per map for auto events 
 * but later if we have too many events we can sub-divide the map
 * into quadrants, octants, etc... in order to limit our search 
 */

/** Event Types */
TRANSPORT_EVENT EQU 1

END_LIST EQU 0

MACRO EndList
  db 0
ENDM

/** 
 * AllocateTransportEvent y1, x1, high, low, y2, x2
 */
MACRO AllocateTransportEvent
  db TRANSPORT_EVENT, \1, \2, \3, \4, \5, \6 ; if you change this size, update the @DEPENDS
ENDM

SECTION "AUTO_EVENT_HANDLERS", ROM0, ALIGN[3]
AUTO_EVENT_HANDLERS:
  ; we need this no op because the auto event enum starts at 1
  AUTO_EVENT_HANDLERS.NO_OP: db 0, 0
  AUTO_EVENT_HANDLERS.TRANSPORT_EVENT: dw handleTransportEvent

; @DEPENDS on AllocateTransportEvent
EVENT_SIZE EQU 7

Section "Events", ROM0

; @param hl - the event
handleAutoEvent:
  push hl

  ; get the index of the event
  ld a, [hl]
  sla a ; double it because callback addresses are 2 bits

  ; get the callback address and call it
  ld hl, AUTO_EVENT_HANDLERS
  add a, l
  ld l, a

  ld a, [hl+]
  ld h, [hl]
  ld l, a

  ; get the event in de
	pop de

  call indirectCall

  ret

; @param de - the event
; @effect - terminal event, resets _PAD
handleTransportEvent:
  call resetInput
  call turnOffLCD

  ; get the target map in current map
  ; @DEPENDS on AllocateTransportEvent
  inc de
  inc de
  inc de

  ; set the current map
  ld hl, CURRENT_MAP_HIGH_BYTE
  ld a, [de]
  inc de
  ld [hl], a
  ld hl, CURRENT_MAP_LOW_BYTE
  ld a, [de]
  inc de
  ld [hl], a

  ; set the player's position
  ld hl, PLAYER_WORLD_Y
  ld a, [de]
  inc de
  ld [hl], a
  ld hl, PLAYER_NEXT_WORLD_Y
  ld [hl], a

  ld hl, PLAYER_WORLD_X
  ld a, [de]
  inc de
  ld [hl], a
  ld hl, PLAYER_NEXT_WORLD_X
  ld [hl], a

  ; set camera to that
  ld hl, CAMERA_WORLD_Y
  ld a, [PLAYER_WORLD_Y]
  sub a, META_TILES_TO_TOP_OF_SCRN
  ld [hl], a
  ld hl, CAMERA_NEXT_WORLD_Y
  ld [hl], a

  ld hl, CAMERA_WORLD_X
  ld a, [PLAYER_WORLD_X]
  sub a, META_TILES_TO_SCRN_LEFT
  ld [hl], a
  ld hl, CAMERA_NEXT_WORLD_X
  ld [hl], a

  ; record that initial world x, y
  ; so that we can later use it to
  ; set the screen to the camera position
  ld a, [CAMERA_WORLD_X]
  ld [CAMERA_INITIAL_WORLD_X], a
  ld a, [CAMERA_WORLD_Y]
  ld [CAMERA_INITIAL_WORLD_Y], a

  ; reset scroll
  ld a, 0
  ld [rSCX], a
  ld [rSCY], a

  call blankVRAM
  call getCurrentMap
  call drawFullScene
  call turnOnLCD

  ret

/** 
 * @return nz - event found
 * @return hl - the event
 * */
checkForAutoEvent:
  call getWorlPosition
  call getCurrentMap
  ; iterate over the event list for this map
  call getMapAutoEvents

.loop
  ; check if we are done
  ld a, [hl+]
  cp a, END_LIST
  jr z, .done ; z is set, no event

  push hl

  ; compare y
  ld a, [hl+]
  cp a, b
  jr nz, .next

  ; compare x
  ld a, [hl+]
  cp a, c
  jr nz, .next

  pop hl

  ; it's a hit :D
  ; decrement back down to the base
  dec hl

  or a, 1
  ret
  
.next  
  ; we pop here because we don't know if we've visited
  ; y, x or both
  pop hl
  ; inc to the next event
  ; @DEPENDS on AllocateTransportEvent
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl

  jr .loop

.done
  
  ret



ENDC
