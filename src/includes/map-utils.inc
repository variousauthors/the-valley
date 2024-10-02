IF !DEF(MAP_UTILS_INC)
MAP_UTILS_INC = 1

SECTION "CURRENT_MAP_STATE", WRAM0
; store a scene address like overworld, or small world
CURRENT_MAP_HIGH_BYTE: ds 1
CURRENT_MAP_LOW_BYTE: ds 1

; instead of seeking the map each time
; we will store the pointer when we change
; maps... this will also allow us to change
; just the attributes without changing the
; tiles for different "modes of travel" 
CURRENT_MAP_TILESET_HIGH_BYTE: ds 1
CURRENT_MAP_TILESET_LOW_BYTE: ds 1

SECTION "MAP_UTILS", ROM0

; @return hl - address of current map
getCurrentMap:
  ld hl, CURRENT_MAP_HIGH_BYTE
  ld a, [hl+]
  ld l, [hl]
  ld h, a

  ret

; this method sets the pointer to the current map
; in RAM to the given bytes... so you give it de
; pointing to the high byte, it's a copy from
; pointer to pointer, not value to pointer
; @param de - address of a pointer to the map
; @return void CURRENT_MAP pointer is set to de
setCurrentMap:
  push de

  ; set the current map
  ld hl, CURRENT_MAP_HIGH_BYTE
  ld a, [de]
  ld [hl], a

  inc de
  ld hl, CURRENT_MAP_LOW_BYTE
  ld a, [de]
  ld [hl], a

  ; set the current tileset using the map
  call getCurrentMap
  call getMapTilesetFromMetadata
  call setCurrentMapTileset

  pop de

  ret

; sets the tileset back to the map metadata
resetCurrentMapTileset:
  call getCurrentMap
  call getMapTilesetFromMetadata
  call setCurrentMapTileset

  ret

; @param hl - tileset 
setCurrentMapTileset:
  ld de, CURRENT_MAP_TILESET_HIGH_BYTE
  ld a, h
  ld [de], a

  ld de, CURRENT_MAP_TILESET_LOW_BYTE
  ld a, l
  ld [de], a

  ret

initCurrentMap:
  ld a, HIGH(Start)
  ld [CURRENT_MAP_HIGH_BYTE], a
  ld a, LOW(Start)
  ld [CURRENT_MAP_LOW_BYTE], a

  ; we also need to properly call setCurrentMap
  ; since it inits the map state properly
  ld de, CURRENT_MAP_HIGH_BYTE
  call initMap

  ret

; @param bc - player next y, x in world position
; @return nz - safe
isTileSafe:
  call getCurrentMap
  call worldPositionToMetaTile
  push af
  call getCurrentMapTilesetAttributes
  pop af

  call addAToHL
  ld a, [hl]
  and a, SAFE

  ret

; @return hl - tileset from map metadata
getCurrentMapTileset:
  ld hl, CURRENT_MAP_TILESET_HIGH_BYTE
  ld a, [hl+]
  ld l, [hl]
  ld h, a

  ret

; @return hl - the current map tileset attributes
; @destroys a
; @destroys de
getCurrentMapTilesetAttributes:
  call getCurrentMapTileset

  ld de, 16
  add hl, de ; advance to the attributes table

  ret

; lots of stuff @DEPENDS on this
MAP_METADATA_SIZE EQU 12
; height, width, events pointer, tileset pointer, encounter table pointer, bump events pointer, ENTITY list pointer

; @param hl - address of map meta data
; @return hl - address of map data
getMapData:
  ; just advancing past the meta data, no problem
  REPT MAP_METADATA_SIZE
    inc hl
  ENDR

  ret

; @param hl - address of map data
; @return hl - address of map meta data
rewindToMetaData:
  ; just decrementing down to the map root
  REPT MAP_METADATA_SIZE
    dec hl
  ENDR

  ret

; @param hl - address of map meta data
; @return hl - meta tile
getMapBlankTile:
  call getMapData
  ld a, [hl] ; now we have two tile indexes
  srl a
  srl a
  srl a
  srl a ; now we have the blank tile

  call metaTileIndexToAddress

  ret

; @param hl - address of map
; @return hl - address of map tileset
getMapTilesetFromMetadata:
  ; advance to the tileset pointer
  ; @DEPENDS on MAP_METADATA_SIZE
  inc hl
  inc hl
  inc hl
  inc hl

  ; dereference the pointer
  ld a, [hl+]
  ld l, [hl]
  ld h, a

  ret

; @param hl - address of map
; @return hl - address of map encounter table
getMapEncounterTableFromMetadata:
  ; advance to the encounter table pointer
  ; @DEPENDS on MAP_METADATA_SIZE
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl

  ; dereference the pointer
  ld a, [hl+]
  ld l, [hl]
  ld h, a

  ret

; the first auto event is the out of bounds event, by convention
; if we can get into a map from the parent, then there must be
; an exit, and that will point to the parent tile
; @param hl - address of map
; @return hl - address of map events list
getMapOutOfBoundsEvent:
  call getMapAutoEvents

  ret

; @param hl - address of map
; @return hl - address of map events list
getMapAutoEvents:
  ; advance to the auto events list pointer
  ; @DEPENDS on MAP_METADATA_SIZE
  inc hl
  inc hl

  ; dereference the pointer
  ld a, [hl+]
  ld l, [hl]
  ld h, a

  ret

; @param hl - address of map
; @return hl - address of map events list
getMapBumpEvents:
  ; advance to the bump events list pointer
  ; @DEPENDS on MAP_METADATA_SIZE
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl

  ; dereference the pointer
  ld a, [hl+]
  ld l, [hl]
  ld h, a

  ret

; @param hl - address of map
; @return hl - address of map events list
getMapEntityList:
  ; advance to the bump events list pointer
  ; @DEPENDS on MAP_METADATA_SIZE
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl
  inc hl

  ; dereference the pointer
  ld a, [hl+]
  ld l, [hl]
  ld h, a

  ret

/** go down the entity list
 * calling init on each? */
initMapEntities:
  call getMapEntityList
  call indirectCall

  ret

; @param de - the map to initialize
; used by transport event to initialize the
; new map
initMap:
  call resetEntities

  ld a, [de] ; the high byte of the pointer
  ; set the current map
  call setCurrentMap
  call getCurrentMap
  call initMapEntities

  ret

; MAP_METADATA_FLAGS
; these are stored in one byte _before_ the map meta data
; for ease of access you know
NO_BOUNDS        EQU %00000000
HAS_BOUNDS       EQU %00000001
IS_OVERWORLD     EQU %00000010
NO_ENCOUNTERS    EQU %00000100
IS_CHECKPOINT    EQU %00001000

; check if the map has bounds
; @param hl - map
; @return z - no bounds
hasBounds:
  dec hl
  ld a, [hl]
  inc hl
  bit 0, a

  ret

; @param hl - map
; @return nz - is checkpoint
isCheckpoint:
  dec hl
  ld a, [hl]
  inc hl
  and a, IS_CHECKPOINT

  ret

; check if the map is overworld lol
; @param hl - map
; @return nz - is overworld
isOverworld:
  dec hl
  ld a, [hl]
  inc hl
  and a, IS_OVERWORLD

  ret

; check if the map has encounters
; @param hl - map
; @return nz - no encounters
isSafeArea:
  dec hl
  ld a, [hl]
  inc hl
  and a, NO_ENCOUNTERS

  ret

ENDC