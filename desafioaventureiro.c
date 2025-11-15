#include <stdio.h>

// Tamanho fixo do tabuleiro
#define TAM 10

// Tamanho fixo dos navios
#define NAVIO 3

// Função para verificar se uma posição já está ocupada
int ocupado(int tabuleiro[TAM][TAM], int linha, int coluna) {
    return tabuleiro[linha][coluna] != 0;
}

int main() {
    int tabuleiro[TAM][TAM];

    // Inicializando o tabuleiro com 0 (água)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // Navios (tamanho fixo 3)
    int navio1[NAVIO] = {3, 3, 3}; // horizontal/vertical
    int navio2[NAVIO] = {3, 3, 3}; // horizontal/vertical
    int navioDiag1[NAVIO] = {3, 3, 3}; // diagonal
    int navioDiag2[NAVIO] = {3, 3, 3}; // diagonal

    // Coordenadas iniciais
    int l1 = 1, c1 = 2; // horizontal
    int l2 = 6, c2 = 5; // vertical
    int ld1 = 0, cd1 = 0; // diagonal principal
    int ld2 = 2, cd2 = 7; // diagonal secundária

    // ----- Validação -----

    // Navio horizontal (navio1)
    if (c1 + NAVIO > TAM) {
        printf("Erro: navio horizontal fora do tabuleiro!
");
        return 1;
    }

    // Navio vertical (navio2)
    if (l2 + NAVIO > TAM) {
        printf("Erro: navio vertical fora do tabuleiro!
");
        return 1;
    }

    // Navio diagonal principal (navioDiag1)
    if (ld1 + NAVIO > TAM || cd1 + NAVIO > TAM) {
        printf("Erro: navio diagonal principal fora do tabuleiro!
");
        return 1;
    }

    // Navio diagonal secundária (navioDiag2)
    if (ld2 + NAVIO > TAM || cd2 - (NAVIO - 1) < 0) {
        printf("Erro: navio diagonal secundária fora do tabuleiro!
");
        return 1;
    }

    // ----- Validação de sobreposição -----

    // Percorrer todas as posições que os navios ocuparão
    for (int i = 0; i < NAVIO; i++) {
        if (ocupado(tabuleiro, l1, c1 + i) ||
            ocupado(tabuleiro, l2 + i, c2) ||
            ocupado(tabuleiro, ld1 + i, cd1 + i) ||
            ocupado(tabuleiro, ld2 + i, cd2 - i)) {
            printf("Erro: navios se sobrepõem!
");
            return 1;
        }
    }

    // ----- Posicionamento -----

    // Horizontal
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[l1][c1 + i] = navio1[i];
    }

    // Vertical
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[l2 + i][c2] = navio2[i];
    }

    // Diagonal principal
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[ld1 + i][cd1 + i] = navioDiag1[i];
    }

    // Diagonal secundária
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[ld2 + i][cd2 - i] = navioDiag2[i];
    }

    // ----- Exibir Tabuleiro -----
    printf("
TABULEIRO COMPLETO:

");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("
");
    }

    return 0;
}
