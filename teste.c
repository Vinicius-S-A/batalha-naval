#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// TO DO
// - Esconder os navios inimigos
// - Config para tamanho máximo do campo (quantidade de células)
// - Config para quantidade de embarcações dos jogadores
// - Esconder os navios inimigos
// - Conferir para ver se pode usar essas duas libs "<time.h>" e "<stdlib.h>"
// - Opção de parar o jogo em sua rodada
// - Cada jogador tem o direito a três bombardeios por turno;
// - Ao acabar o jogo, deve fornecer op¸c˜oes para jogar novamente, voltar ao menu principal ou sair do jogo

int main() {
    srand(time(NULL));

    int tamanhoCampo = 15;
    int qtdeEmbarcacoes = 4;

    int campoHumano[tamanhoCampo], campoComputador[tamanhoCampo];
    int posicaoBombardeio;
    int jogoAtivo = 1;

    while (jogoAtivo) {
        printf("\nMenu Principal:\n");
        printf("1. Novo Jogo\n");
        printf("2. Configurar\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        int opcao;
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                for (int i = 0; i < tamanhoCampo; i++) {
                    campoHumano[i] = 7;
                    campoComputador[i] = 7;
                }

                int embarcacoesPosicionadasHumano = 0;
                while (embarcacoesPosicionadasHumano < qtdeEmbarcacoes) {
                    int posicao = rand() % (tamanhoCampo-1);
                    if (campoHumano[posicao] == 7 && campoHumano[posicao+1] == 7) {
                        campoHumano[posicao] = 1;
                        campoHumano[posicao+1] = 1;
                        embarcacoesPosicionadasHumano++;
                    }
                }

                int embarcacoesPosicionadasComputador = 0;
                while (embarcacoesPosicionadasComputador < qtdeEmbarcacoes) {
                    int posicao = rand() % tamanhoCampo;
                    if (campoComputador[posicao] == 7 && campoComputador[posicao+1] == 7) {
                        campoComputador[posicao] = 1;
                        campoComputador[posicao+ 1] = 1;
                        embarcacoesPosicionadasComputador++;
                    }
                }

                int vitoriaHumano = 0, vitoriaComputador = 0;

                while (!vitoriaHumano && !vitoriaComputador) {
                    printf("\nSeu campo: \n");
                    for (int i = 0; i < tamanhoCampo; i++) {
                        if (campoHumano[i] == 7) {
                            printf("   ");
                        } else {
                            printf(" %d ", campoHumano[i]);
                        }
                    }
                    printf("\n");

                    for (int i = 0; i < tamanhoCampo; i++) {
                        printf("__ ");
                    }
                    printf("\n");

                    for (int i = 0; i < tamanhoCampo; i++) {
                        if (i < 10) {
                            printf(" %d ", i);
                        } else {
                            printf("%d ", i);
                        }
                    }

                    printf("\n");
                    printf("\n");
                    printf("\n");

                    printf("\nCampo Inimigo: \n");
                    for (int i = 0; i < tamanhoCampo; i++) {
                        printf(" %d ", campoComputador[i]);
                    }
                    printf("\n");

                    for (int i = 0; i < tamanhoCampo; i++) {
                        printf("__ ");
                    }
                    printf("\n");

                    for (int i = 0; i < tamanhoCampo; i++) {
                        if (i < 10) {
                            printf(" %d ", i);
                        } else {
                            printf("%d ", i);
                        }
                    }
                    printf("\n");
                    printf("\n");
                    printf("\n");

                    printf("\nSeu turno! Escolha uma posicao para bombardear (0 a %d): ", tamanhoCampo - 1);
                    scanf("%d", &posicaoBombardeio);

                    if (campoComputador[posicaoBombardeio] != 0 && campoComputador[posicaoBombardeio] != 3) {
                        if (campoComputador[posicaoBombardeio] == 7) {
                            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

                            printf("___________________\n");
                            printf("[      AGUA!      ]\n\n");

                            campoComputador[posicaoBombardeio] = 0;
                        } else if (campoComputador[posicaoBombardeio] == 1) {
                            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

                            printf("______________________\n");
                            printf("[      IMPACTO!      ]\n\n");
                            
                            campoComputador[posicaoBombardeio] = 2;
                        }
                    } else {
                        printf("A posicao ja foi bombardeada antes. Tente outra.\n");
                        continue;
                    }

                    vitoriaComputador = 1;
                    for (int i = 0; i < tamanhoCampo; i++) {
                        if (campoComputador[i] == 1) {
                            vitoriaComputador = 0;
                            break;
                        }
                    }

                    if (vitoriaComputador) {
                        printf("\nVoce venceu! O computador perdeu.\n");
                        break;
                    }

                    printf("\nAgora e o turno do computador...\n");
                    int posicaoComputador = rand() % tamanhoCampo;
                    while (campoHumano[posicaoComputador] == 0 || campoHumano[posicaoComputador] == 3) {
                        posicaoComputador = rand() % tamanhoCampo;
                    }

                    printf("O computador bombardeou a posicao %d.\n", posicaoComputador);
                    if (campoHumano[posicaoComputador] == 7) {
                        printf("\n\n___________________\n");
                        printf("[      AGUA!      ]\n\n");
                        campoHumano[posicaoComputador] = 0;
                    } else if (campoHumano[posicaoComputador] == 1) {
                        printf("\n\n______________________\n");
                        printf("[      IMPACTO!      ]\n\n");
                        campoHumano[posicaoComputador] = 2;
                    }

                    vitoriaHumano = 1;
                    for (int i = 0; i < tamanhoCampo; i++) {
                        if (campoHumano[i] == 1) {
                            vitoriaHumano = 0;
                            break;
                        }
                    }

                    if (vitoriaHumano) {
                        printf("\nVocê perdeu! O computador venceu.\n");
                        break;
                    }
                }

                break;
            case 2: // CONFIGURAÇÕES
                jogoAtivo = 0;

                break;
            case 3:
                jogoAtivo = 0;
                break;

            default: // VALIDAR, POIS ESTÁ QUEBRANDO QUANDO CAI AQUI E CONTINUANDO O LOOP
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
