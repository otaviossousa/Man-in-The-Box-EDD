#include <stdio.h>   // Biblioteca padrão de entrada e saída. Contém funções como printf e scanf para entrada e saída de dados.
#include <stdlib.h>  // Biblioteca padrão que fornece funções para alocação de memória dinâmica, controle de processos, conversão de tipos e outras utilidades.
#include <string.h>  // Biblioteca padrão para manipulação de strings. Contém funções como strcpy para copiar strings.
#include <time.h>    // Biblioteca padrão para manipulação de tempo e data. Contém funções e tipos para trabalhar com tempo, como a função time para obter o tempo atual do sistema.

/*
    1 - Cada nó da árvore deve representar um produto, contendo os seguintes campos: código do produto, nome do produto,
    quantidade em estoque, preço unitário.
*/
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

//================================================== FUNCOES ================================================== //
// Retorna o maior entre dois valores
short maior(short a, short b);

// Retorna a altura de um nó na árvore
short alturaDoNo(Node *no);

// Calcula e retorna o fator de balanceamento de um nó na árvore
short fatorDeBalanceamento(Node *no);

// Realiza uma rotação para a esquerda em torno de um nó na árvore AVL
Node* rotacaoEsquerda(Node *r);

// Realiza uma rotação para a direita em torno de um nó na árvore AVL
Node* rotacaoDireita(Node *r);

// Realiza uma rotação à esquerda seguida por uma rotação à direita em torno de um nó na árvore AVL
Node* rotacaoEsquerdaDireita(Node *r);

// Realiza uma rotação à direita seguida por uma rotação à esquerda em torno de um nó na árvore AVL
Node* rotacaoDireitaEsquerda(Node *r);

// Realiza o balanceamento da árvore após uma inserção ou remoção
Node* balancear(Node *raiz);

// Cria um novo nó para a árvore AVL com os dados do produto
Node* criarNo(int codigo, const char *nome, int quantidade, float preco);

// Insere um novo produto na árvore AVL, mantendo-a balanceada
Node* inserir(Node* raiz, int codigo, const char *nome, int quantidade, float preco);

// Remove um produto da árvore AVL, mantendo-a balanceada
Node* remover(Node* raiz, int chave);

// Busca um produto na árvore AVL pelo seu código
Node* buscar(Node* raiz, int codigo);

// Lista os produtos com quantidade menor que um valor especificado
void listarQuantidadeMenor(Node* raiz, int valor);

// Lista os produtos com preço dentro de uma faixa especificada pelo usuário
void listarFaixaPreco(Node* raiz, float minPreco, float maxPreco);

// Calcula o valor total do estoque da loja representado pela árvore
float calcularValorTotal(Node* raiz);

// Imprime a árvore na forma de uma representação gráfica
void imprimirArvore(Node* raiz, int espacos);

// Libera a memória de todos os nós da árvore
void liberarArvore(Node* raiz);

// Gera um número aleatório entre min e max
int randint(int min, int max);

// Cria uma árvore AVL balanceada com 7 elementos de forma automática e aleatória
Node* gerarArvoreAleatoria();
//================================================== FUNCOES ================================================== //

