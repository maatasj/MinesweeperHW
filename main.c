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
Vector2 click;
int isInArray(int num, int arr[], int len) {
  for (int i = 0; i < len; ++i) {
    if (arr[i] == num) {
      return 1;
    }
  }
  return 0;
}
int *generateRandomBombsIndexessList(int horizontal, int vertical, int avoid,
                                     int quantity, int firstClickIndex) {
  int totalCells = horizontal * vertical;
  int firstX = firstClickIndex % horizontal;
  int firstY = firstClickIndex / horizontal;
  int counter = 0;
  int *indexes = malloc(sizeof(int) * quantity);
  if (indexes == NULL) {
    return NULL;
  }
  while (counter < quantity) {
    int temp = rand() % totalCells;
    int randX = temp % horizontal;
    int randY = temp / horizontal;

    if (temp != avoid && !isInArray(temp, indexes, counter)) {
      if (abs(randX - firstX) > 1 && (abs(randY - firstY) > 1)) {
        indexes[counter] = temp;
        ++counter;
      }
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
void placeMines(Tile *tiles, int horizontal, int vertical, int firstClickIndex,
                int bombs) {

  int *bombIndexes = generateRandomBombsIndexessList(
      horizontal, vertical, firstClickIndex, bombs, firstClickIndex);
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
  tiles[firstClickIndex].neighboursMines = 0;
  placeMines(tiles, horizontal, vertical, firstClickIndex, bombs);
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
  // tiles[firstClickIndex].isRevealed = 1;
  return tiles;
}

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
                         BLACK);
    }
  }
}
void drawTiles(Tile *tiles, int gridSizex, int gridSizey, int bombs) {
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

  if (tiles == NULL) {
    return;
  }

  for (int y = 0; y < gridSizey; ++y) {
    for (int x = 0; x < gridSizex; ++x) {
      int hor = x * cubeSize;
      int ver = y * cubeSize;
      int posX = leftMargin + hor;
      int posY = topMargin + ver;
      int fontSize = cubeSize / 2;

      if (tiles[i].isFlagged) {
        const char *txt = "Flag";
        int textWidth = MeasureText(txt, fontSize);
        DrawRectangle(leftMargin + hor, topMargin + ver, cubeSize, cubeSize,
                      DARKGRAY);

        DrawRectangleLines(leftMargin + hor, topMargin + ver, cubeSize,
                           cubeSize, BLACK);
        DrawText(txt, posX + (cubeSize - textWidth) / 2,
                 posY + (cubeSize - fontSize) / 2, fontSize, BLACK);
      }
      if (tiles[i].isRevealed && tiles[i].isMine) {
        const char *txt = "BOMB";
        int textWidth = MeasureText(txt, fontSize / 2);
        DrawRectangle(leftMargin + hor, topMargin + ver, cubeSize, cubeSize,
                      DARKGRAY);

        DrawRectangleLines(leftMargin + hor, topMargin + ver, cubeSize,
                           cubeSize, BLACK);
        DrawText(txt, posX + (cubeSize - textWidth) / 2,
                 posY + (cubeSize - fontSize / 2) / 2, fontSize / 2, BLACK);
      }
      if (tiles[i].isRevealed && tiles[i].neighboursMines > 0) {
        const char *txt = TextFormat("%d", tiles[i].neighboursMines);
        int textWidth = MeasureText(txt, fontSize);
        DrawRectangle(leftMargin + hor, topMargin + ver, cubeSize, cubeSize,
                      DARKGRAY);

        DrawRectangleLines(leftMargin + hor, topMargin + ver, cubeSize,
                           cubeSize, BLACK);
        DrawText(txt, posX + (cubeSize - textWidth) / 2,
                 posY + (cubeSize - fontSize) / 2, fontSize, BLACK);
      }
      if (tiles[i].isRevealed && tiles[i].neighboursMines == 0 &&
          tiles[i].isMine == 0 && tiles[i].isFlagged == 0) {

        DrawRectangle(leftMargin + hor, topMargin + ver, cubeSize, cubeSize,
                      DARKGRAY);
        DrawRectangleLines(leftMargin + hor, topMargin + ver, cubeSize,
                           cubeSize, BLACK);
      }
      ++i;
    }
  }
}
void renderStartMenu(int *horizontal, int *vertical, int *bombs) {
  *horizontal = 30;
  *vertical = 16;
  *bombs = 99;
}
int mouseClickToIndex(Vector2 click, int gridSizex, int gridSizey) {
  int x = click.x;
  int y = click.y;
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
  if (x < leftMargin || x > totalGridWidth + leftMargin || y < topMargin ||
      y > topMargin + totalGridHeight) {
    return -1;
  }
  x = (int)(x - leftMargin) / cubeSize;
  y = (int)(y - topMargin) / cubeSize;
  return ((y * gridSizex) + x);
}
void revealEmptyTiles(Tile *tiles, int x, int y, int gridSizex, int gridSizey) {
  int index = (y * gridSizex) + x;
  if (x < 0 || x >= gridSizex || y < 0 || y >= gridSizey) {
    return;
  }

  if (tiles[index].isRevealed || tiles[index].isFlagged) {
    return;
  }
  tiles[index].isRevealed = 1;
  if (tiles[index].neighboursMines > 0) {
    return;
  }
  for (int dy = -1; dy <= 1; ++dy) {
    for (int dx = -1; dx <= 1; ++dx) {
      if (dx == 0 && dy == 0)
        continue;
      revealEmptyTiles(tiles, x + dx, y + dy, gridSizex, gridSizey);
    }
  }
}
Tile *HandleInput(int *firstClickIndex, Tile *tiles, int horizontalTiles,
                  int verticalTiles, int bombs) {
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    click = GetMousePosition();
    int clickIndex = mouseClickToIndex(click, horizontalTiles, verticalTiles);
    // checks if not out of bounds
    if (clickIndex != -1) {

      if (*firstClickIndex == -1) {
        // handle first click
        *firstClickIndex = clickIndex;
        tiles = generateTilesStructList(horizontalTiles, verticalTiles, bombs,
                                        *firstClickIndex);
        if (tiles != NULL) {
          int tempX = clickIndex % horizontalTiles;
          int tempY = clickIndex / horizontalTiles;
          revealEmptyTiles(tiles, tempX, tempY, horizontalTiles, verticalTiles);
        }
      } else {
        // Handle subsequent clicks
        if (tiles[clickIndex].neighboursMines == 0 &&
            tiles[clickIndex].isMine == 0) {
          int clickX = clickIndex % horizontalTiles;
          int clickY = clickIndex / horizontalTiles;
          revealEmptyTiles(tiles, clickX, clickY, horizontalTiles,
                           verticalTiles);
        } else {
          tiles[clickIndex].isRevealed = 1;
        }
      }
    }
  }
  if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
    click = GetMousePosition();
    int clickIndex = mouseClickToIndex(click, horizontalTiles, verticalTiles);
    if (clickIndex != -1 && tiles[clickIndex].isRevealed == 0) {
      tiles[clickIndex].isFlagged = !tiles[clickIndex].isFlagged;
    }
  }
  return tiles;
}
int main() {
  srand(time(NULL));
  drawWindow();
  int firstClickIndex = -1;
  int horizontalTiles, verticalTiles, bombs;
  renderStartMenu(&horizontalTiles, &verticalTiles, &bombs);
  Tile *tiles = NULL;
  while (!WindowShouldClose()) {
    tiles = HandleInput(&firstClickIndex, tiles, horizontalTiles, verticalTiles,
                        bombs);
    BeginDrawing();
    ClearBackground(GRAY);
    drawMinesweeperGrid(horizontalTiles, verticalTiles);
    drawTiles(tiles, horizontalTiles, verticalTiles, bombs);
    EndDrawing();
  }
  free(tiles);
  CloseWindow();
  return 0;
}
