# Multithreaded Web Server

A concurrent HTTP web server written in C. Built on the single-threaded starter server from the OSTEP concurrency-webserver project and extended into a multithreaded server using a fixed-size worker thread pool and a thread-safe request queue, coordinated with a mutex and condition variables (no busy-waiting).

> Course project based on the concurrency-webserver assignment from *Operating Systems: Three Easy Pieces* (Arpaci-Dusseau). The single-threaded server was provided as starter code; the concurrency layer is my work (see "Provided vs. what I built" below).

## Features
- **Fixed-size worker thread pool** — a master thread accepts incoming connections and hands them off to a pool of worker threads, sized at startup, so multiple requests are served at once.
- **Producer–consumer request queue** — connections are placed on a shared queue by the master thread and pulled off by workers, synchronized with a mutex and a condition variable; workers block (rather than busy-wait) when the queue is empty.
- **Thread-safe queue** — a concurrent linked-list queue with separate head and tail locks. A simpler single-threaded queue variant is also included.
- **Static and dynamic content** — serves static files and runs CGI programs (e.g., the included `spin.cgi`).
- **Configurable at launch** — number of worker threads, listening port, buffer size, root directory, and scheduling policy are all set via command-line flags.

## Build
```
make
```
Builds the server (`wserver`), the test client (`wclient`), and the `spin.cgi` test program.

## Run
```
./wserver -d <basedir> -p <port> -t <threads> -b <buffers> -s <schedalg>
```
- `-d` — root directory to serve from (default `.`)
- `-p` — port to listen on (default 10000)
- `-t` — number of worker threads (default 1)
- `-b` — request buffer size (default 1)
- `-s` — scheduling policy: `FIFO` (default) or `SFF`

Example — serve the current directory on port 8003 with 8 worker threads:
```
./wserver -d . -p 8003 -t 8 -b 16 -s FIFO
```
Then open `http://localhost:8003/index.html`.

## Provided vs. what I built
**Starter code (provided):** a working single-threaded web server — `request.c` / `request.h`, `io_helper.c` / `io_helper.h`, `wclient.c`, `spin.c`, and the base `Makefile`. I made targeted modifications to some of these to support concurrency.

**My primary work:** the concurrency layer — the worker thread pool (`thread_pool.c` / `thread_pool.h`), the thread-safe request queue (`queue_concurrent.c`, `queue.h`), and the changes in `wserver.c` that accept connections on a master thread and dispatch them to workers through the shared queue, using a condition variable so idle workers block instead of busy-waiting.

## Files
- `wserver.c` — master thread: argument parsing, connection accept loop, dispatch to the queue
- `thread_pool.c` / `thread_pool.h` — worker thread pool and its synchronization
- `queue_concurrent.c` / `queue.h` — thread-safe request queue (two-lock)
- `queue_simple.c` — single-threaded queue variant
- `request.c` / `request.h` — HTTP request handling (static files and CGI)
- `io_helper.c` / `io_helper.h` — socket and I/O helper wrappers
- `spin.c` — CGI test program
- `wclient.c` — simple HTTP test client
- `main.c`, `main_threads.c` — queue test harnesses
- `Makefile` — build configuration

## Concepts
POSIX threads (`pthread_create`, `pthread_join`), mutual exclusion and condition variables (`pthread_mutex_*`, `pthread_cond_wait` / `pthread_cond_signal`), the producer–consumer pattern, thread-safe data structures, and socket programming.
