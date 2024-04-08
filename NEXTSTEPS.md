NEXTSTEPS
=========

## GENERAL TODO

- [] Release valley 01
  - [] make a nice itch.io page with lore and instructions
  - [] do another play-test with a small group
  - [] release the game

### Dragon Quest Valley 1.5 (valleyntino)

The Goal for this project is:

 - a lovely archipelago to travel around in
 - random encounters and levelling that feel a bit like an incremental game
   - encounter rates for different terrain
   - encounter tables for different maps and parts of maps
     - perhaps using the "bridge/bottleneck" system

Stretch:
 - a high score based on what you've discovered
   and time spent

STATS:
 - graphics data 3.5kb
 - overworld 8kb
 - slack 10.5kb
 - total: 22kb
 - code: 32kb - 22kb = 10kb !? feels like a lot
  
#### BACKLOG

v0:
 - [x] multiple monsters
   - [x] multiple monsters exist
   - [x] a monster is chosen randomly at the start of an encounter
 - [x] crossing a bridge to change encounter tables
   - [x] implement "change encounter table" auto event
   - [x] add to either side of the bridge
 - [x] refactor! Remove the rule about encounters on auto event tiles
   - I'm fine with monsters at cave entrances, or on either side of
     a bridge, but not on the boat or when entering a village
   - [x] refactor! gather the tilesets into a single file
     and define tileset attributes such as "collision" and "safe"
     with flags COLLISION | NO_ENCOUNTERS
     - [x] BUG! OMG somewhere along the line we must have introduced
       a bug because now moving around is not working. Need to go back
       a few commits to figure out when this started.
       - LOL it was my debug code that was causing the bug, I put
         and early return in toRandomEncounterGameState and it was causing
         the move to happen but the render to not happen :D
     - [x] remove MetaTiles table
       in the old table we were aligned to 8 bits so we were taking the 8 bits
       in l and then setting h to 0001 or 0010 et to get the address of the table
       but now I think we can do a thin where we use the first two bits instead...
       so we can keep the same API and not have to refactor a bunch of drawing code
       we have a temp in WRAM that pretends to be that address. The user asks for tile
       8 so we give them back hl with 00001000
       then when they want the bottom left we write back to that address like
       00001001 or something... think about it
     - [x] remove the old meta tile attributes table
     - [x] use the new tile attributes
   - [x] defined a helper getCurrentMapTilesetAttributed near getCurrentMapTileset
     just by like adding 16 to the address :D
   - [x] could also use this as a chance to experiment with color, have a
     getCurrentMapTilesetPalettes and assign each tile a per map palette
     in CGB mode
     - [x] this was fun! I noticed that since we only use BG tiles 0 - 127
       we always have two bits free in out tile indices. Using those two
       tiles to store a palette number from the metatile attributes lets
       us easily re-use the buffer draw code without having to allocate an
       entire second buffer (buffer is huge)  
       - I've left the code in there because it isn't hurting us in DMG mode
         but just commented out the "drawAttributes" call. Later we can
         use hardware detection to skip it or bail out on DMG
       - I did not augment the scrolling code since that would require
         a change to the draw templates and also the proof of concept
         for GBC did not require scrolling.
         - actually! Just call "draw" and then change the flag that
           determines which VRAM you write to and call "draw" again :D

 - [x] a boat 
   - [x] make it a sprite with a world position
   - [x] walking on the boat heals you
   - [x] boat game state
     - [x] same as overworld
     - [x] moving onto the boat changes game states
     - [x] use the second obj palette with light gray as transparency
     - [x] instead of moving onto land, change gamestate then move
     - [x] the boat heals you
     - [x] refactor! collect the random encounter check and boat landing checks
           into a single subroutine
     - [x] BUG! Finishing random encounter state should put you back in the _previous_ state
           not overworld state :D 
           - toRandomEncounter saves previous state's "to" function
           - fromRandomEncounter calls it
     - [x] BUG! The boat is currently rendered even when it is off-screen
           so if you move around a bit you will find it out there... like
           when VRAM wraps around
           - [x] experiment: draw the boat 10 tiles left, then 10 more 
             tiles left, etc... does it wrap?
           - [x] if so, then we must cull the boat
     - [x] BUG! The boat should not exist outside of the overworld
           currently it is always somewhere, so if you enter a cave
           in the top-left corner of the world you might see the boat render
           do we need like, "interior state"?
     - [x] collide with deep water and bridges, not shallow water

 - [x] dying ends the game
 - [x] running sends you back to the boat and heals you

 - [x] BUG! Seems like... when you hit the random encounter the draw instructions
       for the cancelled move still get stored and acted on? I only noticed this after
       implementing retreat which changes the game state. What happens is:
       - you click retreat
       - screen goes blank
       - we draw the overworld around the boat
       - screen fades in
       - transition to overworld gamestate
       - THEN we apparently perform the draw instructions :D
       SOLVED: was returning z instead of nz when hitting a random encounter
 - [x] fill up the encounter table
       - 64 bytes per monster sprite is 1kb per 16 monsters! Yikes!
         so maybe just 16 monsters in this game :D
       - have 16 monsters with progression like in valentino

 - [x] random damage formula
       - just AND the ATT with the RAND
       - that gives you a number from 0 to 1/2 * ATT
       - add it to ATT
       - if that turns out to be too random we can always >> it to divide by two :D
       - use this:

