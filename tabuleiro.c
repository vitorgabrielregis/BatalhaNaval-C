#include <stdio.h>
#include "navios.c"
#include <windows.h>


void montarTabuleiroJogador(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

void mostrarTabuleiroJogador(char tabuleiro[TAM][TAM]) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79);
    printf("============================\n");
    printf("  x  | a b c d e f g h i j |\n");
    printf("-----|---------------------|");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("\n");

    for (int linha = 0; linha < TAM; linha++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
        if (linha < 9) {
            printf(" ");
        }
        printf(" %d  | ", linha + 1);
        
        for (int coluna = 0; coluna < TAM; coluna++) {
            switch (tabuleiro[linha][coluna]) {
                case 'X':
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                    break;
                case '!':
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    break;
                case '~':
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
                    break;
            }
            printf("%c ", tabuleiro[linha][coluna]);
                
        }
        printf("|\n");
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79);
    printf("============================\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void tentativaAcerto(char tabuleiro[TAM][TAM], char tabuleiroJogador[TAM][TAM]) {
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
                printf("Agua...\n");
            } else {
                tabuleiroJogador[numero][indice_letra] = '!';
                printf("Acerto!\n");
            }
        }
    }
}