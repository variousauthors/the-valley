NEXTSTEPS
=========

### Dragon Quest Valley 01

I have finished implementing events that move the player between maps, and I'm taking a break
from features to make a game with just that.

To Finish Content:

- [x] create sub-overworld areas for all hidden entrances
     this needs some kind of naming convention
- [x] rough out the inner maze, decide on the true paths
- [x] add more places where the inner maze surfaces
  - funnels into into sub-overworld hidden underworld entrances
  - or, temporarily surface e.g. a plateaux with another cave
- [] connect up all the sub-underworld stairs
- [] add more sub-underworld stairs connecting various parts of the inner maze
     - like, _real_ shortcuts. You know?
     - stairs in the top-left corner that lead to the bottom right corner. 
       That kind of thing. Or maybe some "fast travel" hubs, you know?
- [] desert sub-overworld
     - the desert is cool because it makes the tunnels to the east
       more useful. It might _always_ be difficult to cross the desert
       because finding the exit is like finding a grain of sesame
     - oh but this means the exit can't just be the far edge of the map
       because then you could clear it by just walking left, then down
     - hmm...
     - I should use _all_ of the remaining memory for the desert :D
     - add a single cactus tile at the entrance that appears nowhere
       else in the game, an homage to the cactus in Desert Golfing
       -can replace th dots tile with this, and use null tile for sand
- [] make a sprite with a looping walk animation (no animation controller, just always loop)
     - this will make the desert sub-overworld map extra confusing because the player will
       not be sure if they are walking or not :D
     - maybe remove the "sand tile" and use plain white for desert
       for ultimate getting lost in the desert confusion
- [] tower area:
     - make a nicer "ruins" tile
     - 3 sub-oveworlds in the ruins
       - 3 hidden entrances to a special maze under the lake
     - make a ruined tower tile
     - ruined tower in the center of the lake
     - the 3 ruins each have an entrance to the maze under the lake
       and the stairs up to the tower are visible in the maze
       but the correct path is not from any of the 3 ruins... it is
       from the peninsula south of the tower! One final little
       misdirection!
- [] implement an "ending" when they find the tower
- [] fix A and B moving you up lol
- [] add the sub-underworld "lobbies" these will serve as buffers instead
     of adding a "fade out" animation (do with what we have!)
     - if we do this, we could also change up the stone-masonry
       for different parts of the maze, so that each lobby signals
       which part of the maze you are entering
       - but skip this if it is too much work (and do this last)

[x] use tileD map editor and write an import script to convert the json data to map data
[x] fill up 32kb with interlinked map data to explore
[x] delete the silly Changelog file and version this instead

#### Game Feeeeeel Tech:

[] add a short delay to the screen transition
   [] do a palette based fade-in/fade-out
   [] display a location name

#### Data:

Along the way I thought of a bunch of ways to squeeze more juice
out of the 32kb,

[] use 4 bits instead of 8 for meta-tile lookup since there are only 16 metatiles
[] auto-tile
   - paths can have 1 of the 4 brick tiles removed "randomly" (deterministically)
   - coast-lines and rivers
   - various biome edges
[] either run-length encode the underworld (it would compress well)
   - OR we can actually use 2 bits for the underworld tyles, which is already 
     another 2x compression (we could also move those tiles to the front, so
     no additional code necessary to decode)
   - we can prototype this by doing the RLC with no decoder, just to see how much
     it shrinks. If it shrinks by more than x2 then we do that (it probably will)
   - oh wait we can do both, lol :D
[] use 2x2 meta-meta-tiles like in ark _if_ it ends up being smaller
   - the meta-tiles use 4 bits per tile, but a 2x2 meta-meta-tile would not be 4 bits
     per tile we'd probably be back to 8 bits... do just depends on the savings?
[] be able to have different "blank" meta-tiles for rendering off-map, perhaps by sampling nearby tiles
[] different tile-sets per map
   - they can all still be in ROM and we just have a pointer
   - each map would have its own palette of 16 tiles (I thought about
     reducing this to 8 / map but not worth it to save 1 bit/tile I think)
     (underworld can still be 2 bits per tile though)