```
function twiddle (n) {
  const r = Math.floor(Math.random() * 255)
  
  let x = 0
  while (n) {
    n = n >> 1
    x = x | n
  }
  
  return x & r
}
```

 - [x] BUG! retreating doesn't reset the encounter table
       - either you need to retreat into boat state, or
       - it just sets the encounter level to overworld
 - [x] implement the "hit counting" system for random encounters
       - ie you get a random encounter the _second_ time you roll one
         this ensures you never get one immediately
 - [x] XP 0/15 - implement the /
       - also truncation... if the highest digit is 0 just skip
       - until there is a digit
 - [x] We are running out of time when we draw the encounter window
       - [x] prepare the window draw data in the buffer and blast
             the screen instead of trying to fit it all into vblank
 - [x] experiment! re-arrange the main loop so that updates are
       only run when we are not in a steady state
       - [x] improvement! the CPU usage during encounters is high
             because we update the window on every frame. We only need
             to update it when something changes :D 
       - [x] this may have caused a bug where sometimes after fleeing
             the draw buffer is still full of garbage and that goes
             on the screen... but that may be unrelated to this change
             - nope, seems to just be rare
       - [x] just need to investigate why it is happening
             - easy! left over buffer stuff
             - [x] fix it
 - [ ] sometimes the scrolling of a move is not QUITE finished
       when an encounter starts... it should always be finished before
       we move states.
       [ ] this is noticeable now that we are drawing transparency
 - [ ] BUG! Something wrong with the BCD during combat with high
       stat numbers it started to misbehave
 - [ ] BUG! Yeah BCD is just wack gotta fix that
       - [ ] investigate using BCD all the time, and not doing the "double diddle"
             at all
 - [ ] for now maybe just do HP with no ATT/DEF
       - cause I notice you can't really _feel_ the difference
 - [x] BUG! enemies become invincible if you gain enough level?
       maybe like, damage becomes negative or something?
       - we just were only checking player HP in the steady state check

 - [ ] swamp tiles damage you
 - [ ] looks better if monsters have a 1 px buffer all around
 - [ ] rotate the monster to face the player lol
 - [ ] maybe make the random bit update per access instead of per tick?
       or both?


CONTENT

 - a starting area with a smooth ramp, then a sudden cliff
   - biggish island with castle swamp in the middle, lots of
     ways in so you kind of inevitably get there



- [ ] redo graphics data, get all the bg tiles in one place, all the monster tiles, all the sprites etc...

