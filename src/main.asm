INCLUDE "includes/hardware.inc"
INCLUDE "includes/dma.inc"

MAP_TILES EQU _VRAM
SPRITE_TILES EQU $8800 ; 2nd VRAM

VRAM_WIDTH EQU 32
VRAM_HEIGHT EQU 32
VRAM_SIZE EQU VRAM_WIDTH * VRAM_HEIGHT
SCRN_WIDTH EQU 20
SCRN_HEIGHT EQU 18

; temporary, useful for testing
; in practice maps will have their own entrances/exits
PLAYER_START_X EQU 8
PLAYER_START_Y EQU 8

SECTION "OAMData", WRAM0, ALIGN[8]
Sprites: ; OAM Memory is for 40 sprites with 4 bytes per sprite
  ds 40 * 4
.end:
 
SECTION "CommonRAM", WRAM0

; all the bits we need for inputs 
_PAD: ds 2

; directions
RIGHT EQU %00010000
LEFT  EQU %00100000
UP    EQU %01000000
DOWN  EQU %10000000

A_BUTTON EQU %00000001
B_BUTTON EQU %00000010

; world position
PLAYER_WORLD_X: ds 1
PLAYER_WORLD_Y: ds 1

; enough bytes to buffer the whole _SCRN
MAP_BUFFER_WIDTH EQU SCRN_WIDTH
MAP_BUFFER_HEIGHT EQU SCRN_HEIGHT
MAP_BUFFER:
TOP_MAP_BUFFER: ds MAP_BUFFER_WIDTH * 2
MIDDLE_MAP_BUFFER: ds MAP_BUFFER_WIDTH * (MAP_BUFFER_HEIGHT - 4)
BOTTOM_MAP_BUFFER: ds MAP_BUFFER_WIDTH * 2
MAP_BUFFER_END:

; an array of indexes into an instruction table, with fixed instructions
; eg (draw top row) or (draw one tile)
; zero terminated
ACTION_QUEUE: ds 8 ; 8 instructions per frame

; address of the next free instruction
ACTION_QUEUE_POINTER: ds 2 ; two bytes to store an address

NO_OP EQU 0
PLAYER_MOVE_RIGHT EQU 1
PLAYER_MOVE_LEFT EQU 2
PLAYER_MOVE_UP EQU 3
PLAYER_MOVE_DOWN EQU 4

; this is $80 because the tiles are in the
; second tile set which starts at $80
; obviously this will change when we get new graphics
TILE_BLANK EQU $80 + 0

; Hardware interrupts
SECTION "vblank", ROM0[$0040]
  jp DMA_ROUTINE
SECTION "hblank", ROM0[$0048]
  reti
SECTION "timer",  ROM0[$0050]
  reti
SECTION "serial", ROM0[$0058]
  reti
SECTION "joypad", ROM0[$0060]
  reti

Section "start", ROM0[$0100]
  jp init

SECTION "main", ROM0[$150]

init:
  di

  dma_Copy2HRAM	; sets up routine from dma.inc that updates sprites

  call ZeroOutWorkRAM ; it is easier to inspect this way
  call initPalettes
  call turnOffLCD

  call resetDrawInstructionQueuePointer

  ; @TODO placeholder graphics lol
  ld hl, ArkanoidTiles
  ld b, ArkanoidTiles.end - ArkanoidTiles
  ld de, MAP_TILES
  call loadTileData

  ld hl, ArkanoidGraphics
  ld b, ArkanoidGraphics.end - ArkanoidGraphics
  ld de, SPRITE_TILES
  call loadTileData

  ; @TODO the event that moved the player
  ; should determine where the player appears
  ld hl, PLAYER_WORLD_X ; world position
  ld a, PLAYER_START_X
  ld [hl], a

  ld hl, PLAYER_WORLD_Y ; world position
  ld a, PLAYER_START_Y
  ld [hl], a

  call blankVRAM
  ld hl, Overworld
  call writeMapToBuffer

  call drawBuffer
  call turnOnLCD

  ei

