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
META_TILE_COUNT EQU 16 ; <--- REMEMBER TO INCREMENT THIS
; ALSO REMEMBER TO INCREMENT THE "OVERWORLD_TILES_COUNT" in main

MetaTiles:
MT_TOP_LEFT:
  db 0 ; NULL
  db 1 ; TREE
  db 5 ; MOUNTAIN
  db 9 ; DEEP WATER
  db 10 ; SHALLOW WATER
  db 11 ; BRIDGE
  db 0 ; GRASS
  db 0 ; HILL
  db 20 ; SAND
  db 21 ; ENTRANCE
  db 25 ; RUINS
  db 29 ; WALL
  db 33 ; PATH
  db 37 ; STAIRS_DOWN
  db 41 ; STAIRS_UP
  db 45 ; SWAMP
  ds META_TILE_MAX - META_TILE_COUNT

MT_BOTTOM_LEFT:
  db 0 ; NULL
  db 2 ; TREE
  db 6 ; MOUNTAIN
  db 9 ; DEEP WATER
  db 10 ; SHALLOW WATER
  db 12 ; BRIDGE
  db 15 ; GRASS
  db 17 ; HILL
  db 20 ; SAND
  db 22 ; ENTRANCE
  db 26 ; RUINS
  db 30 ; WALL
  db 34 ; PATH
  db 38 ; STAIRS_DOWN
  db 42 ; STAIRS_UP
  db 46 ; SWAMP

  ds META_TILE_MAX - META_TILE_COUNT

MT_TOP_RIGHT:
  db 0 ; NULL
  db 3 ; TREE
  db 7 ; MOUNTAIN
  db 9 ; DEEP WATER
  db 10 ; SHALLOW WATER
  db 13 ; BRIDGE
  db 16 ; GRASS
  db 18 ; HILL
  db 20 ; SAND
  db 23 ; ENTRANCE
  db 27 ; RUINS
  db 31 ; WALL
  db 35 ; PATH
  db 39 ; STAIRS_DOWN
  db 43 ; STAIRS_UP
  db 47 ; SWAMP

  ds META_TILE_MAX - META_TILE_COUNT

MT_BOTTOM_RIGHT:
  db 0 ; NULL
  db 4 ; TREE
  db 8 ; MOUNTAIN
  db 9 ; DEEP WATER
  db 10 ; SHALLOW WATER
  db 14 ; BRIDGE
  db 0 ; GRASS
  db 19 ; HILL
  db 20 ; SAND
  db 24 ; ENTRANCE
  db 28 ; RUINS
  db 32 ; WALL
  db 36 ; PATH
  db 40 ; STAIRS_DOWN
  db 44 ; STAIRS_UP
  db 48 ; SWAMP

  ds META_TILE_MAX - META_TILE_COUNT

MetaTileAttributes:
  db META_TILE ; NULL
  db META_TILE  ; TREE
  db META_TILE | OBSTACLE  ; MOUNTAIN
  db META_TILE | OBSTACLE  ; DEEP WATER
  db META_TILE | OBSTACLE  ; SHALLOW WATER
  db META_TILE  ; BRIDGE
  db META_TILE  ; GRASS
  db META_TILE  ; HILL
  db META_TILE  ; SAND
  db META_TILE ; ENTRANCE
  db META_TILE ; RUINS
  db META_TILE | OBSTACLE ; WALL
  db META_TILE ; PATH
  db META_TILE ; STAIRS_DOWN
  db META_TILE ; STAIRS_UP
  db META_TILE ; SWAMP

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

ENDC	; end definition of map draw file