v1:
 - [ ] use hblank stuff to draw UI on the top _and_ bottom of the screen
       during encounters (maybe not actually)
       - [ ] HP 40/40 XP 0/10
       - [ ] monster name HP 40/40
 - [ ] encounter rates by terrain type give the world texture
       - more likely to encounter mobs in forest, hills, swamp
 - [ ] encounter tables should be per map, so you load up the encounter table when you
       change maps
       - [ ] each map has a default encounter table
 - [ ] encounter tables vary by terrain 
       encounter tables are 16 long, but lets use a d8 to get the encounter
       then we can have forests be +4, hills +8, swamp + 12 etc... so dangerous
       monsters are more common in those terrains

 - [ ] bug! dying doesn't work anymore after re-arranging the graphics tables
       I suspect it's because we set the LCD flags wrong with regard to
       which addressing system to use :D

 - [ ] refactor! The very manual way we draw the encounter UI
       we have a method for printing texts 
       to the screen so we could instead build up
       the string to display during update and then
       pass that to our text rendering subroutine
       since it renders text into the window just like this

 - [ ] refactor! re-organize the player-movement code, see note
       in ocean game state, near handlePlayerMovement
       [x] move the draw stuff to after handlePlayerMovement
       [ ] inline moveReplacementEffects into the relevant game states
       [ ] make sure moveReplacementEffects returns the right code 
           (nz for move replacement)

### Dragon Quest Valley 02

The Goal for this project is:

 - a world to walk around in full of secrets
 - random encounters, leveling, and equipment
   - encounter rates for different terrain
   - encounter tables for different maps and parts of maps
     - perhaps using the "bridge/bottleneck" system
 - password save of some kind

STATS:
 - overworld 128 x 128 (8kb)
 - graphics in bank0 (2.5kb)
 - code in bank0 (5.5kb)
 - slack (16kb)

More:

 - give the player a boat, let them explore whichever islands they want
   - kind of gives them a "birds eye view" and this initial boat tier
     will let them get a sense of the shape of the world, some important
     landmarks, etc... before they dive in to exploration
 - random encounters
   - simple fight, run, defend, item
   - run always works, but maybe it should send you _back_ in the overworld
     like, back to camp or something
     - think about this: do I want run to always work or not and why
     - how does it feel to run back to town/boat
   - dieing just restarts the game?
     - or maybe dying puts you back on your boat
   - start simple but the goal is "resource management" and to have "things in places"
   - harder encounters give the world texture
   - I had considered having the encounters be opt-in in stead of random
     so that a monster is visible on the map, but gates an area
     - could do both! put harder monsters on the map, give players a
       reason to go around
- [x] v0 dialog state that shows the dialog box
  - [x] init with a message
  - [x] play N characters of the message, then wait for A
  - [x] play the next N characters
  - [x] once the message is done, go back to overworld state
- [x] fight v2 - basic game loop: stats, xp, healing
  - [x] deal damage based on ATT stat for player and monster
  - [x] deal damage based on ATT stat vs DEF stat for player and monster
  - [x] gain XP after a fight
  - [x] level up periodically, increase ATT, DEF, HP
       - static levels for now just +4, +1, +1
  - [x] heal at the boat
  - [x] monster graphics
    - [x] use mu's art for the sprite
    - [x] display the sprite
    - [x] clean up after battle
- [x] branch: what if random encounter is something that happens _before_
     you move!? That way the monster sprite will leap up! In front of you!
     - [x] check for random encounter _before_ resolving the move
     - [x] need to "not" collide because we want the "next" y, x values
           and then when we finish the encounter we should reset the next values
           so we don't animate a move.
           - we could use this to animate a little "thrust"
     - [x] put monster where the user trying to go, then we also
           do not have to keep track of facing!!!
     - [x] don't do random encounters on tiles that have AutoEvents
- [x] refactor! split up logic into the game states
      - each game state should have its own set of render functions,
      update functions, checks for state stability, checks for "done step",
      etc...
- [x] BUG - after you hit a random encounter coming off an auto event tile
      the game still runs the auto-event tile. This is because the "render"
      and "update" logic for Overworld is still running even though the game
      state has changed to random encounter. This is addressed by the following
      refactor

#### BACKLOG

##### Words

Going to focus on words for now. I want to be able
to have NPCs who say words in hiragana. Start with the
easy way.

- [] refactor! Need the sprites in VRAM block 1 at 8000
     and the BG/Window in blocks 2 and 3