#### Centers:

That's all tech, but I also got thinking about new centers:
 - I was thinking about "how to add fights" and I thought "ah, a minotaur
   at the center of the labyrinth might be cool. Then I thought, a boss
   guarding each of the dead-ends would: 
   - gesture at dead-ends as being important
   - have a nice relationship with existing centers
   Combat system can start really simple.
 - I keep thinking of clearings or groves like the one I did in bitsy,
   where you can collect flowers, but then we need something to do with
   flowers. I like crafting, but crafting needs to come after some other
   centers (crafting to what end, crafting with what)
 - crafting and materials would leave a loose end: how to learn recipes
   - if we add NPCs that teach recipes, then we can also have camps/shops,
     sign-posting, and lore
 - words: add toki-pona as a language and have NPC say words

---

[x] flux-like "architecture" lol
[x] vblank only 4-direction scrolling
[] going from map to map
   - teleport events on the map
[] drawing from a compressed map

### Camera & Avatar
 - smooth avatar movement
   - when the player presses "up"
   - we check for collisions
   - if it is clear we add to their dy
   - as long as the player has dy we animate them moving up

 - when the avatar moves, the camera should move
 - if the camera hits the edge of the scene, it should not move
   - this is configurable, eg in an outdoor scene we ignore this restriction
     because we want the avatar to be able to see the ocean or forest stretching out
     without needing to store all that useless data,
     but in an interior space there is no need to show the voidscape
   - ah but! if the avatar steps into the voidscape then the camera should move hmm
 - it should be possible to move the camera without the avatar moving, eg
   if the avatar is looking into a telescope to see distant lands

 - fluxy avatar movement
   - when the player presses "up"
   - dispatch a PLAYER_PRESSED_UP action
   - AVATAR reducer checks if the avatar can go up
   - if it can, 
     - it sets the avatar's dy to some value
   - then in the next tick
   - if dy is non-zero we dispatch a AVATAR_MOVE_UP action
   - AVATAR reducer decrements dy by player speed
   - CAMERA reducer, if set to follow cam, moves based on player speed

The idea here is that we have a built in "tick" function, which is the CPU
So the reducers change the state, and then in the next tick we dispatch new
actions based on the new state. This is good for animating state.

What about for music? Which note to play is state that can be animated
in the same way, but actually _playing the music_ is a side-effect.

This got me thinking about ECS again. Game Boy has neither caching nor multi-threading
though, so maybe that's not right.

Music feels more like something you would do with Sagas... AVATAR_MOVE_UP gets
fired, which changes the "move sound started" flag to true and resets the position in the
music. Then on each tick we play the next note.

I think the truth is here somewhere. I want:

 - each tick to iterate through the data, settling it into a steady state
 - react to input and events centrally, respond to actions

There is a state that the data wants to be in. dy wants to be part of y.
The camera wants to follow the player. Loops want to loop (sound, animation, etc)

Actions represent little kicks that move the data out of a settled position,
triggering cascades of action.

---

 - tick
 - player pushes up
 - dispatch PLAYER_PUSHED_UP
 - avatar reducer sets dy on the player state
 - camera reducer sets dy on the camera state
 - tick
 - lerp player y
 - lerp camera y

---

c     | 0 | 1         |
------|---|-----------|
pos_y | 0 | 0         |
mov_y | . | .         |
fol_y | . | { id: 0 } |

tick
nothing happens
player pushes up
dispatch PLAYER_PUSHED_UP
attach "mov_y" to entity 0

c     | 0                  | 1         |
------|--------------------|-----------|
pos_y | 0                  | 0         |
mov_y | `{ y: 10, dy: 1 }` | .         |
fol_y | .                  | { id: 0 } |

tick
move system runs, updates pos_y

c     | 0                  | 1         |
------|--------------------|-----------|
pos_y | 1                  | 0         |
mov_y | `{ y: 10, dy: 1 }` | .         |
fol_y | .                  | { id: 0 } |

