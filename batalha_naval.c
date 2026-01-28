#include <stdio.h>

#define TAM 10
#define AGUA 0
#define NAVIO 3
#define NAVIO_TAM 3

int main() {
    int tabuleiro[TAM][TAM];

    // 1. Inicializa o tabuleiro com água (0)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // 2. Posiciona navio horizontal
    int linha_h = 2;
    int coluna_h = 3;

    if (coluna_h + NAVIO_TAM <= TAM) {
        for (int i = 0; i < NAVIO_TAM; i++) {
            tabuleiro[linha_h][coluna_h + i] = NAVIO;
        }
    }

    // 3. Posiciona navio vertical
    int linha_v = 5;
    int coluna_v = 6;

    if (linha_v + NAVIO_TAM <= TAM) {
        for (int i = 0; i < NAVIO_TAM; i++) {
            tabuleiro[linha_v + i][coluna_v] = NAVIO;
        }
    }

    // 4. Exibe o tabuleiro
    printf("Tabuleiro de Batalha Naval (Navios Horizontal e Vertical):\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
