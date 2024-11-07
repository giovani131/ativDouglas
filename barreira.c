#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_barrier_t barreira;

void *funcao_thread(void *arg) {
    int id = *((int *) arg);
    printf("Thread %d está trabalhando...\n", id);
    sleep(1);

    printf("Thread %d aguardando na barreira...\n", id);
    pthread_barrier_wait(&barreira);

    printf("Thread %d prosseguindo...\n", id);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};

    pthread_barrier_init(&barreira, NULL, 3);

    for (int i = 0; i < 3; i++)
        pthread_create(&threads[i], NULL, funcao_thread, &ids[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(threads[i], NULL);

    pthread_barrier_destroy(&barreira);

    return 0;
}