main:
  halt

  nop

  ; @TODO right now we are limiting input to 1 action per keydown
  ; so we check for input each frame and we only do game logic
  ; if there was no input last frame
  ld a, [_PAD]
  and a
  jp z, .doneDrawing

  ; draw only the relevant part of the buffer
  ; @TODO my first test will be to try to render
  ; just one row or column from the buffer, but still
  ; let the back-side of the main loop load the whole buffer
  ; just to see if that works.
  ; @TODO Then part II will be loading only one row/col into the buffer
  ; at one time
  ; @TODO stretch goal is to break the loading up so that it loads a little
  ; each frame while the screen is scrolling, rather than all at once before
  ; or after the scroll
  call updateVRAM
  call updateScrolling

  ; but don't do anythihng else, we want to wait
  ; for a frame with no input... ie the user has to lift the key
  ; with each input. this is just temporary to prevent duplicate inputs
  call clearInstructionQueue
  call readInput
  jr main

.doneDrawing
  call clearInstructionQueue

  ; -- INPUT PHASE JUST RECORDS ACTIONS --
  call readInput

  ; if there is not input this frame, skip thinking
  ld a, [_PAD]
  and a
  jp z, main

  ; record intents
  call doPlayerMovement

  ; -- UPDATE STATE BASED ON ACTIONS --

  call updatePlayer

  ld hl, Overworld
  call writeMapToBuffer

  jp main
; -- END MAIN --

HALF_SCREEN_WIDTH EQU SCRN_WIDTH / 2 ; 10 meta tiles
HALF_SCREEN_HEIGHT EQU SCRN_HEIGHT / 2 ; 9 meta tiles

META_TILES_TO_SCRN_LEFT EQU SCRN_WIDTH / 2 / 2
META_TILES_TO_TOP_OF_SCRN EQU SCRN_HEIGHT / 2 / 2
META_TILES_PER_SCRN_ROW EQU SCRN_WIDTH / 2
META_TILE_ROWS_PER_SCRN EQU SCRN_HEIGHT / 2

; @param hl - map
writeMapToBuffer:
  ; subtract from player y, x to get top left corner
  ld a, [PLAYER_WORLD_Y]
  sub a, META_TILES_TO_TOP_OF_SCRN
  ld de, MAP_BUFFER
  ld b, a

  ; while y is negative, draw blanks
.loop1
  ld a, b
  cp a, $80 ; is y negative?
  jr c, .done1

  call writeBlankRowToBuffer
  inc b

  jr .loop1
.done1

.loop2
  ; load map height from map
  ld a, [hl]
  dec a ; map height - 1

  ; stop if map height - 1 < y
  cp b
  jr c, .done2

  ; 
  ld a, [PLAYER_WORLD_Y]
  sub a, META_TILES_TO_TOP_OF_SCRN
  add a, META_TILE_ROWS_PER_SCRN - 1

  ; stop if we're past the last row we wanted to write
  cp b
  jr c, .done2

  call writeMapRowToBuffer
  inc b

  jr .loop2
.done2

  ; at this point y will always be equal to the map height
  ; because we've written as much map as we could
  ; and a < b so b - a = rows we wrote
  ; rows we wrote - rows per screen = rows to write
  ; b - a - rows per screen = rows to write
  ; a - b + rows per screen = - rows to write
  ld a, [PLAYER_WORLD_Y]
  sub a, META_TILES_TO_TOP_OF_SCRN ; start y
  sub b ; minus map height, - rows we wrote
  add META_TILE_ROWS_PER_SCRN ; rows to write?

  ld b, a ; be has rows to write
.loop3
  ld a, b
  or a
  jr z, .done3

  call writeBlankRowToBuffer
  dec b

  jr .loop3
.done3

  ret

; @param bc - y, x to write
; @param hl - map to read
; @param de - where to write
writeMapRowToBuffer:
  push bc
  push hl

  ; subtract from player x to get extreme left
  ld a, [PLAYER_WORLD_X]
  sub a, META_TILES_TO_SCRN_LEFT
  ld c, a ; now bc has y, x

  ; while x is negative, draw blanks
.loop1
  ld a, c
  cp a, $80 ; is y negative?
  jr c, .done1

  call writeBlankTileToBuffer
  inc c

  jr .loop1
.done1

.loop2
  ; load map width height from map
  inc hl
  ld a, [hl]
  dec hl
  dec a ; map width - 1

  ; stop if map width - 1 < x
  cp c
  jr c, .done2

  ; 
  ld a, [PLAYER_WORLD_X]
  sub a, META_TILES_TO_SCRN_LEFT
  add a, META_TILES_PER_SCRN_ROW - 1

  ; stop if we're past the last row we wanted to write
  cp c
  jr c, .done2

  push hl
  ; seek past map meta data
  inc hl
  inc hl

  call seekIndex
  ; now hl has the map index to start reading from

  call writeMapTileToBuffer
  pop hl

  inc c

  jr .loop2
