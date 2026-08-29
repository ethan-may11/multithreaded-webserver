# An admittedly primitive Makefile
# To compile, type "make" or make "all"
# To remove files, type "make clean"

CC = gcc
CFLAGS = -Wall
OBJS = wserver.o wclient.o request.o io_helper.o 

.SUFFIXES: .c .o 

all: wserver wclient spin.cgi

wserver: wserver.c request.c io_helper.c thread_pool.c queue_concurrent.c
	gcc -Wall -DCONCURRENT -o wserver wserver.c request.c io_helper.c thread_pool.c queue_concurrent.c -lpthread

wclient: wclient.o io_helper.o
	$(CC) $(CFLAGS) -o wclient wclient.o io_helper.o

spin.cgi: spin.c
	$(CC) $(CFLAGS) -o spin.cgi spin.c

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	-rm -f $(OBJS) wserver wclient spin.cgi


concurrent: main.c queue_concurrent.c queue.h
	gcc -Wall -DCONCURRENT -o main main.c queue_concurrent.c -lpthread

simple: main.c queue_simple.c queue.h
	gcc -Wall -o main main.c queue_simple.c

concurrent_threads: main_threads.c queue_concurrent.c queue.h
	gcc -Wall -DCONCURRENT -o main_threads main_threads.c queue_concurrent.c -lpthread

simple_threads: main_threads.c queue_simple.c queue.h
	gcc -Wall -o main_threads main_threads.c queue_simple.c -lpthread