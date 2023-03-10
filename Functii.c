/* Comisaru Gabriel-Cornel - 311CB */
#include "Functii.h"

void freeTask(void *val)
{
    TTask *Task = calloc(1, sizeof(TTask));
    Task = (TTask *)val;
}
void freeThread(void *val)
{
    TThread *Thread = calloc(1, sizeof(TThread));
    Thread = (TThread *)val;
    free(Thread);
}

/* functia de adaugare a task-urilor in coada de asteptare primind ca parametrii
nr-ul de taskuri pe care dorim sa-l adaugam in coada, timpul acestora de exeutie
si prioritatea*/
Queue *add_tasks(Queue *WaitingQueue, int nr_tasks, int exec_time, int priority, FILE *out)
{
    if (WaitingQueue == NULL) // verificam daca coada exista
        printf("Eroare la coada!");
    int i = 0, j = 0;
    for (i = 0; i < nr_tasks; i++) // un for pentru cate task-uri vrem sa adaugam
    {
        TTask *Task = calloc(1, sizeof(TTask));
        /* am modificat structura cozii pentru a salva intr-un vector
        ID-urile task-urilor care au fost deja adaugate pentru a evita
        probleme de genul : 1 2 3 4 1 2 la id-uri*/
        if (WaitingQueue->TaskIDs[0] == 1)
            for (j = 0; j < 32767; j++)
            {
                if (WaitingQueue->TaskIDs[j] != j + 1)
                    break;
            }
        Task->Thread = calloc(1, sizeof(TThread));
        Task->ID = j + 1;
        Task->timp_de_executie = exec_time;
        Task->prioritate = priority;
        Task->Thread->IDTask = Task->ID;
        Task->Thread->IDThread = 0; //momentan task-ul nu e atribuit niciunui thread
        Task->Thread->stare = "w"; //starea de asteptare (waiting)
        Task->stare = "w";
        WaitingQueue->TaskIDs[j] = j + 1;
        enqueue(WaitingQueue, Task); // adaugam Task-ul in coada
        fprintf(out, "Task created successfully : ID %d.\n", Task->ID);
    }
}

/*functie de gasire al unui Task in oricare din cele 3 cozi si afisarea timpului
ramas de executie al acestuia in cazul in care a fost gasit*/
void get_task(Queue *WaitingQueue, Stack *ThreadPool, int task_id, FILE *out)
{
    Node *n = calloc(1, sizeof(Node));
    for (n = (Node *)WaitingQueue->front; n != NULL; n = n->next) /*parcurg coada*/
    {
        TTask *Task = calloc(1, sizeof(TTask));
        Task = (TTask *)n->value;
        if (Task->ID == task_id)
        {
            fprintf(out, "Task %d is waiting (remaining_time = %d).\n", Task->ID, Task->timp_de_executie);
            break;
        }
    }
}

/* functie de gasire al unui Thread in Pool-ul de thread-uri si afisarea
starii acestuia in cazul in care a fost gasit*/
void get_thread(Stack *ThreadPool, int thread_id, FILE *out)
{
    Node *n = calloc(1, sizeof(Node));
    for (n = (Node *)ThreadPool->top; n != NULL; n = n->next) //parcurg stiva
    {
        TThread *Thread = calloc(1, sizeof(TThread));
        Thread = (TThread *)n->value;
        if (Thread->IDThread == thread_id)
        {
            fprintf(out, "Thread %d is idle.\n", Thread->IDThread);
        }
    }
}

