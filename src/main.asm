INCLUDE "includes/hardware.inc"
INCLUDE "includes/dma.inc"

MAP_TILES EQU _VRAM
SPRITE_TILES EQU $8800 ; 2nd VRAM

SCRN_VERTICAL_STEP EQU 32
SCRN_HORIZONTAL_STEP EQU 1
SCRN_SIZE EQU SCRN_VERTICAL_STEP * SCRN_VERTICAL_STEP
BG_WIDTH EQU 20
BG_HEIGHT EQU 18

CHUNK_WIDTH EQU 20
CHUNK_HEIGHT EQU 18

; field includes the 8 px borders
FIELD_TOP EQU 16 + 8
FIELD_RIGHT EQU 160 - 8
FIELD_BOTTOM EQU 152 ; there is no border on the bottom
FIELD_LEFT EQU 8 + 8

SECTION "OAMData", WRAM0, ALIGN[8]
Sprites: ; OAM Memory is for 40 sprites with 4 bytes per sprite
  ds 40 * 4
.end:
 
SECTION "CommonRAM", WRAM0

; ball velocity
BALL_DX: ds 1
BALL_DY: ds 1
; ball position
BALL_X: ds 1
BALL_Y: ds 1

CAMERA_X: ds 1
CAMERA_Y: ds 1

NEXT_SPRITE: ds 1
ONE_SPRITE EQU 4 ; bytes per sprite

; ball sprite
BALL_SPRITE_NO: ds 1
BALL_SPRITE_ATTRIBUTES: ds 1

; brick position table
BRICK_SIZE EQU 1 ; just a flag to see if the brick exists

; remembet, the bricks are "half tall" only 4 pixels tall
TOP_LEFT_BRICK_X EQU 10 ; 10 x 8 pixels over
TOP_LEFT_BRICK_Y EQU 18 ; 18 x 4 pixels down

BRICK_PER_ROW EQU 12
BRICK_ROWS EQU 8

MAX_BRICKS EQU BRICK_PER_ROW * BRICK_ROWS ; that's just a rectangle of bricks

BRICK_TABLE: ds BRICK_SIZE * MAX_BRICKS

TILE_BLANK EQU $80 + 0
BRICK_BOTTOM EQU $80 + 1
BRICK_TOP EQU $80 + 2
BRICK_DOUBLE EQU $80 + 3
BORDER_LEFT EQU $80 + 4
BORDER_TOP EQU $80 + 5
BORDER_RIGHT EQU $80 + 6
BORDER_TOP_LEFT EQU $80 + 7
BORDER_TOP_RIGHT EQU $80 + 8
TILE_BALL EQU $80 + 9


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

  ld hl, ArkanoidTiles
  ld b, ArkanoidTiles.end - ArkanoidTiles
  ld de, MAP_TILES
  call loadTileData

  ld hl, ArkanoidGraphics
  ld b, ArkanoidGraphics.end - ArkanoidGraphics
  ld de, SPRITE_TILES
  call loadTileData

  call loadBrickData
  call blankScreen

  ; draw stuff in world
  call drawChunk
  call drawBricks
  call initSprites
  call turnOnLCD

  ei

main:
  halt

  nop

  call drawCamera
  call resetSprites
  call drawBall

  call updateBallPosition
  call handleBallWallCollision
  call updateCameraPosition

  call ballBrickBroadPhase
  call ballBrickNarrowPhase

  ; call pause

  jp main

drawCamera:
  ld a, [CAMERA_X]
  ld [rSCX], a

  ld a, [CAMERA_Y]
  ld [rSCY], a

  ret

updateCameraPosition:
  ; position is in pixels
  ld a, 5 * 8
  ld [CAMERA_X], a

  ld a, 5 * 8
  ld [CAMERA_Y], a

  ret

resetSprites:
  ld a, -ONE_SPRITE
  ld [NEXT_SPRITE], a

; @return hl -- the address of the sprite
; @return increments NEXT_SPRITE
getNextSprite:
  push de

  ld a, [NEXT_SPRITE]
  add a, ONE_SPRITE ; advance to next sprite
  ld [NEXT_SPRITE], a

  ; point to the next sprite
  ld d, 0
  ld e, a
  ld hl, Sprites
  add hl, de

  pop de

  ret

; @destroys hl
drawBall:
  ; get a sprite for the ball
  call getNextSprite

  ; translate the ball's world position
  ; into screen position
  ; by subtracting the camera position

  ; map the ball data to a sprite
  ld a, [BALL_Y]
  ld [hl+], a
  ld a, [BALL_X]
  ld [hl+], a
  ld a, [BALL_SPRITE_NO]
  ld [hl+], a
  ld a, [BALL_SPRITE_ATTRIBUTES]
  ld [hl+], a

  ; load the data into that sprite
  ret

