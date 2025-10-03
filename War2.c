#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("Cadastro do territorio %d:\n", i + 1);
        printf("Digite o nome do territorio: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Digite a cor do exercito: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n===== Territorios =====\n");
    for (int i = 0; i < n; i++) {
        printf("Territorio %d:\n", i + 1);
        printf(" Nome: %s\n", mapa[i].nome);
        printf(" Cor do exercito: %s\n", mapa[i].cor);
        printf(" Tropas: %d\n", mapa[i].tropas);
        printf("--------------------------\n");
    }
}

void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante == NULL || defensor == NULL) return;

    int dadoAtq = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("\nDado atacante (%s): %d\n", atacante->nome, dadoAtq);
    printf("Dado defensor (%s): %d\n", defensor->nome, dadoDef);

    if (dadoAtq > dadoDef) {
        int transfer = atacante->tropas / 2;
        if (transfer < 1) transfer = 1;

        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = transfer;
        atacante->tropas -= transfer;
        if (atacante->tropas < 0) atacante->tropas = 0;

        printf("Resultado: atacante venceu!\n");
        printf("%d tropas transferidas de %s para %s.\n", transfer, atacante->nome, defensor->nome);
    } else {
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
        printf("Resultado: ataque falhou. %s perdeu 1 tropa.\n", atacante->nome);
    }
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    srand((unsigned int)time(NULL));

    int n;
    printf("Digite o numero de territorios: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Numero de territorios invalido.\n");
        return 1;
    }

    Territorio* mapa = (Territorio*)calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    int opcao;
    while (1) {
        printf("\nMenu:\n");
        printf("1 - Exibir territorios\n");
        printf("2 - Atacar\n");
        printf("3 - Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // limpa entrada inválida
            printf("Opcao invalida.\n");
            continue;
        }

        if (opcao == 1) {
            exibirTerritorios(mapa, n);
        } else if (opcao == 2) {
            exibirTerritorios(mapa, n);

            int idxAtq, idxDef;
            printf("Digite o numero do territorio atacante: ");
            scanf("%d", &idxAtq);
            printf("Digite o numero do territorio defensor: ");
            scanf("%d", &idxDef);

            idxAtq--; // ajustar para índice do vetor
            idxDef--;

            if (idxAtq < 0 || idxAtq >= n || idxDef < 0 || idxDef >= n) {
                printf("Indices invalidos.\n");
                continue;
            }

            if (idxAtq == idxDef) {
                printf("Nao e possivel atacar o mesmo territorio.\n");
                continue;
            }

            if (strcmp(mapa[idxAtq].cor, mapa[idxDef].cor) == 0) {
                printf("Voce nao pode atacar um territorio da mesma cor.\n");
                continue;
            }

            if (mapa[idxAtq].tropas <= 0) {
                printf("O territorio atacante nao possui tropas suficientes.\n");
                continue;
            }

            atacar(&mapa[idxAtq], &mapa[idxDef]);
            printf("\nSituacao apos o ataque:\n");
            exibirTerritorios(mapa, n);
        } else if (opcao == 3) {
            break;
        } else {
            printf("Opcao invalida.\n");
        }
    }

    liberarMemoria(mapa);
    return 0;
}
