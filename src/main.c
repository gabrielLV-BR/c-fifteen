#include <raylib.h>

#include <inttypes.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

/* CONSTANTS */

#define WINDOW_TITLE "Fifteen"

#define MIN_WINDOW_WIDTH 300
#define MIN_WINDOW_HEIGHT 300

#define MAX_WINDOW_WIDTH 900
#define MAX_WINDOW_HEIGHT 900

/* STRUCTS */

typedef enum Direction
{
  UP,
  DOWN,
  LEFT,
  RIGHT
} Direction;

typedef struct
{
  int width, height;
  int** nums;
} Board;
/* FUNCS */

void randomize_board(Board* board);
void move(Board* board, Direction dir);

// char* int_to_string(int i);
void shuffle(int* arr, int n);

int** allocate_integer_matrix(int w, int h);
void free_integer_matrix(int** matrix, int r);

/* MAIN */

int main()
{
  // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT, WINDOW_TITLE);

  char* NUM_TO_STRING_MAP[17] = {
    "0", "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",
    "9", "10", "11", "12", "13", "14", "15", "16",
  };

  Board board = (Board){ 4, 4, allocate_integer_matrix(4, 4) };

  randomize_board(&board);

  int cell_width, cell_height;
  const int PADDING = 2;

  cell_width =
    (GetScreenWidth() - PADDING - board.width * PADDING) / board.width;
  cell_height =
    (GetScreenHeight() - PADDING - board.height * PADDING) / board.height;

  while (!WindowShouldClose()) {
    ClearBackground(LIGHTGRAY);

    if (IsKeyPressed(KEY_RIGHT))
      move(&board, RIGHT);
    else if (IsKeyPressed(KEY_LEFT))
      move(&board, LEFT);
    else if (IsKeyPressed(KEY_UP))
      move(&board, UP);
    else if (IsKeyPressed(KEY_DOWN))
      move(&board, DOWN);

    BeginDrawing();

    for (int i = 0; i < board.height; i++) {
      for (int j = 0; j < board.width; j++) {
        int x = (j + 1) * PADDING + cell_width * j;
        int y = (i + 1) * PADDING + cell_height * i;

        DrawRectangle(x, y, cell_width, cell_height, GRAY);

        // printf("Board[%d, %d] = %d\n", i, j, board.nums[i][j]);
        // printf("\t-> To String: %s\n", str_num);
        // printf("----\n");

        if (board.nums[i][j] == 0)
          continue;
        const char* str_num = NUM_TO_STRING_MAP[board.nums[i][j]];
        DrawText(str_num, x, y, cell_height * 0.6, BLACK);
      }
    }

    EndDrawing(); // end drawing + swap + poll events
  }

  CloseWindow();
}

/* IMPL */

void randomize_board(Board* b)
{
  int max_num = b->width * b->height - 1;
  int bucket[max_num];
  for (int i = 0; i < max_num; i++) {
    bucket[i] = i + 1;
    printf("bucket[%d] = %d\n", i, i + 1);
  }

  shuffle(bucket, max_num);

  for (int i = 0; i < max_num; i++) {
    int x         = floor(i / b->width);
    int y         = i % b->width;
    b->nums[x][y] = bucket[i];
  }
  b->nums[b->width - 1][b->height - 1] = 0;
}

void move(Board* board, Direction dir)
{
  printf("Called MOVE with direction %d\n", dir);
  switch (dir) {
    case UP: {
      printf("UP!\n");
      for (int column = 0; column < board->width - 1; column++) {
        for (int row = 0; row < board->height - 1; row++) {
          if (board->nums[row][column] == 0) {
            board->nums[row][column]     = board->nums[row + 1][column];
            board->nums[row + 1][column] = 0;
          }
        }
      }

      break;
    }
    case DOWN: {
      printf("Down!\n");
      for (int column = 0; column < board->width; column++) {
        for (int row = board->height - 1; row < 0; row--) {
          if (board->nums[row][column] == 0) {
            board->nums[row][column]     = board->nums[row - 1][column];
            board->nums[row - 1][column] = 0;
          }
        }
      }
      break;
    }
    case LEFT: {
      printf("Left!\n");
      for (int row = 0; row < board->height; row++) {
        for (int column = 0; column < board->width - 1; column++) {
          if (board->nums[row][column] == 0) {
            board->nums[row][column]     = board->nums[row][column + 1];
            board->nums[row][column + 1] = 0;
          }
        }
      }
      break;
    }
    case RIGHT: {
      printf("RIGht!\n");
      for (int row = 0; row < board->height; row++) {
        for (int column = board->width - 1; column > 0; column--) {
          if (board->nums[row][column] == 0) {
            board->nums[row][column]     = board->nums[row][column - 1];
            board->nums[row][column - 1] = 0;
          }
        }
      }
      break;
    }
  }
}

void shuffle(int* arr, int n)
{
  for (int i = 0; i < n; i++) {
    int to_swap_index = (i + GetRandomValue(0, n - i)) % n;

    int temp           = arr[i];
    arr[i]             = arr[to_swap_index];
    arr[to_swap_index] = temp;
  }
}

int** allocate_integer_matrix(int w, int h)
{
  int** matrix = (int**) malloc(h * sizeof(int));
  for (; h > 0; h--) {
    matrix[h - 1] = (int*) malloc(w * sizeof(int));
  }
  return matrix;
}

void free_integer_matrix(int** matrix, int r)
{
  for (; r > 0; r--) {
    free(matrix[r]);
  }
  free(matrix);
}