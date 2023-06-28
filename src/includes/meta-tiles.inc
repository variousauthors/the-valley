IF !DEF(META_TILES_INC)
META_TILES_INC = 1

; meta tile id table
META_TILE_MAX EQU 256
META_TILE_COUNT EQU 4

; meta tile enum
GRASS EQU 0
TREE EQU 1
ROCK EQU 2
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

MetaTiles:
MT0:
  db 0 ; GRASS
  db 1 ; TREE
  db 3 ; ROCK
  db 1 ; TREE_WITH_EVENT
  ds META_TILE_MAX - META_TILE_COUNT

MT1:
  db 0 ; GRASS
  db 2 ; TREE
  db 4 ; ROCK
  db 2 ; TREE_WITH_EVENT
  ds META_TILE_MAX - META_TILE_COUNT

MT2:
  db 0 ; GRASS
  db 5 ; TREE
  db 7 ; ROCK
  db 5 ; TREE_WITH_EVENT
  ds META_TILE_MAX - META_TILE_COUNT

MT3:
  db 0 ; GRASS
  db 6 ; TREE
  db 8 ; ROCK
  db 6 ; TREE_WITH_EVENT
  ds META_TILE_MAX - META_TILE_COUNT

MetaTileAttributes:
  db META_TILE ; GRASS
  db META_TILE | OBSTACLE ; TREE
  db META_TILE | OBSTACLE ; ROCK
  db META_TILE | OBSTACLE | EVENT ; TREE_WITH_EVENT
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
