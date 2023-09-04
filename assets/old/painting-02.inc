
IF !DEF(PAINTING_02_INC)
PAINTING_02_INC = 1

Section "painting_02", ROM0
painting_02:
db height, width, HIGH(painting_02AutoEvents), LOW($painting_02AutoEvents)
db $07, $07, $02, $02, $02, $02, $02, $02, $07, $00, 
db $01, $01, $07, $02, $07, $04, $02, $02, $02, $07, 
db $01, $01, $01, $00, $06, $04, $00, $02, $02, $02, 
db $04, $04, $04, $06, $06, $04, $04, $04, $04, $04, 
db $04, $0a, $04, $04, $06, $06, $06, $06, $06, $04, 
db $01, $06, $06, $04, $06, $01, $01, $04, $04, $04, 
db $01, $06, $04, $04, $06, $06, $04, $04, $06, $06, 
db $06, $06, $05, $06, $06, $06, $05, $06, $01, $01, 
db $06, $06, $04, $04, $04, $04, $04, $06, $06, $06, 

painting_02AutoEvents:
  AllocateTransportEvent 8, 7, HIGH(Smallworld), LOW(Smallworld), 4, 1
  EndList
        