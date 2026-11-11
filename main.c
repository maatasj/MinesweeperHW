/*
Beginner: 9 × 9, 10 mines
Intermediate: 16 × 16, 40 mines
Expert: 30 × 16 tinklelis, 99 mines
*/
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WIDTH 1440
#define HEIGHT 900

int min2(int a, int b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}
int generateRandomBombsList(int start, int end, ) {
  return (rand() % (end - start + 1)) + start;
}

void drawWindow() {
  SetConfigFlags(FLAG_WINDOW_HIGHDPI);

  InitWindow(WIDTH, HEIGHT, "Minesweeper by Matas Janavičius");
  SetTargetFPS(60);
  // SetWindowSize(width * 4 / 5, height * 4 / 5);
  // SetWindowPosition(width / 10, height / 10); //(x - 4/5x) / 2 = x / 10
}
void windowInfo() {
  int cubeWidth = GetScreenWidth();
  int monitorWidth = GetMonitorWidth(0);
  int cubeHeight = GetScreenHeight();
  int monitorHeight = GetMonitorHeight(0);
  printf("Screen Width: %d\n", cubeWidth);
  printf("Monitor Width: %d -- %d\n", monitorWidth, monitorWidth * 4 / 5);
  printf("Screen Height: %d\n", cubeHeight);
  printf("Monitor Height: %d -- %d\n", monitorHeight, monitorHeight * 4 / 5);
}
void drawMinesweeperGrid(int gridSizex, int gridSizey) {
  int minMargin = 50;
  int availableWidth = WIDTH - (2 * minMargin);
  int availableHeight = HEIGHT - (2 * minMargin);
  // calculate size of square
  int cubeWidth = availableWidth / gridSizex;
  int cubeHeight = (availableHeight) / gridSizey;
  int cubeSize = min2(cubeHeight, cubeWidth);
  // calculate size of grid
  int totalGridWidth = cubeSize * gridSizex;
  int totalGridHeight = cubeSize * gridSizey;

  // 4. Center the grid in the window (margins will be >= minMargin)
  int leftMargin = (WIDTH - totalGridWidth) / 2;
  int topMargin = 5 * (HEIGHT - totalGridHeight) / 6;
  int i = 0;
  for (int y = 0; y < gridSizey; ++y) {
    for (int x = 0; x < gridSizex; ++x) {
      int hor = x * cubeSize;
      int ver = y * cubeSize;
      DrawRectangleLines(leftMargin + hor, topMargin + ver, cubeSize, cubeSize,
                         GRAY);
      DrawText(TextFormat("%d", i + 1), leftMargin + hor + 2, topMargin + ver,
               10, BLACK);
      i += 1;
    }
  }
}

int main() {
  drawWindow();
  windowInfo();
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    // int topMargin = 2 * 100;
    // int leftMargin = 2 * 100;
    drawMinesweeperGrid(9, 9);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
