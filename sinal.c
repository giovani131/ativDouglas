#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t condicao;

int pronto = 0;

void *produtor(void *arg) {
    printf("Produtor está preparando dados...\n");
    sleep(2);

    pthread_mutex_lock(&mutex);
    pronto = 1;
    pthread_cond_signal(&condicao);
    pthread_mutex_unlock(&mutex);

    printf("Produtor enviou sinal\n");
    return NULL;
}

void *consumidor(void *arg) {
    pthread_mutex_lock(&mutex);
    while (pronto == 0)
        pthread_cond_wait(&condicao, &mutex);

    printf("Consumidor recebeu sinal e está processando dados\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t prod, cons;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condicao, NULL);

    pthread_create(&prod, NULL, produtor, NULL);
    pthread_create(&cons, NULL, consumidor, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condicao);

    return 0;
}
