#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct peca {
    int e, d;
} peca;

typedef struct pecas_disponiveis {
    peca pecas[28];
    int idx;
    int qtd;
} pecas_disponiveis;

typedef struct estado {
    pecas_disponiveis mesa, pd, jogador1, jogador2;
    int jogador_da_vez;
} estado;

// #define max(a,b) ()
// int max(int a, int  b) {
//     return a >= b? a: b;
// }
#define max(a,b) (((a) > (b)) ? (a) : (b))

int dupla_mais_alta(pecas_disponiveis mao) {
    int maior = -1;
    int idx = -1;
    for (int i = mao.idx; i < mao.idx + mao.qtd; ++i) {
        if (mao.pecas[i].e == mao.pecas[i].d && mao.pecas[i].e > maior)  {
            maior = mao.pecas[i].e;
            idx = i;
        }
    }
    return idx;
}

int maior_soma(pecas_disponiveis jogador1, pecas_disponiveis jogador2) {
    int soma1 = -1, soma2 = -1;
    for (int i = jogador1.idx; i < jogador1.idx + jogador1.qtd; ++i) {
        if (jogador1.pecas[i].e+jogador1.pecas[i].d > soma1)
            soma1 = jogador1.pecas[i].e + jogador1.pecas[i].d;
    }
    for (int i = jogador2.idx; i < jogador2.idx + jogador2.qtd; ++i) {
        if (jogador2.pecas[i].e+jogador2.pecas[i].d > soma2){
            soma2 = jogador2.pecas[i].e + jogador2.pecas[i].d;
        }
    }
    if (soma1 == soma2) return -1;
    if (soma1 > soma2) return 1;
    return 2;
}

int maior_numero (pecas_disponiveis jogador1, pecas_disponiveis jogador2) {
    int maior1 = -1, maior2 = -1;
    for (int i = jogador1.idx; i < jogador1.idx + jogador1.qtd; ++i) {
        if (max(jogador1.pecas[i].e, jogador1.pecas[i].d) > maior1)
            maior1 = max(jogador1.pecas[i].e, jogador1.pecas[i].d);
    }
    for (int i = jogador2.idx; i < jogador2.idx + jogador2.qtd; ++i) {
        if (max(jogador2.pecas[i].e, jogador2.pecas[i].d) > maior2){
            maior2 = max(jogador2.pecas[i].e, jogador2.pecas[i].d);
        }
    }
    if (maior1 > maior2) return 1;
    return 2;
}

int primeiro_a_jogar(pecas_disponiveis jogador1, pecas_disponiveis jogador2) {
    int dupla1 = dupla_mais_alta(jogador1);
    int dupla2 = dupla_mais_alta(jogador2);

    if (dupla1 == -1 && dupla2 == -1) {
        int soma = maior_soma(jogador1, jogador2);
        if (soma == -1) {
            return maior_numero(jogador1, jogador2);
        }
    }
    else if (dupla1 == -1)  return 2;
    else if (dupla2 == -1)  return 1;
    else {
        if (jogador1.pecas[dupla1].e > jogador2.pecas[dupla2].e) return 1;
        else return 2;
    }
}

pecas_disponiveis pd;
pecas_disponiveis mesa;
pecas_disponiveis jogador1, jogador2;
pecas_disponiveis jogador[2];
int jogador_da_vez;
int carregado;

void imprime_mao(pecas_disponiveis jogador) {
    for (int i = jogador.idx; i < jogador.idx + jogador.qtd; ++i) {
        printf(" [%d|%d]", jogador.pecas[i].e, jogador.pecas[i].d);
    }
    printf("\n\n");
}

int eh_possivel(peca p) {
    if (mesa.qtd == 0) return 1;
    if (mesa.pecas[mesa.idx].e == p.d || mesa.pecas[mesa.idx].e == p.e)
        return 1;
    if (mesa.pecas[mesa.idx + mesa.qtd - 1].d == p.d || mesa.pecas[mesa.idx + mesa.qtd - 1].d == p.e)
        return 1;
    return 0;
}

int imprime_pecas_possiveis(pecas_disponiveis jogador) {
    int q = 0;
    
    for (int i = jogador.idx; i < jogador.idx + jogador.qtd; ++i) {
        if (eh_possivel(jogador.pecas[i])) {
            q++;
            if (q == 1) {
                printf("Pecas Disponiveis para jogar: \n");
            }
            printf(" [%d|%d], indice = %d\n", jogador.pecas[i].e, jogador.pecas[i].d, i);
        }
    }
    printf("\n\n");
    return q;
}

