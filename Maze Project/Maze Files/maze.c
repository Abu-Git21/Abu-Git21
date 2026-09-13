#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "maze.h"
#include "queue.h"

static int find_special_positions(Maze *maze);
static int is_inside(const Maze *maze, int row, int col);

int maze_load(Maze *maze, const char *filename)
{
    FILE *file;
    char line[MAZE_MAX_COLS + 2];
    int row = 0;
    int cols = -1;

    if (maze == 0 || filename == 0)
    {
        return 0;
    }

    maze->rows = 0;
    maze->cols = 0;
    maze->score = 0;
    maze->under_lily = '.';

    file = fopen(filename, "r");

    if (file == 0)
    {
        return 0;
    }

    while (fgets(line, sizeof(line), file) != 0)
    {
        size_t length = strcspn(line, "\r\n");
        int col;

        if (length == 0 || length >= MAZE_MAX_COLS)
        {
            fclose(file);
            return 0;
        }

        if (row >= MAZE_MAX_ROWS)
        {
            fclose(file);
            return 0;
        }

        line[length] = '\0';

        if (cols == -1)
        {
            cols = (int)length;
        }
        else if ((int)length != cols)
        {
            fclose(file);
            return 0;
        }

        for (col = 0; col < cols; col++)
        {
            char cell = line[col];

            if (cell != '#' && cell != '.' && cell != 'L' &&
                cell != 'E' && cell != '*')
            {
                fclose(file);
                return 0;
            }
        }

        strcpy(maze->cells[row], line);
        row++;
    }

    if (ferror(file))
    {
        fclose(file);
        return 0;
    }

    fclose(file);

    if (row == 0 || cols <= 0)
    {
        return 0;
    }

    maze->rows = row;
    maze->cols = cols;

    if (!find_special_positions(maze))
    {
        maze->rows = 0;
        maze->cols = 0;
        return 0;
    }

    maze->score = 0;
    maze->under_lily = '.';

    return 1;
}

void maze_print(const Maze *maze)
{
    int row;

    if (maze == 0)
    {
        return;
    }

    for (row = 0; row < maze->rows; row++)
    {
        printf("%s\n", maze->cells[row]);
    }
}

int maze_can_move(const Maze *maze, int row, int col)
{
    if (!is_inside(maze, row, col))
    {
        return 0;
    }

    return maze->cells[row][col] != '#';
}

int maze_move_lily(Maze *maze, char direction)
{
    int next_row;
    int next_col;
    char command;
    char next_cell;

    if (maze == 0)
    {
        return 0;
    }

    next_row = maze->lily.row;
    next_col = maze->lily.col;
    command = (char)toupper((unsigned char)direction);

    if (command == 'W')
    {
        next_row--;
    }
    else if (command == 'S')
    {
        next_row++;
    }
    else if (command == 'A')
    {
        next_col--;
    }
    else if (command == 'D')
    {
        next_col++;
    }
    else
    {
        return 0;
    }

    if (!maze_can_move(maze, next_row, next_col))
    {
        return 0;
    }

    next_cell = maze->cells[next_row][next_col];

    maze->cells[maze->lily.row][maze->lily.col] = maze->under_lily;
    maze->lily.row = next_row;
    maze->lily.col = next_col;
    maze->under_lily = next_cell;
    maze->cells[next_row][next_col] = 'L';

    return 1;
}

int maze_collect_point(Maze *maze)
{
    if (maze == 0)
    {
        return 0;
    }

    if (maze->under_lily == '*')
    {
        maze->score++;
        maze->under_lily = '.';
        return 1;
    }

    return 0;
}

int maze_set_lily_position(Maze *maze, Position position)
{
    char next_cell;

    if (maze == 0)
    {
        return 0;
    }

    if (!maze_can_move(maze, position.row, position.col))
    {
        return 0;
    }

    maze->cells[maze->lily.row][maze->lily.col] = maze->under_lily;

    next_cell = maze->cells[position.row][position.col];
    maze->lily = position;
    maze->under_lily = next_cell;
    maze->cells[position.row][position.col] = 'L';

    return 1;
}

int maze_at_exit(const Maze *maze)
{
    if (maze == 0)
    {
        return 0;
    }

    return maze->lily.row == maze->exit_position.row &&
           maze->lily.col == maze->exit_position.col;
}

int maze_shortest_path(const Maze *maze)
{
    int visited[MAZE_MAX_ROWS][MAZE_MAX_COLS] = {{0}};
    int distance[MAZE_MAX_ROWS][MAZE_MAX_COLS] = {{0}};
    int row_change[4] = {-1, 1, 0, 0};
    int col_change[4] = {0, 0, -1, 1};
    Queue queue;
    Position current;
    int i;

    if (maze == 0 || maze->rows <= 0 || maze->cols <= 0)
    {
        return -2;
    }

    if (maze_at_exit(maze))
    {
        return 0;
    }

    queue_init(&queue);

    if (!queue_enqueue(&queue, maze->lily))
    {
        return -2;
    }

    visited[maze->lily.row][maze->lily.col] = 1;

    while (!queue_is_empty(&queue))
    {
        if (!queue_dequeue(&queue, &current))
        {
            return -2;
        }

        for (i = 0; i < 4; i++)
        {
            int next_row = current.row + row_change[i];
            int next_col = current.col + col_change[i];

            if (maze_can_move(maze, next_row, next_col) &&
                !visited[next_row][next_col])
            {
                Position next_position;

                visited[next_row][next_col] = 1;
                distance[next_row][next_col] =
                    distance[current.row][current.col] + 1;

                if (next_row == maze->exit_position.row &&
                    next_col == maze->exit_position.col)
                {
                    return distance[next_row][next_col];
                }

                next_position.row = next_row;
                next_position.col = next_col;

                if (!queue_enqueue(&queue, next_position))
                {
                    return -2;
                }
            }
        }
    }

    return -1;
}

static int find_special_positions(Maze *maze)
{
    int row;
    int col;
    int lily_count = 0;
    int exit_count = 0;

    if (maze == 0)
    {
        return 0;
    }

    for (row = 0; row < maze->rows; row++)
    {
        for (col = 0; col < maze->cols; col++)
        {
            if (maze->cells[row][col] == 'L')
            {
                maze->lily.row = row;
                maze->lily.col = col;
                lily_count++;
            }
            else if (maze->cells[row][col] == 'E')
            {
                maze->exit_position.row = row;
                maze->exit_position.col = col;
                exit_count++;
            }
        }
    }

    return lily_count == 1 && exit_count == 1;
}

static int is_inside(const Maze *maze, int row, int col)
{
    return maze != 0 &&
           row >= 0 &&
           row < maze->rows &&
           col >= 0 &&
           col < maze->cols;
}
