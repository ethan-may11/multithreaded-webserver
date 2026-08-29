#include <stdlib.h>
#include "queue.h"

void Queue_Init(queue_t *q)
{
    node_t *tmp = malloc(sizeof(node_t));
    tmp->next = NULL;
    q->head = q->tail = tmp;
}

void Queue_Enqueue(queue_t *q, int value)
{
    node_t *tmp = malloc(sizeof(node_t));
    tmp->value = value;
    tmp->next = NULL;
    q->tail->next = tmp;
    q->tail = tmp;
}

int Queue_Dequeue(queue_t *q, int *value)
{
    node_t *tmp = q->head;
    node_t *new_head = tmp->next;
    if (new_head == NULL)
    {
        return -1;
    }
    *value = new_head->value;
    q->head = new_head;
    free(tmp);
    return 0;
}

int Queue_Empty(queue_t *q)
{
    return q->head->next == NULL;
}