.done2

  ld a, [PLAYER_WORLD_X]
  sub a, META_TILES_TO_SCRN_LEFT
  sub c ; minus map width, - cols we wrote
  add META_TILES_PER_SCRN_ROW

  ld c, a ; be has blank tiles to write
.loop3
  ld a, c
  or a
  jr z, .done3

  call writeBlankTileToBuffer
  dec c

  jr .loop3
.done3

  ; after writing two rows of tiles (1 row of meta tiles)
  ; de will be pointing to the end of the top row
  ; so we have to advance de by MAP_BUFFER_WIDTH

  ld a, e
  add a, MAP_BUFFER_WIDTH
  ld e, a
  ld a, 0
  adc a, d
  ; de advanced one row

  pop hl
  pop bc

  ret

; @param hl - map to read
; @param de - where to write
writeBlankRowToBuffer:
  push bc

  ld a, META_TILES_PER_SCRN_ROW
  ld b, a
.loop
  ; the first tile in any map is the blank tile for that map
  call writeBlankTileToBuffer

  dec b
  jr nz, .loop
.done

  ; after writing two rows of tiles (1 row of meta tiles)
  ; de will be pointing to the end of the top row
  ; so we have to advance de by MAP_BUFFER_WIDTH

  ld a, e
  add a, MAP_BUFFER_WIDTH
  ld e, a
  ld a, 0
  adc a, d

  pop bc
  
  ret

; @param hl - meta tile to write
; @param de - write to address
writeMapTileToBuffer:
  ld a, [hl] ; the meta tile

  push bc
  push hl
  push de

  ld hl, MetaTiles
  ld c, 4
  ld b, a
  call seekRow
  ; hl has the meta tile

  ld a, [hl+]
  ld [de], a
  inc de

  ld a, [hl+]
  ld [de], a
  dec de

  ; advance 1 row in the buffer
  ld a, e
  add a, MAP_BUFFER_WIDTH
  ld e, a
  ld a, 0
  adc a, d
  ld d, a

  ; @TODO should we check the carry here and maybe
  ; crash if we stepped wrongly?

  ld a, [hl+]
  ld [de], a
  inc de

  ld a, [hl+]
  ld [de], a

  pop de
  pop hl
  pop bc

  inc hl ; we wrote one meta tile
  inc de
  inc de ; we wrote two tiles

  ret

; @param hl - the map
; @param de - where to write to
writeBlankTileToBuffer:
  push bc
  push hl
  push de

  inc hl
  inc hl ; skip the meta data
  ld a, [hl] ; the meta tile

  ld hl, MetaTiles
  ld c, 4
  ld b, a
  call seekRow
  ; hl has the meta tile

  ld a, [hl+]
  ld [de], a
  inc de

  ld a, [hl+]
  ld [de], a
  dec de

  ; advance 1 row in the buffer
  ld a, e
  add a, MAP_BUFFER_WIDTH
  ld e, a
  ld a, 0
  adc a, d
  ld d, a

  ; @TODO should we check the carry here and maybe
  ; crash if we stepped wrongly?

  ld a, [hl+]
  ld [de], a
  inc de

  ld a, [hl+]
  ld [de], a

  pop de
  pop hl
  pop bc

  inc de
  inc de ; we wrote two tiles

  ret

; @param bc - y, x in world space
; @param hl - address of map
; @result hl - index of meta tile in map
seekIndex:
  push bc

  dec hl ; the map width is before the map
  ld a, [hl] 
  ld c, a
  inc hl ; point to the start of the map
  call seekRow
  ; now hl points to the row

  pop bc

  ld a, c
  inc a
.loop
  dec a
  jr z, .done
  inc hl

  jr .loop
.done

  ret

; @param bc - y, x in screen space (0 - 255)
; @result hl - address in VRAM of that position
scrnPositionToVRAMAddress:
  push bc

  ; multiply y by 32 to get the row index in ba
  ld a, b ; low byte in a
  ld b, 0 ; high byte in b

  sla a
  jr nc, .no_carry1
  inc b
.no_carry1

  REPT 4
    sla b
    sla a
    jr nc, .no_carry2\@
    inc b
  .no_carry2\@
  ENDR

  add a, c
  jr nc, .no_carry3
  inc b