- [] add the /r/n idea to the dialog system:
     - the first special character indicates "wait for input"
     - the second indicates "clear the line", and draw responds to it
     - taken together it lets you advance dialog

- [] events that trigger on A press and start a dialog 
- [] hiragana tiles

##### Equipment

Now that we have fights actually a table of monsters might not be as important
as... items and equipment! The goal here is to be able to put "things in places"
and get a feel for how to manage a JRPG with no battery save.

In order to do equipment we have some questions to answer

I need more think. The game is starting to want all this menu crud. It is losing
the purity of "password entry". It should be "push in the direction of the monster
to attack" hp goes down. "Push away from the monster to retreat, might succeed".

So how to manage equipment?
- player needs to be able to open a chest and get equipment
- equip the equipment
- compare to their existing equipment (possibly by swapping)
  (so they need to be able to see their stats)

"Always On" Stat bar a-la zelda?

OR do I need to accept menu drilling? In which case I need to think about
menu layout, how to display equipment names, etc...

My philosophy so far has been "try to do what you can with what you have"
so maybe I should do this. 

- [] equipment v0
  - [x] during battle: a menu at the bottom of the screen that displays HP and XP
  - [] a second menu for ATT DEF that pops up when you stand near a pedestal
  - [] equipment on pedestals, press A to swap

- [] lerp the XP so player sees gains before ending the encounter

- [] fight v3 - multiple monsters
  - make a table of monsters, randomly pick one
  - art for all monsters
  - stats for all monsters

- [] refactor! currently "handleMove" does to much. It should really
     just determine if the move can happen or not and then return
     control the main, where the game state can determine whether to
     move the player, or check for encounters, and to draw etc...

- [ ] refactor! right now we have this "isCurrentStateFinished" check that is
      always confusing. Here's what it means: 
      - the game starts
      - we hit that check with no inputs, it sends us to "perform step"
      - we perform a step (gather inputs, execute stuff)
        - if there were no inputs this loops
      - if there were inputs then,
      - we git that check again and it sends us through all the event
        checks (auto event, out of bounds, etc...)
      - then whichever one of those happens clears the inputs and we go back to the start

      I feeeeel like it would be better if we had an array of events, then we could do:
      - the game starts
      - there are no events on the stack
      - we perform a step
      - resolve events from the stack until they are gone
      - perform the next step

      This would make it easier to chain events too, since one event could put
      another on the stack... this might also make state changes more elegant
      (currently perform step might change the game state, but this should be handled
      by events or transition functions)
- [] it feels terrible to hit two random encounters in a row, so maybe
     we should actually restore the player's movement after the encounter?
     so they just animate into the next tile?
     - [] maybe we don't need to do anything, just don't reset the next y,x
       since the random encounter logic won't lerp y, x
     - [] I get the feeling that the randomness doesn't build up fast enough?
       like, the next number is low immediately after a low number?
     This can come later, while balancing encounter frequency etc
- [] animate a little "thrust" when the player tries to move into a space
     but is blocked by a random encounter, (or a wall)?
     - later, polish
- [] would be ideal if we could hide the background tile under
     the sprite... could just add this to the draw method for the
     state, so it always also draws 0 to that BG tile
     but it would need to store and restore it upon exiting the state
     - later, polish
- [] refactor! it is time to address sprites in a better way now that we
     are rendering player and encounter as sprites
     - [] get the "next free sprite"
     - [] do this not during vblank since we don't need to (we are just writing to OAMData)
     - address when it becomes an issue
- [] refactor! for stats that don't change often, like MAX_HP and ATT
     maybe store them in BCD instead of binary. Can implement add/sub
     for BCD no problem, and then we don't have to convert between binary
     and BCD so often
     - address when it becomes an issue
- [] refactor: encapsulate _PAD as it has leaked all over
     - it is not that bad really
- [] use a heart for HP and monster face for monster HP
     - polish, once UI is more settled

- [] when the player is idol, show the HP and XP in a top-side window
     - each game state should have its own window I guess
     - polish, once UI is more settled
  
