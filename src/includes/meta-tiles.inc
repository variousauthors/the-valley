IF !DEF(META_TILES_INC)
META_TILES_INC = 1

; meta tile enum
PLAIN EQU 0 ; NULL
TREE EQU 1
ROCK EQU 2
DEEP_WATER EQU 3
SHALLOW_WATER EQU 4
GRASS EQU 5
TREE_WITH_EVENT EQU 3

Section "metatiles", ROM0, Align[8]

; store each tile striped across 4 tables of 256
; so you have an index like 36
; ld hl, MetaTiles ; 1111 1111 0000 0000
; ld a, index
; ld l, a ; now we have tile 0
; inc h ; now you have tile 1
; repeat 4 times
; then one more time for the attributes

/** later on when I decide how many tiles I actually need,
 * I can use the extra bits in l for something... for example
 * I can use the two highest bits for passable and event
 * and still have bits left over for 64 meta tiles
 * then we would not need TREE_WITH_EVENT as a separate entry
 *
 * oh but... I guess that is probably wasteful, since _most_
 * tiles will not have anything set for either bit... I guess
 * it is less wasteful than just not using those bits if, for
 * example, we only have 64 meta tiles in the whole game (which
 * feels entirely possible).
 * 
 * time will tell!
 */

; meta tile id table
META_TILE_MAX EQU 256
META_TILE_COUNT EQU 27 ; <--- REMEMBER TO INCREMENT THIS
; ALSO REMEMBER TO INCREMENT THE "OVERWORLD_TILES_COUNT" in main

MetaTiles:
MT_TOP_LEFT:
  db 0 ; NULL
  db 1 ; TREE
  db 5 ; ROCK
  db 9 ; DEEP WATER
  db 10 ; SHALLOW WATER

  db 11 ; GRASS
  db 15 ; BRIDGE
  db 19 ; DEEP_TL
  db 9 ; DEEP_BL
  db 9 ; DEEP_TR

  db 9 ; DEEP_BR
  db 23 ; SHALLOW_TL
  db 10 ; SHALLOW_BL
  db 10 ; SHALLOW_TR
  db 10 ; SHALLOW_BR

  db 31 ; CLIFF FACE LOW
  db 27 ; CLIFF FACE HIGH
  db 43 ; CLIFF EDGE LEFT
  db 41 ; CLIFF INVERSE CORNER LEFT
  db 39 ; CLIFF CORNER BL

  db 0 ; CLIFF INVERSE CORNER RIGHT
  db 0 ; CLIFF EDGE RIGHT
  db 27 ; CLIFF CORNER BR
  db 32 ; CAVE ENTRANCE
  db 36 ; CLIFF CORNER TL

  db 37 ; CLIFF EDGE TOP
  db 37 ; CLIFF CORNER TR

  ds META_TILE_MAX - META_TILE_COUNT

MT_BOTTOM_LEFT:
  db 0 ; NULL
  db 2 ; TREE
  db 6 ; ROCK
  db 9 ; DEEP WATER
  db 10 ; SHALLOW WATER

  db 12 ; GRASS
  db 16 ; BRIDGE
  db 9 ; DEEP_TL
  db 20 ; DEEP_BL
  db 9 ; DEEP_TR

  db 9 ; DEEP_BR
  db 10 ; SHALLOW_TL
  db 24 ; SHALLOW_BL
  db 10 ; SHALLOW_TR
  db 10 ; SHALLOW_BR

  db 29 ; CLIFF FACE LOW
  db 31 ; CLIFF FACE HIGH
  db 44 ; CLIFF EDGE LEFT
  db 44 ; CLIFF INVERSE CORNER LEFT
  db 31 ; CLIFF CORNER BL

  db 0 ; CLIFF INVERSE CORNER RIGHT
  db 0 ; CLIFF EDGE RIGHT
  db 31 ; CLIFF CORNER BR
  db 33 ; CAVE ENTRANCE
  db 43 ; CLIFF CORNER TL

  db 0 ; CLIFF EDGE TOP
  db 0 ; CLIFF CORNER TR

  ds META_TILE_MAX - META_TILE_COUNT

MT_TOP_RIGHT:
  db 0 ; NULL
  db 3 ; TREE
  db 7 ; ROCK
  db 9 ; DEEP WATER
  db 10 ; SHALLOW WATER

  db 13 ; GRASS
  db 17 ; BRIDGE
  db 9 ; DEEP_TL
  db 9 ; DEEP_BL
  db 21 ; DEEP_TR

  db 9 ; DEEP_BR
  db 10 ; SHALLOW_TL
  db 10 ; SHALLOW_BL
  db 25 ; SHALLOW_TR
  db 10 ; SHALLOW_BR

  db 31 ; CLIFF FACE LOW
  db 28 ; CLIFF FACE HIGH
  db 0 ; CLIFF EDGE LEFT
  db 0 ; CLIFF INVERSE CORNER LEFT
  db 28 ; CLIFF CORNER BL

  db 42 ; CLIFF INVERSE CORNER RIGHT
  db 45 ; CLIFF EDGE RIGHT
  db 40 ; CLIFF CORNER BR
  db 34 ; CAVE ENTRANCE
  db 37 ; CLIFF CORNER TL

  db 37 ; CLIFF EDGE TOP
  db 38 ; CLIFF CORNER TR

  ds META_TILE_MAX - META_TILE_COUNT

