#include "raylib.h"

int main(void) {

  InitWindow(800, 450, "Minesweeper");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}