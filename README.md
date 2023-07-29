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

-[] finish up my import so that I skip step 4.
-[] update import to handle events embedded the tiled layers

