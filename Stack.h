/* Comisaru Gabriel-Cornel - 311CB */
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "Node.h"

#define EmptyStack(stack) ( (stack)->top == (stack)->bottom )

typedef struct _Stack
{
    Node* top;
    Node* bottom;
    int size;
}Stack;

Stack* CreateStack();
void freeStack(Stack** stack, void (*freeEL)(void*));
void push(Stack* stack, void* value);
void pop(Stack* stack, void (*freeEL)(void*));
void* top(Stack* stack);


#endif // STACK_H_INCLUDED
