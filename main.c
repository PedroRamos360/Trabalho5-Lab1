#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
    srand(time(NULL));  
    int dados[5] = {4, 4, 4, 1, 5};
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
        // Inicialização da rodada e contagem das ocorrências de cada número
        printf("############### %s - Rodada %d ###############\n", jogador, rodadas);
        rodadas++;
        int count_numeros[6] = {0, 0, 0, 0, 0, 0}; // pos 0 conta a quantidade de 1s, pos 1 conta quantidade de 2s e assim por diante
        for (int i1 = 0; i1 < 5; i1++) {
            // dados[i1] = rand() % 6 + 1;
            for (int i = 1; i <= 6; i ++) {
                if (dados[i1] == i) count_numeros[i-1]++;
            }
        }

        // Resultado
        printf("Resultado dos dados do %s: ", jogador);
        for (int i = 0; i < 5; i ++) printf("%d ", dados[i]);

        // Verificação de sequências
        // de 1 a 5
        int sequencia1a5 = 1;
        for (int i = 0; i < 5; i++) {
            if (count_numeros[i] != 1) sequencia1a5 = 0;
        }
        if (sequencia1a5) {
            pontos += 500;
            printf("\n####### SEQUENCIA DE 1 A 5 => +500 PONTOS #######");
            printf("\nPontuacao %s: %d\n", jogador, pontos);
            continue;
        }
        // de 2 a 6
        int sequencia2a6 = 1;
        for (int i = 1; i < 6; i++) {
            if (count_numeros[i] != 1) sequencia2a6 = 0;
        }
        if (sequencia2a6) {
            pontos += 500;
            printf("\n####### SEQUENCIA DE 2 A 6 => +500 PONTOS #######");
            printf("\nPontuacao %s: %d\n", jogador, pontos);
            continue;
        }

        // Verificação de sequência de 3x um número
        int sequencia3x = 0;
        for (int i = 0; i < 6; i++) {
            if (count_numeros[i] >= 3) {
                sequencia3x = 1;
                if (i == 0 && count_numeros[i] == 5) {
                    if (count_numeros[i] == 5) {
                        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
                        printf("@@@@@@@@@@ %s GANHOU O JOGO!!! @@@@@@@@@@", jogador);
                        printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
                        return 0;
                    }
                    int add = pow(2, count_numeros[i] - 3) * 100 * (i+1);
                    pontos += add;
                    printf("\n####### SEQUENCIA DE %d 1s => +%d PONTOS #######\n", count_numeros[i], add);
                    break;
                }
                int add = pow(2, count_numeros[i] - 3) * 100 * (i+1);
                pontos += add;
                printf("\n####### SEQUENCIA DE %d %ds => +%d PONTOS #######\n", count_numeros[i], i+1, add);
                break;
            }
        }
        if (sequencia3x) {
            continue;
        }



        // Verificação de separação dos 5s e 1s
        if (count_numeros[4] > 0 || count_numeros[0] > 0) {
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