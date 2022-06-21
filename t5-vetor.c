#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <Windows.h>

// dificuldade = 0 representa o próprio jogador
int jogada(char nome[32], int pontos_jogador, int pontos_computador, int dificuldade) {
    int quantidade_dados = 5;
    int pontos = 0;
    int rodadas = 1;
    int pontuou_no_turno = 0;
    int aux_pontuou = 0;
    while (1) {
        // evita que o jogador ganhe ah não ser que tenha conseguido exatos 5000 pontos
        if (dificuldade == 0) {
            if (pontos_jogador + pontos > 5000) {
                printf("\n**** %s EXTRAPOLOU OS 5000!!! ****", nome);
                printf("\n################## Fim do turno ##################\n");
                return 0;
            }
        } else if (pontos_computador + pontos > 5000) {
            printf("\n**** %s EXTRAPOLOU OS 5000!!! ****", nome);
            printf("\n################## Fim do turno ##################\n");
            return 0;
        }
        int add = 0;
        int pontuou = 0;
        // Inicialização da rodada e contagem das ocorrências de cada número
        printf("############### %s - Rodada %d ###############\n", nome, rodadas);
        rodadas++;
        int count_numeros[6] = {0, 0, 0, 0, 0, 0}; // pos 0 conta a quantidade de 1s, pos 1 conta quantidade de 2s e assim por diante
        
        // caso todos os dados jogados tenham somado pontos, jogam-se todos novamente
        if (quantidade_dados == 0) quantidade_dados = 5;

        
        int dados[5] = {-1, -1, -1, -1, -1};
        for (int i1 = 0; i1 < quantidade_dados; i1++) {
            dados[i1] = rand() % 6 + 1;
            for (int i = 1; i <= 6; i ++) {
                if (dados[i1] == i) count_numeros[i-1]++;
            }
        }


        // Resultado
        printf("Jogando os dados...\n");
        Sleep(2000);
        printf("Resultado dos dados: ");
        for (int i = 0; i < quantidade_dados; i++) printf("%d ", dados[i]);
        Sleep(2000);

        // Verificação de sequências
        if (quantidade_dados == 5) {
            // de 1 a 5
            int sequencia1a5 = 1;
            for (int i = 0; i < 5; i++) {
                if (count_numeros[i] != 1) sequencia1a5 = 0;
            }
            if (sequencia1a5) {
                pontos += 500;
                pontuou_no_turno = 1;
                quantidade_dados -= 5;
                printf("\n####### SEQUENCIA DE 1 A 5 => +500 PONTOS #######");
                printf("\nPontuacao turno %s: %d\n", nome, pontos);
                Sleep(2000);
                continue;
            }
            // de 2 a 6
            int sequencia2a6 = 1;
            for (int i = 1; i < 6; i++) {
                if (count_numeros[i] != 1) sequencia2a6 = 0;
            }
            if (sequencia2a6) {
                pontos += 500;
                pontuou_no_turno = 1;
                quantidade_dados -= 5;
                printf("\n####### SEQUENCIA DE 2 A 6 => +500 PONTOS #######");
                printf("\nPontuacao turno %s: %d\n", nome, pontos);
                Sleep(2000);
                continue;
            }
        }


        // de 3x um número (ou mais)
        if (quantidade_dados >= 3) {
            for (int i = 0; i < 6; i++) {
                if (count_numeros[i] >= 3) {
                    // joga os números usados na sequência pro fim da lista pra que
                    // sejam desconsiderados quando forem removidos os dados
                    int countN = 0;
                    for (int i1 = 0; i1 < 5; i1++) {
                        if (dados[i1] != i+1) {
                            dados[countN] = dados[i1];
                            countN++;
                        }
                    }
                    if (i == 0 && count_numeros[i] == 5) {
                        printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
                        printf("\n@@@@@@ %s GANHOU O JOGO!!! @@@@@@", nome);
                        printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
                        Sleep(2000);
                        return pontos;
                    }
                    add = pow(2, count_numeros[i] - 3) * 100 * (i+1);
                    if (i == 0) add *= 10; // o número 1 tem lógica diferente
                    quantidade_dados -= count_numeros[i];
                    pontos += add;
                    if (quantidade_dados == 0)
                        pontuou_no_turno = 1;
                    else aux_pontuou = 1;
                    pontuou = 1;
                    printf("\n####### SEQUENCIA DE %d %ds => +%d PONTOS #######\n", count_numeros[i], i+1, add);
                    printf("Pontuacao turno %s: %d\n", nome, pontos);
                    printf("Dados restantes: ");
                    count_numeros[i] = 0;
                    for (int i1 = 0; i1 < quantidade_dados; i1++) {
                        printf("%d ", dados[i1]);
                    }
                    printf("\n");
                    Sleep(2000);
                    break;
                }
            }
        }

        // Verificação de separação dos 5s e 1s
        if (count_numeros[4] > 0 || count_numeros[0] > 0) {
            int verificacao_pontuacao;

            if (dificuldade == 0) verificacao_pontuacao = pontos_jogador >= 600;
            else verificacao_pontuacao = pontos_computador >= 600;

            if ((pontos - add >= 600 || verificacao_pontuacao) && pontuou_no_turno) {
                int continuar_jogando = 1;
                printf("\nDeseja continuar jogando?: ");
                Sleep(2000);
                if (dificuldade == 1) {
                    if (pontos_jogador > pontos_computador) {
                        printf("1");
                        continuar_jogando = 1;
                    } else {
                        if (pontos >= 250) {
                            printf("0");
                            continuar_jogando = 0;
                        } else {
                            printf("1");
                            continuar_jogando = 1;
                        }
                    }
                } else if (dificuldade == 2) {
                    if (pontos + pontos_computador == 5000) { // faz com que o bot saiba parar na hora certa
                        continuar_jogando = 0;
                    } else {
                        if (pontos_jogador > pontos_computador) {
                            if (pontos < 300) {
                                printf("1");
                                continuar_jogando = 1;
                            } else {
                                printf("0");
                                continuar_jogando = 0;
                            }
                        } else {
                            if (pontos < 200) {
                                printf("1");
                                continuar_jogando = 1;
                            } else {
                                printf("0");
                                continuar_jogando = 0;
                            }
                        }
                    }
                } else {
                    scanf("%d", &continuar_jogando);
                }


                Sleep(2000);

                if (!continuar_jogando) {
                    printf("\n################## Fim do turno ##################\n");
                    return pontos;
                }
            }
            printf("\nQuais dados gostaria de separar? ");
            if (dificuldade == 0)
                printf("\nDigite a posicao dos dados (de 1 a 5) e 0 para salvar: ");

            int dados_para_separar[5] = {-1, -1, -1, -1, -1};
            // se todos dados da mesma pontuarem com 5 ou 1, ex: dois dados na mesa: 1 5, então todos
            // deverão ser contabilizados para que possam ser jogados mais uma vez
            if (dificuldade == 1 || (dificuldade == 2 && quantidade_dados - count_numeros[4] - count_numeros[0] == 0)) {
                // Como o computador simplesmente separa todos dados que pontua
                // dados_para_separar = dados (o programa desconsidera dados que não pontuam)
                for (int i = 0; i < 5; i++) {
                    dados_para_separar[i] = dados[i];
                }
            } else if (dificuldade == 2) {
                int count1s = 0;
                // primeiro deixa apenas um número 1 no vetor dados_para_separar
                for (int i = 0; i < 5; i++) {
                    if (dados[i] == 1) {
                        dados_para_separar[i] = dados[i];
                        count1s++;
                        break;
                    }
                }
                // depois, se não houver nenhum 1, faz o mesmo com apenas um 5
                if (count1s == 0) {
                    for (int i = 0; i < 5; i++) {
                        if (dados[i] == 5) {
                            dados_para_separar[i] = dados[i];
                            break;
                        }
                    }
                }
            } else if (dificuldade == 0) {
                int input_correto = 0;
                while(!input_correto) {
                    int index = 0;
                    while(1) {
                        int n;
                        scanf("%d", &n);
                        if ((n == 0 || index == quantidade_dados)) {
                            break;
                        }
                        dados_para_separar[index] = dados[n-1];
                        index++;
                    }
                    input_correto = 1;
                    for (int i = 0; i < 5; i++) {
                        if (dados_para_separar[i] != 5 && dados_para_separar[i] != 1 && dados_para_separar[i] != -1) {
                            input_correto = 0;
                        }
                    }
                    if (!input_correto) {
                        printf("\nUm dos dados digitados não é 5 nem 1. Tente novamente: ");
                    }
                }


            }

            if (dificuldade != 0) {
                printf("\nDados separados: ");
                Sleep(2000);
            }
            int copia_quantidade_dados = quantidade_dados;
            for (int i = 0; i < copia_quantidade_dados; i++) {
                if (dados_para_separar[i] == 0) break;
                if (dados_para_separar[i] == 1)  {
                    if (dificuldade != 0) 
                        printf("%d ", i+1);
                    pontos += 100;
                    pontuou_no_turno = 1;
                    quantidade_dados--;
                } else if (dados_para_separar[i] == 5) {
                    if (dificuldade != 0)
                        printf("%d ", i+1);
                    pontos += 50;
                    pontuou_no_turno = 1;
                    quantidade_dados--;
                }
            }
            printf("\nPontuacao turno %s: %d\n", nome, pontos);
            Sleep(2000);
        } 
        else {
            printf("\nNenhum 5 ou 1!\n");
            if (!pontuou) {
                printf("################## Fim do turno ##################\n");
                Sleep(2000);
                pontos = 0;
                quantidade_dados = 5;
                return pontos;
            }
        }
        if (aux_pontuou)
            pontuou_no_turno = aux_pontuou;
    }
}