loadBrickData:
  ld hl, Level1
  ld de, BRICK_TABLE
  ld bc, EndLevel1 - Level1

.loadData
  ld a, [hl]
  ld [de], a
  dec bc
  ld a, b
  or c
  jr z, .doneLoading
  inc hl
  inc de
  jr .loadData
.doneLoading
  ret


; draws two bricks, one tile
; @param hl address of brick in BRICK_TABLE
; @param de address of tile to write
drawBrickTile:
  push bc

; the address of brick tile is $80
; and then there is top only at 82
; bottom only at 81 and top/bottom at 83
; so we kind of or the brick together
.top
  ld a, $80
  ld [de], a ; assume a blank tile
  ld a, [hl] ; check if brick exists
  cp a, 1
  jr nz, .bottom
  ; brick exists
  ld a, [de]
  add 2
  ld [de], a ; so draw the top brick

.bottom
  push hl
  ld bc, BRICK_PER_ROW * BRICK_SIZE ; jump down one row
  add hl, bc ; to the bottom brick
  ld a, [hl] ; check if it exists
  cp a, 1
  jr nz, .done
  ; brick exists
  ld a, [de]
  add 1
  ld [de], a ; so draw bottom brick

.done

  pop hl ; jump back up
  pop bc
  ret

drawBricks:
  ld hl, BRICK_TABLE
  ld de, _SCRN0 + TOP_LEFT_BRICK_X + (TOP_LEFT_BRICK_Y / 2) * 32 ; writing to
  ld b, BRICK_ROWS / 2 ; 2 bricks per brick tile

.loop
  call drawBrickTileRow
  ; seek to the next row in SCRN0
  rept 32 - BRICK_PER_ROW ; bytes to the next row
    inc de
  endr
  
  dec b
  jp nz, .loop

  ret

; draws a row of brick tiles
; @param hl where to read
; @param de where to write
drawBrickTileRow:
  push bc
  ld b, BRICK_PER_ROW ; write 12 bricks

.loop
  call drawBrickTile

  inc hl
  inc de ; next tile
  dec b
  jp nz, .loop

.done
  ; we draw two rows of bricks at a time
  ; so now seek the the end of what we drew
  rept BRICK_PER_ROW
    inc hl
  endr

  pop bc
  ret

ballBrickBroadPhase:
  ; if ball y is < lowest brick y skip, no collision possible
  ; if ball y is > greatest brick y skip, no collision possible
  ; if ball x is < lowest brick x skip, no collision possible
  ; if ball x is > greatest brick x skip, no collision possible

  ; for each brick
  ; load the brick x1 (left)
  ; if x1 > ball x1 + 4
  ;   skip to next ball
  ; load the brick y1 and y2
  ; if y1 > ball y1 + 4 (top)
  ;   skip to next ball
  ; if we are still on this ball
  ; add to narrow phase
  ; this leaves us with 1/4 the checks in the narrow phase

  ; alternative ideas
  ; arrange the tiles in a grid in memory and treat them like
  ; a table
  ; translate the ball's x coord to a column
  ; select that column for the narrow phase
  ; maybe select 2 columns if the ball is on the edge of 2 columns?
  ; maybe select 2 columns by rounding up and rounding down (yeah)
  ; maybe kick out any bricks where lowest y less than ball y

  ; pseudo code
  ; load ball x and y
  ; divide x by 8 to get the column x
  ; check if that's even in the table, and stop if not
  ; step into the table by column x
  ; step down the column, adding bricks to the narrow list
  ret

ballBrickNarrowPhase:
  ; MVP just delete everything that made it to the narrow phase

  ; for each brick
  ; load the brick x1 and x2 (left and right x)
  ; if x1 > ball x1 && x2 > ball x2
  ;   skip to next ball
  ; load the brick y1 and y2
  ; if y1 > ball y1 && y2 > ball y2
  ;   skip to next ball
  ; if we are still on this ball
  ; this is a collision
  ret

updateBallPosition:
  ; increment x
  ld a, [BALL_X]
  ld hl, BALL_DX
  add a, [hl]

  ; save
  ld hl, BALL_X
  ld [hl], a

  ; increment y
  ld a, [BALL_Y]
  ld hl, BALL_DY
  add a, [hl]

  ; save
  ld hl, BALL_Y
  ld [hl], a

  ret

