mkdir -p build objects

rgbgfx -u -o assets/arkanoid-graphics.2bpp assets/arkanoid-graphics.png
rgbgfx -T -u -o assets/arkanoid-map.2bpp assets/arkanoid-map.png

rgbasm -i src -o objects/main.o src/main.asm
rgblink -n build/showdown.sym -m build/showdown.map -o build/showdown.gb objects/main.o
rgbfix -v -p 0 build/showdown.gb
