#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.c"
#include <time.h>

// verifica se ainda tem navios no tabuleiro inimigo
int verificarVitoria(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == NAVIO) {
                return 0; // ainda há navios
            }
        }
    }
    return 1; // nenhum navio restante
}

int main() {
    srand(time(NULL)); //gera números aleatórios a cada execução
    printf("BATALHA NAVAL\n");

    // tabuleiros com os navios
    char tabuleiro1[TAM][TAM];
    char tabuleiro2[TAM][TAM];

    // tabuleiros que mostram os tiros
    char visivel1[TAM][TAM];
    char visivel2[TAM][TAM];

    // inicializa tudo
    setupTabuleiroComNavios(tabuleiro1);
    setupTabuleiroComNavios(tabuleiro2);
    montarTabuleiroJogador(visivel1);
    montarTabuleiroJogador(visivel2);

    int turno = 1; // começa com o jogador 1

    while (1) {
        printf("   VEZ DO JOGADOR %d\n", turno);

        if (turno == 1) {
            mostrarTabuleiroJogador(tabuleiro1);
            mostrarTabuleiroJogador(visivel1);
            tentativaAcerto(tabuleiro1, visivel1);

            if (verificarVitoria(tabuleiro1)) {
                printf("\nJogador 1 ganhou!\n");
                break;
            }

            turno = 2; // passa a vez
        } else {
            mostrarTabuleiroJogador(visivel2);
            tentativaAcerto(tabuleiro2, visivel2);

            if (verificarVitoria(tabuleiro2)) {
                printf("\nJogador 2 ganhou!\n");
                break;
            }

            turno = 1; // volta pra o jogador 1
        }

        printf("\nPressione ENTER pra prosseguir...");
        getchar();
        system("cls || clear"); // limpa tela (windows ou linux)
    }

    printf("\nFim do jogo!\n");
    return 0;
}
