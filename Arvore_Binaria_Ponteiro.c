#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um nó da árvore binária
typedef struct no {
    int conteudo;
    struct no *esquerda, *direita;
} No;

/*---------------------------------Funções-------------------------------------*/

// Função para inserir um valor na árvore binária
No* inserir(No *raiz, int valor);

// Função para obter o tamanho da árvore binária
int tamanho(No *raiz);

// Função para verificar se um valor está presente na árvore binária
int buscar(No *raiz, int chave);

// Função para buscar um nó específico na árvore binária
No* buscarNo(No *raiz, int chave);

// Função para remover um nó da árvore binária
No* remover(No *raiz, int chave);

// Função para imprimir os elementos da árvore binária
void imprimir(No *raiz);

// Função para calcular a altura total da árvore binária
int alturaArv(No *raiz);

// Função para calcular a altura de uma subárvore específica
int alturaSubArv(No *raiz, int chave);

/*------------------------------------------------------------------------------*/


// Função para inserir na árvore
No* inserir(No *raiz, int valor) {
    if (raiz == NULL) {
        // Cria um novo nó se a raiz for nula
        No *novo = (No *) malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    } else {
        // Insere à esquerda se o valor for menor que o conteúdo da raiz, senão insere à direita
        if (valor < raiz->conteudo)
            raiz->esquerda = inserir(raiz->esquerda, valor);
        if (valor > raiz->conteudo)
            raiz->direita = inserir(raiz->direita, valor);
        return raiz;
    }
}

// Função para contar o número de nós na árvore
int tamanho(No *raiz) {
    if (raiz == NULL)
        return 0;
    else
        return 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);
}

// Função para verificar se um valor está presente na árvore
int buscar(No *raiz, int chave) {
    if (raiz == NULL)
        return 0; // Retorna 0 se o elemento não estiver na árvore
    else {
        if (raiz->conteudo == chave)
            return 1; // Retorna 1 se o elemento pertencer à árvore
        else {
            if (chave < raiz->conteudo)
                return buscar(raiz->esquerda, chave);
            else
                return buscar(raiz->direita, chave);
        }
    }
}

// Função para buscar um nó específico na árvore
No* buscarNo(No *raiz, int chave) {
    if (raiz == NULL)
        return NULL;
    else {
        if (raiz->conteudo == chave)
            return raiz;
        else {
            if (chave < raiz->conteudo)
                return buscarNo(raiz->esquerda, chave);
            else
                return buscarNo(raiz->direita, chave);
        }
    }
}

// Função para remover um nó da árvore
No* remover(No *raiz, int chave) {
    if (raiz == NULL) {
        printf("Valor nao encontrado!\n");
        return NULL;
    } else {
        if (raiz->conteudo == chave) {
            // Remove nós folhas
            if (raiz->esquerda == NULL && raiz->direita == NULL) {
                free(raiz);
                return NULL;
            } else {
                // Remove nós que possuem apenas 1 filho
                if (raiz->esquerda == NULL || raiz->direita == NULL) {
                    No *aux;
                    if (raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    return aux;
                } else {
                    // Remove nós com dois filhos
                    No* aux = raiz->esquerda;
                    while (aux->direita != NULL)
                        aux = aux->direita;
                    raiz->conteudo = aux->conteudo;
                    aux->conteudo = chave;
                    raiz->esquerda = remover(raiz->esquerda, chave);
                    return raiz;
                }
            }
        } else {
            if (chave < raiz->conteudo)
                raiz->esquerda = remover(raiz->esquerda, chave);
            else
                raiz->direita = remover(raiz->direita, chave);
            return raiz;
        }
    }
    return NULL;
}

// Função para imprimir os elementos da árvore em ordem
void imprimir(No *raiz) {
    if (raiz != NULL) {
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}

// Função para calcular a altura da árvore
int alturaArv(No *raiz) {
    if (raiz == NULL || raiz->direita == NULL && raiz->esquerda == NULL)
        return 0; // Retorna 0 se a árvore for nula ou uma folha
    else {
        // Calcula a altura recursivamente e retorna a maior altura entre a subárvore esquerda e direita
        int esq = 1 + alturaArv(raiz->esquerda);
        int dir = 1 + alturaArv(raiz->direita);
        if (esq > dir)
            return esq;
        else
            return dir;
    }
}

// Função para calcular a altura de uma subárvore específica
int alturaSubArv(No *raiz, int chave) {
    No *no = buscarNo(raiz, chave);
    if (no)
        return alturaArv(no);
    else
        return -1; // Retorna -1 se o nó não for encontrado na árvore
}

int main(){
    int op, valor;
    No *raiz = NULL; // Inicializa a raiz da árvore como NULL

    do {
        // Exibe o menu de opções para o usuário
        printf("\n0 - Sair\n1 - Inserir\n2 - Imprimir\n3 - Buscar\n4 - Remover\n5 - Altura\n6 - Altura da subarvore\nEscolha uma opcao:");
        scanf("%d", &op);

        switch (op) {
            case 0:
                printf("\nSaindo....\n"); // Mensagem de saída
                break;
            case 1:
                printf("\nDigite um valor para inserir na arvore:");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor); // Chama a função para inserir um valor na árvore
                break;
            case 2:
                printf("\nImpressao da arvore binaria:\n");
                imprimir(raiz); // Chama a função para imprimir a árvore
                printf("\n");
                printf("Tamanho: %d\n", tamanho(raiz)); // Imprime o tamanho da árvore
                break;
            case 3:
                printf("\nDigite o valor que voce deseja buscar:");
                scanf("%d", &valor);
                printf("Resultado da busca: %d\n",buscar(raiz,valor));
                break;
            case 4:
                printf("\nDigite um valor a ser removido:");
                scanf("%d", &valor);
                raiz = remover(raiz, valor); // Chama a função para remover um valor da árvore
                break;
            case 5:
                printf("\nA altura da arvore e: %d\n", alturaArv(raiz)); // Calcula e imprime a altura da árvore
                break;
            case 6:
                printf("\nDigite o valor para calcular a altura da subarvore:");
                scanf("%d", &valor);
                printf("\nA altura da subarvore e: %d\n", alturaSubArv(raiz, valor)); // Calcula e imprime a altura da subárvore
                break;
            default:
                printf("\nOpcao invalida!\n"); // Mensagem de opção inválida
        }
    } while (op != 0); // Loop continua até que o usuário escolha sair

    return 0;
}