/*/
   1 – Crie um programa com dois processos. As medidas de um terreno retangular devem ser
   lidas. O processo Filho deve calcular a área do terreno e o processo Pai o perímetro. Todos
   os resultados obtidos devem ser mostrados ao usuário.
/*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <locale.h>

int main() {
        setlocale(LC_ALL, "Portuguese");

        int base,lado;

        printf("Informe a base do retângulo: ");
        scanf("%d", &base);

        printf("Informe o lado do retângulo: ");
        scanf("%d", &lado);

        pid_t procID;
        procID = fork();

        if (procID < 0) {
                printf("ERRO: O processo não foi criado.\n");
                return -1;
        }
        else if (procID == 0) { //Processo filho
                int resultadoArea = base*lado;
                printf("\n[Processo filho: %d] Área do retângulo: %d\n", getpid(), resultadoArea);
                return 1;
        }
        else { //Processo pai
                int resultadoPerimetro = (base*2) + (lado*2);
                printf("\n[Processo pai: %d] Perímetro do retângulo: %d", getpid(), resultadoPerimetro);
                return 1;
        }
        return 0;
}
