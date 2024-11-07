#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t trava1, trava2;

void *thread1(void *arg) {
    pthread_mutex_lock(&trava1);
    sleep(1);
    pthread_mutex_lock(&trava2);

    printf("Thread 1 possui ambas as travas\n");

    pthread_mutex_unlock(&trava2);
    pthread_mutex_unlock(&trava1);
    return NULL;
}

void *thread2(void *arg) {
    pthread_mutex_lock(&trava2);
    sleep(1);
    pthread_mutex_lock(&trava1);

    printf("Thread 2 possui ambas as travas\n");

    pthread_mutex_unlock(&trava1);
    pthread_mutex_unlock(&trava2);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&trava1, NULL);
    pthread_mutex_init(&trava2, NULL);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&trava1);
    pthread_mutex_destroy(&trava2);

   
