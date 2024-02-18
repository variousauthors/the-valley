mkdir -p build objects

rgbgfx -T -h -o assets/valley-graphics-8x8-tiles.2bpp assets/valley-graphics-8x8-tiles.png
rgbgfx -T -h -o assets/valley-map-8x8-tiles.2bpp assets/valley-map-8x8-tiles.png
rgbgfx -T -h -o assets/valley-sprites-8x8-tiles.2bpp assets/valley-sprites-8x8-tiles.png
rgbgfx -T -h -o assets/valley-additional-8x8-tiles.2bpp assets/valley-additional-8x8-tiles.png
rgbgfx -T -h -o assets/window-graphics.2bpp assets/window-graphics.png
rgbgfx -T -h -d1 -o assets/misaki_gothic.1bpp assets/misaki_gothic.png

rgbasm -i src -o objects/main.o src/main.asm
rgblink -n build/showdown.sym -m build/showdown.map -o build/showdown.gb objects/main.o
rgbfix -c -v -p 0 build/showdown.gb