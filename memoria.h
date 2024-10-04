#ifndef MEMORIA_H
#define MEMORIA_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#define TAM_MEMORIA 8192    // Tamanho do array (8KB)

char memoria[TAM_MEMORIA];  // Array que representa a "memória" para alocação

typedef struct Bloco {
    int tamanho;            // Tamanho do bloco (4 BYTES)
    bool livre;             // true se livre, false se ocupado (4 BYTE) pq????
    struct Bloco* proximo;  // Próximo bloco (4 BYTES)
} Bloco;

void inicializa_memoria();
void* aloca(size_t tamanho);
void libera(void* ptr);
void visualiza_memoria();

#endif // MEMORIA_H
