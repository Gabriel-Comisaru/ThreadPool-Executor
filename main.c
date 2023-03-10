/* Comisaru Gabriel-Cornel - 311CB */
#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "Queue.h"
#include "Functii.h"

int main(int argc, char* argv[])
{
    FILE *in;
    FILE *out;
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL) {
        printf("Mai incearca!\n");
        return -1;
    }
    int Q = 0, i = 0, ok = 0, task_id = 0, thread_id = 0, T = 0;
    int C = 0, N = 0, nrtasks = 0, exec_time = 0, priority = 0;
    char* comanda = calloc(9, sizeof(char));
    fscanf(in, "%d", &Q);
    fscanf(in, "%d", &C);
    N = 2 * C;
    // am creeat atat stiva cat si cele 3 cozi
    Stack* ThreadPool = CreateStack();
    Queue* WaitingQueue = CreateQueue();
    Queue* RunningQueue = CreateQueue();
    Queue* FinishQueue = CreateQueue();
    // am creat Thread-uri cat numarul N
    for (i = N-1 ; i >= 0; i--) {
        TThread* Thread = calloc(1, sizeof(Thread));
        Thread->IDThread = i;
        Thread->IDTask = 0;
        Thread->stare = "w";
        push(ThreadPool, Thread);
    }
    while (fscanf(in, "%s", comanda) != EOF) {
        if (strcmp(comanda, "add_tasks") == 0) {
            nrtasks = 0;
            exec_time = 0;
            priority = 0;
            fscanf(in, "%d", &nrtasks);
            fscanf(in, "%d", &exec_time);
            fscanf(in, "%d", &priority);
            add_tasks(WaitingQueue, nrtasks, exec_time, priority, out);
        }
        if (strcmp(comanda, "get_task") == 0) {
            fscanf(in, "%d", &task_id);
            get_task(WaitingQueue, ThreadPool, task_id, out);

        }
        if (strcmp(comanda, "get_thread") == 0) {
            fscanf(in, "%d", &thread_id);
            get_thread(ThreadPool, thread_id, out);
        }
        if (strcmp(comanda, "print") == 0) {
            fscanf(in, "%s", comanda);
            if (strcmp(comanda, "waiting") == 0) {
                QueueOrder(WaitingQueue);
                printWaiting(WaitingQueue, out);
            }
            if (strcmp(comanda, "running") == 0) {
                if (RunningQueue->front != NULL)
                    QueueOrder(RunningQueue);
                printRunning(RunningQueue, out);
            }
            if (strcmp(comanda, "finished") == 0) {
                printFinish(FinishQueue, out);
            }
        }
    }
    return 0;
} 