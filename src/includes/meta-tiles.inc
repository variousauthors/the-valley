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
META_TILE_COUNT EQU 15 ; <--- REMEMBER TO INCREMENT THIS
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
