#include <stdio.h>
#include "request.h"
#include "io_helper.h"
#include <pthread.h>
#include "queue.h"
#include "thread_pool.h"

char default_root[] = ".";

int main(int argc, char *argv[])
{
    int c;
    char *root_dir = default_root;
    int port = 10000;
    int threads = 1;
    int buffers = 1;
    char *schedalg = "FIFO";

    while ((c = getopt(argc, argv, "d:p:t:b:s:")) != -1)
        switch (c)
        {
        case 'd':
            root_dir = optarg;
            break;
        case 'p':
            port = atoi(optarg);
            break;
        case 't':
            threads = atoi(optarg);
            if (threads < 1)
            {
                fprintf(stderr, "Must be a positive integer\n");
                exit(1);
            }
            break;
        case 'b':
            buffers = atoi(optarg);
            if (buffers < 1)
            {
                fprintf(stderr, "Must be a positive integer\n");
                exit(1);
            }
            break;
        case 's':
            schedalg = optarg;
            if (strcmp(schedalg, "FIFO") == 0)
            {
                break;
            }
            else if (strcmp(schedalg, "SFF") == 0)
            {
                break;
            }
            else
            {
                fprintf(stderr, "Must be FIFO or SFF\n");
                exit(1);
            }
        default:
            fprintf(stderr, "usage: wserver [-d basedir] [-p port] [-t threads] [-b buffers] [-s schedalg] \n");
            exit(1);
        }

    fprintf(stdout, "threads = %d buffers = %d schedalg = %s\n", threads, buffers, schedalg);

    chdir_or_die(root_dir);

    thread_pool_init(threads);

    int listen_fd = open_listen_fd_or_die(port);
    while (1)
    {
        struct sockaddr_in client_addr;
        int client_len = sizeof(client_addr);
        int conn_fd = accept_or_die(listen_fd, (sockaddr_t *) &client_addr, (socklen_t *) &client_len);

        pthread_mutex_lock(&m);
        Queue_Enqueue(&jobs, conn_fd);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&m);
    }
    return 0;
}