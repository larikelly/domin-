#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int jogarPeca ();


int comprarPeca();


int passarVez(tPecaDomino maoJogador, tPecaDomino lado) {
    if (maoJogador.lado_esquerdo != lado.lado_direito && maoJogador.lado_direito != lado.lado_esquerdo) {
        printf("Você não pode jogar essa peça. Passe a vez.\n");
        return 1; 
    }
    printf("Você jogou uma peça!\n");
    return 0;  
}

void erro{
	printf("\n404 - ERRO... =/\n");
	exit(1);
}

void Sair() {
    printf("Encerrando o jogo...\n");
    exit(EXIT_SUCCESS); 
}