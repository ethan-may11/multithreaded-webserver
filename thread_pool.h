#include <pthread.h>
#include "queue.h"

extern queue_t jobs;
extern pthread_cond_t fill;
extern pthread_mutex_t m;

int thread_pool_init(int n);