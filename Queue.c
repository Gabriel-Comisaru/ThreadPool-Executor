/* Comisaru Gabriel-Cornel - 311CB */
#include "Queue.h"
#include "Functii.h"
Queue* CreateQueue()
{
    Queue* q = malloc(sizeof(struct _Queue));
    q->back = q->front = NULL;
    q->size = 0;
    q->TaskIDs = calloc(32767, sizeof(int));
    return q;
}

void freeQueue(Queue** q, void (*freeEL)(void*))
{
    while( !EmptyQueue(*q) )
        dequeue(*q, freeEL);
    (*q)->front = NULL;
    (*q)->back = NULL;
    *q = NULL;
}

void enqueue(Queue* q, void* value)
{
    if (q->back == NULL) {
        q->back = CreateNode(NULL, value);
        q->size++;
        q->front = q->back;
    } else {
        q->back->next = CreateNode(NULL, value);
        q->back = q->back->next;
        q->size++;
    }
}

void dequeue(Queue* q, void (*freeEL)(void*))
{   
    if (q->front != NULL) {
        Node* frontNode = q->front;
        if (frontNode->next != NULL) {
            q->front = frontNode->next;

            freeEL(frontNode->value);
            free(frontNode);
            q->size--;
        }
        else {
            free(q->front);
            q->size--;
        }
    }
}

void* front(Queue* q)
{
    return q->front->value;
}

