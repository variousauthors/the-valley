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

; l is an index so it will always be in the range 0 - 15
; so I don't need the first and

; @param l - index
; @return hl - meta tile top left
metaTileIndexToAddress:
  ld h, HIGH(MetaTiles)

  ret

; @param hl - some meta tile address
; @return hl - that meta tile top left
getMetaTileTopLeft:
  ld a, l
  and a, %00001111 ; recover the index
  ld l, a

  ret

getMetaTileBottomLeft:
  ld a, l
  and a, %00001111 ; recover the index
  add a, %00010000 ; set to bottom left
  ld l, a

  ret

getMetaTileTopRight:
  ld a, l
  and a, %00001111 ; recover the index
  add a, %00100000 ; set to bottom left
  ld l, a

  ret

getMetaTileBottomRight:
  ld a, l
  and a, %00001111 ; recover the index
  add a, %00110000 ; set to bottom left
  ld l, a

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

MetaTiles:
MT_TOP_LEFT:
  db 0 ; NULL
  db 4 ; TREE
  db 8 ; MOUNTAIN
  db 12 ; PASSABLE WALL
  db 16 ; SHALLOW WATER
  db 20 ; BRIDGE
  db 24 ; GRASS
  db 28 ; HILL
  db 32 ; RUINS
  db 36 ; ENTRANCE
  db 40 ; TOWER
  db 44 ; WALL
  db 48 ; PATH
  db 52 ; STAIRS_DOWN
  db 56 ; STAIRS_UP
  db 60 ; SWAMP

MT_BOTTOM_LEFT:
  db 1 ; NULL
  db 5 ; TREE
  db 9 ; MOUNTAIN
  db 13 ; PASSABLE WALL
  db 17 ; SHALLOW WATER
  db 21 ; BRIDGE
  db 25 ; GRASS
  db 29 ; HILL
  db 33 ; RUINS
  db 37 ; ENTRANCE
  db 41 ; TOWER
  db 45 ; WALL
  db 49 ; PATH
  db 53 ; STAIRS_DOWN
  db 57 ; STAIRS_UP
  db 61 ; SWAMP

MT_TOP_RIGHT:
  db 2 ; NULL
  db 6 ; TREE
  db 10 ; MOUNTAIN
  db 14 ; PASSABLE WALL
  db 18 ; SHALLOW WATER
  db 22 ; BRIDGE
  db 26 ; GRASS
  db 30 ; HILL
  db 34 ; RUINS
  db 38 ; ENTRANCE
  db 42 ; TOWER
  db 46 ; WALL
  db 50 ; PATH
  db 54 ; STAIRS_DOWN
  db 58 ; STAIRS_UP
  db 62 ; SWAMP

MT_BOTTOM_RIGHT:
  db 3 ; NULL
  db 7 ; TREE
  db 11 ; MOUNTAIN
  db 15 ; PASSABLE WALL
  db 19 ; SHALLOW WATER
  db 23 ; BRIDGE
  db 27 ; GRASS
  db 31 ; HILL
  db 35 ; RUINS
  db 39 ; ENTRANCE
  db 43 ; TOWER
  db 47 ; WALL
  db 51 ; PATH
  db 55 ; STAIRS_DOWN
  db 59 ; STAIRS_UP
  db 63 ; SWAMP

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