; magical number that makes the ball / wall collision look nice
; the ball is only 4 pixels across, which leaves 2 pixels on either
; side of the sprite... but 3 looks better
WALL_COLLISION_CONSTANT EQU 3

handleBallWallCollision:
.check_bottom
  ld a, [BALL_Y]
  cp FIELD_BOTTOM + WALL_COLLISION_CONSTANT ; 
  jr nz, .check_top

  ; if we hit we bounce up
  ld a, -1
  ld [BALL_DY], a

.check_top
  ld a, [BALL_Y]
  cp FIELD_TOP - WALL_COLLISION_CONSTANT
  jr nz, .check_right

  ; if we hit we bounce down
  ld a, 1
  ld [BALL_DY], a

.check_right
  ld a, [BALL_X]
  cp FIELD_RIGHT + WALL_COLLISION_CONSTANT
  jr nz, .check_left

  ; if we hit we bounce left
  ld a, -1
  ld [BALL_DX], a

.check_left
  ld a, [BALL_X]
  cp FIELD_LEFT - WALL_COLLISION_CONSTANT
  jr nz, .done

  ; if we hit we bounce right
  ld a, 1
  ld [BALL_DX], a

.done

  ret

ARBITRARY_WAIT_CONSTANT EQU 4000

pause:
  ld de, ARBITRARY_WAIT_CONSTANT
.loop:
  dec de
  ld a, d
  or e
  jr nz, .loop

  ret

blankSprites:
  ld hl, BALL_SPRITE_NO
  ld bc, 4 ; bytes per sprite
  ld d, 40 ; number of sprites
  ld e, TILE_BLANK
  call drawLine

  ret

START_Y EQU $0F * 8
START_X EQU $0F * 8

initSprites:
  call blankSprites

  ; init sprite data
  ld a, START_Y
  ld [BALL_Y], a
  ld a, START_X
  ld [BALL_X], a
  ld a, TILE_BALL 
  ld [BALL_SPRITE_NO], a
  ld a, 0
  ld [BALL_SPRITE_ATTRIBUTES], a

  ; init sprite physics
  ld a, 1
  ld [BALL_DX], a
  ld [BALL_DY], a

  ret

; @param de -- start of a row of VRAM
seekNextVRAM::
  push hl
  ld h, d
  ld l, e

  ld de, SCRN_VX_B ; width of SCRN0
  add hl, de ; advance to next row

  ld d, h
  ld e, l

  pop hl
  ret

; @param hl -- from
; @param b -- row count
; @param c -- row length
copyRowsToVRAM::
  ld de, _SCRN0

.loop
  call copyRowToVRAM

  call seekNextVRAM

  dec b
  jr nz, .loop

	ret

; @param hl -- from
; @param de -- to
; @param c -- row length
copyRowToVRAM::
  push bc ; save row length
  push de ; save initial write position

.loop
  ld a, [hl+]
  ld [de], a ; copy

  inc de ; next VRAM
  dec c
  jr nz, .loop

  pop de ; restore initial write position
  pop bc ; restore row length

	ret

; scratches a
drawChunk:
  push bc
  push hl

  ld hl, ArkanoidMap
  ld b, CHUNK_HEIGHT
  ld c, CHUNK_WIDTH
  call copyRowsToVRAM

  pop hl
  pop bc

  ret


; it draws the given tile byte once at the given address
; @param hl where
; @param e the tile
drawPoint:
  ld a, e
  ld [hl], a
  ret

; it draws the given tile byte the given number of times
; at the given interval, starting from the given address
; resulting in a "line" of the same tile
; @param hl where to start
; @param bc bytes per step
; @param d how many steps
; @param e the tile
drawLine:
.loop
  ld a, e
  ld [hl], a ; load the tile
  add hl, bc

  dec d
  ld a, 0
  cp d ; if a == d we are done
  jp nz, .loop

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

; write the blank tile to the whole SCRN0
blankScreen:
  ld hl, _SCRN0
  ld de, SCRN_SIZE
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

Section "level1", ROM0
Level1:
  db 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0
  db 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1
  db 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1
  db 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  db 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1
  db 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1
  db 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0
  db 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0
EndLevel1:

Section "GraphicsData", ROM0

ArkanoidTiles: INCBIN "assets/arkanoid-map.2bpp"
.end

ArkanoidGraphics: INCBIN "assets/arkanoid-graphics.2bpp"
.end

ArkanoidMap: INCBIN "assets/arkanoid-map.tilemap"
.end