#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Definição da estrutura do nó da árvore
typedef struct Node {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
    struct Node* esquerda;
    struct Node* direita;
} Node;

// Função para criar nó
Node* criarNo(int codigo, const char *nome, int quantidade, float preco) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->codigo = codigo;
    strcpy(novoNo->nome, nome);
    novoNo->quantidade = quantidade;
    novoNo->preco = preco;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um nó na árvore
Node* inserir(Node* raiz, int codigo, const char *nome, int quantidade, float preco) {
    if (raiz == NULL) {
        return criarNo(codigo, nome, quantidade, preco);
    }

    if (codigo < raiz->codigo) {
        raiz->esquerda = inserir(raiz->esquerda, codigo, nome, quantidade, preco);
    } else if (codigo > raiz->codigo) {
        raiz->direita = inserir(raiz->direita, codigo, nome, quantidade, preco);
    }

    // Balanceamento da árvore (a ser implementado)
    return raiz;
}

// Função para buscar um produto pelo código
Node* buscar(Node* raiz, int codigo) {
    if (raiz == NULL || raiz->codigo == codigo) {
        return raiz;
    }

    if (codigo < raiz->codigo) {
        return buscar(raiz->esquerda, codigo);
    } else {
        return buscar(raiz->direita, codigo);
    }
}