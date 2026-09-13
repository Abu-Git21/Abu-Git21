#include "stack.h"

void stack_init(Stack *stack)
{
    if (stack != 0)
    {
        stack->top = 0;
    }
}

int stack_push(Stack *stack, Position value)
{
    if (stack == 0)
    {
        return 0;
    }

    if (stack->top >= STACK_CAPACITY)
    {
        return 0;
    }

    stack->data[stack->top] = value;
    stack->top++;

    return 1;
}

int stack_pop(Stack *stack, Position *value)
{
    if (stack == 0 || value == 0)
    {
        return 0;
    }

    if (stack->top <= 0)
    {
        return 0;
    }

    stack->top--;
    *value = stack->data[stack->top];

    return 1;
}

int stack_is_empty(const Stack *stack)
{
    return stack == 0 || stack->top == 0;
}
