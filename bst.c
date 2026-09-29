#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da BST
typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
} No;

// Função para criar um novo nó
No* criarNo(int valor) {
    No* novo = (No*) malloc(sizeof(No));
    if (novo != NULL) {
        novo->valor = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
    }
    return novo;
}

// 1. Inserção (Valores repetidos são ignorados nesta implementação)
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    } else {
        printf("Valor %d ja existe na arvore.\n", valor);
    }
    return raiz;
}

// 2. Busca
No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }
    if (valor < raiz->valor) {
        return buscar(raiz->esquerda, valor);
    }
    return buscar(raiz->direita, valor);
}

// Função auxiliar para encontrar o menor valor (sucessor in-order)
No* encontrarMinimo(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// 3. Remoção (Três casos clássicos)
No* remover(No* raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }

    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        // Caso 1: Nó folha ou com apenas um filho
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Caso 2: Nó com dois filhos (pega o sucessor in-order)
        No* temp = encontrarMinimo(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = remover(raiz->direita, temp->valor);
    }
    return raiz;
}

// 4. Percursos
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

// Liberar toda a memória alocada
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

// Função principal com interface em switch-case
int main() {
    No* raiz = NULL;
    int opcao, subOpcao, valor;

    do {
        printf("\n--- MENU BST ---\n");
        printf("1\nInserir valor\n");
        printf("2\nBuscar valor\n");
        printf("3\nRemover valor\n");
        printf("4\nPercorrer arvore\n");
        printf("0\nSair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a inserir: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                break;
            case 2:
                printf("Digite o valor a buscar: ");
                scanf("%d", &valor);
                if (buscar(raiz, valor) != NULL) {
                    printf("Valor %d encontrado na arvore.\n", valor);
                } else {
                    printf("Valor %d NAO encontrado na arvore.\n", valor);
                }
                break;
            case 3:
                printf("Digite o valor a remover: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                printf("Operacao de remocao concluida.\n");
                break;
            case 4:
                printf("\n--- SUBMENU PERCURSOS ---\n");
                printf("1\nPre-ordem\n");
                printf("2\nEm ordem\n");
                printf("3\nPos-ordem\n");
                printf("Escolha o percurso: ");
                scanf("%d", &subOpcao);

                printf("Resultado: ");
                switch (subOpcao) {
                    case 1: preOrdem(raiz); break;
                    case 2: emOrdem(raiz); break;
                    case 3: posOrdem(raiz); break;
                    default: printf("Opcao invalida!");
                }
                printf("\n");
                break;
            case 0:
                liberarArvore(raiz);
                printf("Encerrando programa e liberando memoria...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
