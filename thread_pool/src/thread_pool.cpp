#include "thread_pool.h"
#include <cstdio>


void* start_thread(void* given_pool) {
    ThreadPool* pool = (ThreadPool*) given_pool;
    while (true) {
        pthread_mutex_lock(&pool->mutex);
        while (pool->tasks.empty() && !pool->finish)
            pthread_cond_wait(&pool->cond, &pool->mutex);
        if (pool->tasks.empty())
            pthread_mutex_unlock(&pool->mutex);
        else {
            Task* task = pool->tasks.front();
            pool->tasks.pop();
            pthread_mutex_unlock(&pool->mutex);
            task->f(task->arg);
            pthread_mutex_lock(&task->mutex);
            task->finish = true;
            pthread_mutex_unlock(&task->mutex);
            pthread_cond_broadcast(&(task->cond));
        }
        pthread_mutex_lock(&pool->mutex);
        if (pool->tasks.empty() && pool->finish) {
            pthread_mutex_unlock(&pool->mutex);
            break;
        }
        pthread_mutex_unlock(&pool->mutex);
    }
    return NULL;
}

void thpool_init(ThreadPool* pool, unsigned threads_nm) {
    pthread_mutex_init(&(pool->mutex), NULL);
    pthread_cond_init(&(pool->cond), NULL);
    pthread_mutex_lock(&pool->mutex);
    pool->finish = false;
    pool->size = threads_nm;
    pthread_mutex_unlock(&pool->mutex);
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
    pthread_mutex_unlock(&task->mutex);
}

void thpool_finit(ThreadPool* pool) {
    pthread_mutex_lock(&pool->mutex);
    pool->finish = true;
    pthread_mutex_unlock(&pool->mutex);
    pthread_cond_broadcast(&(pool->cond));
    for (unsigned i = 0; i < pool->size; i++) {
        pthread_join(pool->threads[i], NULL);
    }
    delete [] pool->threads;
    pthread_cond_destroy(&(pool->cond));
    pthread_mutex_destroy(&(pool->mutex));
}
