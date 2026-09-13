#ifndef MAZE_H
#define MAZE_H

#define MAZE_MAX_ROWS 25
#define MAZE_MAX_COLS 80

typedef struct
{
    int row;
    int col;
} Position;

typedef struct
{
    char cells[MAZE_MAX_ROWS][MAZE_MAX_COLS];
    int rows;
    int cols;
    Position lily;
    Position exit_position;
    int score;
    char under_lily;
} Maze;

/* Load a maze from a text file.
   Return 1 on success and 0 on failure. */
int maze_load(Maze *maze, const char *filename);

/* Display the maze. */
void maze_print(const Maze *maze);

/* Return 1 when the requested cell is inside the maze and is not a wall. */
int maze_can_move(const Maze *maze, int row, int col);

/* Move Lily using W, A, S, or D.
   Return 1 if Lily moved and 0 otherwise. */
int maze_move_lily(Maze *maze, char direction);

/* Collect a point at Lily's current location.
   Return the number of points collected by this call. */
int maze_collect_point(Maze *maze);

/* Restore Lily to a previously saved position. */
int maze_set_lily_position(Maze *maze, Position position);

/* Return 1 when Lily is at the exit. */
int maze_at_exit(const Maze *maze);

/* Use BFS and the Queue ADT to find the shortest distance to the exit.
   Return:
      0 or greater = number of steps
      -1 = no path exists
      -2 = invalid argument */
int maze_shortest_path(const Maze *maze);

#endif
