#include <stdio.h>
#include "navios.c"

int main() {
    
    printf("Tabuleiro inicializado!\n");
    
    
    char tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);
    // vai mostrar os navios (PARA TESTE APENAS)
    // printf("========================\n");
    // printf(" x  |a b c d e f g h i j\n");
    // printf("----|-------------------\n");
    // for (int linha = 0; linha < TAM; linha++) {
    //     if (linha < 9) {
    //         printf(" ");
    //     }
    //     printf("%d  |", linha + 1);
    //     for (int coluna = 0; coluna < TAM; coluna++) {
    //         printf("%c ", tabuleiro[linha][coluna]);
    //     }
    //     printf("\n");
    // }
    char tabuleiroJogador[TAM][TAM];
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiroJogador[i][j] = AGUA;
        }
    }
    while (1)
    {   
        printf("========================\n");
        printf(" x  |a b c d e f g h i j\n");
        printf("----|-------------------\n");
        for (int linha = 0; linha < TAM; linha++) {
            if (linha < 9) {
                printf(" ");
            }
            printf("%d  |", linha + 1);
            for (int coluna = 0; coluna < TAM; coluna++) {
                printf("%c ", tabuleiroJogador[linha][coluna]);
            }
            printf("\n");
        }
        printf("Digite a linha e coluna (Ex.: 3 d, 5 c, 7 a...):");
        int numero;
        char letra;
        scanf("%d %c", &numero, &letra);
        numero -= 1;
        getchar();
        int indice_letra = letra - 'a';
        if (numero > TAM - 1 || numero < 0) {
            printf("Linha invalida.\n");
        } else {
            if (indice_letra > TAM - 1) {
                printf("Coluna invalida.\n");
            } else {
                if (tabuleiro[numero][indice_letra] != 'N') {
                    tabuleiroJogador[numero][indice_letra] = 'X';
                    printf("Nenhum acerto.\n");
                } else {
                    tabuleiroJogador[numero][indice_letra] = '!';
                    printf("Acerto!\n");
                }
            }
        }
        
        
    }
    return 0;
}