/* functie de ordonare a cozii descrescator dupa prioritate,
crescator dupa timp de executie in caz de prioritati egale si
crescator dupa ID in caz ca prioritatile si timp-ul de executie
sunt egale*/
Queue *QueueOrder(Queue *QueueToOrder)
{
    int i = 0, j = 0, k = 0;
    int size = QueueToOrder->size; // am salvat dimensiunea cozii intr-o variabila
    Node *n = calloc(1, sizeof(Node));
    Node *m = calloc(1, sizeof(Node));
    Queue *aux = CreateQueue(); // coada auxiliara in care vom salva Task-urile in ordinea dorita
    int contor = size;
    if (QueueToOrder->front != NULL)
    {
        for (i = 0; i < size; i++) // parcurc coada de size-ori
        {
            int MaxIdx = 0; //variabila in care se salveaza index-ul Maximului
            TTask *MaxValue = calloc(1, sizeof(TTask)); // structura de Maxim unde se salveaza Task-ul "Maxim"
            MaxValue->ID = 100000;
            MaxValue->prioritate = 0;
            MaxValue->timp_de_executie = 1000000;
            for (j = 0; j < contor; j++) // parcurgem coada pentru a gasi Maximul
            {
                TTask *Task = calloc(1, sizeof(TTask));
                Task = QueueToOrder->front->value; // atribuim Task-ului front vale-ul pentru a putea face comparatia
                if (Task->prioritate > MaxValue->prioritate)
                {
                    MaxIdx = j;
                    MaxValue = Task;
                }
                else if (Task->prioritate == MaxValue->prioritate && Task->timp_de_executie < MaxValue->timp_de_executie)
                {
                    MaxIdx = j;
                    MaxValue = Task;
                }
                else if (Task->prioritate == MaxValue->prioritate && Task->timp_de_executie == MaxValue->timp_de_executie && Task->ID < MaxValue->ID)
                {
                    MaxIdx = j;
                    MaxValue = Task;
                }
                dequeue(QueueToOrder, freeTask); // scoatem si reintroducem Task-ul in coada pentru a putea parcurge coada
                enqueue(QueueToOrder, Task);
            }

            for (k = 0; k < MaxIdx; k++) // functie pentru a "aduce" task-ul maxim in fata cozii(front)
            {
                TTask *Task = calloc(1, sizeof(TTask));
                Task = QueueToOrder->front->value; // salvam acel Task-urile pentru a le putea reintroduce in coada
                dequeue(QueueToOrder, freeTask);
                enqueue(QueueToOrder, Task);
            }
            
            TTask *Task = calloc(1, sizeof(TTask));
            Task = QueueToOrder->front->value; // salvam Task-ul maxim dorit
            enqueue(aux, Task); // il adaugam in coada auxiliara
            if (contor != 1) // se opreste cand coada are doar un element ce va fi eliminat ulterior 
            {
                dequeue(QueueToOrder, freeTask); // scoatem din coada elementul Maxim gasit pentru a evita repetarea adaugarii aceluiasi element in coada auxiliara.
            }
            contor--; // decrementam size-ul
        }
    }
    for (n = (Node *)aux->front; n != NULL; n = n->next)
    {
        TTask *Task = calloc(1, sizeof(TTask));
        Task = n->value;
        enqueue(QueueToOrder, Task); // adaugam Task-urile din coada auxiliara in coada noastra
    }
    dequeue(QueueToOrder, freeTask); // stergem Task-ul ce ramasese in plus de la conditia de if
}

/* functia cu care scriem in fisierul de output coada de asteptare*/
void printWaiting(Queue *WaitingQueue, FILE *out)
{
    Node *n = calloc(1, sizeof(Node));
    fprintf(out, "====== Waiting queue =======\n[");
    if (WaitingQueue->front != NULL) //verificam daca coada are elemente
    {
        QueueOrder(WaitingQueue); //ordonam elementele inainte sa fie afisate
        for (n = (Node *)WaitingQueue->front; n != NULL; n = n->next)
        {
            TTask *Task = calloc(1, sizeof(TTask));
            Task = (TTask *)n->value;
            fprintf(out, "(%d: priority = %d, remaining_time = %d)", Task->ID, Task->prioritate, Task->timp_de_executie);
            if (n->next != NULL)
                fprintf(out, ",\n");
            else
                fprintf(out, "]\n");
        }
    }
    else
    {
        fprintf(out, "]\n");
    }
}
/* functia cu care scriem in fisierul de output coada de running*/
void printRunning(Queue *RunningQueue, FILE *out)
{
    Node *n = calloc(1, sizeof(Node));
    fprintf(out, "====== Running in parallel =======\n[");
    if (RunningQueue->front != NULL)
    {
        for (n = (Node *)RunningQueue->front; n != NULL; n = n->next)
        {
            TTask *Task = calloc(1, sizeof(TTask));
            Task = (TTask *)n->value;
            fprintf(out, "(%d: priority = %d, remaining_time = %d)", Task->ID, Task->prioritate, Task->timp_de_executie);
            if (n->next != NULL)
                fprintf(out, ",\n");
            else
                fprintf(out, "]\n");
        }
    }
    else
    {
        fprintf(out, "]\n");
    }
}

/* functia cu care scriem in fisierul de output coada de finish*/
void printFinish(Queue *FinishQueue, FILE *out)
{
    Node *n = calloc(1, sizeof(Node));
    fprintf(out, "====== Finished queue =======\n[");
    if (FinishQueue->front != NULL)
    {
        for (n = (Node *)FinishQueue->front; n != NULL; n = n->next)
        {
            TTask *Task = calloc(1, sizeof(TTask));
            Task = (TTask *)n->value;
            fprintf(out, "(%d: priority = %d, remaining_time = %d)", Task->ID, Task->prioritate, Task->timp_de_executie);
            if (n->next != NULL)
                fprintf(out, ",\n");
            else
                fprintf(out, "]\n");
        }
    }
    else
    {
        fprintf(out, "]\n");
    }
}