.no_carry3

  ld c, a
  ; now bc has the index of y, x

  ld hl, _SCRN0

  ; add bc to hl to get address in meta tile map
  ld a, LOW(bc)
  add l
  ld l, a
  ld a, HIGH(bc)
  adc h ; add possible carry from a + e
  ld h, a

  pop bc

  ret

updateVRAM:
  ; iterate down the list until we hit 0
  ; switch on each instruction and call a subroutine
  ld hl, ACTION_QUEUE

  ; loop until the instruction is NO_OP
.loop
  ld a, [hl]
  cp a, NO_OP
  jp z, .done

  push hl

  ; perform the instruction
  cp a, PLAYER_MOVE_LEFT
  jr nz, .next1
  ld hl, drawLeftColumn

.next1
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .next2
  ld hl, drawRightColumn

.next2
  cp a, PLAYER_MOVE_UP
  jr nz, .next3
  ld hl, drawTopRow

.next3
  cp a, PLAYER_MOVE_DOWN
  jr nz, .next4
  ld hl, drawBottomRow

.next4

  call indirectCall

  pop hl

  inc hl
  jr .loop
  
.done


  ret

updateScrolling:
  ; iterate down the list until we hit 0
  ; switch on each instruction and call a subroutine
  ld hl, ACTION_QUEUE

  ; loop until the instruction is NO_OP
.loop
  ld a, [hl]
  cp a, NO_OP
  jp z, .done

  push hl

    ; perform the instruction
    cp a, PLAYER_MOVE_LEFT
    jr nz, .next1
    ld hl, scrollLeft
  
  .next1
    cp a, PLAYER_MOVE_RIGHT
    jr nz, .next2
    ld hl, scrollRight
  
  .next2
    cp a, PLAYER_MOVE_UP
    jr nz, .next3
    ld hl, scrollUp
  
  .next3
    cp a, PLAYER_MOVE_DOWN
    jr nz, .next4
    ld hl, scrollDown
  
  .next4
  
    call indirectCall

  pop hl

  inc hl
  jr .loop
  
.done


  ret

scrollUp:
  ld a, [rSCY]
  sub a, 16
  ld [rSCY], a

  ret

scrollDown:
  ld a, [rSCY]
  add a, 16
  ld [rSCY], a

  ret

scrollLeft:
  ld a, [rSCX]
  add a, 16
  ld [rSCX], a

  ret

scrollRight:
  ld a, [rSCX]
  sub a, 16
  ld [rSCX], a

  ret

; empty the queue
clearInstructionQueue:
  ld hl, ACTION_QUEUE
  ld [hl], NO_OP

  call resetDrawInstructionQueuePointer

  ret

resetDrawInstructionQueuePointer:
  ; point the draw instruction queue pointer to the draw instruction queue
  ld hl, ACTION_QUEUE
  ld a, h
  ld [ACTION_QUEUE_POINTER], a
  ld a, l
  ld [ACTION_QUEUE_POINTER + 1], a

  ret

drawLeftColumn:
  ret

drawRightColumn:
  ret

drawTopRow:
  ; the correct data is in the buffer
  ; we just copy the top row from the buffer
  ; and then scroll
  ; the trick is figuring out where in VRAM to copy to

  ; get screen y, x
  call getTopLeftScreenPosition
  ; move "up" to the meta tile row we want to draw
  dec b 
  dec b 

  ; adjust for screen wrap if we wrapped
  ; if b < 0 add 32
  ; b is in 0 - 31 so we can use bit 7 to check for negative
  bit 7, b
  jr z, .noWrap
  ld a, b
  add VRAM_HEIGHT
  ld b, a
.noWrap

  ; convert y, x to index in VRAM
  call scrnPositionToVRAMAddress
  ; now hl had where to write to

  ; we're just copying the first 40 tiles
  ; no need for cleverness, just set de to the buffer
  ; @TODO we'll have a separate buffer that is always just the 40 tiles we need
  ; regardless of whether they are vertical or not
  ld de, TOP_MAP_BUFFER

  call drawRow

  ; move to the next tile row we want to write to
  inc b 
  ; adjust for screen wrap if we wrapped
  ; if b < 0 add 32
  ; b is in 0 - 31 so we can use bit 7 to check for negative
  bit 7, b
  jr z, .noWrap2
  ld a, b
  sub VRAM_HEIGHT
  ld b, a
