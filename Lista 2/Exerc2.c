/*/
   2 – Escreva um programa formado por 3 processos concorrentes, que executam um laço de
   repetição de N interações. Neste laço, cada processo imprime sua identificação. A partir da
   execução do programa, identifique como acontece o escalonamento dos processos.
   /*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <locale.h>

int main() {
        setlocale(LC_ALL, "Portuguese");

        int i,n;

        printf("Informe o número de iterações: ");
        scanf("%d", &n);

        pid_t procID;
        procID = fork();

        if (procID < 0) {
                printf("ERRO: O processo não foi criado.\n");
                return -1;
        }
        else if (procID == 0) { //Processo filho
                for (i = 0; i < n; i++) {
                        printf("\nProcesso filho 1: %d", getpid());
                }
                procID = fork(); //Criação do 3 processo

                if (procID == 0) {
                        for (i = 0; i < n; i++) {
                                printf("\nProcesso filho 2: %d", getpid());
                        }
                }
                return 1;
        }
        else { //Processo pai
                for (i = 0; i < n; i++) {
                        printf("\nProcesso pai: %d", getpid());
                }
                return 1;
        }
        return 0;
}
