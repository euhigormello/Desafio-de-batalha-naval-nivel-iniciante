#include <stdio.h>

// Tamanho fixo do tabuleiro
#define TAM 10

// Tamanho fixo dos navios e das matrizes de habilidade (usar tamanho ímpar para centrar)
#define NAVIO 3
#define HABIL_SIZE 5

// Valores no tabuleiro
#define AGUA 0
#define NAVIO_VAL 3
#define HABIL_VAL 5

// Função para verificar se índice está dentro dos limites do tabuleiro
int dentro(int x, int lim) {
    return x >= 0 && x < lim;
}

int main() {
    int tabuleiro[TAM][TAM];
    int overlay[TAM][TAM]; // marca as áreas de habilidade (1 = afetado)

    // Inicializando tabuleiro (água) e overlay
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
            overlay[i][j] = 0;
        }
    }

    // ------------------ Navios (tamanho fixo NAVIO) ------------------
    int navioH[NAVIO] = {NAVIO_VAL, NAVIO_VAL, NAVIO_VAL}; // horizontal
    int navioV[NAVIO] = {NAVIO_VAL, NAVIO_VAL, NAVIO_VAL}; // vertical

    // Coordenadas iniciais definidas no código
    int lH = 1, cH = 2; // navio horizontal: linha 1, coluna 2
    int lV = 6, cV = 5; // navio vertical: linha 6, coluna 5

    // Validações simples de limites
    if (cH + NAVIO > TAM) {
        printf("Erro: navio horizontal fora do tabuleiro!\n");
        return 1;
    }
    if (lV + NAVIO > TAM) {
        printf("Erro: navio vertical fora do tabuleiro!\n");
        return 1;
    }

    // Posicionando navios no tabuleiro
    for (int i = 0; i < NAVIO; i++) tabuleiro[lH][cH + i] = navioH[i];
    for (int i = 0; i < NAVIO; i++) tabuleiro[lV + i][cV] = navioV[i];

    // ------------------ Matrizes de Habilidade (construídas dinamicamente) ------------------
    // Usaremos HABIL_SIZE x HABIL_SIZE (aqui 5x5) e o centro será HABIL_SIZE/2
    int cone[HABIL_SIZE][HABIL_SIZE];
    int cruz[HABIL_SIZE][HABIL_SIZE];
    int octaedro[HABIL_SIZE][HABIL_SIZE];

    int centro = HABIL_SIZE / 2; // índice central (para HABIL_SIZE=5, centro=2)

    // Construir a matriz CONE (triângulo apontando para baixo)
    // Regra: para cada linha r (0..HABIL_SIZE-1), marque colunas de (centro - r) a (centro + r)
    // dentro dos limites da matriz. Isso cria um "cone" que se expande para baixo.
    for (int r = 0; r < HABIL_SIZE; r++) {
        for (int c = 0; c < HABIL_SIZE; c++) {
            if (c >= centro - r && c <= centro + r) cone[r][c] = 1;
            else cone[r][c] = 0;
        }
    }

    // Construir a matriz CRUZ (linha e coluna centrais)
    for (int r = 0; r < HABIL_SIZE; r++) {
        for (int c = 0; c < HABIL_SIZE; c++) {
            if (r == centro || c == centro) cruz[r][c] = 1;
            else cruz[r][c] = 0;
        }
    }

    // Construir a matriz OCTAEDRO (losango via distância Manhattan)
    // Regra: marque posições cuja distância manhattan ao centro <= centro
    for (int r = 0; r < HABIL_SIZE; r++) {
        for (int c = 0; c < HABIL_SIZE; c++) {
            int dist = (centro - r) >= 0 ? (centro - r) : (r - centro);
            dist += (centro - c) >= 0 ? (centro - c) : (c - centro);
            if (dist <= centro) octaedro[r][c] = 1;
            else octaedro[r][c] = 0;
        }
    }

    // ------------------ Pontos de origem das habilidades no tabuleiro ------------------
    // Defina no código os pontos de origem (linha, coluna) para cada habilidade
    int origem_cone_r = 2, origem_cone_c = 4;
    int origem_cruz_r = 7, origem_cruz_c = 2;
    int origem_octa_r = 4, origem_octa_c = 7;

    // ------------------ Sobrepor matrizes de habilidade ao tabuleiro ------------------
    // Para cada célula da matriz de habilidade com valor 1, calcule a posição correspondente
    // no tabuleiro centralizando pela célula central da matriz de habilidade.

    // Função inline (simulada) para aplicar uma matriz de habilidade ao overlay
    // (não sobrescreve definitvamente o tabuleiro; usa-se overlay para visualização)
    for (int r = 0; r < HABIL_SIZE; r++) {
        for (int c = 0; c < HABIL_SIZE; c++) {
            if (cone[r][c] == 1) {
                int br = origem_cone_r - centro + r;
                int bc = origem_cone_c - centro + c;
                if (dentro(br, TAM) && dentro(bc, TAM)) overlay[br][bc] = 1;
            }
            if (cruz[r][c] == 1) {
                int br = origem_cruz_r - centro + r;
                int bc = origem_cruz_c - centro + c;
                if (dentro(br, TAM) && dentro(bc, TAM)) overlay[br][bc] = 1;
            }
            if (octaedro[r][c] == 1) {
                int br = origem_octa_r - centro + r;
                int bc = origem_octa_c - centro + c;
                if (dentro(br, TAM) && dentro(bc, TAM)) overlay[br][bc] = 1;
            }
        }
    }

    // ------------------ Exibir o tabuleiro com legenda ------------------
    // Decisão de apresentação:
    // - Se apenas água: imprime 0
    // - Se navio (3) sem habilidade: imprime 3
    // - Se habilidade (overlay==1) sem navio: imprime 5
    // - Se navio e habilidade sobrepostos: imprime 8 (para indicar navio atingido pela habilidade)

    printf("\nTABULEIRO FINAL (0=agua,3=navio,5=area,8=navio+area):\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            int valor = AGUA;
            if (tabuleiro[i][j] == NAVIO_VAL && overlay[i][j] == 1) valor = 8; // navio + area
            else if (tabuleiro[i][j] == NAVIO_VAL) valor = NAVIO_VAL;      // navio
            else if (overlay[i][j] == 1) valor = HABIL_VAL;               // area de habilidade
            else valor = AGUA;                                            // agua

            // Imprime com espaçamento alinhado
            printf("%d ", valor);
        }
        printf("\n");
    }

    // ------------------ Exibição das matrizes de habilidade (opcional para verificação) ------------------
    printf("\nMATRIZ - CONE (1=afetado):\n");
    for (int r = 0; r < HABIL_SIZE; r++) {
        for (int c = 0; c < HABIL_SIZE; c++) printf("%d ", cone[r][c]);
        printf("\n");
    }

    printf("\nMATRIZ - CRUZ (1=afetado):\n");
    for (int r = 0; r < HABIL_SIZE; r++) {
        for (int c = 0; c < HABIL_SIZE; c++) printf("%d ", cruz[r][c]);
        printf("\n");
    }

    printf("\nMATRIZ - OCTAEDRO (1=afetado):\n");
    for (int r = 0; r < HABIL_SIZE; r++) {
        for (int c = 0; c < HABIL_SIZE; c++) printf("%d ", octaedro[r][c]);
        printf("\n");
    }

    return 0;
}