.noWrap2

  ; convert y, x to index in VRAM
  call scrnPositionToVRAMAddress
  ; now hl has where to write to

  ; we're just copying the first 40 tiles
  ; no need for cleverness, just set de to the buffer
  ; @TODO we'll have a separate buffer that is always just the 40 tiles we need
  ; regardless of whether they are vertical or not
  ; 
  ; feeels like de is already where we want it
  ; as a side effect of drawRow
  ; ld de, MAP_BUFFER

  call drawRow

  ret

drawBottomRow:
  ; the correct data is in the buffer
  ; we just copy the top row from the buffer
  ; and then scroll
  ; the trick is figuring out where in VRAM to copy to

  ; get screen y, x
  call getBottomLeftScreenPosition
  ; increment y by 1
  inc b 
  ; adjust for screen wrap if we wrapped
  ; if b > 31 subtract 32
  ; b was in 0 - 31 so we just need to check if it is now 32
  ; and since that is a power of two, we can just check bit 5
  bit 5, b
  jr z, .noWrap
  ld a, b
  sub VRAM_HEIGHT
  ld b, a
.noWrap

  ; convert y, x to index in VRAM
  call scrnPositionToVRAMAddress
  ; now hl had where to write to

  ; we're just copying the first 40 tiles
  ; no need for cleverness, just set de to the buffer
  ; @TODO we'll have a separate buffer that is always just the 40 tiles we need
  ; regardless of whether they are vertical or not
  ld de, BOTTOM_MAP_BUFFER

  call drawRow

  ; now get the next row in vram
  ; increment y by 1
  inc b 
  ; adjust for screen wrap if we wrapped
  ; if b > 31 subtract 32
  ; b was in 0 - 31 so we just need to check if it is now 32
  ; and since that is a power of two, we can just check bit 5
  bit 5, b
  jr z, .noWrap2
  ld a, b
  sub VRAM_HEIGHT
  ld b, a
.noWrap2

  ; convert y, x to index in VRAM
  call scrnPositionToVRAMAddress
  ; now hl has where to write to

  ; we're just copying the first 40 tiles
  ; no need for cleverness, just set de to the buffer
  ; @TODO we'll have a separate buffer that is always just the 40 tiles we need
  ; regardless of whether they are vertical or not
  ;
  ; feeeels like we already have de where we want it 
  ; ld de, MAP_BUFFER

  call drawRow

  ret

; @param de - row to read
; @param hl - address to write
drawRow:
  REPT SCRN_WIDTH
    ld a, [de]
    inc de
    ld [hl+], a
  ENDR

  ret

; @return bc - y, x of the top left tile of VRAM
getTopLeftScreenPosition:
  ld a, [rSCY]

  ; divide by 8 to get the y
  srl a
  srl a
  srl a

  ld b, a

  ld a, [rSCX]
  ld c, a

  ; divide by 8 to get the x
  srl c
  srl c
  srl c

  ret

; @return bc - y, x of the bottom left tile of VRAM
getBottomLeftScreenPosition:
  ld a, [rSCY]

  ; divide by 8 to get the y in tile space
  srl a
  srl a
  srl a

  ; move to the bottom of the screen
  add SCRN_HEIGHT - 1

  ld b, a

  ld a, [rSCX]
  ld c, a

  ; divide by 8 to get the x
  srl c
  srl c
  srl c

  ret

; @return hl - pointer to the top left corner of the visible screen
getBottomLeftScreenPointer:
  ld a, [rSCY]
  ld l, a

  ; y is in pixels but we need it as an index
  ; so divide by 8
  srl l
  srl l
  srl l ; divide by 8 to get the index space

  ; in the index space determine if we are
  ; wrapping around, and adjust

  ; hl's index is pointing to the first row of the screen
  ; if it is greater than 32 - 18, then
  ; the bottom of the screen will have wrapped around
  ; so we can subtract 32 to put it up above the
  ; bottom, and then subtract 18 to get an index into the bottom

  ld a, VRAM_HEIGHT - SCRN_HEIGHT
  cp a, l
  jr nc, .skip 

  ; if e > VRAM_HEIGHT - SCRN_HEIGHT
  ; subtract VRAM_HEIGH

  ld a, l
  ld l, VRAM_HEIGHT

  sub a, l ; index - 32
  jr nc, .skip ; no carry
  dec h ; borrow
  ld l, a

