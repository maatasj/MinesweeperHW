
# Minesweeper

## Reikalavimai
Projekto paleidimui reikalinga `raylib` biblioteka

### macOS
1. Įdiekite raylib per Homebrew:
   `brew install raylib`
2. Kompiliavimas:
   `clang src/main.c -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -o Minesweeper`
3. Paleidimas:
   `./Minesweeper`

### Windows
1. Įdiekite raylib (arba turėkite bibliotekos failus).
2. Kompiliavimas (su MinGW / GCC):
   `gcc src/main.c -lraylib -lopengl32 -lgdi32 -lwinmm -o Minesweeper.exe`
3. Paleidimas:
   `Minesweeper.exe`

### Linux
1. Įdiekite raylib paketą (pvz., `sudo apt install libraylib-dev`).
2. Kompiliavimas:
   `gcc src/main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o Minesweeper`
3. Paleidimas:
   `./Minesweeper`