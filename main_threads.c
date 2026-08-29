#include <stdio.h>
#include <pthread.h>
#include "queue.h"

queue_t q;

void *producer(void *arg)
{
    for (int i = 0; i < 1000; i++)
        Queue_Enqueue(&q, (int)(long)arg);
    return NULL;
}

int main()
{
    pthread_t producers[4];

    Queue_Init(&q);

    for (int i = 0; i < 4; i++)
        pthread_create(&producers[i], NULL, producer, (void *)(long)i);

    for (int i = 0; i < 4; i++)
        pthread_join(producers[i], NULL);

    int count = 0;
    int value;
    while (!Queue_Empty(&q))
    {
        Queue_Dequeue(&q, &value);
        count++;
    }
    printf("expected 4000, got %d\n", count);

    return 0;
}