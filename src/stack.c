#include "stack.h"

Stack *create_stack(int size) {
  Stack *stack = malloc(sizeof(Stack));
  stack->top = -1;
  stack->maxsize = size;
  stack->elements = malloc(size * sizeof(uint16_t));
  return stack;
}
void free_stack(Stack *st) {
  free(st->elements);
  free(st);
}

int push(Stack *st, uint16_t dir) {
  if (!isFull(st)) {
    st->elements[++st->top] = dir;
    return 0;
  }
  return -1;
}
int pop(Stack *st, uint16_t *out) {
  if (!isEmpty(st)) {
    out = st->elements[st->top--];
    return 0;
  }
  return -1;
}
int peek(Stack *st, uint16_t *out) {
  if (!isEmpty(st)) {
    out = st->elements[st->top];
    return 0;
  }
  return -1;
}
int isEmpty(Stack *st) { return st->top == -1; }
int isFull(Stack *st) { return st->top == st->maxsize; }
int size(Stack *st) { return st->top + 1; }
