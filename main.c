#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>

int jogador(char nome_jogador[32]) {
    int quantidade_dados = 5;
    int pontos = 0;
    int dados[5];
    int rodadas = 1;
    while (1) {
        // Inicialização da rodada e contagem das ocorrências de cada número
        printf("############### %s - Rodada %d ###############\n", nome_jogador, rodadas);
        rodadas++;
        int count_numeros[6] = {0, 0, 0, 0, 0, 0}; // pos 0 conta a quantidade de 1s, pos 1 conta quantidade de 2s e assim por diante
        
        // caso todos os dados jogados tenham somado pontos, jogam-se todos novamente
        if (quantidade_dados == 0) quantidade_dados = 5;

        for (int i1 = 0; i1 < quantidade_dados; i1++) {
            dados[i1] = rand() % 6 + 1;
            for (int i = 1; i <= 6; i ++) {
                if (dados[i1] == i) count_numeros[i-1]++;
            }
        }

        // Resultado
        printf("Jogando os dados...\n");
        Sleep(1000);
        printf("Resultado dos dados: ");
        for (int i = 0; i < quantidade_dados; i++) printf("%d ", dados[i]);
        Sleep(1000);

        // Verificação de sequências
        if (quantidade_dados == 5) {
            // de 1 a 5
            int sequencia1a5 = 1;
            for (int i = 0; i < 5; i++) {
                if (count_numeros[i] != 1) sequencia1a5 = 0;
            }
            if (sequencia1a5) {
                pontos += 500;
                quantidade_dados -= 5;
                printf("\n####### SEQUENCIA DE 1 A 5 => +500 PONTOS #######");
                printf("\nPontuacao %s: %d\n", nome_jogador, pontos);
                Sleep(1000);
                continue;
            }
            // de 2 a 6
            int sequencia2a6 = 1;
            for (int i = 1; i < 6; i++) {
                if (count_numeros[i] != 1) sequencia2a6 = 0;
            }
            if (sequencia2a6) {
                pontos += 500;
                quantidade_dados -= 5;
                printf("\n####### SEQUENCIA DE 2 A 6 => +500 PONTOS #######");
                printf("\nPontuacao %s: %d\n", nome_jogador, pontos);
                Sleep(1000);
                continue;
            }
        }


        // de 3x um número (ou mais)
        if (quantidade_dados >= 3) {
            int sequencia3x = 0;
            for (int i = 0; i < 6; i++) {
                if (count_numeros[i] >= 3) {
                    sequencia3x = 1;
                    if (i == 0) {
                        if (count_numeros[i] == 5) {
                            printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
                            printf("\n@@@@@@ %s GANHOU O JOGO!!! @@@@@@", nome_jogador);
                            printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
                            Sleep(1000);
                            return pontos;
                        }
                        int add = pow(2, count_numeros[i] - 3) * 1000;
                        pontos += add;
                        quantidade_dados -= count_numeros[i];
                        printf("\n####### SEQUENCIA DE %d 1s => +%d PONTOS #######\n", count_numeros[i], add);
                        printf("Pontuacao %s: %d\n", nome_jogador, pontos);
                        Sleep(1000);
                        break;
                    }
                    int add = pow(2, count_numeros[i] - 3) * 100 * (i+1);
                    pontos += add;
                    quantidade_dados -= count_numeros[i];
                    printf("\n####### SEQUENCIA DE %d %ds => +%d PONTOS #######\n", count_numeros[i], i+1, add);
                    printf("Pontuacao %s: %d\n", nome_jogador, pontos);
                    Sleep(1000);
                    break;
                }
            }
            if (sequencia3x) {
                continue;
            }
        }

        // Verificação de separação dos 5s e 1s
        if (count_numeros[4] > 0 || count_numeros[0] > 0) {
            if (pontos >= 600) {
                int continuar_jogando;
                printf("\nDeseja continuar jogando? (0 ou 1): ");
                scanf("%d", &continuar_jogando);
                printf("\n################## Fim do turno ##################\n");
                Sleep(1000);
                if (!continuar_jogando) return pontos;
            }
            printf("\nQuais dados gostaria de separar?");
            printf("\nDigite o numero dos dados (1 a 5) e 0 para salvar: ");
            int dados_para_separar[5] = {0, 0, 0, 0, 0};
            int index = 0;
            while(1) {
                int n;
                scanf("%d", &n);
                if (n == 0 || index == quantidade_dados) break;
                dados_para_separar[index] = dados[n-1];
                index++;
            }
            for (int i = 0; i < quantidade_dados; i++) {
                if (dados_para_separar[i] == 0) break;
                if (dados_para_separar[i] == 1)  {
                    pontos += 100;
                    quantidade_dados--;
                }
                if (dados_para_separar[i] == 5) {
                    pontos += 50;
                    quantidade_dados--;
                }
            }
            printf("Pontuacao %s: %d\n", nome_jogador, pontos);
            Sleep(1000);
        } else {
            printf("\nNenhuma combinacao ocorreu!");
            printf("\n################## Fim do turno ##################\n");
            Sleep(1000);
            pontos = 0;
            quantidade_dados = 5;
            return pontos;
        }
    }
}

int computador() {
    int pontos = 0;
    return pontos;
}

int main() {
    printf("------------------------------------------------\n");
    printf("------------------JOGO DO 5000------------------\n");
    printf("------------------------------------------------\n");

    srand(time(NULL));  

    int dados[5] = {0, 0, 0, 0, 0};
    int quantidade_dados = 5;

    int jogador1_comeca = 1;//rand() % 2;
    char nome_jogador[32];
    printf("Digite o nome do jogador: ");
    scanf("%s", nome_jogador);
    if (jogador1_comeca) {
        printf("%s comeca:\n", nome_jogador);
    } else printf("Computador começa");

    int pontos_jogador = 0;
    int pontos_computador = 0;

    while (1) {
        pontos_jogador += jogador(nome_jogador);
        printf("\nPONTUACAO TOTAL %s: %d\n", nome_jogador, pontos_jogador);
        if (pontos_jogador >= 5000) {
            printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
            printf("\n@@@@@@ %s GANHOU O JOGO!!! @@@@@@", nome_jogador);
            printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
        }
        Sleep(1000);
        pontos_computador += computador();
        printf("\nPONTUACAO TOTAL COMPUTADOR %s: %d\n", nome_jogador, pontos_jogador);
            if (pontos_jogador >= 5000) {
            printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
            printf("\n@@@@ O COMPUTADOR GANHOU O JOGO!!! @@@@", nome_jogador);
            printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
        }
        Sleep(1000);
    }

    
    return 0;
}