void compra(pecas_disponiveis *jogador) {
    //retira peca da primeira posicao de pd 
    // e insere na ultima posicao de jogador
    if (pd.qtd == 0) return;
    printf("Comprando peca [%d|%d]\n", pd.pecas[pd.idx].e, pd.pecas[pd.idx].d);
    jogador->pecas[jogador->idx + jogador->qtd] = pd.pecas[pd.idx];
    jogador->qtd++;
    pd.qtd--;
    pd.idx++;
}

void insere(peca p, int ponta) {
    if (ponta == 0) {
        if (p.d != mesa.pecas[mesa.idx].e) {
            int aux = p.d;
            p.d = p.e;
            p.e = aux;
        }
        int i = mesa.idx + mesa.qtd;
        while (i > mesa.idx) {
            mesa.pecas[i] = mesa.pecas[i-1];
            i--;
        }
        mesa.pecas[mesa.idx] = p;
    }   
    else {
        if (p.e != mesa.pecas[mesa.idx + mesa.qtd - 1].d) {
            int aux = p.d;
            p.d = p.e;
            p.e = aux;
        }
        mesa.pecas[mesa.idx + mesa.qtd] = p;
    }
    mesa.qtd++;
}

void jogada(pecas_disponiveis *jogador) {
    printf("Digite o indice da peca que deseja jogar: "); 
    int indice;
    scanf("%d", &indice);
    if (mesa.qtd == 0) {
        mesa.pecas[mesa.idx] = jogador->pecas[indice];
        mesa.qtd++;
    }
    else if (mesa.pecas[mesa.idx].e == mesa.pecas[mesa.idx + mesa.qtd - 1].d) {
        printf("Digite a ponta que deseja inserir a peca (E ou D): ");
        char ponta;
        scanf("%c", &ponta);
        scanf("%c", &ponta);
        if (ponta == 'E')
            insere(jogador->pecas[indice], 0);
        else
            insere(jogador->pecas[indice], 1);
    }
    else {
        if (mesa.pecas[mesa.idx].e == jogador->pecas[indice].e || 
            mesa.pecas[mesa.idx].e == jogador->pecas[indice].d) {
            insere(jogador->pecas[indice], 0);
        }
        else {
            insere(jogador->pecas[indice], 1);
        }
    }
    for (int i = indice; i < jogador->idx + jogador->qtd - 1; ++i)
        jogador->pecas[i] = jogador->pecas[i+1];
    jogador->qtd--;
    printf("\n");
}

void imprime_mesa() {
    if (mesa.qtd == 0) {
        return;
    }
    printf("Mesa: ");
    for (int i = mesa.idx; i < mesa.idx + mesa.qtd; ++i) {
        printf("[%d|%d]", mesa.pecas[i].e, mesa.pecas[i].d);
    }
    printf("\n");
}


