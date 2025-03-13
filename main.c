#include <stdio.h>
#include <string.h>
#include <locale.h>

#define TAM 3

typedef struct {
    char nome[50];
    char simbolo;
} Jogador;

void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

void mostrarTabuleiro(char tabuleiro[TAM][TAM]) {
    printf("\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < TAM - 1) printf("|");
        }
        printf("\n");
        if (i < TAM - 1) printf("---|---|---\n");
    }
    printf("\n");
}

int verificarVencedor(char tabuleiro[TAM][TAM], char simbolo) {
    for (int i = 0; i < TAM; i++) {
        if (tabuleiro[i][0] == simbolo && tabuleiro[i][1] == simbolo && tabuleiro[i][2] == simbolo) return 1;
        if (tabuleiro[0][i] == simbolo && tabuleiro[1][i] == simbolo && tabuleiro[2][i] == simbolo) return 1;
    }
    if (tabuleiro[0][0] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][2] == simbolo) return 1;
    if (tabuleiro[0][2] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][0] == simbolo) return 1;
    return 0;
}

int tabuleiroCheio(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == ' ') return 0;
        }
    }
    return 1;
}

int jogadaValida(char tabuleiro[TAM][TAM], int linha, int coluna) {
    return linha >= 1 && linha <= TAM && coluna >= 1 && coluna <= TAM && tabuleiro[linha - 1][coluna - 1] == ' ';
}

void jogar(Jogador jogador, char tabuleiro[TAM][TAM]) {
    int linha, coluna;
    do {
        printf("%s (%c), digite linha e coluna (1-3): ", jogador.nome, jogador.simbolo);
        scanf("%d %d", &linha, &coluna);
        if (!jogadaValida(tabuleiro, linha, coluna)) {
            printf("Posição inválida, tente novamente!\n");
        }
    } while (!jogadaValida(tabuleiro, linha, coluna));
    tabuleiro[linha - 1][coluna - 1] = jogador.simbolo;
}

int main() {

         setlocale(LC_ALL, "Portuguese_Brazil");
    
    Jogador jogador1, jogador2;
    char tabuleiro[TAM][TAM];
    int turno = 0;

    printf("Digite o nome do Jogador 1: ");
    scanf("%s", jogador1.nome);
    jogador1.simbolo = 'X';
    
    printf("Digite o nome do Jogador 2: ");
    scanf("%s", jogador2.nome);
    jogador2.simbolo = 'O';

    inicializarTabuleiro(tabuleiro);
    
    while (1) {
        mostrarTabuleiro(tabuleiro);
        Jogador jogadorAtual = (turno % 2 == 0) ? jogador1 : jogador2;
        jogar(jogadorAtual, tabuleiro);
        
        if (verificarVencedor(tabuleiro, jogadorAtual.simbolo)) {
            mostrarTabuleiro(tabuleiro);
            printf("Parabéns, %s! Você venceu!\n", jogadorAtual.nome);
            break;
        }
        
        if (tabuleiroCheio(tabuleiro)) {
            mostrarTabuleiro(tabuleiro);
            printf("O jogo empatou!\n");
            break;
        }
        
        turno++;
    }
    
    return 0;
}