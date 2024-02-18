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

; @TODO this name is wrong should be metatileIndexToTileIndex
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

ENDC	; end definition of map draw file
