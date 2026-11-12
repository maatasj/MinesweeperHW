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

Color dark_charcoal = {38, 35, 34, 255};
Color parchment_cream = {225, 216, 196, 255};
Color royal_crimson = {124, 24, 39, 255};
Color aged_gold = {197, 155, 39, 255};
Color tarnished_steel = {112, 120, 128, 255};

typedef struct {
  int posx;
  int posy;
  int isMine;
  int isRevealed;
  int isFlagged;
  int neighboursMines;
} Tile;

int min2(int a, int b) {
  if (a < b) {
    return a;
  } else {
    return b;
  }
}
int generateRandomBombsList(int start, int end, int avoid) {

  return 0;
  return (rand() % (end - start + 1)) + start;
}
/*int isInArray(int num, int arr[], int len) {
  for (int i = 0; i < len; ++i) {
    if () {
    }
  }
}
*/
void drawWindow() {
  SetConfigFlags(FLAG_WINDOW_HIGHDPI);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(WIDTH, HEIGHT, "Minesweeper by Matas Janavičius");
  SetTargetFPS(60);
  // SetWindowSize(width * 4 / 5, height * 4 / 5);
  // SetWindowPosition(width / 10, height / 10); //(x - 4/5x) / 2 = x / 10
}
void windowInfo();
void drawMinesweeperGrid(int gridSizex, int gridSizey) {
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();

  int minMargin = 50;
  int availableWidth = screenWidth - (2 * minMargin);
  int availableHeight = screenHeight - (2 * minMargin);

  // Calculate size of square
  int cubeWidth = availableWidth / gridSizex;
  int cubeHeight = availableHeight / gridSizey;
  int cubeSize = (cubeWidth < cubeHeight) ? cubeWidth : cubeHeight;

  // Calculate size of grid
  int totalGridWidth = cubeSize * gridSizex;
  int totalGridHeight = cubeSize * gridSizey;

  // Center the grid in the window
  int leftMargin = (screenWidth - totalGridWidth) / 2;
  int topMargin = 5 * (screenHeight - totalGridHeight) / 6;

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
    ClearBackground(parchment_cream);
    // int topMargin = 2 * 100;
    // int leftMargin = 2 * 100;
    drawMinesweeperGrid(9, 9);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

// will be deleted in the future
void windowInfo() {
  int cubeWidth = GetScreenWidth();
  int monitorWidth = GetMonitorWidth(0);
  int cubeHeight = GetScreenHeight();
  int monitorHeight = GetMonitorHeight(0);
  printf("Screen Width: %d\n", cubeWidth);
  printf("Monitor Width: %d -- %d\n", monitorWidth, monitorWidth * 4 / 5);
  printf("Screen Height: %d\n", cubeHeight);
  printf("Monitor Height: %d -- %d\n", monitorHeight, monitorHeight * 4 / 5);
  printf("After changes:\n");
  SetWindowSize(monitorWidth * 4 / 5, monitorHeight * 4 / 5);
  cubeWidth = GetScreenWidth();
  monitorWidth = GetMonitorWidth(0);
  cubeHeight = GetScreenHeight();
  monitorHeight = GetMonitorHeight(0);
  printf("Screen Width: %d\n", cubeWidth);
  printf("Monitor Width: %d -- %d\n", monitorWidth, monitorWidth * 4 / 5);
  printf("Screen Height: %d\n", cubeHeight);
  printf("Monitor Height: %d -- %d\n", monitorHeight, monitorHeight * 4 / 5);
}