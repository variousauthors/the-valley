IF !DEF(OVERWORLD_INC)
OVERWORLD_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "Overworld", ROM0
Overworld:
  db 36, 50, HIGH(OverworldAutoEvents), LOW(OverworldAutoEvents), HIGH(StartTileset), LOW(StartTileset)
  db $44, $42, $22, $76, $66, $64, $44, $44, $26, $66, $67, $22, $22, $24, $44, $ff, $f4, $44, $44, $44, $12, $66, $66, $44, $44, 
  db $44, $67, $22, $22, $76, $66, $44, $47, $22, $76, $66, $67, $22, $22, $1f, $f1, $ff, $ff, $4f, $41, $62, $26, $66, $64, $44, 
  db $46, $16, $72, $22, $29, $66, $65, $66, $77, $66, $66, $66, $72, $22, $21, $11, $1f, $66, $f4, $f4, $61, $26, $ff, $66, $44, 
  db $46, $11, $67, $22, $27, $66, $64, $72, $27, $66, $66, $66, $67, $22, $22, $11, $f6, $66, $61, $4f, $f6, $6f, $44, $f6, $56, 
  db $46, $11, $16, $92, $62, $77, $24, $22, $22, $77, $66, $66, $66, $22, $91, $21, $1f, $16, $14, $f4, $4f, $f4, $4f, $44, $46, 
  db $61, $16, $11, $72, $27, $27, $44, $22, $22, $22, $22, $27, $66, $62, $21, $12, $21, $f4, $ff, $44, $44, $44, $44, $44, $46, 
  db $11, $11, $11, $67, $22, $27, $42, $22, $29, $27, $22, $22, $76, $67, $21, $11, $21, $44, $44, $44, $44, $44, $44, $44, $46, 
  db $11, $12, $11, $66, $72, $22, $42, $27, $26, $66, $72, $22, $26, $66, $22, $11, $12, $44, $ff, $64, $f4, $24, $44, $44, $46, 
  db $46, $11, $27, $27, $72, $22, $44, $21, $12, $16, $67, $22, $26, $66, $72, $21, $11, $24, $f6, $f6, $4f, $62, $41, $44, $26, 
  db $41, $11, $12, $22, $71, $12, $65, $11, $17, $21, $66, $72, $26, $66, $62, $22, $16, $65, $6f, $66, $56, $f6, $2f, $42, $16, 
  db $41, $11, $67, $22, $22, $26, $64, $86, $11, $22, $11, $22, $27, $66, $67, $22, $16, $f4, $ff, $f4, $f4, $66, $56, $42, $14, 
  db $11, $16, $72, $21, $27, $66, $44, $41, $61, $17, $21, $72, $22, $27, $66, $72, $64, $6f, $4f, $44, $44, $f2, $44, $11, $64, 
  db $11, $11, $72, $11, $12, $61, $44, $44, $66, $66, $21, $72, $22, $22, $76, $72, $24, $26, $f4, $4f, $f4, $f6, $24, $14, $44, 
  db $61, $16, $17, $12, $22, $61, $44, $44, $44, $16, $27, $27, $22, $22, $27, $22, $24, $42, $ff, $f4, $4f, $46, $24, $65, $64, 
  db $61, $11, $17, $22, $12, $26, $81, $44, $a4, $41, $12, $21, $71, $22, $27, $22, $22, $42, $66, $65, $14, $f6, $24, $44, $16, 
  db $62, $61, $11, $71, $12, $76, $66, $64, $44, $41, $72, $76, $16, $12, $27, $79, $26, $21, $66, $44, $65, $66, $44, $44, $26, 
  db $47, $21, $11, $71, $22, $27, $66, $24, $14, $48, $22, $27, $76, $62, $22, $77, $26, $21, $14, $4f, $64, $44, $44, $44, $26, 
  db $44, $22, $11, $21, $77, $27, $72, $24, $11, $17, $22, $22, $16, $96, $22, $22, $26, $62, $14, $f4, $f6, $44, $44, $42, $21, 
  db $44, $42, $11, $26, $17, $22, $77, $94, $47, $22, $22, $22, $66, $62, $22, $22, $26, $41, $6f, $4f, $f1, $14, $44, $42, $11, 
  db $44, $44, $62, $16, $67, $22, $22, $22, $42, $22, $22, $72, $22, $22, $00, $02, $26, $46, $f4, $ff, $11, $14, $44, $22, $16, 
  db $42, $44, $62, $11, $22, $22, $72, $24, $49, $21, $22, $27, $22, $20, $00, $00, $26, $44, $4f, $f2, $22, $14, $42, $26, $12, 
  db $26, $64, $12, $61, $72, $27, $69, $24, $21, $16, $12, $22, $00, $00, $02, $20, $66, $64, $4f, $21, $16, $24, $46, $19, $24, 
  db $29, $14, $16, $26, $27, $11, $66, $24, $21, $61, $12, $00, $00, $00, $22, $26, $66, $65, $66, $61, $61, $24, $21, $24, $44, 
  db $11, $64, $61, $26, $61, $16, $16, $64, $44, $41, $16, $62, $00, $00, $22, $26, $66, $64, $46, $27, $16, $24, $11, $44, $24, 
  db $66, $44, $61, $66, $62, $11, $62, $21, $16, $41, $22, $72, $20, $00, $00, $02, $26, $64, $46, $62, $22, $44, $44, $42, $94, 
  db $64, $44, $26, $66, $22, $66, $12, $16, $16, $41, $12, $27, $20, $02, $22, $00, $26, $64, $44, $66, $26, $65, $64, $42, $f4, 
  db $44, $44, $22, $66, $29, $16, $11, $66, $64, $41, $61, $27, $70, $22, $22, $20, $26, $44, $44, $46, $66, $44, $61, $44, $6f, 
  db $44, $42, $26, $66, $61, $61, $66, $44, $44, $16, $16, $76, $44, $47, $22, $26, $26, $44, $2f, $44, $44, $41, $66, $64, $6f, 
  db $44, $12, $66, $62, $22, $44, $44, $46, $16, $11, $62, $76, $44, $44, $17, $66, $26, $42, $1f, $44, $4f, $16, $74, $44, $62, 
  db $41, $26, $66, $22, $92, $46, $22, $41, $61, $12, $22, $74, $44, $44, $42, $26, $26, $41, $64, $44, $f4, $f4, $44, $65, $62, 
  db $41, $26, $62, $26, $66, $56, $12, $24, $16, $62, $27, $64, $22, $14, $44, $62, $66, $49, $44, $42, $4f, $44, $16, $f4, $21, 
  db $46, $66, $22, $16, $44, $46, $62, $24, $16, $22, $76, $44, $91, $61, $41, $66, $64, $44, $44, $22, $66, $ff, $f4, $41, $14, 
  db $46, $69, $22, $24, $44, $44, $44, $24, $66, $22, $64, $41, $16, $64, $44, $66, $44, $44, $46, $26, $66, $f4, $4f, $44, $44, 
  db $46, $62, $44, $44, $46, $56, $64, $44, $26, $62, $66, $44, $44, $44, $44, $44, $44, $42, $22, $66, $66, $44, $44, $44, $44, 
  db $44, $66, $56, $14, $16, $44, $69, $44, $26, $44, $46, $66, $64, $44, $91, $64, $42, $96, $66, $66, $64, $44, $44, $44, $44, 
  db $44, $44, $44, $44, $44, $44, $44, $44, $46, $65, $66, $66, $44, $41, $16, $44, $66, $66, $66, $44, $44, $44, $44, $44, $44, 