int main() {
    printf("------------------------------------------------\n");
    printf("------------------JOGO DO 5000------------------\n");
    printf("------------------------------------------------\n");

    srand(time(0));

    int jogador1_comeca = rand() % 2;

    char nome_jogador[32];
    printf("Digite o nome do jogador: ");
    scanf("%s", nome_jogador);

    if (jogador1_comeca) {
        printf("%s comeca:\n", nome_jogador);
    } else printf("Computador comeca\n");

    int dificuldade;
    printf("Selecione a dificuldade do bot\n");
    printf("1 - Basico\n");
    printf("2 - Avancado\n");
    scanf("%d", &dificuldade);

    int pontos_jogador = 0;
    int pontos_computador = 0;
    if (jogador1_comeca) {
        pontos_jogador += jogada(nome_jogador, pontos_jogador, pontos_computador, 0);
        printf("\nPONTUACAO TOTAL %s: %d\n", nome_jogador, pontos_jogador);
        Sleep(2000);
    }

    while (1) {
        pontos_computador += jogada("Computador", pontos_jogador, pontos_computador, dificuldade);
        printf("\nPONTUACAO TOTAL COMPUTADOR: %d\n", pontos_computador);
        if (pontos_computador == 5000) {
            printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
            printf("\n@@@@ Computador GANHOU O JOGO!!! @@@@");
            printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
            break;
        }
        Sleep(2000);
        pontos_jogador += jogada(nome_jogador, pontos_jogador, pontos_computador, 0);
        printf("\nPONTUACAO TOTAL %s: %d\n", nome_jogador, pontos_jogador);
        if (pontos_jogador == 5000) {
            printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
            printf("\n@@@@@@ %s GANHOU O JOGO!!! @@@@@@", nome_jogador);
            printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
            break;
        }
        Sleep(2000);
    }

    return 0;
}