
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10 //tabuleiro 10x10
#define AGUA '~' //símbolo da água
#define  NAVIO 'N' //símbolo do navio

#define NUM_NAVIOS 5 //número de navios no tabuleiro

void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i   <TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

//parte dos navios!!
int podeColocar(char tabuleiro[TAM][TAM], int linha, int coluna, int tamanho, char direcao) {
    if (direcao == 'H') {
        if (coluna + tamanho > TAM) return 0;
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha][coluna + i] != AGUA) return 0;
        }
    } else {
        return 0;
    }
    return 1;
}
//colocando os navios no tabuleiro
void colocarNavio(char tabuleiro[TAM][TAM], int linha, int coluna, int tamanho, char direcao) {
    if (direcao == 'H') {
        for  (int i = 0; i < tamanho; i++) tabuleiro[linha][coluna + i] = NAVIO;
    } else {
        for (int i = 0; i < tamanho; i++) tabuleiro[linha + i][coluna] = NAVIO;
    }
}
//colocando os navios automaticamente
void posicionarNaviosAutomatico(char tabuleiro[TAM][TAM]) {
    int tamanhos[] = {4, 3, 3, 2, 2};
    int numNavios = 5;

    srand(time(NULL)); //gera números aleatórios a cada execução

    for (int n = 0; n < numNavios; n++) {
        int linha, coluna;
        char direcao;

        do {
            linha = rand() % TAM;
            coluna = rand() % TAM;
            direcao = (rand() % 2 == 0) ? 'H' : 'V'; // H:horizontal V:vertical
        } while (!podeColocar(tabuleiro, linha, coluna, tamanhos[n], direcao));

        colocarNavio(tabuleiro, linha, coluna, tamanhos[n], direcao);
    }
}

void setupTabuleiroComNavios(char tabuleiro[TAM][TAM]) {
    inicializarTabuleiro(tabuleiro);
    posicionarNaviosAutomatico(tabuleiro);
}