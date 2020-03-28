#include "../lib/queue.h"


int construct(Queue *fifo)
{
    if (fifo == NULL)
        return -1;
    
    fifo->numNodes = 0;
    
    fifo->enqueue = enqueue;
    fifo->dequeue = dequeue;
    fifo->peek    = peek;
    
    return 0;
}

void destruct(Queue *fifo)
{
    QNode *q;
    
    if (fifo == NULL)
        return;
    
    for (q = fifo->queue; q != NULL; q = q->next)
    {
        free(q);
    }
}

int enqueue(Queue *fifo, int n)
{
    QNode *node = NULL;
    
    if (fifo == NULL)
        return -1;
    
    node = (QNode *)malloc(sizeof(QNode));
    if (node == NULL)
        return -1;
    node->val = n;
    
    if (fifo->numNodes == 0)
    {
        fifo->queue = node;
        fifo->back  = fifo->queue;
        node->next  = NULL;
    }
    else
    {
        fifo->back->next = node;
        fifo->back = node;
    }
    
    fifo->numNodes++;
    
    return 0;
}

int dequeue(Queue *fifo)
{
    int    n;
    QNode *front = NULL;
    
    if (fifo == NULL)
        return -1;
    
    if (fifo->numNodes == 0)
        return -1;
    
    front = fifo->queue;
    n = front->val;
    fifo->queue = front->next;
    front->next = NULL;
    free(front);
    
    fifo->numNodes--;
    
    return n;
}

int peek(Queue *fifo)
{
    if (fifo == NULL)
        return -1;
    
    if (fifo->numNodes == 0)
        return -1;
    
    return fifo->queue->val;
}