MT_BOTTOM_RIGHT:
  db 0 ; NULL
  db 4 ; TREE
  db 8 ; ROCK
  db 9 ; DEEP WATER
  db 10 ; SHALLOW WATER

  db 14 ; GRASS
  db 18 ; BRIDGE
  db 9 ; DEEP_TL
  db 9 ; DEEP_BL
  db 9 ; DEEP_TR

  db 22 ; DEEP_BR
  db 10 ; SHALLOW_TL
  db 10 ; SHALLOW_BL
  db 10 ; SHALLOW_TR
  db 26 ; SHALLOW_BR

  db 30 ; CLIFF FACE LOW
  db 31 ; CLIFF FACE HIGH
  db 0 ; CLIFF EDGE LEFT
  db 0 ; CLIFF INVERSE CORNER LEFT
  db 31 ; CLIFF CORNER BL

  db 46 ; CLIFF INVERSE CORNER RIGHT
  db 46 ; CLIFF EDGE RIGHT
  db 31 ; CLIFF CORNER BR
  db 35 ; CAVE ENTRANCE
  db 0 ; CLIFF CORNER TL

  db 0 ; CLIFF EDGE TOP
  db 46 ; CLIFF CORNER TR

  ds META_TILE_MAX - META_TILE_COUNT

MetaTileAttributes:
  db META_TILE ; NULL
  db META_TILE | OBSTACLE ; TREE
  db META_TILE | OBSTACLE ; ROCK
  db META_TILE | OBSTACLE ; DEEP WATER
  db META_TILE | OBSTACLE ; SHALLOW WATER
  db META_TILE  ; GRASS
  db META_TILE  ; BRIDGE
  db META_TILE | OBSTACLE ; DEEP_TL
  db META_TILE | OBSTACLE ; DEEP_BL
  db META_TILE | OBSTACLE ; DEEP_TR
  db META_TILE | OBSTACLE ; DEEP_RB
  db META_TILE | OBSTACLE ; SHALLOW_TL
  db META_TILE | OBSTACLE ; SHALLOW_BL
  db META_TILE | OBSTACLE ; SHALLOW_TR
  db META_TILE | OBSTACLE ; SHALLOW_RB
  db META_TILE ; CLIFF FACE LOW
  db META_TILE ; CLIFF FACE HIGH
  db META_TILE ; CLIFF EDGE LEFT
  db META_TILE ; CLIFF INVERSE CORNER LEFT
  db META_TILE ; CLIFF CORNER BL

  db META_TILE ; CLIFF INVERSE CORNER RIGHT
  db META_TILE ; CLIFF EDGE RIGHT
  db META_TILE ; CLIFF CORNER BR
  db META_TILE ; CAVE ENTRANCE
  db META_TILE ; CLIFF CORNER TL

  db META_TILE ; CLIFF EDGE TOP
  db META_TILE ; CLIFF CORNER TR

  ds META_TILE_MAX - META_TILE_COUNT

META_TILE EQU %00000000
OBSTACLE EQU %01000000
EVENT EQU %00100000

/* attributes
Bit 7    BG-to-OAM Priority         (0=Use OAM Priority bit, 1=BG Priority)
Bit 6    Passable                   (0=Normal, 1=Obstacle)
Bit 5    Event                      (0=Normal, 1=Event)
Bit 4    Not used
Bit 3    Tile VRAM Bank number      (0=Bank 0, 1=Bank 1)
Bit 2-0  Background Palette number  (BGP0-7)

Remember to zero out bits 5 and 6 when writing to the bg attributes table
*/

/** we need to record whether a tile is passable in many ways: 
 * 4 bits: blocking edges (up/right/down/left), 
 * 4 bits: layer (for passing under, we probably only need like 1 bit or 2 maybe)

 * player can't move INTO a tile blocking agains their direction
 * player can't move OUT of a tile blocking with their direction
 */
B_UP EQU %10000000
B_RIGHT EQU %01000000
B_DOWN EQU %00100000
B_LEFT EQU %00010000
B_OBSTACLE EQU %11110000

MetaTileCollision:
  db META_TILE ; NULL
  db META_TILE | B_OBSTACLE ; TREE
  db META_TILE | B_OBSTACLE ; ROCK
  db META_TILE | B_OBSTACLE ; DEEP WATER
  db META_TILE | B_OBSTACLE ; SHALLOW WATER
  db META_TILE  ; GRASS
  db META_TILE  ; BRIDGE
  db META_TILE | B_OBSTACLE ; DEEP_TL
  db META_TILE | B_OBSTACLE ; DEEP_BL
  db META_TILE | B_OBSTACLE ; DEEP_TR
  db META_TILE | B_OBSTACLE ; DEEP_RB
  db META_TILE | B_OBSTACLE ; SHALLOW_TL
  db META_TILE | B_OBSTACLE ; SHALLOW_BL
  db META_TILE | B_OBSTACLE ; SHALLOW_TR
  db META_TILE | B_OBSTACLE ; SHALLOW_RB

  db META_TILE | B_DOWN ; CLIFF FACE LOW
  db META_TILE | B_UP ; CLIFF FACE HIGH
  db META_TILE | B_LEFT ; CLIFF EDGE LEFT
  db META_TILE | B_LEFT ; CLIFF INVERSE CORNER LEFT
  db META_TILE | B_DOWN | B_LEFT ; CLIFF CORNER BL

  db META_TILE | B_RIGHT ; CLIFF INVERSE CORNER RIGHT
  db META_TILE | B_RIGHT ; CLIFF EDGE RIGHT
  db META_TILE | B_DOWN | B_RIGHT ; CLIFF CORNER BR
  db META_TILE ; CAVE ENTRANCE
  db META_TILE | B_UP | B_LEFT ; CLIFF CORNER TL

  db META_TILE | B_UP ; CLIFF EDGE TOP
  db META_TILE | B_UP | B_RIGHT ; CLIFF CORNER TR



  ds META_TILE_MAX - META_TILE_COUNT

ENDC	; end definition of map draw file
