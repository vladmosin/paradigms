#pragma once
#include <pthread.h>
#include <queue>
#include <vector>


typedef struct Task {
    void (*f) (void* arg);
    void* arg; 
    bool finish;  
    pthread_mutex_t mutex;
    pthread_cond_t cond;  
} Task;

typedef struct ThreadPool {
    std::vector<pthread_t> threads;
    std::queue<Task*> tasks; 
    bool finish;
    unsigned size;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} ThreadPool;


void thpool_init(ThreadPool* pool, unsigned threads_nm);
void thpool_submit(ThreadPool* pool, Task* task);
void thpool_wait(Task* task);
void thpool_finit(ThreadPool* pool);
