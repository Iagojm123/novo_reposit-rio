#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da AVL
typedef struct NoAVL {
    int valor;
    int altura;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
} NoAVL;

// Funções auxiliares de altura e máximo
int altura(NoAVL* n) {
    if (n == NULL) return 0;
    return n->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

NoAVL* criarNo(int valor) {
    NoAVL* novo = (NoAVL*) malloc(sizeof(NoAVL));
    if (novo != NULL) {
        novo->valor = valor;
        novo->altura = 1;
        novo->esquerda = NULL;
        novo->direita = NULL;
    }
    return novo;
}

// Fator de balanceamento
int fatorBalanceamento(NoAVL* n) {
    if (n == NULL) return 0;
    return altura(n->esquerda) - altura(n->direita);
}

// Rotação simples à direita
NoAVL* rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

// Rotação simples à esquerda
NoAVL* rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->direita;
    NoAVL* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

// Inserção com balanceamento
NoAVL* inserir(NoAVL* no, int valor) {
    if (no == NULL) return criarNo(valor);

    if (valor < no->valor) {
        no->esquerda = inserir(no->esquerda, valor);
    } else if (valor > no->valor) {
        no->direita = inserir(no->direita, valor);
    } else {
        printf("Valor %d ja existe na arvore.\n", valor);
        return no;
    }

    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    int balance = fatorBalanceamento(no);

    // Esquerda Esquerda
    if (balance > 1 && valor < no->esquerda->valor) {
        return rotacaoDireita(no);
    }

    // Direita Direita
    if (balance < -1 && valor > no->direita->valor) {
        return rotacaoEsquerda(no);
    }

    // Esquerda Direita
    if (balance > 1 && valor > no->esquerda->valor) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Direita Esquerda
    if (balance < -1 && valor < no->direita->valor) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

NoAVL* menorValorNo(NoAVL* no) {
    NoAVL* atual = no;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

// Remoção com balanceamento
NoAVL* remover(NoAVL* raiz, int valor) {
    if (raiz == NULL) return raiz;

    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    } else {
        if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {
            NoAVL* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            NoAVL* temp = menorValorNo(raiz->direita);
            raiz->valor = temp->valor;
            raiz->direita = remover(raiz->direita, temp->valor);
        }
    }

    if (raiz == NULL) return raiz;

    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    int balance = fatorBalanceamento(raiz);

    if (balance > 1 && fatorBalanceamento(raiz->esquerda) >= 0) {
        return rotacaoDireita(raiz);
    }

    if (balance > 1 && fatorBalanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (balance < -1 && fatorBalanceamento(raiz->direita) <= 0) {
        return rotacaoEsquerda(raiz);
    }

    if (balance < -1 && fatorBalanceamento(raiz->direita) > 0) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// Busca
NoAVL* buscar(NoAVL* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) return raiz;
    if (valor < raiz->valor) return buscar(raiz->esquerda, valor);
    return buscar(raiz->direita, valor);
}

// Percursos
void preOrdem(NoAVL* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void emOrdem(NoAVL* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

void posOrdem(NoAVL* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

// Exibição da altura e fator de balanceamento
void exibirBalanceamento(NoAVL* raiz) {
    if (raiz != NULL) {
        exibirBalanceamento(raiz->esquerda);
        printf("No: %d | Altura: %d | Fator de Balanceamento: %d\n", 
               raiz->valor, altura(raiz), fatorBalanceamento(raiz));
        exibirBalanceamento(raiz->direita);
    }
}

void liberarArvore(NoAVL* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

// Função principal
int main() {
    NoAVL* raiz = NULL;
    int opcao, subOpcao, valor;

    do {
        printf("\n--- MENU AVL ---\n");
        printf("1\nInserir valor\n");
        printf("2\nBuscar valor\n");
        printf("3\nRemover valor\n");
        printf("4\nPercorrer arvore\n");
        printf("5\nExibir altura e fator de balanceamento\n");
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
            case 5:
                printf("\n--- ALTURA E BALANCEAMENTO DOS NOS ---\n");
                if (raiz == NULL) {
                    printf("Arvore vazia.\n");
                } else {
                    printf("Altura total da arvore: %d\n", altura(raiz));
                    exibirBalanceamento(raiz);
                }
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
