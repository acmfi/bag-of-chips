#include <inttypes.h>

typedef struct Stack
{
    int maxsize;
    int top;
    uint16_t *elements;
} Stack;

// creates a new stack of size "int size"
Stack* newStack(int size);
// frees memory allocated by the stack 
void freeStack(Stack* st);
// adds new direction to the stack
// leaves a 0 on error parameter if everything went well, -1 if it didn't
void push(Stack* st, uint16_t dir, int* error);
// gets last element from the stack
// leaves a 0 on error parameter if everything went well, -1 if it didn't
uint16_t pop(Stack* st, int* error);
// gets value from the last element 
// leaves a 0 on error parameter if everything went well, -1 if it didn't
uint16_t peek(Stack* st, int* error);
// gets stack size
int size(Stack* st);