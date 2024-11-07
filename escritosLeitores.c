#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, bloqueio_escrita;
int dado = 0, contagem_leitores = 0;

void *leitor(void *arg) {
    int id = *((int *) arg);

    sem_wait(&mutex);
    contagem_leitores++;
    if (contagem_leitores == 1)
        sem_wait(&bloqueio_escrita);
    sem_post(&mutex);

    printf("Leitor %d: Dado = %d\n", id, dado);
    sleep(1);

    sem_wait(&mutex);
    contagem_leitores--;
    if (contagem_leitores == 0)
        sem_post(&bloqueio_escrita);
    sem_post(&mutex);
    
    return NULL;
}

void *escritor(void *arg) {
    int id = *((int *) arg);

    sem_wait(&bloqueio_escrita);
    dado++;
    printf("Escritor %d: Dado = %d\n", id, dado);
    sleep(1);
    sem_post(&bloqueio_escrita);
    
    return NULL;
}

int main() {
    pthread_t leitores[5], escritores[2];
    int ids[5] = {1, 2, 3, 4, 5};
    
    sem_init(&mutex, 0, 1);
    sem_init(&bloqueio_escrita, 0, 1);

    for (int i = 0; i < 5; i++)
        pthread_create(&leitores[i], NULL, leitor, &ids[i]);
    for (int i = 0; i < 2; i++)
        pthread_create(&escritores[i], NULL, escritor, &ids[i]);

    for (int i = 0; i < 5; i++)
        pthread_join(leitores[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(escritores[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&bloqueio_escrita);

    return 0;
}
