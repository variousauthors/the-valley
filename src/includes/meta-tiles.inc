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

; 
; ld hl, MetaTiles ; 1111 1111 0000 0000
; ld a, index ; we only have 16 tiles so only the lower half of l is used for index
; add a, $F ; advance to next tile
; so we need 4 tables for tiles, 1 table for collision info
; and then 8 palettes... so like

; 0000 NNNN ; 1st tile index of meta tile N
; 0001 NNNN ; 2nd tile index of meta tile N
; 0010 NNNN ; 3rd tile index of meta tile N
; 0011 NNNN ; 4th tile index of meta tile N
; 0110 NNNN ; BG tile attribute data for meta tile N
; 0101 NNNN ; collision data for meta tile N

; so we store 6 bytes per meta-tile
; each map has different meta-tiles, but that just determines
; what exactly the first 4 bytes are refering too, we don't
; need to duplicate this per map

Section "metatile methods", ROM0

; @param a - meta tile index
; @param l - tile position
metaTileIndexToAddress:
  ld l, a

  ; tiles are arranged in memory such that
  ; multiplying the metatile index by 4 gets
  ; the tile index of the start of the metatile
  sla l
  sla l

  ret

/** the tile index at the top left
 * is a multiple of 4 or in other words
 * it is aligned to 2 bits 
 * so we can just use the low 2 bits
 * to select the tile within the metatile */
META_TILE_TOP_LEFT EQU %00000000
META_TILE_BOTTOM_LEFT EQU %00000001
META_TILE_TOP_RIGHT EQU %00000010
META_TILE_BOTTOM_RIGHT EQU %00000011

; @param l - index of the first tile in the meta tile
; @return a - index of top left tile
getMetaTileTopLeft:
  ld a, l
  or META_TILE_TOP_LEFT

  ret

; @param l - index of the first tile in the meta tile
; @return a - index of bottom left tile
getMetaTileBottomLeft:
  ld a, l
  or META_TILE_BOTTOM_LEFT

  ret

; @param l - index of the first tile in the meta tile
; @return a - index of top right tile
getMetaTileTopRight:
  ld a, l
  or META_TILE_TOP_RIGHT

  ret

; @param l - index of the first tile in the meta tile
; @return a - index of bottom right tile
getMetaTileBottomRight:
  ld a, l
  or META_TILE_BOTTOM_RIGHT

  ret

getMetaTileAttributes:
  ld a, l
  and a, %00001111 ; recover the index
  add a, %01000000 ; set to bottom left
  ld l, a

  ret

; @param hl - some part of a meta tile
; @return hl - the next part
getNextTileFromMetaTile:
  ret

Section "metatiles", ROM0, Align[8]

MetaTileAttributes:
  db META_TILE ; NULL
  db META_TILE  ; TREE
  db META_TILE | OBSTACLE  ; MOUNTAIN
  db META_TILE ; PASSABLE WALL
  db META_TILE | OBSTACLE  ; SHALLOW WATER
  db META_TILE  ; BRIDGE
  db META_TILE  ; GRASS
  db META_TILE  ; HILL
  db META_TILE ; RUINS
  db META_TILE ; ENTRANCE
  db META_TILE  ; SAND
  db META_TILE | OBSTACLE ; WALL
  db META_TILE ; PATH
  db META_TILE ; STAIRS_DOWN
  db META_TILE ; STAIRS_UP
  db META_TILE ; SWAMP

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
