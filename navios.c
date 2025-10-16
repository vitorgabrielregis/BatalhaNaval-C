#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10 //tabuleiro 10x10
#define AGUA '~' //símbolo da água
#define  NAVIO 'N' //símbolo do navio

// apenas para debug
// #define AGUA '0' //símbolo da água
// #define  NAVIO '1' //símbolo do navio

#define NUM_NAVIOS 5 //número de navios no tabuleiro

void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    //gera o tabuleiro com água
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    //inicializa o gerador de números aleatórios
    srand(time(NULL));
    for (int n = 0; n < NUM_NAVIOS; n++) {
        int linha, coluna, direcao, tamanho_aleatorio;
        int valido = 0;
        while (!valido) {
            linha = rand() % TAM;
            coluna = rand() % TAM;
            tamanho_aleatorio = (rand() % 3) + 1; //gera de 1 a 3
            direcao = rand() % 2; //0 = horizontal,1 = vertical

            valido = 1;
            if (direcao == 0) { //horizontal
                if (coluna + tamanho_aleatorio > TAM) valido = 0;
                else {
                    for (int i = 0; i < tamanho_aleatorio; i++) {
                        if (tabuleiro[linha][coluna + i] == NAVIO) {
                            valido = 0;
                            break;
                        }
                    }
                }
            } else { //vertical
                if (linha + tamanho_aleatorio > TAM) valido = 0;
                else {
                    for (int i = 0; i < tamanho_aleatorio; i++) {
                        if (tabuleiro[linha + i][coluna] == NAVIO) {
                            valido = 0;
                            break;
                        }
                    }
                }
            }
        }
        //posiciona o navio
        if (direcao == 0) { //horizontal
            for (int i = 0; i < tamanho_aleatorio; i++) {
                tabuleiro[linha][coluna + i] = NAVIO;
            }
        } else { //vertical
            for (int i = 0; i < tamanho_aleatorio; i++) {
                tabuleiro[linha + i][coluna] = NAVIO;
            }
        }
    }
}