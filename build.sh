mkdir -p build objects

./bin/rgbgfx -T -h -o assets/valley-graphics-8x8-tiles.2bpp assets/valley-graphics-8x8-tiles.png
./bin/rgbgfx -T -h -o assets/valley-map-8x8-tiles.2bpp assets/valley-map-8x8-tiles.png
./bin/rgbgfx -T -h -o assets/valley-sprites-8x8-tiles.2bpp assets/valley-sprites-8x8-tiles.png
./bin/rgbgfx -T -h -o assets/valley-hero-8x8-tiles.2bpp assets/valley-hero-8x8-tiles.png
./bin/rgbgfx -T -h -o assets/valley-additional-8x8-tiles.2bpp assets/valley-additional-8x8-tiles.png
./bin/rgbgfx -T -h -o assets/window-graphics.2bpp assets/window-graphics.png
./bin/rgbgfx -T -h -o assets/valley-monsters.2bpp assets/valley-monsters.png
./bin/rgbgfx -T -h -d1 -o assets/misaki_gothic.1bpp assets/misaki_gothic.png
./bin/rgbgfx -T -h -d1 -o assets/alphabet.1bpp assets/alphabet.png

./bin/rgbasm -i src -o objects/main.o src/main.asm
./bin/rgblink -n build/showdown.sym -m build/showdown.map -o build/showdown.gb objects/main.o
./bin/rgbfix -v -p 0 build/showdown.gb