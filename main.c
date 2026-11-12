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
int isInArray(int num, int arr[], int len) {
  for (int i = 0; i < len; ++i) {
    if (arr[i] == num) {
      return 1;
    }
  }
  return 0;
}
int *generateRandomBombsIndexessList(int totalCells, int avoid, int quantity) {
  int counter = 0;
  int *indexes = malloc(sizeof(int) * quantity);
  if (indexes == NULL) {
    return NULL;
  }
  while (counter < quantity) {
    int temp = rand() % totalCells;
    if (temp != avoid && !isInArray(temp, indexes, counter)) {
      indexes[counter] = temp;
      ++counter;
    }
  }
  return indexes;
}
int countMinesAroundTile(Tile *tiles, int x, int y, int gridsizex,
                         int gridsizey) {
  int minesAround = 0;
  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (dx == 0 && dy == 0)
        continue;
      int actualX = x + dx;
      int actualY = y + dy;
      if (actualX < gridsizex && actualY < gridsizey && actualX >= 0 &&
          actualY >= 0) {
        int index = gridsizex * actualY + actualX;
        if (tiles[index].isMine) {
          ++minesAround;
        }
      }
    }
  }
  return minesAround;
}
void placeMines(Tile *tiles, int totalCells, int firstClickIndex, int bombs) {
  int *bombIndexes =
      generateRandomBombsIndexessList(totalCells, firstClickIndex, bombs);
  if (bombIndexes != NULL) {
    for (int i = 0; i < bombs; ++i) {
      tiles[bombIndexes[i]].isMine = 1;
    }
    free(bombIndexes);
  }
}
Tile *initEmptyTiles(int totalCells) {
  Tile *tiles = malloc(sizeof(Tile) * totalCells);
  if (tiles == NULL) {
    return NULL;
  }
  for (int i = 0; i < totalCells; ++i) {
    tiles[i].isMine = 0;
    tiles[i].isFlagged = 0;
    tiles[i].isRevealed = 0;
    tiles[i].neighboursMines = 0;
  }
  return tiles;
}
Tile *generateTilesStructList(int horizontal, int vertical, int bombs,
                              int firstClickIndex) {
  // generate empty Tile type list
  Tile *tiles = initEmptyTiles(horizontal * vertical);
  // place mines at random indexes
  placeMines(tiles, horizontal * vertical, firstClickIndex, bombs);
  // count neighbours
  for (int y = 0; y < vertical; ++y) {
    for (int x = 0; x < horizontal; ++x) {
      int index = y * horizontal + x;
      if (!tiles[index].isMine) {
        tiles[index].neighboursMines =
            countMinesAroundTile(tiles, x, y, horizontal, vertical);
      }
    }
  }
  return tiles;
}
void drawTiles(int horizontal, int vertical, int bombs) { return; }
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