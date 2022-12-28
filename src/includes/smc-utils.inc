IF !DEF(SMC_UTILS_INC)
SMC_UTILS_INC = 1

NO_OP_OP EQU $00 ; no oppish!
CALL_OP EQU $CD ; remember, low then high!
RET_OP EQU $C9
LD_A_N8 EQU $3E ; for loading tiles into a
LD_N16_A EQU $EA ; for loading a into VRAM

LD_A_N16 EQU $FA ; unused

ENDC	; end definition of SMC utils file