follow system runs, notices pos_y of 0 is different from 1
adds a mov_y to 1

c     | 0                  | 1                      |
------|--------------------|------------------------|
pos_y | 1                  | 0                      |
mov_y | `{ y: 10, dy: 1 }` | { y: 1, dy: 1}         |
fol_y | .                  | { id: 0 }              |

tick
move system runs, updates pos_y, 1's move is done so removes it

c     | 0                  | 1                      |
------|--------------------|------------------------|
pos_y | 2                  | 1                      |
mov_y | `{ y: 10, dy: 1 }` | ..............         |
fol_y | .                  | { id: 0 }              |

this continues

c     | 0                  | 1                      |
------|--------------------|------------------------|
pos_y | 10                 | 10                     |
mov_y | .................. | ..............         |
fol_y | .                  | { id: 0 }              |

so the camera follows the player

OK but what if we want the camera to start following the player
more slowly, and then speed up to match the player's speed after
a moment.

I guess we'd create a new "tail" component that had some
additional info, a threshold, two velocities...

c      | 0                  | 1                                                 |
-------|--------------------|---------------------------------------------------|
pos_y  | 10                 | 10                                                |
mov_y  | .................. | ..............                                    |
tail_y | .                  | { id: 0, max: 10 } |

if the target is within max, then we move at target speed / 2, otherwise we move at target speed

and the _idea_ with ECS is that once we implemented that behaviour for camera,
we could add the same behaviour to an NPC or a bullet if we wanted, with no problem.

---


all the y positions in the game are in a contiguous array
the deltas are in another

pos_y - 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
del_y - 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

when we update we just iterate over these, adding del to pos
without even really thinking about "who's position"

if things are aligned in memory, then we can use a single hl
where we increment l to iterate over entities and h to advance through the components

; puts the least length from each required component in l
call getLastFromShortestComponentList

.loop
  ld a, 0
  cp l
  jr z, .done
  ld h, COMPONENTS + POS_Y
  ld a, [hl]
  ld h, COMPONENTS + DEL_Y
  ld b, [hl]
  add b
  dec l
  jr .loop
.done

this is nice for any values that just need to be lerped

we can do the same for sprites

sprite x   - 0, 0, 0, 0, 0, 0
sprite y   - 0, 0, 0, 0, 0, 0
other attr - 0, 0, 0, 0, 0, 0

rendering sprite is just a component

but how do we delete and insert entities in this schema?
the suggestion online was to have a tightly packed array
pointing to active entities

pos_y 4, 6, 1, 7
POS_Y 0, 9, 0, 0, 2, 0, 8, 6
  
(so note that 4 6 1 and 7 are entities, not just indexes)

we could keep a "next available spot" index, that defaults to the end

next 4
pos_y 4, 6, 1, 7
POS_Y 0, 9, 0, 0, 2, 0, 8, 6

now entity 5 wants a pos_y
so we add entity 5 to the 4th pos_y
and write its requested y value to POS_Y
then walk down pos_y to a 0
and record that as next

next 5
pos_y 4, 6, 1, 7, 5
POS_Y 0, 9, 0, 0, 2, 7, 8, 6

when we remove y from an entity, say from 6
we walk to entity 6 in pos_y
we record that index as next

next 1
pos_y 4, 0, 1, 7, 5
POS_Y 0, 9, 0, 0, 2, 7, 0, 6

the next time an entity gets a y we add it there

then the loop becomes

; puts the least length from each required component in l
call getLastFromShortestComponentList

.loop
  ld a, 0
  cp l
  jr z, .done

  ld h, TIGHTS + POS_Y
  ld a, [hl]
  ld hl, COMPONENTS + POS_Y
  ld b, [hl]

  ld h, TIGHTS + DEL_Y
  ld a, [hl]
  ld hl, COMPONENTS + DEL_Y
  ld a, [hl]

  add b
  dec l
  jr .loop
.done

---

it migth actually make more sense to just start with a conservative estimate about
the number of entities we can have in a scene. For example, 16 entities

