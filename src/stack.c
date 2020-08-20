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

void push(Stack *st, uint16_t dir)
{
    if (!isFull(st))
    {
        st->elements[++st->top] = dir;
    }
}
int pop(Stack *st)
{
    if (!isEmpty(st))
    {
        return st->elements[st->top--];
    }
    return -1;
}
uint16_t peek(Stack *st)
{
    return st->elements[st->top];
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