#ifndef MAZE_H
#define MAZE_H

#define MAZE_MAX_ROWS 20
#define MAZE_MAX_COLS 20

typedef struct {
    int row;
    int col;
} Cell;

typedef struct {
    int rows;
    int cols;
    char cells[MAZE_MAX_ROWS][MAZE_MAX_COLS];
    Cell start;
    Cell exit;
} Maze;

int mazeBFS(const Maze *maze, Cell path[], int *path_length);
int mazeDFS(const Maze *maze, Cell path[], int *path_length);

#endif