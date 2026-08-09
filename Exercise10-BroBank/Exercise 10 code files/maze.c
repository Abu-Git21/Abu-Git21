#include <stddef.h>
#include "maze.h"
#include "adt.h"

static int valid_cell(const Maze *maze, int row, int col) {
    return row >= 0 && row < maze->rows &&
           col >= 0 && col < maze->cols &&
           maze->cells[row][col] != '#';
}

static int reconstruct_path(const Maze *maze,
                            Cell parent[MAZE_MAX_ROWS][MAZE_MAX_COLS],
                            Cell path[],
                            int *path_length) {
    Cell temp[MAZE_MAX_ROWS * MAZE_MAX_COLS];
    int count = 0;

    Cell current = maze->exit;

    while (!(current.row == maze->start.row &&
             current.col == maze->start.col)) {

        temp[count++] = current;
        current = parent[current.row][current.col];

        if (current.row < 0 || current.col < 0) {
            *path_length = 0;
            return 0;
        }
    }

    temp[count++] = maze->start;

    for (int i = 0; i < count; i++) {
        path[i] = temp[count - 1 - i];
    }

    *path_length = count - 1;

    return 1;
}

int mazeBFS(const Maze *maze, Cell path[], int *path_length) {
    if (path_length != NULL) {
        *path_length = 0;
    }

    if (maze == NULL || path == NULL || path_length == NULL) {
        return 0;
    }

    if (maze->rows <= 0 || maze->rows > MAZE_MAX_ROWS ||
        maze->cols <= 0 || maze->cols > MAZE_MAX_COLS) {
        return 0;
    }

    if (!valid_cell(maze, maze->start.row, maze->start.col) ||
        !valid_cell(maze, maze->exit.row, maze->exit.col)) {
        return 0;
    }

    int visited[MAZE_MAX_ROWS][MAZE_MAX_COLS] = {0};
    Cell parent[MAZE_MAX_ROWS][MAZE_MAX_COLS];

    for (int r = 0; r < maze->rows; r++) {
        for (int c = 0; c < maze->cols; c++) {
            parent[r][c].row = -1;
            parent[r][c].col = -1;
        }
    }

    Queue q;
    queueInit(&q);

    int start_index =
        maze->start.row * maze->cols + maze->start.col;

    if (!enqueue(&q, start_index)) {
        return 0;
    }

    visited[maze->start.row][maze->start.col] = 1;

    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};

    while (!queueIsEmpty(&q)) {
        int index;

        if (!dequeue(&q, &index)) {
            return 0;
        }

        int row = index / maze->cols;
        int col = index % maze->cols;

        if (row == maze->exit.row &&
            col == maze->exit.col) {
            return reconstruct_path(
                maze, parent, path, path_length
            );
        }

        for (int i = 0; i < 4; i++) {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if (valid_cell(maze, nr, nc) &&
                !visited[nr][nc]) {

                visited[nr][nc] = 1;

                parent[nr][nc].row = row;
                parent[nr][nc].col = col;

                int next_index =
                    nr * maze->cols + nc;

                if (!enqueue(&q, next_index)) {
                    return 0;
                }
            }
        }
    }

    return 0;
}

int mazeDFS(const Maze *maze, Cell path[], int *path_length) {
    if (path_length != NULL) {
        *path_length = 0;
    }

    if (maze == NULL || path == NULL || path_length == NULL) {
        return 0;
    }

    if (maze->rows <= 0 || maze->rows > MAZE_MAX_ROWS ||
        maze->cols <= 0 || maze->cols > MAZE_MAX_COLS) {
        return 0;
    }

    if (!valid_cell(maze, maze->start.row, maze->start.col) ||
        !valid_cell(maze, maze->exit.row, maze->exit.col)) {
        return 0;
    }

    int visited[MAZE_MAX_ROWS][MAZE_MAX_COLS] = {0};
    Cell parent[MAZE_MAX_ROWS][MAZE_MAX_COLS];

    for (int r = 0; r < maze->rows; r++) {
        for (int c = 0; c < maze->cols; c++) {
            parent[r][c].row = -1;
            parent[r][c].col = -1;
        }
    }

    Stack s;
    stackInit(&s);

    int start_index =
        maze->start.row * maze->cols + maze->start.col;

    if (!stackPush(&s, start_index)) {
        return 0;
    }

    visited[maze->start.row][maze->start.col] = 1;

    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};

    while (!stackIsEmpty(&s)) {
        int index;

        if (!stackPop(&s, &index)) {
            return 0;
        }

        int row = index / maze->cols;
        int col = index % maze->cols;

        if (row == maze->exit.row &&
            col == maze->exit.col) {
            return reconstruct_path(
                maze, parent, path, path_length
            );
        }

        for (int i = 3; i >= 0; i--) {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if (valid_cell(maze, nr, nc) &&
                !visited[nr][nc]) {

                visited[nr][nc] = 1;

                parent[nr][nc].row = row;
                parent[nr][nc].col = col;

                int next_index =
                    nr * maze->cols + nc;

                if (!stackPush(&s, next_index)) {
                    return 0;
                }
            }
        }
    }

    return 0;
}