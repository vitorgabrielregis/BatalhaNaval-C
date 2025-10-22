#include <stdio.h>
#include "tabuleiro.c"

int main() {
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
            mostrarTabuleiroJogador(visivel1);
            tentativaAcerto(tabuleiro2, visivel1);

            if (verificarVitoria(tabuleiro2)) {
                printf("\n Jogador 1 ganhou! \n");
                break;
            }

            turno = 2; // passa a vez
        } else {
            mostrarTabuleiroJogador(visivel2);
            tentativaAcerto(tabuleiro1, visivel2);

            if (verificarVitoria(tabuleiro1)) {
                printf("\n*** Jogador 2 ganhou!!! ***\n");
                break;
            }

            turno = 1; // volta pra o jogador 1
        }

        printf("\nPressione ENTER pra prosseguir...");
        getchar();
        system("cls || clear"); // limpa tela (windows ou linux)
    }

    printf("\nFim do jogo\n");
    return 0;
}