void comeca_jogo () {
    if (!carregado) {

        pd.idx = 0;
        pd.qtd = 0;
        mesa.qtd = 0;
        mesa.idx = 0;
        for (int i = 0; i < 7; ++i)
            for (int j = i; j < 7; ++j) {
                pd.pecas[pd.qtd].e = i;
                pd.pecas[pd.qtd].d = j;
                pd.qtd++;
            }
        //embaralhar pecas
        for (int i = 0; i < 1000; ++i) {
            int k = rand() % 28;
            int l = rand() % 28;
            peca aux = pd.pecas[k];
            pd.pecas[k] = pd.pecas[l];
            pd.pecas[l] = aux;
        }
        
        printf("Jogador 1 deve comprar 7 pecas: ");
        jogador1.idx = jogador1.qtd = 0;
        jogador2.idx = jogador2.qtd = 0;
        for (int i = 0; i < 7; ++i) {
            jogador1.pecas[i] = pd.pecas[pd.idx];
            pd.idx++;
            pd.qtd--;
            jogador1.qtd++;
        }
        printf("Jogador 2 deve comprar 7 pecas: ");
        for (int i = 0; i < 7; ++i) {
            jogador2.pecas[i] = pd.pecas[pd.idx];
            pd.idx++;
            pd.qtd--;
            jogador2.qtd++;
        }
        jogador_da_vez = primeiro_a_jogar(jogador1, jogador2);
    }
    
    printf("Pecas do jogador 1:");
    for (int i = jogador1.idx; i < jogador1.idx + jogador1.qtd; ++i) {
        printf(" [%d|%d]", jogador1.pecas[i].e, jogador1.pecas[i].d);
    }
    printf("\n\n");
    printf("Pecas do jogador 2:");
    for (int i = jogador2.idx; i < jogador2.idx + jogador2.qtd; ++i) {
        printf(" [%d|%d]", jogador2.pecas[i].e, jogador2.pecas[i].d);
    }
    printf("\n\n");
    
    
    jogador[0] = jogador1;
    jogador[1] = jogador2;
    while (1) {
        printf("Vez de Jogador %d\n", jogador_da_vez);
        imprime_mesa();
        printf("Mao do jogador %d\n", jogador_da_vez);
        imprime_mao(jogador[jogador_da_vez-1]);
        printf("Quantidade de pecas disponiveis para compra: %d\n", pd.qtd);
        printf("Quantiade de pecas na mao do adversario: %d\n", jogador[3 - jogador_da_vez-1].qtd);
        int q_pecas = imprime_pecas_possiveis(jogador[jogador_da_vez-1]);
        printf("1 - Continuar jogando\n");
        printf("2 - Salvar estado\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao acima: ");
        int opcao;
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            break;
        case 2:
            printf("Digite o nome do arquivo: ");
            char arquivo[200];
            scanf("%s", arquivo);
            FILE *f = fopen(arquivo, "w");
            fprintf(f, "%d\n", mesa.qtd);
            for (int i = mesa.idx; i < mesa.idx + mesa.qtd; ++i) {
                fprintf(f, "%d\n%d\n", mesa.pecas[i].e, mesa.pecas[i].d);
            }
            fprintf(f, "%d\n", pd.qtd);
            for (int i = pd.idx; i < pd.idx + pd.qtd; ++i) {
                fprintf(f, "%d\n%d\n", pd.pecas[i].e, pd.pecas[i].d);
            }
            fprintf(f, "%d\n", jogador[0].qtd);
            for (int i = jogador[0].idx; i < jogador[0].idx + jogador[0].qtd; ++i) {
                fprintf(f, "%d\n%d\n", jogador[0].pecas[i].e, jogador[0].pecas[i].d);
            }
            fprintf(f, "%d\n", jogador[1].qtd);
            for (int i = jogador[1].idx; i < jogador[1].idx + jogador[1].qtd; ++i) {
                fprintf(f, "%d\n%d\n", jogador[1].pecas[i].e, jogador[1].pecas[i].d);
            }
            fprintf(f, "%d\n", jogador_da_vez);
            fclose(f);
            return;
        case 3:
            return;
        default:
            break;
        }
        if (q_pecas == 0) {
            //comprar
            while (pd.qtd > 0 && q_pecas == 0) {
                compra(&jogador[jogador_da_vez-1]);
                q_pecas = imprime_pecas_possiveis(jogador[jogador_da_vez-1]);
            }
        }
        if (q_pecas != 0) {
            jogada(&jogador[jogador_da_vez-1]);
        }
        else {
            printf("Passando a vez...\n\n");
        }
        if (jogador[jogador_da_vez-1].qtd == 0) {
            printf("Jogador %d venceu!\n", jogador_da_vez);
            break;
        }
        //alterna jogador
        jogador_da_vez = 3 - jogador_da_vez;
        
    }
}

void carrega_jogo(){
    char arquivo[200];
    printf("Digite o caminho do arquivo: ");
    scanf("%s", arquivo);
    FILE *f;
    if ((f = fopen(arquivo, "r")) == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return ;
    }
    fscanf(f, "%d", &mesa.qtd);
    mesa.idx = 0;
    for (int i = 0; i < mesa.qtd; ++i) {
        fscanf(f, "%d%d", &mesa.pecas[i].e, &mesa.pecas[i].d);
    }
    fscanf(f, "%d", &pd.qtd);
    pd.idx = 0;
    for (int i = 0; i < pd.qtd; ++i) {
        fscanf(f, "%d%d", &pd.pecas[i].e, &pd.pecas[i].d);
    }
    fscanf(f, "%d", &jogador1.qtd);
    jogador1.idx = 0;
    for (int i = 0; i < jogador1.qtd; ++i) {
        fscanf(f, "%d%d", &jogador1.pecas[i].e, &jogador1.pecas[i].d);
    }
    fscanf(f, "%d", &jogador2.qtd);
    jogador2.idx = 0;
    for (int i = 0; i < jogador2.qtd; ++i) {
        fscanf(f, "%d%d", &jogador2.pecas[i].e, &jogador2.pecas[i].d);
    }
    fscanf(f, "%d", &jogador_da_vez);
    fclose(f);
    carregado = 1;
    comeca_jogo();
}

void menu_inicial() {
    srand(time(NULL));
    printf("Opcoes: \n");
    printf("1 - Continuar jogo em andamento\n");
    printf("2 - Iniciar novo jogo\n");
    printf("3 - Sair\n");
    printf("Escolha uma das opcoes acima (1,2 ou 3): ");
    int opcao;
    scanf("%d", &opcao);
    printf("\n");
    switch (opcao)
    {
    case 1:
        carrega_jogo();
        break;
    case 2:
        comeca_jogo();
        break;
    default:
        break;
    }
}

int main () {
    menu_inicial();
    return 0;
}