- [] must improve import script, it should create the whole map file in the correct
     file location. It _could_ initialize the events based on a second layer in the
     tiled file, but I'm fine to do that later (actually I think this is unrealistic
     unless we had a custom map tool, because we need to init both sides of the link...
     ultimately we would still be manually entering the same amount of data)
     - [x] import multiple maps at once with a glob
     - [] split map file into two files and generate only what we can completely
       generate (ie remove the "copy/paste" step)
       - just manually wire up the teleports it is not so hard
       - adding a second layer with events would be hard
       - [] mmm maybe I should re-visit this idea later
- [] spread the render over several frames
     - right now, for larger maps, the CPU spikes up around 80% when we walk
     - render an extra tile around the currently visible map at all times 
       (eg render y - 1, x - 1 our to h + 1 w + 1)
     - turn the tile fiddling parts into continuation and run them in 2 frames, or 4
       rather than all at once
     - actually this is currently not a problem! I was able to render a 128x128 map
       however, it is 8kb and I will probably need to compress it later
       which will mean addressing this issue

#### DONE

- [x] a source of RNG
- [x] show the window on the bottom of the screen
- [x] display a byte as BCD
     [x] need tiles for the numbers
     [x] implement double-dabble
     [x] display player X, Y on the window (just for fun)
- [x] fight v0 - skeleton implementation of random encounter 
     - [x] while wandering around, after arriving in a new square,
       check against the random (start with 50/50)
     - [x] if the check passes,move the game into the encounter state
     - [x] put the window onto the bottom of the screen to indicate 
       this state visually for debugging
     - [x] in this state a button press returns us to the map state
- [x] bug: accidentally walking after ending a fight, or accidentally attacking immediately
     - we basically need to slow down the beginning and ending of
       and encounter so that the player who is pressing "up" when the
       encounter starts isn't automatically attacking... and the player
       who ends the fight isn't automatically stepping
     - is it enough to insert a pause? How long?
     - this might be trouble... normally in these games you press "A"
       to fight, and maybe this is why :D would not be a problem if
       we were rapidly pressing "A" but also these games definitely had
       a distinction between "press" and "hold"
       - if you had to "press" up to attack... and only start moving
         on a "press" but continue moving on a "hold"...
       - we need states "down" and then a delay and "held"
     - might need more sophisticated input processing for stuff like
       password input, where it is important... input buffer...
- [x] for now, change v0 so that "A" is the button for fight
- [x] fight v1 - whack'em
  - [x] add a stat block for the monster and player in data with
    just HP for both
  - [x] pushing "up" causes both numbers to go down by 1
    - we're going with "A" for now
  - [x] display player health on the window (implemented above)
  - [x] if player health hits 0 restart the game
  - [x] if monster health hits 0 end the encounter
- [x] only do fight command on "press" so that we don't have double inputs
  - [x] remember previous input state and compare
  - [x] refactor: we are using resetInput as a way to signal 
       that we are done processing the current frame... but
       this is bad because it means the input _PAD gets reset
       outside of the readInput routine so we can't do the "press"
       thing
- [x] calling doubleDabble is expensive, we should do it
      only when we need to not every frame

#### Double Dabble

3 bytes

byte 2    byte 1    byte 0
0000 0000 0000 0000 00000000

copy the value into the dabble

0000 0000 0000 0000 11111001 ; 249
0000 0000 0000 0001 11110010 ; shift
0000 0000 0000 0011 11100100 ; shift
0000 0000 0000 0111 11001000 ; shift
0000 0000 0000 1010 11001000 ; add 3
0000 0000 0001 0101 10010000 ; we always shift after adding in each column
0000 0000 0001 1000 10010000 ; add 3
0000 0000 0011 0001 00100000 ; shift
0000 0000 0110 0010 01000000 ; shift
0000 0000 1001 0010 01000000 ; add 3
0000 0001 0010 0100 10000000 ; shift
0000 0010 0100 1001 00000000 ; shift
        2    4    9          ; nooice

REPT 8, no need to iterate since all numbers are 8 bit

first, add 3 (no need to check for carry because the values 0101, 0110, 0111, 1000, 1001 will not overflow if you add 3)

