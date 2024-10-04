#include <stdio.h>
#include "memoria.h"

// Estrutura de um nó da lista ligada
typedef struct No {
    int valor;
    struct No* proximo;
} No;

// Função para inserir um valor no início da lista
No* inserir_no_inicio(No* cabeca, int valor) {
    No* novo_no = (No*)aloca(sizeof(No)); // Usa a função aloca
    if (novo_no == NULL) {
        printf("Erro: Memória insuficiente.\n");
        return cabeca;
    }
    novo_no->valor = valor;
    novo_no->proximo = cabeca;
    return novo_no;
}

// Função para imprimir a lista
void imprimir_lista(No* cabeca) {
    No* atual = cabeca;
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

// Função para liberar toda a lista
void liberar_lista(No* cabeca) {
    No* atual = cabeca;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        libera(temp); // Usa a função libera
    }
}

int main() {
    inicializa_memoria();

    visualiza_memoria();

    No* lista = NULL;
    lista = inserir_no_inicio(lista, 10);
    lista = inserir_no_inicio(lista, 20);
    
    visualiza_memoria();

    printf("Lista ligada:\n");
    imprimir_lista(lista);
    liberar_lista(lista);

    visualiza_memoria();

    void* ptr1 = aloca(1000);
    void* ptr2 = aloca(2000);
    void* ptr3 = aloca(3000);

    // Visualizar memória após liberar
    visualiza_memoria();

    libera(ptr2);

    void* ptr4 = aloca(400);
    void* ptr5 = aloca(1500);

    visualiza_memoria();

    libera(ptr1);
    libera(ptr3);
    libera(ptr4);

    visualiza_memoria();

    ptr2 = aloca(9000);

    visualiza_memoria();

    libera(ptr5);
    libera(ptr2);

    visualiza_memoria();
    
    return 0;
}