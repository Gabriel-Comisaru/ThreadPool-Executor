/* Comisaru Gabriel-Cornel - 311CB */
#include "Stack.h"

Stack* CreateStack()
{
    Stack* stack = malloc(sizeof(struct _Stack));
    stack->bottom = stack->top = NULL;
    stack->size = 0;
    return stack;
}

void freeStack(Stack** stack, void (*freeEl)(void*))
{
    while( ! EmptyStack(*stack) )
        pop(*stack, freeEl);
    *stack = NULL;
}

void push(Stack* stack, void* value)
{
    Node* n = CreateNode(stack->top, value);
    stack->top = n;
    stack->size++;
}

void pop(Stack* stack, void (*freeEl)(void*))
{
    Node* topNode = stack->top;
    stack->top = topNode->next;

    freeEl(topNode->value);
    free(topNode);
    stack->size--;
}

void* top(Stack* stack)
{
    return stack->top->value;
}
