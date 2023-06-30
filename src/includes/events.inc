IF !DEF(EVENTS_INC)
EVENTS_INC = 1

/** for now we will just have a table per map for auto events 
 * but later if we have too many events we can sub-divide the map
 * into quadrants, octants, etc... in order to limit our search 
 */

EVENT_SIZE EQU 8

/** Event Types */
TRANSPORT_EVENT EQU 1

END_LIST EQU 0

MACRO EndList
  db 0
ENDM

/** 
 * AllocateTransportEvent y1, x1, y2, x2
 */
MACRO AllocateTransportEvent
  db TRANSPORT_EVENT, \1, \2, \3, \4, 0, 0, 0
ENDM

Section "EventQueue", ROM0

Section "Events", ROM0

/** 
 * @param bc - y,x world position 
 * @return nz - event found
 * @return hl - the event
 * */
checkForAutoEvent:
  ; iterate over the event list for this map
  call getMapAutoEvents

.loop
  ; check if we are done
  ld a, [hl+]
  cp a, END_LIST
  jr z, .done ; z is set, no event

  ; compare y
  ld a, [hl+]
  cp a, b
  jr nz, .next

  ; compare x
  ld a, [hl+]
  cp a, c
  jr nz, .next

  ; it's a hit :D
  or a, 1
  ret
  
.next  
  ; inc to the next event
  ; the aligned math is too expensive for 3 bits
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl

  jr .loop

.done
  
  ret

/** the player has triggered an auto event 
 * so we write it out to be processed later
 * @param hl - the event
 * */
scheduleAutoEvent:
  ret


ENDC
