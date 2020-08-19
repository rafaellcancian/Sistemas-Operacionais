/*
*************************************************
Exemplo da implementação do Protocolo de Acesso 2
para proteção da Seção crítica.
*************************************************
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100000000
int num = 0;
int x = 0; // variável compartilhada entre as threads, inicializada com o valor 0 ou 1

int flag[2];

void* contaIteracoes(void* nome){
	int aux, i, id, outro;

        id = atoi(nome);
        printf("Thread %d\n", id);

				outro = 1 - id;
				flag[id] = 1;

        //Entrada na Seção crítica
        while (flag[outro] == 1){
             //espera
        }

	//Seção crítica
	for(i=0;i<N;i++)	{
		aux = num;
		aux = aux + 1;
		num = aux;

	}

        //Saída da Seção crítica
        flag[id] = 0;

	pthread_exit(0);
}

int main(){
	int i;
	pthread_t thUm, thDois;

	pthread_create(&thUm, 0, contaIteracoes, "0");
	pthread_create(&thDois, 0, contaIteracoes, "1");

	pthread_join(thUm, NULL);
	pthread_join(thDois, NULL);

	if(num != 2*N)
		printf("**** ERRO na SOMA TOTAL das iteracoees dos Threads ****\nnum = %d\n", num);
	else
		printf("OK! SOMA FINAL CORRETA!!!\nnum = 2 * N = %d\n", num);
	printf("Fim do Thread Principal\n");

	pthread_join(thUm, 0);
	pthread_join(thDois, 0);
	return 0;

}
