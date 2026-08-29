#include <stdio.h>
#include "queue.h"

int main()
{
    queue_t q;
    int value;

    Queue_Init(&q);

    Queue_Enqueue(&q, 1);
    Queue_Enqueue(&q, 2);
    Queue_Enqueue(&q, 3);

    Queue_Dequeue(&q, &value);
    printf("%d\n", value);
    Queue_Dequeue(&q, &value);
    printf("%d\n", value);
    Queue_Dequeue(&q, &value);
    printf("%d\n", value);

    return 0;
}