#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define NUM_PECAS 28
#define MAX_PECAS 7

typedef struct {
    int lado_esquerdo;
    int lado_direito;
} tPecaDomino;

int somarPecasJogador1(tPecaDomino jogador1[]) {
    int soma = 0;
    for (int i = 0; i < MAX_PECAS; i++) {
        soma += jogador1[i].lado_esquerdo + jogador1[i].lado_direito;
    }
    return soma;
}

int somarPecasJogador2(tPecaDomino jogador2[]) {
    int soma = 0;
    for (int i = 0; i < MAX_PECAS; i++) {
        soma += jogador2[i].lado_esquerdo + jogador2[i].lado_direito;
    }
    return soma;
}

bool comparaPeca(tPecaDomino jogador1[], tPecaDomino jogador2[]) {
    if (jogador1[0].lado_esquerdo == jogador1[0].lado_direito) {
        printf("Jogador 1 possui uma dupla mais alta. Jogador 1 inicia.\n");
        return true;
    } else if (jogador2[0].lado_esquerdo == jogador2[0].lado_direito) {
        printf("Jogador 2 possui uma dupla mais alta. Jogador 2 inicia.\n");
        return false;
    }

    int somaJogador1 = somarPecasJogador1(jogador1);
    int somaJogador2 = somarPecasJogador2(jogador2);

    if (somaJogador1 > somaJogador2) {
        printf("A soma das peças do Jogador 1 é: %d\n", somaJogador1);
        printf("Jogador 1 inicia\n");
        return true;
    } else if (somaJogador2 > somaJogador1) {
        printf("A soma das peças do Jogador 2 é: %d\n", somaJogador2);
        printf("Jogador 2 inicia\n");
        return false;
    } else {
        if (jogador1[0].lado_esquerdo > jogador2[0].lado_esquerdo) {
            printf("Jogador 1 inicia (peça de maior número)\n");
            return true;
        } else if (jogador2[0].lado_esquerdo > jogador1[0].lado_esquerdo) {
            printf("Jogador 2 inicia (peça de maior número)\n");
            return false;
        } else {
            printf("Empate total. Jogador 1 inicia por padrão.\n");
            return true;
        }
    }
}

void imprimirPecas(tPecaDomino pecas[], int numPecas) {
    printf("Peças de dominó:\n");
    for (int contador = 0; contador < numPecas; contador++) {
        printf("\n[%d|%d] ", pecas[contador].lado_esquerdo, pecas[contador].lado_direito);
    }
}

void criarPecas(tPecaDomino pecas[]) {
    int index = 0;
    for (int i = 0; i <= 6; i++) {
        for (int j = i; j <= 6; j++) {
            pecas[index].lado_esquerdo = i;
            pecas[index].lado_direito = j;
            index++;
        }
    }
}

void embaralharPecas(tPecaDomino pecas[], int numPecas) {
    srand(time(NULL));

    for (int i = 0; i < numPecas; i++) {
        int randIndex = rand() % numPecas;

        tPecaDomino temp = pecas[i];
        pecas[i] = pecas[randIndex];
        pecas[randIndex] = temp;
    }
}

void distribuirPecas(tPecaDomino pecas[], int numPecas, tPecaDomino jogador1[], tPecaDomino jogador2[]) {
    for (int i = 0; i < MAX_PECAS; i++) {
        jogador1[i] = pecas[i];
        jogador2[i] = pecas[i + MAX_PECAS];
    }
}

int main() {
    tPecaDomino pecas[NUM_PECAS];
    tPecaDomino jogador1[MAX_PECAS];
    tPecaDomino jogador2[MAX_PECAS];

    criarPecas(pecas);
    printf("Peças antes de embaralhar:\n");
    imprimirPecas(pecas, NUM_PECAS);

    embaralharPecas(pecas, NUM_PECAS);
    printf("\nPeças após embaralhar:\n");
    imprimirPecas(pecas, NUM_PECAS);

    distribuirPecas(pecas, NUM_PECAS, jogador1, jogador2);

    printf("\nJogador 1:\n");
    imprimirPecas(jogador1, MAX_PECAS);

    printf("\nJogador 2:\n");
    imprimirPecas(jogador2, MAX_PECAS);

    if (!comparaPeca(jogador1, jogador2)) {
        printf("As somas das peças são iguais. Determinar quem inicia de outra maneira.\n");
    }

    return 0;
}
