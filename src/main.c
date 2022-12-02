#include <raylib.h>

#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

/* CONSTANTS */

#define WINDOW_TITLE "Fifteen"

#define MIN_WINDOW_WIDTH 300
#define MIN_WINDOW_HEIGHT 300

#define MAX_WINDOW_WIDTH 900
#define MAX_WINDOW_HEIGHT 900

/* STRUCTS */

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct {
    int width, height;
    int** nums;
} Board;
/* FUNCS */

void randomize_board(int** board, int w, int h);
void move(int** board, int w, int h, Direction dir);

// char* int_to_string(int i);
void shuffle(int** arr, int n);

int** allocate_integer_matrix(int w, int h);
void free_integer_matrix(int** matrix, int r);

/* MAIN */

int main() {
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT, WINDOW_TITLE);

    const char* NUM_TO_STRING_MAP = {
        "1\0",
        "2\0",
        "3\0",
        "4\0",
        "5\0",
        "6\0",
        "7\0",
        "8\0",
        "9\0",
        "10\0",
        "11\0",
        "12\0",
        "13\0",
        "14\0",
        "15\0",
        "16\0",
    };

    Board board = (Board) {
        4, 4,
        allocate_integer_matrix(4, 4)
    };

    // randomize_board(board.nums, board.width, board.height);

    int cell_width, cell_height;
    const int PADDING = 2;

    cell_width = (GetScreenWidth() - PADDING - board.width * PADDING) / board.width;
    cell_height = (GetScreenHeight() - PADDING - board.height * PADDING) / board.height;

    while(!WindowShouldClose()) {
        ClearBackground(LIGHTGRAY);

        BeginDrawing();

        for(int i = 0; i < board.height; i++) {
            for(int j = 0; j < board.width; j++) {
                int x = (i + 1) * PADDING + cell_width  * i;
                int y = (j + 1) * PADDING + cell_height * j;

                DrawRectangle(
                    x, y,
                    cell_width, cell_height,
                    GRAY
                );

                printf("i: %d, j: %d\n", i, j);

                printf("Board[%d, %d] = %d\n", i, j, board.nums[i][j]);
                printf("\t-> To String: %s\n", NUM_TO_STRING_MAP[board.nums[i][j]]);
                printf("----\n");
            }
        }

        EndDrawing(); // end drawing + swap + poll events
    }

    CloseWindow();
}

/* IMPL */

void randomize_board(int** board, int w, int h) {
    int max_num = w * h - 1;

    int bucket[max_num];
    memset(bucket, 0, max_num * sizeof(int));
    // Equivalente -> for(int i = 0; i < max_num; i++) bucket[i] = 0;

    for(int i = 0; i < max_num; i++) {
        int num = 0;
        do {
            num = GetRandomValue(1, max_num);
        } while(bucket[num] != 0);
        bucket[num] = 1;

        int i = floor(num / w);
        int j = num % w;

        board[i][j] = num;
    }

}

void move(int** board, int w, int h, Direction dir);

void shuffle(int* arr, int n) {
    for(int i = 0; i < n-1; i++) {
        int random = GetRandomValue(0, i);
        int temp = arr[i];
    }
}

int** allocate_integer_matrix(int w, int h) {
    int** matrix = (int**) malloc(h * sizeof(int));
    for(; h > 0 ; h--) {
        matrix[h - 1] = (int*) malloc(w * sizeof(int));
    }
    return matrix;
}

void free_integer_matrix(int** matrix, int r) {
    for(; r > 0 ; r-- ) {
        free(matrix[r]);
    }
    free(matrix);
}