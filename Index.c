#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 1 - Cada nó da árvore deve representar um produto, contendo os seguintes campos: código do produto, nome do produto,
* quantidade em estoque, preço unitário.*/
typedef struct produto {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

// Definição da estrutura do nó da árvore
typedef struct Node {
    Produto* produto;
    struct Node* esquerda;
    struct Node* direita;
    short altura;
} Node;

/*************************** N E W *****************************************/
/*
    Retorna o maior dentre dois valores
    a, b -> altura de dois nós da árvore
*/
short maior(short a, short b){
    return (a > b)? a: b;
}


//  Retorna a altura de um nó ou -1 caso ele seja null
short alturaDoNo(Node *no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

//   Calcula e retorna o fator de balanceamento de um nó
short fatorDeBalanceamento(Node *no){
    if(no)
        return (alturaDoNo(no->esquerda) - alturaDoNo(no->direita));
    else
        return 0;
}

// função para a rotação à esquerda
Node* rotacaoEsquerda(Node *r){
    Node *y, *f;

    y = r->direita;
    f = y->esquerda;

    y->esquerda = r;
    r->direita = f;

    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;

    return y;
}

// função para a rotação à direita
Node* rotacaoDireita(Node *r){
    Node *y, *f;

    y = r->esquerda;
    f = y->direita;

    y->direita = r;
    r->esquerda = f;

    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;

    return y;
}

Node* rotacaoEsquerdaDireita(Node *r){
    r->esquerda = rotacaoEsquerda(r->esquerda);
    return rotacaoDireita(r);
}

Node* rotacaoDireitaEsquerda(Node *r){
    r->direita = rotacaoDireita(r->direita);
    return rotacaoEsquerda(r);
}

/*
    Função para realizar o balanceamento da árvore após uma inserção ou remoção
    Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
*/
Node* balancear(Node *raiz){
    short fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda
    if(fb < -1 && fatorDeBalanceamento(raiz->direita) <= 0)
        raiz = rotacaoEsquerda(raiz);

        // Rotação à direita
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerda) >= 0)
        raiz = rotacaoDireita(raiz);

        // Rotação dupla à esquerda
    else if(fb > 1 && fatorDeBalanceamento(raiz->esquerda) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

        // Rotação dupla à direita
    else if(fb < -1 && fatorDeBalanceamento(raiz->direita) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}

// Função para criar nó
Node* criarNo(int codigo, const char *nome, int quantidade, float preco) {
    if (codigo < 0 || quantidade < 0 || preco < 0) {
        printf("Nao e possivel criar o no com valores negativos.\n");
        exit(EXIT_FAILURE);
    }

    Node* novoNo = malloc(sizeof(Node)); // Alocamos memória para o novo nó
    if (novoNo == NULL) {
        printf("Erro na alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }

    novoNo->produto = malloc(sizeof(Produto)); // Alocamos memória para o produto dentro do nó
    if (novoNo->produto == NULL) {
        printf("Erro na alocacao de memoria para o produto.\n");
        free(novoNo); // Liberamos a memória alocada para o nó
        exit(EXIT_FAILURE);
    }

    novoNo->produto->codigo = codigo;
    strcpy(novoNo->produto->nome, nome);
    novoNo->produto->quantidade = quantidade;
    novoNo->produto->preco = preco;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->altura = 0;
    return novoNo;
}

/* Função para inserir elementos na árvore
 *
 * 2 - Implemente uma função para inserir um novo produto na árvore, mantendo-a balanceada. Garanta que a árvore
 * não esteja desbalanceada em mais de 1 nível.
 *
 * 8 - Garanta que não é possível inserir produtos com códigos duplicados na árvore, nem quantidades ou
 * preços menores que zero.*/
/* Função para inserir elementos na árvore */
/* Função para inserir elementos na árvore */
Node* inserir(Node* raiz, int codigo, const char *nome, int quantidade, float preco) {
    // Verifica se algum dos valores inseridos é negativo
    if (codigo < 0 || quantidade < 0 || preco < 0) {
        printf("Nao e possivel inserir um produto com valores negativos.\n");
        return raiz; // Retorna a raiz original sem inserir o produto
    }

    if (raiz == NULL) { // Se a árvore estiver vazia, insere o produto como raiz
        raiz = criarNo(codigo, nome, quantidade, preco);
        printf("Produto inserido com sucesso!\n");
        return raiz;
    }

    // Se a árvore não estiver vazia, insere o produto em uma posição apropriada
    if (codigo < raiz->produto->codigo) {
        raiz->esquerda = inserir(raiz->esquerda, codigo, nome, quantidade, preco);
    } else if (codigo > raiz->produto->codigo) {
        raiz->direita = inserir(raiz->direita, codigo, nome, quantidade, preco);
    } else { // Se o código já existir na árvore, exibe uma mensagem de aviso
        printf("Produto com codigo %d ja existe na arvore.\n", codigo);
        return raiz; // Retorna a raiz original sem alterações
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;

    // Verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz; // Retorna a nova raiz após o balanceamento
}

/* Função para remover um elemento da árvore
 *
 * 3 - Implemente uma função para remover um produto da árvore, atualizando a estrutura para manter
 * a propriedade da árvore binária.*/
Node* remover(Node* raiz, int chave) {
    // Verifica se a árvore está vazia
    if (raiz == NULL) {
        printf("Valor nao encontrado!\n");
        return NULL;
    }

    // Procura o nó a ser removido
    if (chave < raiz->produto->codigo) {
        raiz->esquerda = remover(raiz->esquerda, chave);
    } else if (chave > raiz->produto->codigo) {
        raiz->direita = remover(raiz->direita, chave);
    } else { // Nó a ser removido encontrado
        // Caso 1: Nó sem filhos ou com apenas um filho
        if (raiz->esquerda == NULL) {
            Node* temp = raiz->direita;
            free(raiz->produto);
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Node* temp = raiz->esquerda;
            free(raiz->produto);
            free(raiz);
            return temp;
        }

        // Caso 2: Nó com dois filhos
        // Encontra o sucessor (menor valor na subárvore direita)
        Node* temp = raiz->direita;
        while (temp->esquerda != NULL) {
            temp = temp->esquerda;
        }
        // Copia os dados do sucessor para este nó
        raiz->produto->codigo = temp->produto->codigo;
        strcpy(raiz->produto->nome, temp->produto->nome);
        raiz->produto->quantidade = temp->produto->quantidade;
        raiz->produto->preco = temp->produto->preco;
        // Remove o sucessor
        raiz->direita = remover(raiz->direita, temp->produto->codigo);
    }

    // Recalcula a altura de todos os nós entre a raiz e o nó removido
    raiz->altura = 1 + maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita));

    // Verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

/* Função para buscar um produto pelo código
 *
 * 4 Implemente uma função para buscar um produto na árvore pelo seu código.*/
Node* buscar(Node* raiz, int codigo) {
    if (raiz == NULL || raiz->produto->codigo == codigo) {
        return raiz;
    }

    if (codigo < raiz->produto->codigo) {
        return buscar(raiz->esquerda, codigo);
    } else {
        return buscar(raiz->direita, codigo);
    }
}

/* Função para listar produtos com quantidade menor que um valor especificado
 *
 * 5 - Implemente uma função para listar todos os produtos com uma quantidade menor que a informada pelo usuário.*/
void listarQuantidadeMenor(Node* raiz, int valor) {
    if (raiz == NULL) {
        return;
    }

    listarQuantidadeMenor(raiz->esquerda, valor);
    if (raiz->produto->quantidade < valor) {
        printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n", raiz->produto->codigo, raiz->produto->nome, raiz->produto->quantidade, raiz->produto->preco);
    }
    listarQuantidadeMenor(raiz->direita, valor);
}

/* Função para listar produtos com preço dentro de uma faixa especificada
 *
 * 6 - Implemente uma função para listar todos os produtos em uma faixa de preço especificada pelo usuário.*/
void listarFaixaPreco(Node* raiz, float minPreco, float maxPreco) {
    if (raiz == NULL) {
        return;
    }

    listarFaixaPreco(raiz->esquerda, minPreco, maxPreco);
    if (raiz->produto->preco >= minPreco && raiz->produto->preco <= maxPreco) {
        printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n", raiz->produto->codigo, raiz->produto->nome, raiz->produto->quantidade, raiz->produto->preco);
    }
    listarFaixaPreco(raiz->direita, minPreco, maxPreco);
}

/* Função para calcular o valor total do estoque
 *
 * 7 - Implemente uma função para calcular o valor total do estoque da loja.*/
float calcularValorTotal(Node* raiz) {
    if (raiz == NULL) {
        return 0;
    }

    return raiz->produto->preco * raiz->produto->quantidade + calcularValorTotal(raiz->esquerda) + calcularValorTotal(raiz->direita);
}

/* Função para imprimir a árvore
 *
 * 10 - O código deve implementar uma maneira de exibir a árvore de maneira intuitiva no console.*/
void imprimirArvore(Node* raiz, int espacos) {
    if (raiz == NULL) {
        return;
    }

    espacos += 10;

    imprimirArvore(raiz->direita, espacos);

    printf("\n");
    for (int i = 10; i < espacos; i++) {
        printf(" ");
    }
    printf("%d - %s\n", raiz->produto->codigo,raiz->produto->nome);

    imprimirArvore(raiz->esquerda, espacos);
}

int main() {
    Node* raiz = NULL;
    int opcao;

    do {
        printf("\n=== Menu ===\n");
        printf("0. Sair\n");
        printf("1. Inserir produto\n");
        printf("2. Remover produto\n");
        printf("3. Buscar produto\n");
        printf("4. Listar produtos com preco dentro de uma faixa\n");
        printf("5. Listar produtos com quantidade menor que um valor especificado\n");
        printf("6. Calcular valor total do estoque\n");
        printf("7. Imprimir arvore de produtos\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                break;
            case 1: {
                int codigo, quantidade;
                float preco;
                char nome[50];
                printf("\nDigite o codigo do produto:");
                scanf("%d", &codigo);
                printf("Digite o nome do produto:");
                scanf("%s", nome);
                printf("Digite a quantidade do produto:");
                scanf("%d", &quantidade);
                printf("Digite o preco do produto:");
                scanf("%f", &preco);
                raiz = inserir(raiz, codigo, nome, quantidade, preco);
                break;
            }
            case 2: {
                int codigoRemover;
                printf("\nDigite o codigo do produto a ser removido:");
                scanf("%d", &codigoRemover);
                raiz = remover(raiz, codigoRemover);
                break;
            }
            case 3: {
                int codigoBuscar;
                printf("\nDigite o codigo do produto a ser buscado:");
                scanf("%d", &codigoBuscar);
                Node* produtoBuscado = buscar(raiz, codigoBuscar);
                if (produtoBuscado != NULL) {
                    printf("Produto encontrado:\n");
                    printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: R$ %.2f\n", produtoBuscado->produto->codigo, produtoBuscado->produto->nome, produtoBuscado->produto->quantidade, produtoBuscado->produto->preco);
                } else {
                    printf("Produto com codigo %d nao encontrado!\n", codigoBuscar);
                }
                break;
            }
            case 4: {
                float minPreco, maxPreco;
                printf("\nDigite o preco minimo:");
                scanf("%f", &minPreco);
                printf("Digite o preco maximo:");
                scanf("%f", &maxPreco);
                printf("Produtos com preco entre R$ %.2f e R$ %.2f:\n", minPreco, maxPreco);
                listarFaixaPreco(raiz, minPreco, maxPreco);
                break;
            }
            case 5: {
                int valor;
                printf("\nDigite a quantidade maxima:");
                scanf("%d", &valor);
                printf("Produtos com quantidade menor que %d:\n", valor);
                listarQuantidadeMenor(raiz, valor);
                break;
            }
            case 6:
                printf("\nValor total do estoque: R$ %.2f\n", calcularValorTotal(raiz));
                break;
            case 7:
                printf("\nArvore de produtos:\n");
                imprimirArvore(raiz, 0);
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}