check the bottom 4 bits of byte 2 (if >= 00000101, then add 3)
check the top 4 bits of byte 1 (if >= 01010000, then add 00110000)
check the bottom 4 bits of byte 1 (if >= 00000101, then add 3)

then shift

shift byte 2
shift byte 1
add carry to byte 2
shift byte 0 add carry to byte 1

repeat

Check out this sweet double dabble by pinoBatch:

bcd8bit_baa::
  swap a
  ld b,a
  and $0F  ; bits 3-0 in A, range $00-$0F
  or a     ; for some odd reason, AND sets half carry to 1
  daa      ; A=$00-$15

  sla b
  adc a
  daa
  sla b
  adc a
  daa      ; A=$00-$63
  rl b
  adc a
  daa
  rl b
  adc a
  daa
  rl b
  ret

### Before Dragon Quest Valley 02

- [x] implement 4 bit map tiles
- [x] implement tilesets per map (well or have a db of tilesets the maps point into)
- [x] parent/child maps so that walking off an edge leads you out
     - [x] no exit
     - [NAH] different exits for different edges

### Dragon Quest Valley 01

I have finished implementing events that move the player between maps, and I'm taking a break
from features to make a game with just that.

To Finish Content:

- [x] use tileD map editor and write an import script to convert the json data to map data
- [x] fill up 32kb with interlinked map data to explore
- [x] delete the silly Changelog file and version this instead
- [x] create sub-overworld areas for all hidden entrances
     this needs some kind of naming convention
- [x] rough out the inner maze, decide on the true paths
- [x] add more places where the inner maze surfaces
  - funnels into into sub-overworld hidden underworld entrances
  - or, temporarily surface e.g. a plateaux with another cave
- [x] connect up all the sub-underworld stairs
- [x] add more sub-underworld stairs connecting various parts of the inner maze
     - like, _real_ shortcuts. You know?
     - stairs in the top-left corner that lead to the bottom right corner. 
       That kind of thing. Or maybe some "fast travel" hubs, you know?
     - added the "tunnels" for this
- [x] tower area:
     - [x] make a nicer "ruins" tile
     - 3 sub-oveworlds in the ruins
       - 3 hidden entrances to a special maze under the lake
     - [x] make a ruined tower tile
     - [x] ruined tower in the center of the lake
     - the 3 ruins each have an entrance to the maze under the lake
       and the stairs up to the tower are visible in the maze
       but the correct path is not from any of the 3 ruins... it is
       from the peninsula south of the tower! One final little
       misdirection!
       - [x] make the final maze
         - [x] maybe make it a little smaller, simpler. The "puzzle" should be
           figuring out that the ruins are a misdirection, not navigating
           the maze per-say
       - [x] make 3 ruins
         - for the ruins, lets have an "interior" and "exterior" map for each one
           so the exterior map has a bunch of solid stone structures and the doors
           of each one take you to the interior map, where everything outside of the
           building is a solid stone structure
         - this will just make it different enough to matter, you know?
       - [x] wire up the ruins to the final maze
       - [x] wire up the stairs from the inner maze to the ruins
       - [x] make the grove on the peninsula
     - [x] make the tower
       - [x] link meditation room to the stairs in tower interior
       - [x] link peninsula and tower to the underworld stairs
- [x] start area
     - [x] add the interior
     - [x] use the village tile
     - [x] make the basement more like a basement
          - it can be the one place in the world where
            you walk in through a flat wall, I think that
            is better, lowers the chances of someone 
            stumbling into the inner maze randomly
- [x] make a sprite with a looping walk animation (no animation controller, just always loop)
     - this will make the desert sub-overworld map extra confusing because the player will
       not be sure if they are walking or not :D
     - maybe remove the "sand tile" and use plain white for desert
       for ultimate getting lost in the desert confusion
- [x] implement an "ending" when they find the tower
     - just a fade to black triggered by walking on the exit
