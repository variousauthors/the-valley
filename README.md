# Dragon Quest Valley 01

I have 4-directional scrolling, a single bit for collision, and
screen transitions. Combine this with a couple of tiles and you've
got a good chunk of Dragon Quest's features.

I'm stopping now to create a valley with just these things.

### Process

When I made the first valley, I started with a picture of a valley essentially.
Then I gradually filled it up with little tunnels and towns and such. This was
a challenge for me, and trying to fill this big space with things that felt
like they were the right scale was a challenge. In the end I broke some of my
own rules, and the valley ended up feeling very dominated by a small number of
representations of places, center pieces, rather than being about pathways
and authored sight-lines.

In my first attempt at a second valley, again in RPG maker, I tried to focus
more on those paths. I encountered a motivation problem that got me thinking
more about process. In the second valley the player starts at a dock, crosses
a beach, and then ascends winding paths up the side of a cliff to a town. Those
winding paths I find very compelling to explore... caves behind waterfalls, nice
sight-lines encouraging a bit of curiosity, etc... but I found making it to be
really exhausting. I had once again chosen an arbitrary dimension that felt pleasing
mathematically, like 32x64 tiles or something, and then tried to fill it in.

This isn't the way that I build puzzles, and I enjoy building puzzles. In a puzzle
you typically have a tiny space and are moving blocks around in order to coax out
a pleasing puzzle... every tile you place or move changes the puzzle significantly.
Compared to this, filling in an arbitrarily large space that may ultimately have just
1 or 2 events feels empty, just a way to fill time. I have often commented that making
a puzzle game is more fun that playing a puzzle game, deeper in some ways.

That's why this time I am not making a big valley and "filling it in". I'm making
tiny 10x9 paintings, little spaces packed as tightly as possible with visual
interest, and then stitching them together. So far it is working very nicely!

### Tools

Gosh! I really need to further automate the build process. As it stands:

1. modify either the overworld or a single painting, and then keep them in sync
2. export each map I've changed to json
3. run my import script to generate bytes
4. copy/paste those bytes into the includes, possibly also updating the h/w values
5. manually copy over the auto events, twice each for exits/entrances

to run the build of the maps:

```
cd pipeline
cargo run -- --in-file="../assets/*.json"
cd ..
```

to generate texts:

```
node ./src/scripts/text-encode.js "our people live" "on the coast where" "it is still safe"
```


-[] finish up my import so that I skip step 4.
-[] update import to handle events embedded the tiled layers

### Features

While I work I stumble upon limitations, and potential new features. Once
this valley is done, I will implement some of them, and then make another valley.

1. auto-tiling

I love having just 16 tiles, but it would be nice to have coasts and
rounded forests and stuff... I can have both if I implement auto-tiling!
The $02 that represents "forest" can instead represent "auto-tile forest here"
that way I can have 16 indices into a much larger table of meta-tiles

2. Seed tiles

There are other ways to use proc-gen to go from single tile to something
bigger. For example $02 could indicate "draw a tree here". The renderer
might need to "look around" while it is rendering, to determine whether
it needs to start filling in something like a tree.

3. Per Map tile sets

We can have 16 meta-tiles per map, instead of 16 over all. Very nice.

4. Directional Collisions

Nice cliffs and bridges and stuff require edges to be marked for collision
but I'm not sure how to do this with just 16 tiles. Where does the collision
data live? Maybe at that point we would need to use "geometry"...

Or the auto-tile system could maybe help with this. Like, if I'm stepping
onto a cliff it will be one of the auto-tiled cliff bits, not just "cliff"
and it is pretty clear how each of those cliff tiles should behave.
    
5. Directional Auto-events

Stepping onto a broken bridge that takes us to a broken bridge sub-map
is cool, but then when you step off it should animate you leaving
the bridge in the overworld so that you don't end up in the overworld
on the broken bridge...
