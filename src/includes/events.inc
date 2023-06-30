IF !DEF(EVENTS_INC)
EVENTS_INC = 1

/** for now we will just have a table per map for auto events 
 * but later if we have too many events we can sub-divide the map
 * into quadrants, octants, etc... in order to limit our search 
 */

/** Event Types */
TRANSPORT_EVENT EQU 0

/** 
 * AllocateTransportEvent y1, x1, y2, x2
 */
MACRO AllocateTransportEvent
  db \1, \2, TRANSPORT_EVENT, \3, \4
ENDM

ENDC