- [x] fix A and B moving you up lol
- [x] desert sub-overworld
     - the desert is cool because it makes the tunnels to the east
       more useful. It might _always_ be difficult to cross the desert
       because finding the exit is like finding a grain of sesame
     - oh but this means the exit can't just be the far edge of the map
       because then you could clear it by just walking left, then down
     - [x] I should use _all_ of the remaining memory for the desert :D
     - [x] add a single cactus tile at the entrance that appears nowhere
       else in the game, an homage to the cactus in Desert Golfing
       - can replace the dots tile with this, and use null tile for sand
       - for now just add it, since we aren't actually limited to 16 tiles atm
     - [x] decide what to do with the stairs in the desert and wire them up
     - [x] create the isolated town near the desert
- [x] connect underworld 88x46 and add a sub-overworld map for that
- [x] store map data as nibbles
  - [x] pipeline converts json to array of nibbles
  - [x] pipeline can bulk process files
  - [x] make temporary desert map with no dunes of cacti called `desert-temp`
  - [x] convert all existing maps
- [x] overworld changes:
  - [x] remove all "town" tiles outside of the centre
- [x] implement unique meta-tileset per map
  - [x] make a plan
  - [x] implement it
  - [x] restore desert to its former glory (old desert.tmx file)
  - [x] update every map with the tileset pointer
- [x] implement the "map" and put it in the underworld tileset
  - [x] make a "map room" in the sub-underworld
  - [x] give it its own tileset with the map
  - note: this also frees up tiles to distinguish the "inner maze"
- [x] fix bugs and implement feedback
  - [x] map is filling from the wrong blank when walking around
  - [x] bug: you can enter a door by pressing a or b and it is glitchy
- [x] parent/child maps so that you can exit a map from any side
     specified with a flag in metadata so you can turn it off for desert
     - [x] implement it
     - [x] get all the appropriate maps using it
- [x] try adding a 3 frame fade out/in when entering/exiting
  - I think with parent/child implemented this will be important
    because it gives the player time to take their finder off the
    button if they want (DQ has this)
- [x] folks stumbling into that first illusory wall
  - [x] start the player outside, I think a lot of people felt like
    that was the only way they could go
  - [x] originally that area was also a forest, maybe make it a
    forest again and make it optional so that a player
    would have to 1. go into that forest, 2. push up against
    random walls. Just reduces the probability of that happening
    first.
  - [?] have it be a little town with 3 houses that all have basements
    but only one of them is connected to the underworld in
    that way
    - maybe not! The player would visit each basement and would
      notice that one of them is surrounded by maze paths and
      they would push up against the walls in search of treasure
- [x] add a path from east to west across the desert so that the player isn't 
     immediately thrown into the deep end... they can take the plunge if they
     want (it also connects east to west which is how the map was designed)
- [NO] try doubling the movement speed in the underworld
     - easy to double movement, no problem... but how to tell if
       the player is in the overworld?
- [x] player arrives on a boat or something
   - boat sprite, cut scene of boat coming up across the water,
     through the delta, and the player emerges
- [x] add missing sub-overworlds
  - [x] add sub-overworld at 25, 16
  - [x] connect 35, 30 to the underworld
- [NO] try implementing "recall spell" the player can press "A" to leave a marker
     and then "B" to return to the marker
     - could implement it at as TransportEvent in RAM :D just 7 bytes
       and the game would know how to deal with it...
       - buuuuut needs an animation, maybe even a sound effect
       - buuuuut I can prototype it without that
     - feels like this could make maze navigation a little nicer
     - general exploration activities are nicer too
     - it encourages "returning" to a known location
     - hmm... but then the player can't really get "lost"
       it is a bit of a double edged sword...
     - having sat on this I say nay
- [x] try using a different scale of tree for sub-maps
     - dragon quest gets away with the scale thing because
       sub-map entrances indicate interior scale (ie town icons)
     - dragon quest II uses interior scale trees in towns
     - this seems OK!
- [x] bug: desert bounds seems to be misbehaving
     - put some objects around the bounds so that you can see
       if you are in fact colliding, watch the VRAM

- [NAH] bug: stop waiting for vblank in the fade in/out
     it should set up draw instructions, just like draw
- [NAH] maybe make sub overworld maps more like "groves" and "ruins" 
  rather than "paths" so that it makes sense to exit from
  wherever
  - after playing around with these it seems fine
- [NAH] try implementing a visual distinction between "inner maze" and outer maze
     - inner maze could be more dilapidated 
