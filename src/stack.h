#include <inttypes.h>

typedef struct Stack
{
    int maxsize;
    int top;
    uint16_t *elements;
} Stack;

// creates a new stack
Stack* newStack(int size);
// frees memory allocated by the stack
void freeStack(Stack* st);
// adds new element to the stack
void push(Stack* st, uint16_t dir);
// gets last element from the stack
uint16_t pop(Stack* st);
// gets value from the last element
uint16_t peek(Stack* st);
// gets stack size
int size(Stack* st);