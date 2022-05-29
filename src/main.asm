INCLUDE "includes/hardware.inc"

SCRN_VERTICAL_STEP EQU 32
SCRN_HORIZONTAL_STEP EQU 1
SCRN_SIZE EQU SCRN_VERTICAL_STEP * SCRN_VERTICAL_STEP
BG_WIDTH EQU 20
BG_HEIGHT EQU 18

; field includes the 8 px borders
FIELD_TOP EQU 16 + 8
FIELD_RIGHT EQU 160 - 8
FIELD_BOTTOM EQU 152 ; there is no border on the bottom
FIELD_LEFT EQU 8 + 8

; ball sprite
BALL_SPRITE_Y EQU _OAMRAM ; the first sprite in OAM
BALL_SPRITE_X EQU _OAMRAM+1
BALL_SPRITE_NO EQU _OAMRAM+2
BALL_SPRITE_ATTRIBUTES EQU _OAMRAM+3
 
COMMON_RAM EQU _RAM

rsset COMMON_RAM

; ball velocity
BALL_DX RB 1
BALL_DY RB 1

; brick position table
BRICK_SIZE EQU 1 ; just a flag to see if the brick exists

TOP_LEFT_BRICK_X EQU 4 ; 3 x 8 pixels over
TOP_LEFT_BRICK_Y EQU 6 ; 10 x 4 pixels down

BRICK_PER_ROW EQU 12
BRICK_ROWS EQU 8

MAX_BRICKS EQU BRICK_PER_ROW * BRICK_ROWS ; that's just a rectangle of bricks

BRICK_TABLE RB BRICK_SIZE * MAX_BRICKS

Section "start", ROM0[$0100]
  jp init

SECTION "main", ROM0[$150]

init:
  di

  call ZeroOutWorkRAM ; it is easier to inspect this way
  call initPalettes
  call turnOffLCD
  call loadTileData
  call loadBrickData
  call blankScreen
  call drawBorder
  call drawBricks
  call initSprites
  call turnOnLCD

main:
  call waitForVBlank
  call updateBallPosition
  call handleBallWallCollision

  call ballBrickBroadPhase
  call ballBrickNarrowPhase

  call pause

  jp main

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

.top
  ld a, 0
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
  ld a, [BALL_SPRITE_X]
  ld hl, BALL_DX
  add a, [hl]

  ; save it back to the sprite x
  ld hl, BALL_SPRITE_X
  ld [hl], a

  ; increment y
  ld a, [BALL_SPRITE_Y]
  ld hl, BALL_DY
  add a, [hl]

  ; save it back to the sprite y
  ld hl, BALL_SPRITE_Y
  ld [hl], a

  ret

; magical number that makes the ball / wall collision look nice
; the ball is only 4 pixels across, which leaves 2 pixels on either
; side of the sprite... but 3 looks better
WALL_COLLISION_CONSTANT EQU 3

handleBallWallCollision:
.check_bottom
  ld a, [BALL_SPRITE_Y]
  cp FIELD_BOTTOM + WALL_COLLISION_CONSTANT ; 
  jr nz, .check_top

  ; if we hit we bounce up
  ld a, -1
  ld [BALL_DY], a

.check_top
  ld a, [BALL_SPRITE_Y]
  cp FIELD_TOP - WALL_COLLISION_CONSTANT
  jr nz, .check_right

  ; if we hit we bounce down
  ld a, 1
  ld [BALL_DY], a

.check_right
  ld a, [BALL_SPRITE_X]
  cp FIELD_RIGHT + WALL_COLLISION_CONSTANT
  jr nz, .check_left

  ; if we hit we bounce left
  ld a, -1
  ld [BALL_DX], a

.check_left
  ld a, [BALL_SPRITE_X]
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

START_Y EQU 30
START_X EQU 30

initSprites:
  call blankSprites

  ; init sprite data
  ld a, START_Y
  ld [BALL_SPRITE_Y], a
  ld a, START_X
  ld [BALL_SPRITE_X], a
  ld a, TILE_BALL 
  ld [BALL_SPRITE_NO], a
  ld a, 0
  ld [BALL_SPRITE_ATTRIBUTES], a

  ; init sprite physics
  ld a, 1
  ld [BALL_DX], a
  ld [BALL_DY], a

  ret

; scratches a
drawBorder:
  push bc
  push de
  push hl

  ; left
  ld hl, _SCRN0
  ld bc, SCRN_VERTICAL_STEP
  ld d, BG_HEIGHT
  ld e, BORDER_LEFT
  call drawLine

  ; top
  ld hl, _SCRN0
  ld bc, SCRN_HORIZONTAL_STEP
  ld d, BG_WIDTH
  ld e, BORDER_TOP
  call drawLine

  ; right
  ld hl, _SCRN0 + BG_WIDTH - 1
  ld bc, SCRN_VERTICAL_STEP
  ld d, BG_HEIGHT
  ld e, BORDER_RIGHT
  call drawLine

  ; corners

  ld hl, _SCRN0
  ld e, BORDER_TOP_LEFT
  call drawPoint

  ld hl, _SCRN0 + BG_WIDTH - 1
  ld e, BORDER_TOP_RIGHT
  call drawPoint

  pop hl
  pop de
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


loadTileData:
  ld hl, TileData
  ld de, _VRAM
  ld b, EndTileData - TileData

.loadData
  ld a, [hl]
  ld [de], a
  dec b
  jr z, .doneLoading
  inc hl
  inc de
  jr .loadData
.doneLoading
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

TileData:
opt g.123
TILE_BLANK EQU 0
  dw `........
  dw `........
  dw `........
  dw `........
  dw `........
  dw `........
  dw `........
  dw `........

BRICK_BOTTOM EQU 1
  dw `........
  dw `........
  dw `........
  dw `........
  dw `11111113
  dw `1......3
  dw `1......3
  dw `33333333

BRICK_TOP EQU 2
  dw `11111113
  dw `1......3
  dw `1......3
  dw `33333333
  dw `........
  dw `........
  dw `........
  dw `........

BRICK_DOUBLE EQU 3
  dw `11111113
  dw `1......3
  dw `1......3
  dw `33333333
  dw `11111113
  dw `1......3
  dw `1......3
  dw `33333333

BORDER_LEFT EQU 4
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223
  dw `32111223

BORDER_TOP EQU 5
  dw `33333333
  dw `22222222
  dw `11111111
  dw `11111111
  dw `11111111
  dw `22222222
  dw `22222222
  dw `33333333

BORDER_RIGHT EQU 6
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123
  dw `32211123

BORDER_TOP_LEFT EQU 7
  dw `33333333
  dw `33222222
  dw `32311111
  dw `32121111
  dw `32112111
  dw `32111322
  dw `32111232
  dw `32111223

BORDER_TOP_RIGHT EQU 8
  dw `33333333
  dw `22222233
  dw `11111323
  dw `11112123
  dw `11121123
  dw `22311123
  dw `23211123
  dw `32211123

TILE_BALL EQU 9
  dw `........
  dw `........
  dw `...33...
  dw `..3.33..
  dw `..3333..
  dw `...33...
  dw `........
  dw `........

EndTileData:

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