#include "thread_pool.h" 
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstdio>


void crazy_func(void*) {
    long long c = 3374;
    for (long long i = 0; i < 1000000; i++) {
        c += c * cos(c);
    }
}

int main(int argc, char* argv[]) {
    std::time_t start_time = time(NULL);
    ThreadPool pool;
    thpool_init(&pool, atoi(argv[1]));
    Task task[1000];
    for (int i = 0; i < 100; i++) {
        task[i].f = crazy_func;
        task[i].arg = NULL;
        task[i].finish = false;
        pthread_mutex_init(&(task[i].mutex), NULL);
        pthread_cond_init(&(task[i].cond), NULL);
        thpool_submit(&pool, &task[i]);
    }
    thpool_wait(&task[3]);
    thpool_finit(&pool);
    std::time_t end_time = time(NULL);
    printf("%d", (int)(end_time - start_time));
    return 0;
}