OverworldTileset:
  db $00, $00, $00, $00, $00, $00, $00, $00,
  db $00, $00, $00, $00, $00, $00, $00, $00,

OverworldAutoEvents:
  ; underworld
  AllocateTransportEvent 34, 13, HIGH(Underworld), LOW(Underworld), 68, 26
  AllocateTransportEvent 34, 28, HIGH(Underworld), LOW(Underworld), 68, 56
  AllocateTransportEvent 34, 34, HIGH(Underworld), LOW(Underworld), 68, 68
  AllocateTransportEvent 32, 3, HIGH(Underworld), LOW(Underworld), 64, 6
  AllocateTransportEvent 31, 6, HIGH(Underworld), LOW(Underworld), 62, 12
  AllocateTransportEvent 31, 24, HIGH(Underworld), LOW(Underworld), 62, 48
  AllocateTransportEvent 29, 8, HIGH(Underworld), LOW(Underworld), 58, 16
  AllocateTransportEvent 26, 9, HIGH(Underworld), LOW(Underworld), 52, 18
  AllocateTransportEvent 25, 16, HIGH(Underworld), LOW(Underworld), 50, 32
  AllocateTransportEvent 24, 48, HIGH(Underworld), LOW(Underworld), 48, 96
  AllocateTransportEvent 22, 1, HIGH(Underworld), LOW(Underworld), 44, 2
  AllocateTransportEvent 21, 13, HIGH(Underworld), LOW(Underworld), 42, 26
  AllocateTransportEvent 21, 47, HIGH(Underworld), LOW(Underworld), 42, 94
  AllocateTransportEvent 20, 17, HIGH(Underworld), LOW(Underworld), 40, 34
  AllocateTransportEvent 18, 14, HIGH(Underworld), LOW(Underworld), 36, 28
  AllocateTransportEvent 17, 26, HIGH(Underworld), LOW(Underworld), 34, 52
  AllocateTransportEvent 15, 31, HIGH(Underworld), LOW(Underworld), 30, 62
  AllocateTransportEvent 6, 17, HIGH(Underworld), LOW(Underworld), 12, 34
  AllocateTransportEvent 4, 6, HIGH(Underworld), LOW(Underworld), 8, 12
  AllocateTransportEvent 4, 28, HIGH(Underworld), LOW(Underworld), 8, 56
  AllocateTransportEvent 2, 9, HIGH(Underworld), LOW(Underworld), 4, 18

  ; sub-maps
  AllocateTransportEvent 34, 6, HIGH(Ford01), LOW(Ford01), 3, 0
  AllocateTransportEvent 34, 8, HIGH(Ford01), LOW(Ford01), 2, 9
  AllocateTransportEvent 30, 12, HIGH(Start), LOW(Start), 4, 0
  AllocateTransportEvent 2, 31, HIGH(OldSwamp), LOW(OldSwamp), 4, 9
  AllocateTransportEvent 3, 37, HIGH(SwampTunnelWest), LOW(SwampTunnelWest), 3, 0
  AllocateTransportEvent 1, 39, HIGH(SwampTunnelEast), LOW(SwampTunnelEast), 6, 9
  AllocateTransportEvent 22, 41, HIGH(RuinedTemple), LOW(RuinedTemple), 1, 0
  AllocateTransportEvent 31, 29, HIGH(TwinsCrossingEast), LOW(TwinsCrossingEast), 3, 9
  AllocateTransportEvent 31, 27, HIGH(TwinsCrossingWest), LOW(TwinsCrossingWest), 6, 0
  AllocateTransportEvent 18, 8, HIGH(OldPond), LOW(OldPond), 8, 5
  AllocateTransportEvent 29, 1, HIGH(CoastalGrove), LOW(CoastalGrove), 8, 2
  AllocateTransportEvent 9, 10, HIGH(NorthForestTemple), LOW(NorthForestTemple), 8, 1
  AllocateTransportEvent 12, 8, HIGH(CentralForestTemple), LOW(CentralForestTemple), 1, 0
  AllocateTransportEvent 14, 8, HIGH(SouthForestTemple), LOW(SouthForestTemple), 2, 0
  AllocateTransportEvent 8, 45, HIGH(PeninsulaRuins), LOW(PeninsulaRuins), 8, 4
  AllocateTransportEvent 6, 33, HIGH(OldSwampSouth), LOW(OldSwampSouth), 0, 3
  AllocateTransportEvent 16, 16, HIGH(TowerApproach), LOW(TowerApproach), 17, 4
  AllocateTransportEvent 23, 44, HIGH(HiddenPeninsula), LOW(HiddenPeninsula), 2, 9
  AllocateTransportEvent 28, 28, HIGH(DesertTown), LOW(DesertTown), 3, 19

  ; desert (two entrances per entrance so you can't slip into the middle)
  AllocateTransportEvent 22, 22, HIGH(Desert), LOW(Desert), 40, 0
  AllocateTransportEvent 22, 23, HIGH(Desert), LOW(Desert), 40, 0
  AllocateTransportEvent 26, 25, HIGH(Desert), LOW(Desert), 80, 40
  AllocateTransportEvent 25, 25, HIGH(Desert), LOW(Desert), 80, 40
  AllocateTransportEvent 26, 31, HIGH(Desert), LOW(Desert), 80, 89
  AllocateTransportEvent 25, 31, HIGH(Desert), LOW(Desert), 80, 89
  AllocateTransportEvent 21, 31, HIGH(Desert), LOW(Desert), 36, 89
  AllocateTransportEvent 20, 31, HIGH(Desert), LOW(Desert), 36, 89

  ; ruins
  AllocateTransportEvent 14, 12, HIGH(RuinsOne), LOW(RuinsOne), 17, 11
  AllocateTransportEvent 10, 14, HIGH(RuinsTwo), LOW(RuinsTwo), 0, 11
  AllocateTransportEvent 16, 19, HIGH(RuinsThree), LOW(RuinsThree), 0, 9

  ; tower

  EndList

OverworldTriggerEvents:
  EndList

ENDC