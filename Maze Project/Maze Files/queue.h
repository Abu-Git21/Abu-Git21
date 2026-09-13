#ifndef QUEUE_H
#define QUEUE_H

#include "maze.h"

#define QUEUE_CAPACITY (MAZE_MAX_ROWS * MAZE_MAX_COLS)

typedef struct
{
    Position data[QUEUE_CAPACITY];
    int front;
    int rear;
    int size;
} Queue;

void queue_init(Queue *queue);
int queue_enqueue(Queue *queue, Position value);
int queue_dequeue(Queue *queue, Position *value);
int queue_is_empty(const Queue *queue);

#endif
