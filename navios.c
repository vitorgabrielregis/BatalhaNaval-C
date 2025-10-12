#include <stdio.h>
#include <stdlib.h>

#define TAM 10 //tabuleiro 10x10
#define AGUA '~' //símbolo da água
#define  NAVIO 'N' //símbolo do navio

void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i   <TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}