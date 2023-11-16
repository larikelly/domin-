#include <stdio.h>
#include <game.h>

// Declaração de funções
void Inicio();
void PeçasMãoJogador1();
void PeçasMãoJogador2();
void QntPeças();
void PeçasIndisponiveis();
void Sair();

int main() {
    int escolha;
    printf ("JOGO DE DOMINÓ")
    printf ("Vamos Iniciar")
    printf("Qual operacao voce deseja realizar?\n");
    printf("1-Iniciar\n2-Peças na mão Jogador 01\n3-Peças na mão Jogador 02\n4-Quantidades de peças\n5-Peças Já Jogadas\n6-Sair\n");
    scanf(" %d", &escolha);

    switch (escolha) {
        case 1:
            Inicio();
            break;
        case 2: 
            PeçasMãoJogador1();
            break;
        case 3:
            PeçasMãoJogador2();
            break;
        case 4:
            QntPeças();
            break;
        case 5:
            PeçasIndisponiveis();
            break; 
        case 6:
            Sair();
            break;
        default:
            printf("Selecione uma opcao valida.");
            break;
    }

    return 0;
}
