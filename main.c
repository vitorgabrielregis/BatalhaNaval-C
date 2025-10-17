#include <stdio.h>
#include "tabuleiro.c"

int main() {
    
    printf("Tabuleiro inicializado!\n");
    
    char tabuleiro[TAM][TAM];
    setupTabuleiroComNavios(tabuleiro);
    
    char tabuleiroJogador[TAM][TAM];
    montarTabuleiroJogador(tabuleiroJogador);
    
    while (1)
    {   
        mostrarTabuleiroJogador(tabuleiroJogador);
        tentativaAcerto(tabuleiro, tabuleiroJogador);
    }
    return 0;
}