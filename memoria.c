#include "memoria.h"

Bloco* listaLivres = (Bloco*)memoria; // Lista de blocos livres

// Função que inicializa a memória
void inicializa_memoria() {
    listaLivres->tamanho = TAM_MEMORIA - sizeof(Bloco);
    listaLivres->livre = true;
    listaLivres->proximo = NULL;
}

// Função 'aloca'
void* aloca(size_t tamanho) {
    if (tamanho <= 0) {
        printf("Erro: Tamanho inválido para alocação.\n");
        return NULL;
    }

    Bloco* atual = listaLivres;

    while (atual != NULL) {
        // Verifica se o bloco atual está livre e se é grande o suficiente
        if (atual->livre && atual->tamanho >= tamanho) {
            // Divide o bloco se sobrar espaço
            if (atual->tamanho > tamanho + sizeof(Bloco)) {
                Bloco* novoBloco = (Bloco*)((char*)atual + sizeof(Bloco) + tamanho);
                novoBloco->tamanho = atual->tamanho - tamanho - sizeof(Bloco);
                novoBloco->livre = true;
                novoBloco->proximo = atual->proximo;

                atual->tamanho = tamanho;
                atual->proximo = novoBloco;
            }
            atual->livre = false; // Marca o bloco como ocupado
            return (char*)atual + sizeof(Bloco); // Retorna o ponteiro para a área alocada
        }
        atual = atual->proximo; // Avança para o próximo bloco
    }

    printf("Erro: Memória insuficiente para alocação.\n");
    return NULL; // Retorna NULL se não houver memória suficiente
}

// Função 'libera'
void libera(void* ptr) {
    if (ptr == NULL) return; // Verifica se o ponteiro é NULL

    Bloco* bloco = (Bloco*)((char*)ptr - sizeof(Bloco));
    bloco->livre = true; // Marca o bloco como livre

    // Tenta mesclar blocos livres adjacentes
    Bloco* atual = listaLivres;
    while (atual != NULL) {
        if (atual->livre && atual->proximo != NULL && ((Bloco*)atual->proximo)->livre) {
            atual->tamanho += sizeof(Bloco) + ((Bloco*)atual->proximo)->tamanho; // Mescla
            atual->proximo = ((Bloco*)atual->proximo)->proximo; // Remove o próximo bloco
        } else {
            atual = atual->proximo; // Avança para o próximo bloco
        }
    }
}

// Função que visualiza o estado atual da memória
void visualiza_memoria() {
    Bloco* atual = (Bloco*)memoria;
    int indice = 0;

    printf("Estado atual da memória:\n");
    while (atual != NULL) {
        printf("Bloco %d: ", indice);
        printf("Tamanho: %zu, ", atual->tamanho);
        printf("Livre: %s, ", atual->livre ? "Sim" : "Não");
        printf("Posição: %p\n", (void*)atual);

        if (atual->proximo == NULL) {
            break; // Saímos quando não há mais blocos
        }

        atual = (Bloco*)atual->proximo; // Avança para o próximo bloco
        indice++;
    }
    printf("---------------------------\n");
}
