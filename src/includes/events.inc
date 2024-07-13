IF !DEF(EVENTS_INC)
EVENTS_INC = 1

/** for now we will just have a table per map for auto events 
 * but later if we have too many events we can sub-divide the map
 * into quadrants, octants, etc... in order to limit our search 
 */

/** Event Types */
END_LIST EQU 0
TRANSPORT_EVENT EQU 1
GAME_OVER_EVENT EQU 2
FULL_HEAL_EVENT EQU 3
ENCOUNTER_TABLE_EVENT EQU 4
NPC_DIALOG_EVENT EQU 5

MACRO EndList
  db 0
ENDM

/** 
 * AllocateNPCDialogEvent y1, x1, high, low
 */
MACRO AllocateNPCDialogEvent
  db NPC_DIALOG_EVENT, \1, \2, \3, \4, 0, 0
ENDM

/** 
 * AllocateEncounterTableEvent y1, x1, high, low
 */
MACRO AllocateEncounterTableEvent
  db ENCOUNTER_TABLE_EVENT, \1, \2, \3, \4, 0, 0 ; if you change this size, update the @DEPENDS
ENDM

/** 
 * AllocateTransportEvent y1, x1, high, low, y2, x2
 */
MACRO AllocateTransportEvent
  db TRANSPORT_EVENT, \1, \2, \3, \4, \5, \6 ; if you change this size, update the @DEPENDS
ENDM

/** 
 * AllocateGameOverEvent y1, x1
 */
MACRO AllocateGameOverEvent
  db GAME_OVER_EVENT, \1, \2, 0, 0, 0, 0
ENDM

/** 
 * AllocateFullHealEvent y1, x1
 */
MACRO AllocateFullHealEvent
  db FULL_HEAL_EVENT, \1, \2, 0, 0, 0, 0
ENDM

SECTION "CURRENT_EVENT", WRAM0
CURRENT_EVENT: ds 2 ; a reference to an event

; really this is just "event handlers" it doesn't need to be
; only auto-events
SECTION "AUTO_EVENT_HANDLERS", ROM0, ALIGN[3]
AUTO_EVENT_HANDLERS:
  ; we need this no op because the auto event enum starts at 1
  AUTO_EVENT_HANDLERS.NO_OP: db 0, 0
  AUTO_EVENT_HANDLERS.TRANSPORT_EVENT: dw handleTransportEvent
  AUTO_EVENT_HANDLERS.GAME_OVER_EVENT: dw handleGameOverEvent
  AUTO_EVENT_HANDLERS.FULL_HEAL_EVENT: dw handleFullHealEvent
  AUTO_EVENT_HANDLERS.ENCOUNTER_TABLE_EVENT: dw handleEncounterTableEvent
  AUTO_EVENT_HANDLERS.NPC_DIALOG: dw handleNPCDialogEvent

; @DEPENDS on AllocateTransportEvent
EVENT_SIZE EQU 7

; @param de - the event pointer
setCurrentEvent:
  ld hl, CURRENT_EVENT
  ld a, d
  ld [hl+], a
  ld a, e
  ld [hl], a
  ret

; @return de - the event
getCurrentEvent:
  ld hl, CURRENT_EVENT
  ld a, [hl+]
  ld d, a
  ld a, [hl]
  ld e, a
  ret

getNextAutoEvent:
  ; @DEPENDS on AllocateTransportEvent
  ; advance EVENT_SIZE bytes
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl

  ret


Section "Events", ROM0

handleOutOfBoundsEvents:
  ; out of bounds event is just the first auto event
  call handleAutoEvent
  ret

; @param hl - the event
handleBumpEvent:
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

/** ATTENTION 
 * 
 * the game detects the end of the current "step" by checking whether
 * inputs have been cleared. Probably we should do this more explicitly
 * by setting "is process step" and then unsetting it. Alas.
 *
 * an event will loop forever if you do not call resetInput 
 */

; @param de - the event
handleTransportEvent:
  ; this is a terminal event, it kicks off a series of
  ; state changes
  call resetTime
  call resetInput

  ; we need to record the event
  call setCurrentEvent

  ; we want to undraw the boat when the fade out happens
  call undrawBoat
  call toExitState

  ret

doTransportRedraw:
  ; get the target map in current map
  ; @DEPENDS on AllocateTransportEvent
  inc de
  inc de
  inc de

  call initMap

  call turnOffLCD
  call drawFreshNewMap
  call turnOnLCD

  ret

handleGameOverEvent:
  call resetTime
  call resetInput ; this signals the end of the "step"

  call toGameOverState

  ret

handleFullHealEvent:
  call resetTime
  call resetInput ; this signals the end of the "step"

  call playerFullHeal

  ret

handleEncounterTableEvent:
  call resetTime
  call resetInput ; this signals the end of the "step"

  ; inc to the pointer
  inc de
  inc de
  inc de

  call setEventEncounterTable

  ret

handleNPCDialogEvent:
  call resetPlayerMovement
  call resetTime
  call resetInput ; this signals the end of the "step"

  ; inc to the pointer
  inc de
  inc de
  inc de

  ld h, d
  ld l, e

  ; load the text into bc
  ld a, [hl+]
  ld c, [hl]
  ld b, a

  call toDialogGameState

  ret

/** 
 * @return nz - event found
 * @return hl - the event
 * */
checkForOutOfBoundsEvent:
  call getCurrentMap

  ; we only need to check for out of bounds
  ; events if the map has no bounds collision
  call hasBounds
  jr nz, .skip

  ; we should check for out of bounds
  call getWorldPosition
  call checkForOutOfBounds
  jr z, .skip ; we are not out of bounds so skip

  ; check if we are out of bounds
  ; if yes, return the event
  call getMapOutOfBoundsEvent
  ret

.skip
  ; no need to check because we could not
  ; be out of bounds
  cp a ; set the return to z signalling no event

  ret

/** 
 * @param bc - world y, x
 * @return nz - event found
 * @return hl - the event
 * */
checkForAutoEvent:
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
  ; decrement back down to the type of the event, the base
  dec hl

  or a, 1 ; set nz to signal success
  ret
  
.next  
  ; we pop here because we don't know if we've visited
  ; y, x or both
  pop hl

  dec hl ; point back to the base of the event

  ; advance to the next event
  call getNextAutoEvent

  jr .loop

.done
  
  ret

/** bump events */

/** 
 * @return nz - event found
 * @return hl - the event
 * */
checkForBumpEvent:
  call getCurrentMap
  ; iterate over the event list for this map
  call getMapBumpEvents
  call getNextWorldPosition

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
  ; decrement back down to the type of the event, the base
  dec hl

  or a, 1 ; set nz to signal success
  ret
  
.next  
  ; we pop here because we don't know if we've visited
  ; y, x or both
  pop hl

  dec hl ; point back to the base of the event

  ; works for bump events too
  call getNextAutoEvent

  jr .loop

.done
  
  ret


ENDC
