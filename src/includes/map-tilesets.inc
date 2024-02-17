IF !DEF(MAP_TILESETS_INC)
MAP_TILESETS_INC = 1

Section "MapTilesets", ROM0

PASSABLE EQU %00000000
UNPASSABLE EQU %00000001
SAFE EQU %00000010

EMPTY_TILE EQU $00
FOREST_TILE EQU $01
MOUNTAIN_TILE EQU $02

OverworldTileset:
  db $00, $01, $02, $09, $03, $04, $05, $06,
  db $08, $07, $0E, $09, $21, $23, $0C, $0D,

OverworldTilesetAttributes:
  db
/** this tileset is just like overworld but it has
 * bricks and stairs and such, it was used for
 * the underworld, but also villages and such */
InteriorTileset:
  db $00, $22, $02, $09, $03, $04, $05, $06,
  db $08, $07, $0E, $09, $0A, $0B, $0C, $0D,

ENDC