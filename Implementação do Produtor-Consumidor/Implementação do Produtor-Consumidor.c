//Feito pela dupla Rafael Cancian e Thiago Rocha

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define N 3

int buffer[N];
int proxima_insercao = 0;
int proxima_remocao = 0;

sem_t exclusao_mutua;
sem_t espera_vaga;
sem_t espera_dado;

void* produtor(void* nome) {
	for (int i = 0; i < 10; i++) {
		sem_wait(&espera_vaga);
		sem_wait(&exclusao_mutua);
		buffer[proxima_insercao] = 10;
		printf("O produtor criou um item (%d).\n", buffer[proxima_insercao]);
		proxima_insercao = (proxima_insercao + 1) % N;
		sem_post(&exclusao_mutua);
		sem_post(&espera_dado);
	}
}

void* consumidor(void* nome) {
	for (int i = 0; i < 10; i++) {
		sem_wait(&espera_dado);
		sem_wait(&exclusao_mutua);
		buffer[proxima_remocao] = 0;
		printf("O consumidor consumiu um item (%d).\n", buffer[proxima_remocao]);
		proxima_remocao = (proxima_remocao + 1) % N;
		sem_post(&exclusao_mutua);
		sem_post(&espera_vaga);
	}
}

int main(){
	int i;
	pthread_t thUm, thDois;

	sem_init(&exclusao_mutua, 0, 1);
	sem_init(&espera_vaga, 0, N);
	sem_init(&espera_dado, 0, 0);

	pthread_create(&thUm, 0, produtor, "Thread Produtor");
	pthread_create(&thDois, 0, consumidor, "Thread Consumidor");

	pthread_join(thUm, NULL);
	pthread_join(thDois, NULL);

	sem_destroy(&exclusao_mutua);
	sem_destroy(&espera_vaga);
	sem_destroy(&espera_dado);
	printf("\nFim do Thread Principal\n");

	return 1;
}
