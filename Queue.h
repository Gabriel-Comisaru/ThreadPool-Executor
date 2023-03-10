/* Comisaru Gabriel-Cornel - 311CB */
#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "Node.h"

#define EmptyQueue(q) ( (q)->front == (q)->back )

typedef struct _Queue
{
    Node* front;
    Node* back;
    int size;
    int* TaskIDs; // vector in care salvam ce id-uri am folosit pt task-uri
}Queue;

Queue* CreateQueue();
void freeQueue(Queue** q, void (*freeEL)(void*));

void enqueue(Queue* q, void* value);
void dequeue(Queue* q, void (*freeEL)(void*));
void* front(Queue* q);


#endif // QUEUE_H_INCLUDED
