/*/
   3 – Faça um programa em que dois processos concorrentes executam as ações a seguir.
   Lembre-se de imprimir o PID de cada processo em cada impressão.
   • Processo Pai:
   Imprime os números de 1 a 50, com um intervalo de 2 segundos entre cada
   número. Ao terminar, imprime “Processo Pai finalizou”.
   • Processo Filho1:
   Imprime os números de 100 a 200, com um intervalo de 1 segundo entre
   cada um. Ao terminar, imprime “Filho1 finalizou”.
   • Processo Filho2:
   Imprime os números de 250 a 350, com um intervalo de 1 segundo entre
   cada um. Ao terminar, imprime “Filho2 finalizou”.
/*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <locale.h>

int main() {
        setlocale(LC_ALL, "Portuguese");

        int i;

        pid_t procID;
        procID = fork();

        if (procID < 0) {
                printf("ERRO: O processo não foi criado.\n");
                return -1;
        }
        else if (procID == 0) { //Processo filho 1

                procID = fork(); //Processo filho 2

                if (procID == 0) {
                        for (i = 250; i < 350; i++) {
                                printf("\n[Filho 2] Número: %d", i + 1);
                                sleep(1);
                        }
                }

                for (i = 100; i < 200; i++) {
                        printf("\n[Filho 1] Número: %d", i + 1);
                        sleep(1);
                }
                return 1;
        }
        else { //Processo pai
                for (i = 0; i < 50; i++) {
                        printf("\n[Pai] Número: %d", i + 1);
                        sleep(2);
                }
                return 1;
        }
        return 0;
}
