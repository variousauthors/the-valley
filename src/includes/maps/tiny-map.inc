IF !DEF(TINY_MAP_INC)
TINY_MAP_INC = 1

Section "TinyMap", ROM0
  db NO_BOUNDS
TinyMap:
  db 5, 4, 
  db HIGH(TinyMapAutoEvents), LOW(TinyMapAutoEvents), 
  db HIGH(InteriorTileset), LOW(InteriorTileset), 
  db HIGH(OverworldEncounters), LOW(OverworldEncounters), 
  db HIGH(TinyMapBumpEvents), LOW(TinyMapBumpEvents)
  db HIGH(TinyMapEntities), LOW(TinyMapEntities),
  db $36, $66, 
  db $66, $66, 
  db $66, $66, 
  db $66, $66, 
  db $66, $66, 

TinyMapAutoEvents:
  /** entrance */
  AllocateTransportEvent 2, 3, HIGH(Overworld), LOW(Overworld), 27, 46

  EndList

TinyMapBumpEvents:
  EndList

TinyMapEntities:
  ld b, 2
  ld c, 2
  call initElder
  ret

ENDC