int main() {
    Node* raiz = NULL; // Inicializa a raiz da árvore como nula
    int opcao; // Variável para armazenar a opção do menu

    // Loop do menu principal
    do {
        printf("\n============================== Menu =============================\n0. Sair\n1. Inserir produto\n2. Remover produto"
               "\n3. Buscar produto\n4. Listar produtos com preco dentro de uma faixa\n5. Listar produtos com quantidade menor que um valor especificado\n"
               "6. Calcular valor total do estoque\n7. Imprimir arvore de produtos\n8. Gerar Arvore Aleatoria\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                break;
            case 1: {
                // Inserir produto
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
                raiz = inserir(raiz, codigo, nome, quantidade, preco); // Chama a função para inserir o produto na árvore
                break;
            }
            case 2: {
                // Remover produto
                int codigoRemover;
                printf("\nDigite o codigo do produto a ser removido:");
                scanf("%d", &codigoRemover);
                raiz = remover(raiz, codigoRemover); // Chama a função para remover o produto da árvore
                break;
            }
            case 3: {
                // Buscar produto
                int codigoBuscar;
                printf("\nDigite o codigo do produto a ser buscado:");
                scanf("%d", &codigoBuscar);
                Node* produtoBuscado = buscar(raiz, codigoBuscar); // Chama a função para buscar o produto na árvore
                if (produtoBuscado != NULL) {
                    printf("Produto encontrado:\n");
                    printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: R$ %.2f\n", produtoBuscado->produto->codigo, produtoBuscado->produto->nome, produtoBuscado->produto->quantidade, produtoBuscado->produto->preco);
                } else {
                    printf("Produto com codigo %d nao encontrado!\n", codigoBuscar);
                }
                break;
            }
            case 4: {
                // Listar produtos com preço dentro de uma faixa
                float minPreco, maxPreco;
                printf("\nDigite o preco minimo:");
                scanf("%f", &minPreco);
                printf("Digite o preco maximo:");
                scanf("%f", &maxPreco);
                printf("Produtos com preco entre R$ %.2f e R$ %.2f:\n", minPreco, maxPreco);
                listarFaixaPreco(raiz, minPreco, maxPreco); // Chama a função para listar produtos dentro da faixa de preço especificada
                break;
            }
            case 5: {
                // Listar produtos com quantidade menor que um valor especificado
                int valor;
                printf("\nDigite a quantidade maxima:");
                scanf("%d", &valor);
                printf("Produtos com quantidade menor que %d:\n", valor);
                listarQuantidadeMenor(raiz, valor); // Chama a função para listar produtos com quantidade menor que um valor especificado
                break;
            }
            case 6:
                // Calcular valor total do estoque
                printf("\nValor total do estoque: R$ %.2f\n", calcularValorTotal(raiz)); // Chama a função para calcular o valor total do estoque
                break;
            case 7:
                // Imprimir árvore de produtos
                printf("\nArvore de produtos:\n");
                imprimirArvore(raiz, 0); // Chama a função para imprimir a árvore de produtos
                break;
            case 8:
                liberarArvore(raiz); // Liberar a memória da árvore existente
                raiz = gerarArvoreAleatoria(); // Gerar automaticamente uma nova árvore balanceada com 7 elementos
                printf("\nNova arvore balanceada com 7 elementos gerada com sucesso!\n");
                break;
            default:
                printf("\nOpcao invalida!\n"); // Mensagem de opção inválida
        }
    } while (opcao != 0); // Repete até que a opção 0 (Sair) seja escolhida

    liberarArvore(raiz); // Liberar a memória alocada para a árvore antes de encerrar o programa
    return 0;
}

/*
    Retorna o maior entre dois valores.
    a: primeiro valor a ser comparado
    b: segundo valor a ser comparado
    Retorna o maior valor entre a e b.
*/
short maior(short a, short b){
    return (a > b) ? a : b;
}

/*
    Retorna a altura de um nó na árvore.
    no: nó cuja altura será verificada
    Retorna a altura do nó. Se o nó for nulo, retorna -1.
*/
short alturaDoNo(Node *no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

/*
    Calcula e retorna o fator de balanceamento de um nó na árvore.
    no: nó cujo fator de balanceamento será calculado
    Retorna o fator de balanceamento do nó. Se o nó for nulo, retorna 0.
*/
short fatorDeBalanceamento(Node *no){
    if(no)
        return (alturaDoNo(no->esquerda) - alturaDoNo(no->direita));
    else
        return 0;
}

/*
    Realiza uma rotação para a esquerda em torno de um nó na árvore AVL.
    r: nó em torno do qual a rotação é realizada
    Retorna o novo nó que se torna a raiz após a rotação.
*/
Node* rotacaoEsquerda(Node *r){
    Node *y, *f;

    y = r->direita; // Define y como o filho à direita de r
    f = y->esquerda; // Define f como o filho à esquerda de y

    // Realiza a rotação
    y->esquerda = r;
    r->direita = f;

    // Atualiza as alturas dos nós afetados
    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;

    return y; // Retorna o novo nó que se torna a raiz após a rotação
}

/*
    Realiza uma rotação para a direita em torno de um nó na árvore AVL.
    r: nó em torno do qual a rotação é realizada
    Retorna o novo nó que se torna a raiz após a rotação.
*/
Node* rotacaoDireita(Node *r){
    Node *y, *f;

    y = r->esquerda; // Define y como o filho à esquerda de r
    f = y->direita; // Define f como o filho à direita de y

    // Realiza a rotação
    y->direita = r;
    r->esquerda = f;

    // Atualiza as alturas dos nós afetados
    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita)) + 1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita)) + 1;

    return y; // Retorna o novo nó que se torna a raiz após a rotação
}

