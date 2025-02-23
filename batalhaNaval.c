#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// TO DO
// Resolver problema do loop de criação de embarcações

int verificarNavioAfundado(int campo[], int tamanhoCampo, int *naviosAfundados) {
    int novosNaviosAfundados = 0;
    for (int i = 0; i < tamanhoCampo - 1; i++) {
        if (campo[i] == 2 && campo[i + 1] == 2) {
            if (naviosAfundados[i] == 0 && naviosAfundados[i + 1] == 0) {
                novosNaviosAfundados++;
                naviosAfundados[i] = 1;
                naviosAfundados[i + 1] = 1;
            }
            i++;
        }
    }
    return novosNaviosAfundados;
}

int main() {
    srand(time(NULL));

    int tamanhoCampo = 15;
    int qtdeEmbarcacoes = 4;
    int esconderInimigo = 1;

    int posicaoBombardeio;
    int maxBombardeios = 3;
    int continuarJogo = 1;

    while (continuarJogo) {
        printf("----------------------------------\n");
        printf("BEM VINDO AO JOGO DE BATALHA NAVAL\n");
        printf("----------------------------------\n");
        printf("Menu Principal:\n");
        printf("1. Novo Jogo\n");
        printf("2. Configurar\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        int opcao;
        scanf("%d", &opcao);

        int campoHumano[tamanhoCampo], campoComputador[tamanhoCampo];
        int naviosAfundadosHumano[tamanhoCampo], naviosAfundadosComputador[tamanhoCampo];

        if (opcao == 1) {
            int jogarNovamente = 1;
            while (jogarNovamente == 1) {
                for (int i = 0; i < tamanhoCampo; i++) {
                    campoHumano[i] = 7;
                    campoComputador[i] = 7;
                    naviosAfundadosHumano[i] = 0;
                    naviosAfundadosComputador[i] = 0;
                }

                int embarcacoesPosicionadasHumano = 0;
                while (embarcacoesPosicionadasHumano < qtdeEmbarcacoes) {
                    int posicao = rand() % (tamanhoCampo - 1);
                    if (campoHumano[posicao] == 7 && campoHumano[posicao + 1] == 7) {
                        campoHumano[posicao] = 1;
                        campoHumano[posicao + 1] = 1;
                        embarcacoesPosicionadasHumano++;
                    }
                }

                int embarcacoesPosicionadasComputador = 0;
                while (embarcacoesPosicionadasComputador < qtdeEmbarcacoes) {
                    int posicao = rand() % (tamanhoCampo - 1);
                    if (campoComputador[posicao] == 7 && campoComputador[posicao + 1] == 7) {
                        campoComputador[posicao] = 1;
                        campoComputador[posicao + 1] = 1;
                        embarcacoesPosicionadasComputador++;
                    }
                }

                printf("Embarcacoes posicionadas: Humano = %d, Computador = %d\n", embarcacoesPosicionadasHumano, embarcacoesPosicionadasComputador);

                int vitoriaHumano = 0, vitoriaComputador = 0, pararJogo = 0;

                while (!vitoriaHumano && !vitoriaComputador && !pararJogo) {
                    int bombardeiosRestantes = maxBombardeios;
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
                    printf("\nCampo Inimigo: \n");
                    for (int i = 0; i < tamanhoCampo; i++) {
                        if (esconderInimigo && campoComputador[i] == 1) {
                            printf(" 7 ");
                        } else {
                            printf(" %d ", campoComputador[i]);
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
                    printf("\nSeu turno! Voce tem %d bombardeios restantes.\n", bombardeiosRestantes);
                    while (bombardeiosRestantes > 0) {
                        printf("Escolha uma posicao para bombardear (0 a %d), ou -1 para parar o jogo: ", tamanhoCampo - 1);
                        scanf("%d", &posicaoBombardeio);

                        if (posicaoBombardeio == -1) {
                            printf("Voce escolheu parar o jogo.\n");
                            pararJogo = 1;
                            break;
                        }

                        if (posicaoBombardeio < 0 || posicaoBombardeio >= tamanhoCampo) {
                            printf("Posicao invalida! Tente novamente.\n");
                            continue;
                        }

                        if (campoComputador[posicaoBombardeio] == 0 || campoComputador[posicaoBombardeio] == 2) {
                            printf("A posicao ja foi bombardeada antes. Tente outra.\n");
                            continue;
                        }

                        if (campoComputador[posicaoBombardeio] == 7) {
                            printf("\nAGUA!\n");
                            campoComputador[posicaoBombardeio] = 0;
                        } else if (campoComputador[posicaoBombardeio] == 1) {
                            printf("\nIMPACTO!\n");
                            campoComputador[posicaoBombardeio] = 2;

                            int novosNaviosAfundados = verificarNavioAfundado(campoComputador, tamanhoCampo, naviosAfundadosComputador);
                            if (novosNaviosAfundados > 0) {
                                printf("\nNavio inimigo afundado!\n");
                            }

                            vitoriaHumano = 1;
                            for (int i = 0; i < tamanhoCampo; i++) {
                                if (campoComputador[i] == 1) {
                                    vitoriaHumano = 0;
                                    break;
                                }
                            }

                            if (vitoriaHumano) {
                                printf("\nVoce venceu! O computador perdeu.\n");
                                break;
                            }
                        }
                        bombardeiosRestantes--;
                    }

                    if (!vitoriaHumano) {
                        printf("\nAgora e o turno do computador...\n");
                        for (int i = 0; i < 3; i++) {
                            int posicaoComputador = rand() % tamanhoCampo;
                            while (campoHumano[posicaoComputador] == 0 || campoHumano[posicaoComputador] == 2) {
                                posicaoComputador = rand() % tamanhoCampo;
                            }

                            printf("O computador bombardeou a posicao %d.\n", posicaoComputador);
                            if (campoHumano[posicaoComputador] == 7) {
                                printf("\nAGUA!\n");
                                campoHumano[posicaoComputador] = 0;
                            } else if (campoHumano[posicaoComputador] == 1) {
                                printf("\nIMPACTO!\n");
                                campoHumano[posicaoComputador] = 2;

                                int novosNaviosAfundados = verificarNavioAfundado(campoHumano, tamanhoCampo, naviosAfundadosHumano);
                                if (novosNaviosAfundados > 0) {
                                    printf("\nSeu navio foi afundado!\n");
                                }
                            }

                            vitoriaComputador = 1;
                            for (int i = 0; i < tamanhoCampo; i++) {
                                if (campoHumano[i] == 1) {
                                    vitoriaComputador = 0;
                                    break;
                                }
                            }

                            if (vitoriaComputador) {
                                printf("\nVoce perdeu! O computador venceu.\n");
                                break;
                            }
                        }
                    }
                }

                printf("\nDeseja jogar novamente?\n1. Sim\n2. Voltar ao menu\n3. Sair\n");
                scanf("%d", &jogarNovamente);
                if (jogarNovamente == 3) {
                    continuarJogo = 0;
                    break;
                }
            }
        } else if (opcao == 2) {
            printf("\nConfiguracoes:\n");
            printf("Digite o tamanho do campo (minimo 15): ");
            scanf("%d", &tamanhoCampo);
            if (tamanhoCampo < 15) tamanhoCampo = 15;

            printf("Digite a quantidade de embarcacoes (minimo 1): ");
            scanf("%d", &qtdeEmbarcacoes);
            if (qtdeEmbarcacoes < 1) qtdeEmbarcacoes = 1;

            if (qtdeEmbarcacoes > tamanhoCampo / 2) {
                printf("Aviso: A quantidade de embarcacoes deve ser no maximo a metade do tamanho do campo.\n");
                qtdeEmbarcacoes = tamanhoCampo / 2;
                printf("Quantidade de embarcacoes ajustada para %d.\n", qtdeEmbarcacoes);
            }

        } else if (opcao == 3) {
            continuarJogo = 0;
        } else {
            printf("Opcao invalida!\n");
        }
    }

    return 0;
}
