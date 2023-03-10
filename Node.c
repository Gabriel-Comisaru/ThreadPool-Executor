/* Comisaru Gabriel-Cornel - 311CB */
#include "Node.h"

Node* CreateNode(Node* next, void* value)
{
    Node* newNode = malloc(sizeof(struct _Node));
    newNode->next = next;
    newNode->value = value;
    return newNode;
}

Node* CreateNodee_CopyValue(Node* next, void* value, int elementSize)
{
    Node* newNode = malloc(sizeof(struct _Node));
    newNode->next = malloc(elementSize);
    memcpy(newNode->value, value, elementSize);
    newNode->value = value;
    return newNode;
}

void* getValue(Node* node)
{
    return node->value;
}

void* getValue_Copy(Node* node, int elementSize)
{
    void* value = malloc(elementSize);
    memcpy(value, node->value, elementSize);
    return value;
}