.skip
  ; go to the bottom of the screen
  ld a, l
  ld l, SCRN_HEIGHT
  add a, l
  ld l, a 
  dec l
  dec l ; now l is an index to second to last row on the screen

  ; now translate into address space, building up
  ; the high byte in a
  ld a, 0 ; build up the high byte in here

  sla l
  adc a, 0
  
  sla a ; don't forget to multiply the high byte
  sla l
  adc a, 0

  sla a ; don't forget to multiply the high byte
  sla l
  adc a, 0

  sla a ; don't forget to multiply the high byte
  sla l
  adc a, 0

  sla a ; don't forget to multiply the high byte
  sla l
  adc a, 0

  ld h, a ; we built up the high byte in a

  ; get the x
  ld a, [rSCX]
  srl a
  srl a
  srl a ; divide by 8 to get the index

  add a, l ; add x to hl
  ld l, a
  ld a, 0
  adc a, h ; add the carry
  ld h, a ; now hl has hl + x

  ; convert to an address in VRAM
  ld de, _SCRN0
  add hl, de

  ret

drawBuffer:
  ld hl, MAP_BUFFER
  ld de, _SCRN0
  ld b, SCRN_HEIGHT

.loop
  call drawBufferRow
  REPT VRAM_WIDTH - SCRN_WIDTH ; advance to the next SCRN row
    inc de
  ENDR
  dec b
  jr nz, .loop
.done
  ret

drawBufferRow:
  ld c, SCRN_WIDTH
.loop
  ld a, [hl]
  ld [de], a
  inc hl
  inc de
  dec c
  jr nz, .loop
.done
  ret

waitForVBlank:
.loop
  ld a, [rLY]
  cp 145
  jr nz, .loop

  ret

initPalettes:
  ; darkest to lightest
  ld a, %11100100
  ld [rBGP], a
  ld [rOBP0], a

  ret

turnOffLCD:
  ld a, [rLCDC]
  rlca
  ret nc

  call waitForVBlank

  ; in VBlank
  ld a, [rLCDC]
  res 7, a
  ld [rLCDC], a

  ret

turnOnLCD:
  ; configure and activate the display
  ld a, LCDCF_ON|LCDCF_BG8000|LCDCF_BG9800|LCDCF_BGON|LCDCF_OBJ8|LCDCF_OBJON
  ld [rLCDC], a

	ld a, IEF_VBLANK
	ld [rIE], a	; Set only Vblank interrupt flag

  ret

readInput:
  ; read the cruzeta (the d-pad)
  ld a, %00100000 ; select the d-pad
  ld [rP1], a

  ; read the d-pad several times to avoid bouncing
  ld a, [rP1] ; could also do
  ld a, [rP1] ; rept 4
  ld a, [rP1] ; ld a, [rP1]
  ld a, [rP1] ; endr

  and $0F
  swap a
  ld b, a

  ; we go for the buttons
  ld a, %00010000 ; bit 4 to 1 bit 5 to 0 (enable buttons, disable d-pad)
  ld [rP1], a

  ; read the buttons several times to avoid bouncing
  ld a, [rP1] ; could also do
  ld a, [rP1] ; rept 4
  ld a, [rP1] ; ld a, [rP1]
  ld a, [rP1] ; endr

  and $0F
  or b

  ; we now have a with 0 for down and 1 for up
  cpl ; complement so 1 means down :D
  ld [_PAD], a
.done
  ret

; @TODO for movement we want it to feel smooth
; so if the player was pressing down left
; and then they rolled their thumb onto down
; we want to be able to see "last frame we saw left
; but this frame we see left and down, so we will
; interpret this as down"
; for now though left > right > up > down
;
; while the player is walking around, we want to
; interpret their direction pad as movement
doPlayerMovement:
  ; if there is no input bail
  ld a, [_PAD]
  and a
  ret z

  ; now we dispatch actions based on the input

  ld a, [_PAD]
  and RIGHT
  ld b, PLAYER_MOVE_RIGHT
  jr nz, .done

  ld a, [_PAD]
  and LEFT
  ld b, PLAYER_MOVE_LEFT
  jr nz, .done ; move left

  ld a, [_PAD]
  and UP
  ld b, PLAYER_MOVE_UP
  jr nz, .done ; move up

  ld a, [_PAD]
  and DOWN
  ld b, PLAYER_MOVE_DOWN
  jr nz, .done ; move down

.done

  call dispatchAction

  ret

updatePlayer:
  ; iterate down the list until we hit 0
  ; switch on each instruction and call a subroutine
  ld hl, ACTION_QUEUE

  ; loop until the instruction is NO_OP
