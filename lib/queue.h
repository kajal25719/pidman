#ifndef QUEUE_h
#define QUEUE_h

#include <stdlib.h>

typedef struct QNode QNode;
typedef struct Queue Queue;


typedef int    Construct(Queue *fifo);

typedef void   Destruct(Queue *queue);

typedef int    Enqueue(Queue *fifo, int n);

typedef int     Dequeue(Queue *fifo);

typedef int     Peek(Queue *fifo);


struct QNode
{
    int val;
    
    QNode *next;
};

struct Queue
{
    QNode *queue;
    
    QNode *back;
    
    unsigned int numNodes;
    
    Enqueue *enqueue;
    Dequeue *dequeue;
    Peek    *peek;
};

Construct   construct;
Destruct    destruct;
Enqueue     enqueue;
Dequeue     dequeue;
Peek        peek;

#endif /* QUEUE_h */
