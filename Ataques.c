/* ataques.c  - funções para processar ataques em Batalha Naval */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 10       /* tamanho padrão do tabuleiro (10x10) */
#define MAXNAVIOS 10  /* máximo navios por jogador - */

typedef enum { AGUA=0, NAVIO, ACERTO, ERRO } CelulaEstado;

/* representa posição do navio */
typedef struct {
    int id;            /* id do navio */
    int tam;           /* comprimento */
    int linha;         /* linha inicio (0-index) */
    int coluna;        /* coluna inicio (0-index) */
    bool horizontal;   /* orientação: true -> horizontal, false -> vertical */
    int hits;          /* quantos quadrados já foram atingidos */
    bool colocado;     /* se o navio está posicionado */
} Navio;

/* tabuleiro simples: matriz de estados */
typedef struct {
    CelulaEstado cel[MAXN][MAXN];
    int n; /* dimensão */
    Navio navios[MAXNAVIOS];
    int qtd_navios;
} Tabuleiro;


/* Inicializa tabuleiro vazio */
void inicializa_tabuleiro(Tabuleiro *t, int n) {
    t->n = n;
    t->qtd_navios = 0;
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            t->cel[i][j] = AGUA;
    for (int k=0;k<MAXNAVIOS;k++) {
        t->navios[k].colocado = false;
        t->navios[k].hits = 0;
    }
}

/* Adiciona navio no tabuleiro (sem checar colisões extras aqui) */
bool coloca_navio(Tabuleiro *t, int id, int tam, int linha, int coluna, bool horizontal) {
    /* checar limite */
    if (t->qtd_navios >= MAXNAVIOS) return false;
    if (horizontal) {
        if (coluna + tam > t->n) return false;
    } else {
        if (linha + tam > t->n) return false;
    }
    /* checar sobreposição */
    for (int k=0;k<tam;k++){
        int r = linha + (horizontal?0:k);
        int c = coluna + (horizontal?k:0);
        if (t->cel[r][c] != AGUA) return false;
    }
    /* marcar navio no tabuleiro */
    for (int k=0;k<tam;k++){
        int r = linha + (horizontal?0:k);
        int c = coluna + (horizontal?k:0);
        t->cel[r][c] = NAVIO;
    }
    /* registrar navio */
    Navio nv;
    nv.id = id;
    nv.tam = tam;
    nv.linha = linha;
    nv.coluna = coluna;
    nv.horizontal = horizontal;
    nv.hits = 0;
    nv.colocado = true;
    t->navios[t->qtd_navios++] = nv;
    return true;
}

/* função auxiliar: encontra navio que ocupa a célula (se existir), retorna índice ou -1 */
int encontra_navio_por_celula(Tabuleiro *t, int linha, int coluna){
    for (int i=0;i<t->qtd_navios;i++){
        Navio *nv = &t->navios[i];
        if (!nv->colocado) continue;
        for (int k=0;k<nv->tam;k++){
            int r = nv->linha + (nv->horizontal?0:k);
            int c = nv->coluna + (nv->horizontal?k:0);
            if (r==linha && c==coluna) return i;
        }
    }
    return -1;
}

/* Verifica se navio está afundado */
bool navio_afundado(Navio *nv) {
    return nv->hits >= nv->tam;
}

/* Recebe um ataque na posição (linha, coluna) - 0-index
   Retorna:
     1 -> acerto (hit) e navio afundou
     2 -> acerto (hit) mas não afundou
     0 -> água (miss)
    -1 -> inválido (fora do tabuleiro) ou já atacado
*/
int processa_ataque(Tabuleiro *t, int linha, int coluna){
    if (linha < 0 || coluna < 0 || linha >= t->n || coluna >= t->n) return -1;

    CelulaEstado estado = t->cel[linha][coluna];

    if (estado == ACERTO || estado == ERRO) {
        return -1; /* já atacado */
    }

    if (estado == NAVIO) {
        /* marcar acerto */
        t->cel[linha][coluna] = ACERTO;
        int idx = encontra_navio_por_celula(t, linha, coluna);
        if (idx >= 0) {
            t->navios[idx].hits++;
            if (navio_afundado(&t->navios[idx])){
                return 1; /* hit + afundou */
            } else {
                return 2; /* hit só */
            }
        } else {
            /* inconsistente: celula dizia NAVIO mas não encontrou navio */
            return 2;
        }
    } else {
        /* água -> marcar erro (miss) */
        t->cel[linha][coluna] = ERRO;
        return 0;
    }
}

/* Imprime tabuleiro (modo debug: mostra navios e marcações) */
void imprime_tabuleiro_debug(Tabuleiro *t) {
    printf("  ");
    for (int c=0;c<t->n;c++) printf("%d ", c);
    printf("\n");
    for (int r=0;r<t->n;r++){
        printf("%d ", r);
        for (int c=0;c<t->n;c++){
            char ch;
            switch (t->cel[r][c]) {
                case AGUA: ch='.'; break;
                case NAVIO: ch='N'; break;
                case ACERTO: ch='X'; break;
                case ERRO: ch='o'; break;
                default: ch='?'; break;
            }
            printf("%c ", ch);
        }
        printf("\n");
    }
}

/* Exemplo de uso simples (para testar) */
#ifdef TEST_ATAQUES
int main(){
    Tabuleiro t;
    inicializa_tabuleiro(&t, 10);
    coloca_navio(&t, 1, 4, 1, 1, true);  /* navio tamanho 4 em (1,1) horizontal */
    coloca_navio(&t, 2, 3, 4, 4, false); /* navio tamanho 3 em (4,4) vertical */

    imprime_tabuleiro_debug(&t);
    int res;

    res = processa_ataque(&t, 1, 1); printf("Ataque 1,1 -> res = %d\n", res); /* hit */
    res = processa_ataque(&t, 1, 2); printf("Ataque 1,2 -> res = %d\n", res); /* hit */
    res = processa_ataque(&t, 1, 3); printf("Ataque 1,3 -> res = %d\n", res); /* hit */
    res = processa_ataque(&t, 1, 4); printf("Ataque 1,4 -> res = %d\n", res); /* hit -> afunda (se tam 4) */

    res = processa_ataque(&t, 0, 0); printf("Ataque 0,0 -> res = %d\n", res); /* miss */
    imprime_tabuleiro_debug(&t);
    return 0;
}
#endif

// teste de atualização