- [NAH] expand the desert to fill up the remaining bytes

- [] create paratext! lore, manual, box art!!!
     - I'll do this after letting the game sleep for a bit
       I will play it again and then make a nice itch.io page

### v0.8.9 Feedback
 - [x] remove the river from the north side of the map 
   (the river should flow down from the mountain)
 - [x] make it clearer where "the centre" is. I think that this one
   is tricky for me personally because I love when people figure
   stuff out on there own... but I can't just ignore that it
   isn't happening. 
   - [x] maybe have a room early on with a big map of the island's
     contours or something... like when you enter a hedge maze
     you can typically see whole thing layed out before you
 - [x] have to make it clear I mean "geographic centre"
   - [x] add a vague map to a room (maybe the big room full of squares in the
     east, or the big empty room in the west)
 - [x] widen desert exits and start the player 1 tile in so they can back out
 - more loops at the start, to keep the player in that initial area for
   a while?
   - at the moment they rush out, they leave too soon and don't form
     enough attachment to that area, so when they return they aren't
     sure.

Dragon Quest gets away with not varying the scale of trees, but I think it's 
partly because entrances in DQ always signal the scale of the interior. A 
small picture of a castle... a cave entrance... etc. When someone entered a
cave in the valley they never said "whoa so confusing, where am I whoa" but any time they
entered a forest I got that kind of feedback.

#### Meta-tileset Per Map Plan

- we import the graphics file into ROM as the "master tileset"
  - aside: looking ahead to a future where we might want to be able
    to "swap" the master tileset, for things like day/night or seasons...
    - each tile is 16 bytes so each meta tile is 64 bytes
    - easy enough to just use a pointer and set it
- each map has a list of 16 indexes into the master tileset
  along with a meta data pointer to this list
- when we load a map we iterate over this list, loading
  tiles into VRAM (LCD is already off when we load a map)
- each map has a pointer to a metatile attribute table
  - and possibly later to two such tables

- we need to add 4 bytes of meta data and adjust all the
  places that depend on meta data size
  - meta data will be up to 8 bytes so we might want to consider
    an alignment that will let us easily jump to and from
    the map data without needing to inc inc inc inc
- subroutines to getMetaTileAttributes and getMetaTileList
- we should have "default" meta tile attributes and lists in ROM
  somewhere and point to these by default, so that for the current
  game (valley 02) we don't need to add a bunch of useless tables

- later we can optimize this by keeping a list of "loaded indexes"
  and checking "is this tile already loaded in this slot"

- this adds 4 bytes of pointers, 16 bytes of attributes and 16 bytes of
  tile list to each map...
  - OK SO! Actually it is OK because we are using pointers so a map _can_
    have a completely unique tileset all its own... OR it can point into
    a collection of tilesets. So yeah we will add 36 bytes per unique tileset
    but not per map

### 15->15 Compression Thing

 - Tom Sutton suggested this for text representation but I think it might
   be great for tiles. The idea is
   - each nibble has 15 indexes into the table that are the 15 most common
     tiles
   - the 16th value F is a symbol that indicates we should check the next byte
   - the next byte is an index into the next most common 15 tiles
 - the idea is that each map could have its own "rare tiles" sub-set that could
   be used to encode things like big old trees, shrines in the forest, or a cactus
 - the trouble is, then the "rows" in each map will not be consistent length so our
   seekIndex method will need to change:
   - we could store the length of each row in the first byte... but then every map
     gets an extra N bytes :/
   - we could have seekIndex actually seek across the whole array and just count the F's
     but then we have slowed down an already slow bit of the game
   - we could store the "second byte" elsewhere... like below the map or after the map
     data... that's interesting. We'd have to push hl jump to the list of special tiles
     seek to the correct tile index for the given y, x and then pop
     - it is possibly less work than scanning the whole line
     - NO: is scanning the whole line such a lot of work? We just have to inc and test,
       and don't count F's
       - but man seekIndex is called many times...
       - no it's waaaaay too long! Imagine seeking the last row! It's already basically
         too long if we are thinking to have 128 rows or something. Damn.


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
