#include <inttypes.h>

typedef struct Stack {
  int maxsize;
  int top;
  uint16_t *elements;
} Stack;

// creates a new stack of size "int size"
Stack *create_stack(int size);
// frees memory allocated by thes stack
void free_stack(Stack *st);
// adds new direction to the stack
// leaves a 0 on error parameter if everything went well, -1 if it didn't
int push(Stack *st, uint16_t dir);
// gets last element from the stack
// leaves a 0 on error parameter if everything went well, -1 if it didn't
int pop(Stack *st, uint16_t *out);
// gets value from the last element
// leaves a 0 on error parameter if everything went well, -1 if it didn't
int peek(Stack *st, uint16_t *out);
// gets stack size
int size(Stack *st);
