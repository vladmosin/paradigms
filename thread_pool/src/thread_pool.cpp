#include "thread_pool.h"
#include <cstdio>


void* thread_work(void* given_pool) {
    ThreadPool* pool = (ThreadPool*) given_pool;
    while (true) {
        pthread_mutex_lock(&pool->mutex);
        while (pool->tasks.empty() && !pool->finish)
            pthread_cond_wait(&pool->cond, &pool->mutex);
        if (pool->finish) {
            pthread_mutex_unlock(&pool->mutex);
            break;
        }
        else {
            Task* task = pool->tasks.front();
            pool->not_free_tasks.push_back(task);
            pool->tasks.pop();
            pthread_mutex_unlock(&pool->mutex);
            task->f(task->arg);
            pthread_mutex_lock(&task->mutex);
            task->finish = true;
            pthread_cond_broadcast(&task->cond);
            pthread_mutex_unlock(&task->mutex);
        }
    }
    return NULL;
}

void thpool_init(ThreadPool* pool, unsigned threads_nm) {
    pthread_mutex_init(&pool->mutex, NULL);
    pthread_cond_init(&pool->cond, NULL);
    pool->finish = false;
    pool->threads.resize(threads_nm);
    for (unsigned i = 0; i < threads_nm; i++) {
        pthread_create(&pool->threads[i], NULL, thread_work, pool);
    }
}

void thpool_submit(ThreadPool* pool, Task* task) {
    pthread_mutex_init(&task->mutex, NULL);
    pthread_mutex_lock(&task->mutex);
    task->finish = false;
    pthread_cond_init(&task->cond, NULL);
    pthread_mutex_unlock(&task->mutex);
    
    pthread_mutex_lock(&pool->mutex);
    pool->tasks.push(task);
    pthread_cond_signal(&pool->cond); 
    pthread_mutex_unlock(&pool->mutex); 
}

void thpool_wait(Task* task) {
    pthread_mutex_lock(&task->mutex);
    while(!task->finish)
        pthread_cond_wait(&task->cond, &task->mutex);
    pthread_mutex_unlock(&task->mutex);
}

void thpool_finit(ThreadPool* pool) {
    pthread_mutex_lock(&pool->mutex);
    pool->finish = true;
    pthread_cond_broadcast(&pool->cond);
    pthread_mutex_unlock(&pool->mutex);
    
    for (unsigned i = 0; i < pool->threads.size(); i++) {
        pthread_join(pool->threads[i], NULL);
    }
    
    for (unsigned i = 0; i < pool->not_free_tasks.size(); i++) {
        pthread_cond_destroy(&pool->not_free_tasks[i]->cond);
        pthread_mutex_destroy(&pool->not_free_tasks[i]->mutex);
    }
    
    pthread_cond_destroy(&pool->cond);
    pthread_mutex_destroy(&pool->mutex);
}
