#include <inttypes.h>

#define MAXSIZE 16

int top = -1;
uint16_t stack[MAXSIZE];

void push(uint16_t dir)
{
    if (!isFull())
    {
        stack[++top] = dir;
    }
}
int pop()
{
    if (!isEmpty()){
        return stack[top--];
    }
    return -1;
}
uint16_t peek()
{
    return stack[top];
}
int isEmpty()
{
    return top == -1;
}
int isFull(){
    return top == MAXSIZE;
}
int size()
{
    return top+1;
}