then each system can just iterate over every entity checking its mask
(oh actually, the masks are no good for us since then we could only have
16 systems, which is probably not enough)
(ok so instead, set a component's highest bit if it is on)

ld l, 0
REPT 16
  ld h, COMPONENTS + POS_Y
  ld a, [hl] ; pos y
  bit 7
  jr z, .next
  ld h, COMPONENTS + DEL_Y
  ld b, [hl] ; del y
  add b

  ld h, COMPONENTS + POS_X
  ld a, [hl] ; pos x
  bit 7
  jr z, .next
  ld h, COMPONENTS + DEL_X
  ld b, [hl] ; del x
  add b
.next\@
ENDR

could also think about "16 systems per scene" being a thing :D
like, how many systems do we need to run an RPG overworld?

"physics", update positions
ai, each npc makes a plan
controls, each entity reacts to button presses
dialog, which character to print next if this npc is talking

---

what about if instead we do it with an action queue...

tick
each entity gains some energy
if they have enough energy their ai runs
and writes an action to the queue
  actions are templates in ROM,
  so we copy the template, filling in the holes as we go

Yeah I really think a blend of the two, where we have
actions that are setting things up, kicking the game
our of a steady state, and then letting it lerp back

like, you talk to an NPC
this changes the game state:
 - set state machine to "talking" state
 - set the NPC whose dialogue to deal with
 - set the current character to 0
 - open the menu

Then the dialog system just runs every frame
as long as there is work to do... and if there
isn't it fires a "done" action

if it hits a "decision" in the dialog it fires an action
 - set state machine to "decision"
 - set the decision of interest (each decision can be stored discretely)

Then the decision system just runs every frame
until the user has made a decision, which fires another
action using the option they chose

meanwhile, NPCs can still be wandering around. Flowers
can still be animating, etc...

; maybe this "reducer" idea should be implemented as tables in ROM
; yessssssssssss
; we visit each table and look up the correct reducer for the action
; and add it to the smc
; this means we no longer have to like iterate through every option
; oh man this is so right, this is how switch statements are under
; the hood anyway!

---

### SCENE TRANSITIONS

I'm going to implement scene transitions so that I can start thinking
about a data format for scenes. I want to implement collision, but
I feel like I will make better decisions about tiles and collision map
stuff if we already have scene transitions (so even though the scene
transition events themselves will probably live in the scene data,
this is like a bootstrap to kick-off that work)

Thinking about meta tiles

House:
1, 1, 1, 1, 7, 7, 7, 7, 7, 1, 1, 1, 1, 1
1, 0, 0, 1, 7, 7, 7, 7, 7, 1, 4, 0, 9, 1
1, 5, 0, 3, 6, 6, 6, 6, 6, 3, 0, 0, 8, 1
1, 0, 0, 1, 7, 7, 7, 7, 7, 1, 0, 0, A, 1
1, 1, 1, 1, 7, 7, 7, 7, 7, 1, 1, 2, 1, 1

InteriorMetaTiles:
0 FLOOR
1 WALL
2 DOOR
3 WALL_FAUX
4 STAIRS_DOWN
5 CHEST_CLOSED
6 VOIDSCAPE_TUNNEL
7 VOIDSCAPE
8 TABLE
9 CHAIR_DOWN
A CHAIR_UP

MetaTileData:
; 4 bytes for tiles, 1 byte for attributes (passable, event, etc...)
0, 0, 0, 0, 0 ; 0 FLOOR
0, 0, 0, 0, 0 ; 1 WALL
0, 0, 0, 0, 0 ; 2 DOOR
0, 0, 0, 0, 0 ; 3 WALL_FAUX
0, 0, 0, 0, 0 ; 4 STAIRS_DOWN
0, 0, 0, 0, 0 ; 5 CHEST_CLOSED
0, 0, 0, 0, 0 ; 6 VOIDSCAPE_TUNNEL
0, 0, 0, 0, 0 ; 7 VOIDSCAPE
0, 0, 0, 0, 0 ; 8 TABLE
0, 0, 0, 0, 0 ; 9 CHAIR_DOWN
0, 0, 0, 0, 0 ; A CHAIR_UP

attributes can be

Bit 7    BG-to-OAM Priority         (0=Use OAM Priority bit, 1=BG Priority)
Bit 6    passable  ; just have to remember to zero
Bit 5    event     ; these attributes
Bit 4    Not used
Bit 3    Tile VRAM Bank number      (0=Bank 0, 1=Bank 1)
Bit 2-0  Background Palette number  (BGP0-7)

8 bg palettes
 - can have 3 for trees/folliage so that we can have orange/yellow/red in autumn
 - 5 remaining for general decor

---

I have just now realized that 32kb is not a lot!

A 256x256 meta tile map is 65kb
If I used 2x2 meta meta tiles then it would be 128x128 of those so only 16kb
but then I have just an overworld and not a lot else and it takes up a whole bank of ROM :D

SO. I have some thinking to do.

What if I restrict myself to palettes of 16 meta tiles so that I can use each byte as two tiles?
That gets me down to 8kb for the over world map, and leaves room for another 8kb of interiors...

Hmm but wait, then the 2x2 meta meta tiles would actually represent 8 meta tiles, right? If they
are 2x2 bytes... and that seems hard to reason about. Wait wait wait

256x256 of 4 bit meta tile indexes is 32kb
compress that with 2x2 meta meta tiles, each meta meta tile is 2 bytes

Dragon Quest had a 128x128 map
7 towns of 32x32
5 dungeons of various sizes...

if I divide 256x256 into 32x32 chunks I get uh... quite a few. 64 of them? That's actually pretty good.

But then I have to deal with so much work to go from y,x to tile...

### To check for a collision
 - get the y,x
 - divide by 4 to get the meta meta tile
 - pull out that meta meta tile
 - use mod 2 on y to find if we need the top or bottom byte
 - use mod 2 on x to find if we need the high or low nibble
 - then proceed as normal

#### OR

Proceed and do not worry about this problem. After all, I am not trying to make the
biggest RPG ever, you know? DQ's map was only 128x128 and if I use 2x2 meta meta tiles
on that I get 8kb without the extra thing.

My goal right now is to make a JRPG in 32kb and I should focus on that. If it is small,
it is small. I can try again later!

---

### States

Imagine if the game had no animation. The player presses left, we check for collision
to see if they can move left. Then we set player previous x to player x, and player x
to the new x. They have moved. After the state is updated, we should check for any auto
events, and then a random encounter.

Then the game halts, waiting for input. Only the secondary animations and ai subroutines
run.

So that's the problem I think, there is this "edge" that happens each time state changes,
but only once per state change. We want to implement it such that when we add animations
we are guaranteed that this happens only after they run, and only once.

I feel like a state machine is the way to go? Then we can have enter states.

No...

1. waiting for input (steady state)
2. input occurs
  3. validate input
  4. update state
  -> lerp between prev state and next
  5. check for triggers
  6. (potentially we now have a new state to validate)

Essentially "check for triggers" is like "can we enter a steady state"
So maybe it should be part of the "isSteadyState" check lol

ugh no this still loops forever, right? Because suppose we check for triggers
and we find one, and it moves us to another trigger locations...

It's like we need auto events to turn off once triggered. No no,
that wouldn't do it. Because:

1. waiting for input (steady state)
2. player presses left
  3. is left a valid move?
  4. set player next x
  -> lerp between prev state and next
  5. player moved onto a staircase, teleport them
  4. set the player to the new location
  -> play the transition animation
  5. player moved onto a staircase (on the other side), teleport them
  ... loop

So this is about "cascades" of events after player input. Maybe the thing
is to only check for movement events once per input, rather than whenever state
settles...

This would not work for a puzzle game though, right? Player pushes a block,
which slides across and hits another block, which slides over and triggers
something... this is a cascade of several state transition off one player input.

So maybe it's about the presence of player input, maybe some events "consume"
player inputs... Like if you walk onto a staircase it checks "is there
a player input" and then if there isn't it doesn't do anything, and part
of resolving a staircase is to remove the player input...
