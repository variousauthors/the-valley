IF !DEF(SMC_UTILS_INC)
SMC_UTILS_INC = 1

; operations
NO_OP_OP EQU $00 ; no oppish!
CALL_OP EQU $CD ; remember, low then high!
RET_OP EQU $C9
LD_A_N8 EQU $3E ; for loading tiles into a
LD_N16_A EQU $EA ; for loading a into VRAM

LD_A_N16 EQU $FA ; unused

; ld a, n8 ; 2 bytes
; ld [n16], a ; 3 bytes
TEMPLATE_SLOT EQU 5 ; 5 bytes per slot
START_TEMPLATE EQU 1 ; ret/nop at the start
END_TEMPLATE EQU 1 ; ret at the end

SECTION "TemplateUtilites", ROM0

VRAM_ADDRESS EQU 0
TILE_DATA EQU 0

/*
@param b - number of tiles
@param hl - address at which to create the template */
makeVRAMTemplate:
  ld a, RET_OP
  ld [hl+], a

; ld a, n8 ; 2 bytes, 2 cycles
; ld [n16], a ; 3 bytes, 4 cycles
.loop
  ld a, LD_A_N8
  ld [hl+], a
  ld a, TILE_DATA
  ld [hl+], a
  ld a, LD_N16_A
  ld [hl+], a
  ld a, VRAM_ADDRESS ; low byte
  ld [hl+], a
  ld a, VRAM_ADDRESS ; high byte
  ld [hl+], a

  dec b
  jr nz, .loop

  ld a, RET_OP
  ld [hl+], a

  ret


ENDC	; end definition of SMC utils file