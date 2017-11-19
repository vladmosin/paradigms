#include "thread_pool.h"
#include <cstdio>


void* start_thread(void* pool) {
    while (!((ThreadPool*) pool)->finish || !((ThreadPool*) pool)->tasks.empty()) {
        while (((ThreadPool*) pool)->tasks.empty() && !((ThreadPool*) pool)->finish)
            pthread_cond_wait(&(((ThreadPool*) pool)->cond), &((ThreadPool*) pool)->mutex);
        pthread_mutex_lock(&(((ThreadPool*) pool)->mutex));
        if (((ThreadPool*) pool)->tasks.empty())
            pthread_mutex_unlock(&((ThreadPool*) pool)->mutex);
        else {
            Task* task = ((ThreadPool*) pool)->tasks.front();
            ((ThreadPool*) pool)->tasks.pop();
            pthread_mutex_unlock(&((ThreadPool*) pool)->mutex);
            task->f(task->arg);
            task->finish = true;
            pthread_cond_broadcast(&(task->cond));
        }
    }
    return NULL;
}

void thpool_init(ThreadPool* pool, unsigned threads_nm) {
    pthread_mutex_init(&(pool->mutex), NULL);
    pthread_cond_init(&(pool->cond), NULL);
    pool->finish = false;
    pool->size = threads_nm;
    pool->threads = new pthread_t[threads_nm];
    for (unsigned i = 0; i < threads_nm; i++) {
        pthread_create(&(pool->threads[i]), NULL, start_thread, pool);
    }
}

void thpool_submit(ThreadPool* pool, Task* task) {
    pthread_mutex_lock(&(pool->mutex));
    pool->tasks.push(task);
    pthread_mutex_unlock(&(pool->mutex)); 
    pthread_cond_signal(&(pool->cond));   
}

void thpool_wait(Task* task) {
    pthread_mutex_lock(&task->mutex);
    while(task->finish == false)
        pthread_cond_wait(&task->cond, &task->mutex);
}

void thpool_finit(ThreadPool* pool) {
    pool->finish = true;
    pthread_cond_broadcast(&(pool->cond));
    for (unsigned i = 0; i < pool->size; i++) {
        pthread_join(pool->threads[i], NULL);
    }
    delete [] pool->threads;
    pthread_cond_destroy(&(pool->cond));
    pthread_mutex_destroy(&(pool->mutex));
}
