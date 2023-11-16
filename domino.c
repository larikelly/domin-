#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PECAS 28 
#define MAX_PECAS 7

typedef struct {
    int lado_esquerdo;
    int lado_direito;
} tPecaDomino;

void criarPecas(pedra pecas[]) {
    int index = 0;
    for (int i = 0; i <= 6; i++) {
        for (int j = i; j <= 6; j++) {
            pecas[index].pEsquerda = i;
            pecas[index].pDireita = j;
            index++;
        }
    }
}

void imprimirPecas(pedra pecas[]) {
    printf("Peças de dominó:\n");
    for (int i = 0; i < 28; i ++) {
        printf("\n[%d|%d] ", pecas[i].pEsquerda, pecas[i].pDireita);
    }
}

void embaralharPecas(tPecaDomino pecas[], int numPecas = NUM_PECAS) {
    srand(time(NULL));

    for (int i = 0; i < numPecas; i++) {
        int randIndex = rand() % numPecas;

        tPecaDomino temp = pecas[i];
        pecas[i] = pecas[randIndex];
        pecas[randIndex] = temp;
    }
}

void distribuirPecas(tPecaDomino pecas[], int numPecas = MAX_PECAS, tPecaDomino jogador1[], tPecaDomino jogador2[]) {
    for (int i = 0; i < 7; i++) {
        if (i % 2 == 0) {
            jogador1[i / 2] = pecas[i];
        } else {
            jogador2[i / 2] = pecas[i];
        }
    }
}
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

    else if (somaJogador1 > somaJogador2) {
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