.loop
  ld a, [hl]
  cp a, NO_OP
  jp z, .done

  push hl

  ; perform the instruction
  cp a, PLAYER_MOVE_LEFT
  jr nz, .next1
  ld hl, moveLeft

.next1
  cp a, PLAYER_MOVE_RIGHT
  jr nz, .next2
  ld hl, moveRight

.next2
  cp a, PLAYER_MOVE_UP
  jr nz, .next3
  ld hl, moveUp

.next3
  cp a, PLAYER_MOVE_DOWN
  jr nz, .next4
  ld hl, moveDown

.next4

  call indirectCall

  pop hl

  inc hl
  jr .loop
  
.done

  ret

; @param - hl the address of some subroutie to call
indirectCall:
  jp hl

moveLeft:
  ld a, [PLAYER_WORLD_X]
  inc a
  ld [PLAYER_WORLD_X], a

  ret

moveRight:
  ld a, [PLAYER_WORLD_X]
  dec a
  ld [PLAYER_WORLD_X], a

  ret

moveUp:
  ld a, [PLAYER_WORLD_Y]
  dec a
  ld [PLAYER_WORLD_Y], a

  ret

moveDown:
  ld a, [PLAYER_WORLD_Y]
  inc a
  ld [PLAYER_WORLD_Y], a

  ret

; @param b - instruction to record
dispatchAction:
  ; request tiles to draw
  ld a, [ACTION_QUEUE_POINTER]
  ld h, a
  ld a, [ACTION_QUEUE_POINTER + 1]
  ld l, a

  ld a, b ; the instruction code
  ld [hl+], a
  
  ld a, h
  ld [ACTION_QUEUE_POINTER], a
  ld a, l
  ld [ACTION_QUEUE_POINTER + 1], a

  ret

; write the blank tile to the whole SCRN0
blankVRAM:
  ld hl, _SCRN0
  ld de, VRAM_SIZE
.loop
  ld a, TILE_BLANK
  ld [hl], a
  dec de
  ld a, d
  or e
  jp z, .done
  inc hl
  jp .loop
.done
  ret

; @param hl - start
; @param b - the y to seek
; @param c - width
; @return hl - the row
seekRow:
  push de

  ld a, b
  or a ; if y is zero we are done
  jr z, .done
  rlca ; if y is negative we are done
  jr c, .done

  ld a, b

  ; de gets the width
  ld d, 0
  ld e, c
.loop
  add hl, de
  dec a
  jr nz, .loop
.done
  pop de
  ret

; @param hl -- tileset
; @param de -- location
; @param b -- bytes
loadTileData:
  push de
  push bc

.loadData
  ld a, [hl]
  ld [de], a
  dec b
  jr z, .doneLoading
  inc hl
  inc de
  jr .loadData
.doneLoading

  pop bc
  pop de

  ret

ZeroOutWorkRAM:
  ld hl, _RAM
  ld de, $DFFF - _RAM ; number of bytes to write
.write
  ld a, $00
  ld [hli], a
  dec de
  ld a, d
  or e
  jr nz, .write
  ret

Section "metatiles", ROM0
MetaTiles:
  db 0, 0, 0, 0
  db 1, 1, 1, 1
  db 2, 2, 3, 3
  db 3, 3, 3, 3
  db 4, 4, 4, 4

Section "overworld", ROM0
Overworld:
  db 16, 16
  db 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
  db 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2
  db 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2
  db 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2
  db 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2
  db 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2
  db 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2
  db 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2
  db 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2
  db 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2
  db 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2
  db 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2
  db 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2
  db 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2
  db 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2
  db 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2

Section "smallworld", ROM0
Smallworld:
  db 10, 4
  db 4, 2, 2, 2
  db 2, 2, 1, 2
  db 2, 1, 2, 2
  db 2, 1, 1, 2
  db 2, 1, 1, 2
  db 2, 1, 1, 2
  db 2, 1, 1, 2
  db 2, 2, 1, 2
  db 2, 1, 2, 2
  db 2, 2, 2, 2

Section "GraphicsData", ROM0

ArkanoidTiles: INCBIN "assets/arkanoid-map.2bpp"
.end

ArkanoidGraphics: INCBIN "assets/arkanoid-graphics.2bpp"
.end

ArkanoidMap: INCBIN "assets/arkanoid-map.tilemap"
.end