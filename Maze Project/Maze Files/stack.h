#ifndef STACK_H
#define STACK_H

#include "maze.h"

#define STACK_CAPACITY 1000

typedef struct
{
    Position data[STACK_CAPACITY];
    int top;
} Stack;

void stack_init(Stack *stack);
int stack_push(Stack *stack, Position value);
int stack_pop(Stack *stack, Position *value);
int stack_is_empty(const Stack *stack);

#endif
