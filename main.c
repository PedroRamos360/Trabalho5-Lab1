#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));  
    int dados[5];
    printf("------------------------------------------------\n");
    printf("------------------JOGO DO 5000------------------\n");
    printf("------------------------------------------------\n");
    int jogador1_comeca = 1;//rand() % 2;
    char jogador[32];
    if (jogador1_comeca) sprintf(jogador, "Jogador 1");
    else sprintf(jogador, "Computador");

    printf("%s comeca\n", jogador);
    int rodadas = 1;
    int pontos = 0;
    while (1) {
        printf("############### %s - Rodada %d ###############\n", jogador, rodadas);
        rodadas++;
        int count5 = 0;
        int count1 = 0;
        for (int i = 0; i < 5; i++) {
            dados[i] = rand() % 6 + 1;
            if (dados[i] == 1) count1++;
            else if (dados[i] == 5) count5++;
        }
        printf("Resultado dos dados do %s: ", jogador);
        for (int i = 0; i < 5; i ++) printf("%d ", dados[i]);
        if (count5 > 0 || count1 > 0) {
            if (pontos >= 600) {
                int continuar_jogando;
                printf("\nDeseja continuar jogando? (0 ou 1): ");
                scanf("%d", &continuar_jogando);
                printf("\n################## Fim do turno ##################\n");
                if (!continuar_jogando) break;
            }
            printf("\nQuais dados gostaria de separar?");
            printf("\nDigite o numero dos dados (1 a 5) ou 0 para terminar: ");
            int dados_para_separar[5] = {0, 0, 0, 0, 0};
            int index = 0;
            while(1) {
                int n;
                scanf("%d", &n);
                if (n == 0 || index == 5) break;
                dados_para_separar[index] = dados[n-1];
                index++;
            }
            for (int i = 0; i < 5; i++) {
                if (dados_para_separar[i] == 0) break;
                if (dados_para_separar[i] == 1) pontos += 100;
                if (dados_para_separar[i] == 5) pontos += 50;
            }
            printf("Pontuacao %s: %d\n", jogador, pontos);
        } else {
            printf("\n################## Fim do turno ##################\n");
            pontos = 0;
            break;
        }
    }

}