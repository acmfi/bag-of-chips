#include "stack.h"

Stack *newStack(int size)
{
    Stack *stack = malloc(sizeof(Stack));
    stack->top = -1;
    stack->maxsize = size;
    stack->elements = malloc(size * sizeof(uint16_t));
    return stack;
}
void freeStack(Stack *st)
{
    free(st->elements);
    free(st);
}

void push(Stack *st, uint16_t dir, int *error)
{
    if (!isFull(st))
    {
        error = 0;
        st->elements[++st->top] = dir;
    }
    error = -1;
}
uint16_t pop(Stack *st, int *error)
{
    if (!isEmpty(st))
    {
        error = 0;
        return st->elements[st->top--];
    }
    error = -1;
    return 0;
}
uint16_t peek(Stack *st, int *error)
{
    if (!isEmpty(st))
    {
        error = 0;
        return st->elements[st->top];
    }
    error = -1;
    return 0;

}
int isEmpty(Stack *st)
{
    return st->top == -1;
}
int isFull(Stack *st)
{
    return st->top == st->maxsize;
}
int size(Stack *st)
{
    return st->top + 1;
}

