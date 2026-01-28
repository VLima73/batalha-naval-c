#include <stdio.h>

#define TAM 10
#define AGUA 0
#define NAVIO 3
#define HABIL 5
#define NAVIO_TAM 3
#define HAB_TAM 5

typedef struct {
    int dr;
    int dc;
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

int podePosicionar(int tab[TAM][TAM], int lin, int col, Direcao dir, int tamanho) {
    for (int k = 0; k < tamanho; k++) {
        int r = lin + k * dir.dr;
        int c = col + k * dir.dc;

        if (r < 0 || r >= TAM || c < 0 || c >= TAM) return 0;
        if (tab[r][c] == NAVIO) return 0; // evita sobreposição de navios
    }
    return 1;
}

int posicionarNavio(int tab[TAM][TAM], int lin, int col, Direcao dir, int tamanho) {
    if (!podePosicionar(tab, lin, col, dir, tamanho)) return 0;

    for (int k = 0; k < tamanho; k++) {
        int r = lin + k * dir.dr;
        int c = col + k * dir.dc;
        tab[r][c] = NAVIO;
    }
    return 1;
}

// ---------- HABILIDADES (MATRIZES 5x5) ----------

void zerarHab(int hab[HAB_TAM][HAB_TAM]) {
    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = 0; j < HAB_TAM; j++) {
            hab[i][j] = 0;
        }
    }
}

// Cone (apontando para baixo): topo no meio, abrindo conforme desce
void criarCone(int cone[HAB_TAM][HAB_TAM]) {
    zerarHab(cone);

    int meio = HAB_TAM / 2; // 2 (em 5x5)
    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = meio - i; j <= meio + i; j++) {
            if (j >= 0 && j < HAB_TAM) cone[i][j] = 1;
        }
    }
}

// Cruz: linha do meio e coluna do meio
void criarCruz(int cruz[HAB_TAM][HAB_TAM]) {
    zerarHab(cruz);

    int meio = HAB_TAM / 2;
    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = 0; j < HAB_TAM; j++) {
            if (i == meio || j == meio) cruz[i][j] = 1;
        }
    }
}

// Octaedro/Losango: dist. Manhattan ao centro <= raio
void criarOctaedro(int oct[HAB_TAM][HAB_TAM]) {
    zerarHab(oct);

    int meio = HAB_TAM / 2;
    int raio = HAB_TAM / 2;

    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = 0; j < HAB_TAM; j++) {
            int di = (i > meio) ? (i - meio) : (meio - i);
            int dj = (j > meio) ? (j - meio) : (meio - j);
            int dist = di + dj;

            if (dist <= raio) oct[i][j] = 1;
        }
    }
}

// Sobrepõe habilidade no tabuleiro (marca 5), respeitando limites e sem apagar navio (3)
void aplicarHabilidade(int tab[TAM][TAM], int hab[HAB_TAM][HAB_TAM], int origemLin, int origemCol) {
    int meio = HAB_TAM / 2;

    for (int i = 0; i < HAB_TAM; i++) {
        for (int j = 0; j < HAB_TAM; j++) {
            if (hab[i][j] == 1) {
                int r = origemLin + (i - meio);
                int c = origemCol + (j - meio);

                if (r >= 0 && r < TAM && c >= 0 && c < TAM) {
                    if (tab[r][c] != NAVIO) { // mantém navio
                        tab[r][c] = HABIL;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Direções de navios
    Direcao horizontal = {0, 1};
    Direcao vertical = {1, 0};
    Direcao diag_principal = {1, 1};   // ↘
    Direcao diag_secundaria = {1, -1}; // ↙

    // Navios (FEAT 3)
    if (!posicionarNavio(tabuleiro, 2, 3, horizontal, NAVIO_TAM)) {
        printf("Erro: nao foi possivel posicionar navio horizontal.\n");
        return 1;
    }
    if (!posicionarNavio(tabuleiro, 5, 6, vertical, NAVIO_TAM)) {
        printf("Erro: nao foi possivel posicionar navio vertical.\n");
        return 1;
    }
    if (!posicionarNavio(tabuleiro, 1, 1, diag_principal, NAVIO_TAM)) {
        printf("Erro: nao foi possivel posicionar navio diagonal principal.\n");
        return 1;
    }
    if (!posicionarNavio(tabuleiro, 0, 9, diag_secundaria, NAVIO_TAM)) {
        printf("Erro: nao foi possivel posicionar navio diagonal secundaria.\n");
        return 1;
    }

    // Habilidades (FEAT 4)
    int cone[HAB_TAM][HAB_TAM];
    int cruz[HAB_TAM][HAB_TAM];
    int oct[HAB_TAM][HAB_TAM];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(oct);

    // Pontos de origem no tabuleiro (centro da habilidade)
    aplicarHabilidade(tabuleiro, cone, 3, 3); // cone no ponto (3,3)
    aplicarHabilidade(tabuleiro, cruz, 7, 2); // cruz no ponto (7,2)
    aplicarHabilidade(tabuleiro, oct, 6, 8);  // octaedro no ponto (6,8)

    imprimirTabuleiro(tabuleiro);
    return 0;
}