/*
    Realiza uma rotação à esquerda seguida por uma rotação à direita em torno de um nó na árvore AVL.
    r: nó em torno do qual as rotações são realizadas
    Retorna o novo nó que se torna a raiz após as rotações.
*/
Node* rotacaoEsquerdaDireita(Node *r){
    // Realiza uma rotação à esquerda no filho à esquerda de r
    r->esquerda = rotacaoEsquerda(r->esquerda);

    // Realiza uma rotação à direita em r
    return rotacaoDireita(r);
}

/*
    Realiza uma rotação à direita seguida por uma rotação à esquerda em torno de um nó na árvore AVL.
    r: nó em torno do qual as rotações são realizadas
    Retorna o novo nó que se torna a raiz após as rotações.
*/
Node* rotacaoDireitaEsquerda(Node *r){
    // Realiza uma rotação à direita no filho à direita de r
    r->direita = rotacaoDireita(r->direita);

    // Realiza uma rotação à esquerda em r
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

/*
    Cria um novo nó para a árvore AVL com os dados do produto.
    codigo: código do produto
    nome: nome do produto
    quantidade: quantidade em estoque do produto
    preco: preço unitário do produto
    Retorna um ponteiro para o novo nó criado.
*/
Node* criarNo(int codigo, const char *nome, int quantidade, float preco) {
    // Verifica se os valores passados são válidos
    if (codigo < 0 || quantidade < 0 || preco < 0) {
        printf("Não é possível criar o nó com valores negativos.\n");
        exit(EXIT_FAILURE);
    }

    // Aloca memória para o novo nó
    Node* novoNo = malloc(sizeof(Node));
    if (novoNo == NULL) {
        printf("Erro na alocação de memória para o nó.\n");
        exit(EXIT_FAILURE);
    }

    // Aloca memória para o produto dentro do nó
    novoNo->produto = malloc(sizeof(Produto));
    if (novoNo->produto == NULL) {
        printf("Erro na alocação de memória para o produto.\n");
        free(novoNo); // Libera a memória alocada para o nó
        exit(EXIT_FAILURE);
    }

    novoNo->produto->codigo = codigo;
    strcpy(novoNo->produto->nome, nome);
    novoNo->produto->quantidade = quantidade;
    novoNo->produto->preco = preco;
    novoNo->esquerda = NULL;// Inicializa os ponteiros para os filhos como nulos
    novoNo->direita = NULL;
    novoNo->altura = 0; // Inicializa a altura do nó como 0

    return novoNo; // Retorna o novo nó criado
}

/*
    2 - Implemente uma função para inserir um novo produto na árvore, mantendo-a balanceada. Garanta que a árvore
    não esteja desbalanceada em mais de 1 nível.

    8 - Garanta que não é possível inserir produtos com códigos duplicados na árvore, nem quantidades ou
    preços menores que zero.

    Insere um novo produto na árvore AVL, mantendo-a balanceada.
    raiz: ponteiro para a raiz da árvore
    codigo: código do produto a ser inserido
    nome: nome do produto a ser inserido
    quantidade: quantidade em estoque do produto a ser inserido
    preco: preço unitário do produto a ser inserido
    Retorna um ponteiro para a nova raiz da árvore após a inserção e o balanceamento.
*/
Node* inserir(Node* raiz, int codigo, const char *nome, int quantidade, float preco) {
    // Verifica se algum dos valores inseridos é negativo
    if (codigo < 0 || quantidade < 0 || preco < 0) {
        printf("Não é possível inserir um produto com valores negativos.\n");
        return raiz; // Retorna a raiz original sem inserir o produto
    }

    // Se a árvore estiver vazia, insere o produto como raiz
    if (raiz == NULL) {
        raiz = criarNo(codigo, nome, quantidade, preco);
        printf("Produto inserido com sucesso!\n");
        return raiz;
    }

    // Se o código já existir na árvore, exibe uma mensagem de aviso
    if (codigo == raiz->produto->codigo) {
        printf("Produto com código %d já existe na árvore.\n", codigo);
        return raiz; // Retorna a raiz original sem alterações
    }

    // Insere o produto em uma posição apropriada na árvore
    if (codigo < raiz->produto->codigo) {
        raiz->esquerda = inserir(raiz->esquerda, codigo, nome, quantidade, preco);
    } else {
        raiz->direita = inserir(raiz->direita, codigo, nome, quantidade, preco);
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;

    // Verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz; // Retorna a nova raiz após o balanceamento
}

/*
    3 - Implemente uma função para remover um produto da árvore, atualizando a estrutura para manter
    a propriedade da árvore binária.

    Remove um produto da árvore AVL, mantendo-a balanceada.
    raiz: ponteiro para a raiz da árvore
    chave: código do produto a ser removido
    Retorna um ponteiro para a nova raiz da árvore após a remoção e o balanceamento.
*/
Node* remover(Node* raiz, int chave) {
    // Verifica se a árvore está vazia
    if (raiz == NULL) {
        printf("Valor não encontrado!\n");
        return NULL;
    }

    // Procura o nó a ser removido nas subárvores esquerda e direita
    if (chave < raiz->produto->codigo) {
        raiz->esquerda = remover(raiz->esquerda, chave);
    } else if (chave > raiz->produto->codigo) {
        raiz->direita = remover(raiz->direita, chave);
    } else {
        // Nó encontrado para remoção

        // Verifica se o nó tem zero ou um filho
        if (raiz->esquerda == NULL || raiz->direita == NULL) {
            // Armazena o ponteiro para o filho não nulo
            Node* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            // Libera a memória do nó atual
            free(raiz->produto);
            free(raiz);
            // Retorna o ponteiro para o filho não nulo (ou NULL se ambos forem nulos)
            return temp;
        }

        // Nó com dois filhos
        Node* temp = raiz->direita;
        // Encontra o nó mais à esquerda da subárvore direita
        while (temp->esquerda != NULL) {
            temp = temp->esquerda;
        }
        // Copia os valores do nó mais à esquerda para o nó a ser removido
        raiz->produto->codigo = temp->produto->codigo;
        strcpy(raiz->produto->nome, temp->produto->nome);
        raiz->produto->quantidade = temp->produto->quantidade;
        raiz->produto->preco = temp->produto->preco;
        // Remove o nó mais à esquerda da subárvore direita
        raiz->direita = remover(raiz->direita, temp->produto->codigo);
    }

    // Recalcula a altura de todos os nós entre a raiz e o nó removido
    raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;

    // Verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz; // Retorna a nova raiz após o balanceamento
}

/*
    4 - Implemente uma função para buscar um produto na árvore pelo seu código.

    Busca um produto na árvore AVL com base no código.
    raiz: ponteiro para a raiz da árvore
    codigo: código do produto a ser buscado
    Retorna um ponteiro para o nó que contém o produto com o código buscado, ou NULL se não encontrado.
*/
Node* buscar(Node* raiz, int codigo) {
    // Verifica se a raiz é nula ou se o código da raiz é igual ao código buscado
    if (raiz == NULL || raiz->produto->codigo == codigo) {
        return raiz; // Retorna a raiz se for nula ou se encontrar o código na raiz
    }

    // Se o código buscado for menor que o código da raiz, busca na subárvore esquerda
    if (codigo < raiz->produto->codigo) {
        return buscar(raiz->esquerda, codigo);
    } else { // Caso contrário, busca na subárvore direita
        return buscar(raiz->direita, codigo);
    }
}

/*
    5 - Implemente uma função para listar todos os produtos com uma quantidade menor que a informada pelo usuário.

    Lista os produtos com quantidade menor que um valor especificado.
    raiz: ponteiro para a raiz da árvore
    valor: valor máximo de quantidade para listar os produtos
*/
void listarQuantidadeMenor(Node* raiz, int valor) {
    // Verifica se a raiz é nula
    if (raiz == NULL) {
        return; // Se sim, retorna, pois não há nada para listar nesta subárvore
    }

    // Realiza uma travessia em ordem na subárvore esquerda
    listarQuantidadeMenor(raiz->esquerda, valor);

    // Verifica se a quantidade do produto na raiz é menor que o valor especificado
    if (raiz->produto->quantidade < valor) {
        // Se sim, exibe as informações do produto
        printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n", raiz->produto->codigo, raiz->produto->nome, raiz->produto->quantidade, raiz->produto->preco);
    }

    // Realiza uma travessia em ordem na subárvore direita
    listarQuantidadeMenor(raiz->direita, valor);
}

/*
    6 - Implemente uma função para listar todos os produtos em uma faixa de preço especificada pelo usuário.

    Lista os produtos com preço dentro de uma faixa específica.
    raiz: ponteiro para a raiz da árvore
    minPreco: preço mínimo da faixa de preços
    maxPreco: preço máximo da faixa de preços
*/
void listarFaixaPreco(Node* raiz, float minPreco, float maxPreco) {
    // Verifica se a raiz é nula
    if (raiz == NULL) {
        return; // Se sim, retorna, pois não há nada para listar nesta subárvore
    }

    // Realiza uma travessia em ordem na subárvore esquerda
    listarFaixaPreco(raiz->esquerda, minPreco, maxPreco);

    // Verifica se o preço do produto na raiz está dentro da faixa especificada
    if (raiz->produto->preco >= minPreco && raiz->produto->preco <= maxPreco) {
        // Se sim, exibe as informações do produto
        printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n", raiz->produto->codigo, raiz->produto->nome, raiz->produto->quantidade, raiz->produto->preco);
    }

    // Realiza uma travessia em ordem na subárvore direita
    listarFaixaPreco(raiz->direita, minPreco, maxPreco);
}

/*
    7 - Implemente uma função para calcular o valor total do estoque da loja.
    Calcula e retorna o valor total do estoque representado pela árvore.
    raiz: ponteiro para a raiz da árvore
    Retorna o valor total do estoque.
*/
float calcularValorTotal(Node* raiz) {
    // Verifica se a raiz é nula
    if (raiz == NULL) {
        return 0; // Se sim, o valor total é zero
    }

    // Calcula o valor total do estoque da subárvore esquerda, da raiz e da subárvore direita
    return raiz->produto->preco * raiz->produto->quantidade + calcularValorTotal(raiz->esquerda) + calcularValorTotal(raiz->direita);
}

/*
    10 - O código deve implementar uma maneira de exibir a árvore de maneira intuitiva no console.
    Imprime a árvore na forma de uma representação gráfica.
    raiz: ponteiro para a raiz da árvore
    espacos: quantidade de espaços de indentação para a formatação
*/
void imprimirArvore(Node* raiz, int espacos) {
    // Verifica se a raiz é nula
    if (raiz == NULL) {
        return; // Se sim, retorna
    }

    // Adiciona espaços para indentação
    espacos += 10;

    // Imprime a subárvore direita
    imprimirArvore(raiz->direita, espacos);

    // Imprime uma quebra de linha
    printf("\n");

    // Imprime os espaços de indentação
    for (int i = 10; i < espacos; i++) {
        printf(" ");
    }

    // Imprime o código e o nome do produto
    printf("%d - %s\n", raiz->produto->codigo, raiz->produto->nome);

    // Imprime a subárvore esquerda
    imprimirArvore(raiz->esquerda, espacos);
}

// Função para liberar a memória de todos os nós da árvore
void liberarArvore(Node* raiz) {
    // Verifica se a raiz é nula
    if (raiz == NULL) {
        return; // Se for nula, não há mais nós para liberar, então retorna
    }

    liberarArvore(raiz->esquerda); // Libera a memória dos nós da subárvore esquerda
    liberarArvore(raiz->direita); // Libera a memória dos nós da subárvore direita
    free(raiz->produto); // Libera a memória do produto armazenado no nó atual
    free(raiz);  // Libera a memória do próprio nó atual
}

// Função para gerar um número aleatório entre min e max
int randint(int min, int max) {
    return min + rand() % (max - min + 1);
}

/*
   9 - O código deve implementar uma opção de geração automática e aleatória de uma árvore balanceada com 07 elementos.
   Função para criar uma árvore AVL balanceada com 7 elementos
*/
Node* gerarArvoreAleatoria() {
    Node* raiz = NULL;
    int i, codigo, quantidade;
    float preco;
    char nome[50];

    // Semente para a geração de números aleatórios
    srand(time(NULL));

    // Insere 7 elementos aleatórios na árvore
    for (i = 0; i < 7; i++) {
        codigo = randint(1000, 9999); // Gera um código aleatório de 4 dígitos
        sprintf(nome, "Produto%d", codigo); // Gera um nome aleatório baseado no código
        quantidade = randint(1, 100); // Gera uma quantidade aleatória entre 1 e 100
        preco = randint(1, 1000) / 10.0f; // Gera um preço aleatório entre 0.1 e 100.0
        raiz = inserir(raiz, codigo, nome, quantidade, preco); // Insere o produto na árvore
    }
    return raiz;
}