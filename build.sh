mkdir -p build objects
rgbgfx -o assets/arkanoid-graphics.2bpp assets/arkanoid-graphics.png
rgbasm -i src -o objects/main.o src/main.asm
rgblink -m build/showdown.map -o build/showdown.gb objects/main.o
rgbfix -v -p 0 build/showdown.gb
