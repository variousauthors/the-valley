
IF !DEF(PAINTING_01_INC)
PAINTING_01_INC = 1

Section "painting_01", ROM0
painting_01:
db height, width, HIGH(painting_01AutoEvents), LOW($painting_01AutoEvents)
db $02, $02, $02, $02, $02, $00, $00, $06, $04, $06, 
db $07, $02, $09, $02, $02, $02, $09, $02, $04, $06, 
db $00, $07, $07, $02, $02, $02, $02, $02, $02, $06, 
db $00, $06, $01, $07, $07, $02, $02, $02, $02, $02, 
db $06, $01, $01, $01, $01, $07, $02, $07, $04, $02, 
db $01, $01, $01, $01, $01, $01, $00, $06, $04, $00, 
db $06, $01, $06, $04, $04, $04, $06, $06, $04, $04, 
db $04, $04, $04, $04, $0a, $04, $04, $06, $06, $06, 
db $06, $01, $01, $01, $06, $06, $04, $06, $00, $00, 

painting_01AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        