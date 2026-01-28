#include <stdio.h>

#define TAM 10
#define AGUA 0
#define NAVIO 3
#define NAVIO_TAM 3

typedef struct {
    int dr; // variação da linha
    int dc; // variação da coluna
} Direcao;

void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tab[i][j] = AGUA;
        }
    }
}

void imprimirTabuleiro(int tab[TAM][TAM]) {
    printf("\nTabuleiro (10x10):\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

// Verifica se é possível posicionar (dentro do tabuleiro e sem sobrepor navio)
int podePosicionar(int tab[TAM][TAM], int lin, int col, Direcao dir, int tamanho) {
    for (int k = 0; k < tamanho; k++) {
        int r = lin + k * dir.dr;
        int c = col + k * dir.dc;

        // 1) limites
        if (r < 0 || r >= TAM || c < 0 || c >= TAM) return 0;

        // 2) sobreposição
        if (tab[r][c] == NAVIO) return 0;
    }
    return 1;
}

// Posiciona o navio se for possível
int posicionarNavio(int tab[TAM][TAM], int lin, int col, Direcao dir, int tamanho) {
    if (!podePosicionar(tab, lin, col, dir, tamanho)) return 0;

    for (int k = 0; k < tamanho; k++) {
        int r = lin + k * dir.dr;
        int c = col + k * dir.dc;
        tab[r][c] = NAVIO;
    }
    return 1;
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Direções
    Direcao horizontal = {0, 1};
    Direcao vertical = {1, 0};
    Direcao diag_principal = {1, 1};   // ↘
    Direcao diag_secundaria = {1, -1}; // ↙

    // FEAT 2 (mantido): navio horizontal e vertical (com validação + sem sobrepor)
    if (!posicionarNavio(tabuleiro, 2, 3, horizontal, NAVIO_TAM)) {
        printf("Erro: nao foi possivel posicionar navio horizontal.\n");
        return 1;
    }

    if (!posicionarNavio(tabuleiro, 5, 6, vertical, NAVIO_TAM)) {
        printf("Erro: nao foi possivel posicionar navio vertical.\n");
        return 1;
    }

    // FEAT 3: adicionar navios diagonais e evitar sobreposição
    if (!posicionarNavio(tabuleiro, 1, 1, diag_principal, NAVIO_TAM)) {
        printf("Erro: nao foi possivel posicionar navio diagonal principal.\n");
        return 1;
    }

    if (!posicionarNavio(tabuleiro, 0, 9, diag_secundaria, NAVIO_TAM)) {
        printf("Erro: nao foi possivel posicionar navio diagonal secundaria.\n");
        return 1;
    }

    imprimirTabuleiro(tabuleiro);
    return 0;
}
