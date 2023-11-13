IF !DEF(RUINED_STRUCTURE_INC)
RUINED_STRUCTURE_INC = 1

/** the top left corner metatile is the "blank" tile
 * which is used to fill in anything that falls off the
 * map... tree for a forest, water for an island, black
 * or stone for a cave... */

Section "RuinedStructure", ROM0
  db NO_BOUNDS ; metadata flags
RuinedStructure:
  db 9, 10, HIGH(RuinedStructureAutoEvents), LOW(RuinedStructureAutoEvents), HIGH(OverworldTileset), LOW(OverworldTileset)
  db $11, $11, $11, $11, $11, 
  db $11, $11, $11, $11, $11, 
  db $11, $16, $61, $11, $66, 
  db $1b, $b6, $b6, $6c, $61, 
  db $1b, $d6, $6b, $6c, $11, 
  db $16, $66, $66, $cc, $11, 
  db $1b, $66, $66, $11, $11, 
  db $11, $bb, $b1, $11, $11, 
  db $11, $11, $11, $11, $11, 

RuinedStructureAutoEvents:
  ; overworld
  AllocateTransportEvent 2, 9, HIGH(Overworld), LOW(Overworld), 31, 6

  ; underworld
  AllocateTransportEvent 4, 2, HIGH(Underworld), LOW(Underworld), 62, 12

  EndList

RuinedStructureTriggerEvents:
  EndList

ENDC