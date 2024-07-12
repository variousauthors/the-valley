IF !DEF(SPRITE_UTILS_INC)
SPRITE_UTILS_INC = 1

SECTION "SpriteDataTable", ROM0, ALIGN[1]

; AllocateSpriteData spriteIndex, attributes
MACRO AllocateSpriteData
  db \1, \2
ENDM

SpriteDataTable:
  ; player sprite
  AllocateSpriteData 0, 0
  ; boat sprite
  AllocateSpriteData 4, OAMF_PAL1
  ; encounter sprite
  AllocateSpriteData 8, 0
  ; elder sprite
  AllocateSpriteData 12, 0

SPRITE_DATA_SIZE EQU 2

SECTION "SpriteUtils", ROM0

PLAYER_SPRITE_INDEX EQU 0
BOAT_SPRITE_INDEX EQU 1
ENCOUNTER_SPRITE_INDEX EQU 2
ELDER_SPRITE_INDEX EQU 3

; @TODO the sprite data table should contain this VRAM index
; then we just need a, bc
; @param a - VRAM index of sprite to draw, first tile
; @param bc - y, x position in screen pixels
; @param d - index into sprite data table
; @destroys de
; @destroys hl
; draws a four tile sprite
drawSprite:
  ; we need to increment a each time

  push af

  ld a, d
  sla a ; sprite data is two bytes
  ld hl, SpriteDataTable
  call addAToHL

  ; determine _where_ to draw in OAM
  ld a, [hl+]
  sla a
  sla a ; 4 bytes per sprite
  ld de, Sprites

  call addAToDE

  ; do the y, x position
  ld a, 16 - 1 ; adjusts for sprites "half off" the screen, we might want to do this outside the func so we _can_ show things half off lol
  ; the y position is offset by 1 so that sprites float a bit above the tile
  add a, b ; player position y
  ld [de], a
  inc de
  ld a, 8 ; x-position is not offset
  add a, c ; player position x
  ld [de], a
  inc de

  pop af ; recover tile to draw
  ld [de], a ; draw
  inc de
  inc a ; advance to next tile
  push af ; save for next tile

  ld a, [hl] ; attr
  ld [de], a
  inc de ; advance to next sprite

  ; draw the next tile

  ; do the y, x position
  ld a, 16 + 8 - 1 ; adjusts for sprites "half off" the screen, we might want to do this outside the func so we _can_ show things half off lol
  ; the y position is offset by 1 so that sprites float a bit above the tile
  add a, b ; player position y
  ld [de], a
  inc de
  ld a, 8 ; x-position is not offset
  add a, c ; player position x
  ld [de], a
  inc de

  pop af ; recover tile to draw
  ld [de], a ; draw
  inc de
  inc a ; advance to next tile
  push af ; save for next tile

  ld a, [hl] ; attr
  ld [de], a
  inc de

  ; draw the next tile

  ; do the y, x position
  ld a, 16 - 1 ; adjusts for sprites "half off" the screen, we might want to do this outside the func so we _can_ show things half off lol
  ; the y position is offset by 1 so that sprites float a bit above the tile
  add a, b ; player position y
  ld [de], a
  inc de
  ld a, 8 + 8 ; x-position is not offset
  add a, c ; player position x
  ld [de], a
  inc de

  pop af ; recover tile to draw
  ld [de], a ; draw
  inc de
  inc a ; advance to next tile
  push af ; save for next tile

  ld a, [hl] ; attr
  ld [de], a
  inc de

  ; draw the next tile

  ; do the y, x position
  ld a, 16 + 8 - 1 ; adjusts for sprites "half off" the screen, we might want to do this outside the func so we _can_ show things half off lol
  ; the y position is offset by 1 so that sprites float a bit above the tile
  add a, b ; player position y
  ld [de], a
  inc de
  ld a, 8 + 8 ; x-position is not offset
  add a, c ; player position x
  ld [de], a
  inc de

  pop af ; recover tile to draw
  ld [de], a ; draw
  inc de
  inc a ; advance to next tile

  ld a, [hl] ; attr
  ld [de], a
  inc de

  ret

; @param a - sprite index 
undrawSprite:
  sla a ; sprite data is two bytes
  ld hl, SpriteDataTable
  call addAToHL

  ld a, [hl] ; get the OAM position
  sla a
  sla a ; 4 bytes per sprite
  ld hl, Sprites

  call addAToHL

  ld a, 0
  ld [hl+], a
  ld [hl+], a
  ld [hl+], a
  ld [hl], a
  ld [hl+], a
  ld [hl+], a
  ld [hl+], a
  ld [hl], a
  ld [hl+], a
  ld [hl+], a
  ld [hl+], a
  ld [hl], a
  ld [hl+], a
  ld [hl+], a
  ld [hl+], a
  ld [hl], a

  ret

ENDC
