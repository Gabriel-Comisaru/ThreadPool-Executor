/* Comisaru Gabriel-Cornel - 311CB */
#ifndef FUNCTII_H_INCLUDED
#define FUNCTII_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Node.h"
#include "Queue.h"
#include "Stack.h"

typedef struct _Thread {
    int IDThread;
    int IDTask;
    char* stare;
}TThread;

typedef struct _Task {
    int ID;
    TThread* Thread;
    int prioritate;
    unsigned int timp_de_executie;
    char* stare;
}TTask;

Queue* add_tasks(Queue* WaitingQueue, int nr_tasks, int exec_time, int priority, FILE* out);
void get_task(Queue* WaitingQueue, Stack* ThreadPool, int task_id, FILE* out);
void get_thread(Stack* ThreadPool, int thread_id, FILE* out);
void printWaiting(Queue* WaitingQueue, FILE* out);
Queue* QueueOrder(Queue* QueueToOrder);
void freeTask(void* val);
void freeThread(void* val);
void printRunning(Queue* RunningQueue, FILE* out);
void printFinish(Queue* FinishQueue, FILE* out);
void run(Stack* ThreadPool, Queue* WaitingQueue, Queue* RunningQueue, Queue* FinishQueue, int T, int Q);

#endif