/* Comisaru Gabriel-Cornel - 311CB */
#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <string.h>
#include <stdlib.h>
typedef struct _Node
{
    void* value;
    struct _Node* next;
}Node;

Node* CreateNode(Node* next, void* value);
Node* CreateNodee_CopyValue(Node* next, void* value, int elementSize);

void* getValue(Node* node);
void* getValue_Copy(Node* node, int elementSize);

#endif // NODE_H_INCLUDED
