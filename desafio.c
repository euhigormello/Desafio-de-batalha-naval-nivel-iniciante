#include <stdio.h>

// Tamanho fixo do tabuleiro
#define TAM 10

// Tamanho fixo dos navios
#define NAVIO 3

int main() {
    int tabuleiro[TAM][TAM];

    // Inicializando o tabuleiro com 0 (água)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Vetores representando os navios (3 partes)
    int navioHorizontal[NAVIO] = {3, 3, 3};
    int navioVertical[NAVIO] = {3, 3, 3};

    // Coordenadas iniciais dos navios (definidas no código)
    int linhaH = 2, colunaH = 4;  // Navio horizontal
    int linhaV = 5, colunaV = 7;  // Navio vertical

    // ---- Validação simples ----

    // Validar se navio horizontal cabe no tabuleiro
    if (colunaH + NAVIO > TAM) {
        printf("Erro: navio horizontal fora do tabuleiro!\n");
        return 1;
    }

    // Validar se navio vertical cabe no tabuleiro
    if (linhaV + NAVIO > TAM) {
        printf("Erro: navio vertical fora do tabuleiro!\n");
        return 1;
    }

    // Validar sobreposição
    for (int i = 0; i < NAVIO; i++) {
        if (linhaH == linhaV + i && (colunaH <= colunaV && colunaV < colunaH + NAVIO)) {
            printf("Erro: navios se sobrepõem!\n");
            return 1;
        }
    }

    // ---- Posicionando os navios ----

    // Navio horizontal
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[linhaH][colunaH + i] = navioHorizontal[i];
    }

    // Navio vertical
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[linhaV + i][colunaV] = navioVertical[i];
    }

    // ---- Exibindo o tabuleiro ----
    printf("\nTABULEIRO:\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
