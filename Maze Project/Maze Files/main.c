#include <ctype.h>
#include <stdio.h>
#include <time.h>

#include "maze.h"
#include "stack.h"

#define TIME_LIMIT_SECONDS 60

static void print_controls(void);
static void print_final_result(const Maze *maze, time_t start_time);

int main(void)
{
    Maze maze;
    Stack history;
    char command;
    time_t start_time;

    stack_init(&history);

    if (!maze_load(&maze, "maze.txt"))
    {
        fprintf(stderr, "Error: could not load maze.txt\n");
        return 1;
    }

    start_time = time(NULL);
    print_controls();

    while (1)
    {
        Position previous_position;
        double elapsed_seconds = difftime(time(NULL), start_time);

        if (elapsed_seconds >= TIME_LIMIT_SECONDS)
        {
            printf("\nTime is up!\n");
            break;
        }

        maze_print(&maze);
        printf("Score: %d | Time remaining: %.0f seconds\n",
               maze.score,
               TIME_LIMIT_SECONDS - elapsed_seconds);
        printf("Command: ");

        if (scanf(" %c", &command) != 1)
        {
            printf("Input ended.\n");
            break;
        }

        elapsed_seconds = difftime(time(NULL), start_time);

        if (elapsed_seconds >= TIME_LIMIT_SECONDS)
        {
            printf("\nTime is up!\n");
            break;
        }

        command = (char)toupper((unsigned char)command);

        if (command == 'Q')
        {
            break;
        }
        else if (command == 'U')
        {
            if (stack_pop(&history, &previous_position))
            {
                maze_set_lily_position(&maze, previous_position);
                printf("Last move undone.\n");
            }
            else
            {
                printf("Nothing to undo.\n");
            }
        }
        else if (command == 'H')
        {
            int steps = maze_shortest_path(&maze);

            if (steps >= 0)
            {
                printf("Shortest path to exit: %d step(s)\n", steps);
            }
            else if (steps == -1)
            {
                printf("No path to the exit exists.\n");
            }
            else
            {
                printf("Could not calculate a hint.\n");
            }
        }
        else if (command == 'W' || command == 'A' ||
                 command == 'S' || command == 'D')
        {
            previous_position = maze.lily;

            if (maze_move_lily(&maze, command))
            {
                if (!stack_push(&history, previous_position))
                {
                    printf("Warning: move history is full.\n");
                }

                if (maze_collect_point(&maze))
                {
                    printf("Point collected! Score: %d\n", maze.score);
                }

                if (maze_at_exit(&maze))
                {
                    printf("Lily reached the exit!\n");
                    break;
                }
            }
            else
            {
                printf("Invalid move.\n");
            }
        }
        else
        {
            printf("Invalid command. Use W, A, S, D, U, H, or Q.\n");
        }

        printf("\n");
    }

    print_final_result(&maze, start_time);
    return 0;
}

static void print_controls(void)
{
    printf("=== Maze Exploration with Lily the Ant ===\n");
    printf("W/A/S/D = move\n");
    printf("U = undo\n");
    printf("H = shortest-path hint\n");
    printf("Q = quit\n\n");
}

static void print_final_result(const Maze *maze, time_t start_time)
{
    double elapsed_seconds = difftime(time(NULL), start_time);

    printf("\n=== Final Result ===\n");
    printf("Final score: %d\n", maze->score);
    printf("Elapsed time: %.0f second(s)\n", elapsed_seconds);
}
