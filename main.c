/*
Beginner: 9 × 9, 10 mines
Intermediate: 16 × 16, 40 mines
Expert: 30 × 16 tinklelis, 99 mines
*/

#include "raylib.h"
#include <stdio.h>

int main() {

  InitWindow(800, 600, "Minesweeper by Matas Janavičius");
  int height = GetMonitorHeight(0);
  int width = GetMonitorWidth(0);
  SetWindowSize(width * 4 / 5, height * 4 / 5);
  SetWindowPosition(width / 10, height / 10); //(x - 4/5x) / 2 = x / 10
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
