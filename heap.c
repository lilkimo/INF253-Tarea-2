#include "heap.h"
#include <string.h>

tHeap * newHeap(int (* cmpElemento)(void *, void *), void (* printElemento)(void *)) {
    tHeap *heap = (tHeap *)malloc(sizeof(tHeap));
    if(heap == NULL){
        return NULL;
    }
    
    heap->capacidad = 1;
    heap->contenido = (void **)malloc(sizeof(tHeap)*(heap->capacidad+1));
    heap->largo = 0;

    heap->error = 0;
    if(heap->contenido == NULL)
        heap->error = 1;
    
    heap->cmpElemento = cmpElemento;
    heap->printElemento = printElemento;

    return heap;
}

void deleteHeap(tHeap *heap) {
    /*
    for (int i = 1; i <= heap->largo; i++)
        free(heap->contenido[i]);
    */
    free(heap->contenido);
    free(heap);
    return;
}

void growHeap(tHeap *heap) {
    heap->capacidad *= 2;
    void **auxiliar = (void **)realloc(heap->contenido, sizeof(void *)*(heap->capacidad+1));
    if (auxiliar == NULL) {
        heap->error = 1;
        return;
    }
    heap->contenido = auxiliar;
    return;
}

void clearHeap(tHeap *heap) {
    /*
    for (int i = 1; i <= heap->largo; i++)
        free(heap->contenido[i]);
    */
    heap->largo = 0;
    
    heap->capacidad = 1;
    void **auxiliar = (void **)realloc(heap->contenido, sizeof(void *)*(heap->capacidad+1));
    if (auxiliar == NULL) {
        heap->error = 1;
        return;
    }
    heap->contenido = auxiliar;
    
    return;
}

void * topHeap(tHeap *heap){
    return heap->contenido[1];
}

int sizeHeap(tHeap *heap){
    return heap->largo;
}

int emptyHeap(tHeap *heap){
    return !(heap->largo > 0);
}

int is_goodHeap(tHeap* heap){
    return !heap->error;
}

// Comentar
void swapInHeap(tHeap *heap, int i, int j) {
    void *auxiliar = heap->contenido[i];
    heap->contenido[i] = heap->contenido[j];
    heap->contenido[j] = auxiliar;
    return;
}

void pushHeap(tHeap *heap, void *elemento) {
    int i = heap->largo + 1;
    if (i > heap->capacidad) {
        growHeap(heap);
        if (!is_goodHeap(heap)) {
            printf("Error al expandir la memoria del heap\n");
            return;
        }
    }

    heap->contenido[i] = elemento;
    while (i > 1) {
        int j = i/2;
        if (heap->cmpElemento(heap->contenido[i], heap->contenido[j]))
            swapInHeap(heap, i, j);
        i = j;
    }
    heap->largo++;
}

void popHeap(tHeap *heap) {
    if (heap->largo < 1) {
        if (heap->largo != 0)
            heap->error = 1;
        return;
    }
    
    int i = 1;
    heap->contenido[i] = heap->contenido[heap->largo--];
    while (2*i <= heap->largo) {
        int izq = 2*i;
        int der = 2*i + 1;

        if (der > heap->largo || heap->cmpElemento(heap->contenido[izq], heap->contenido[der])) {
            if (heap->cmpElemento(heap->contenido[i], heap->contenido[izq]))
                break;
            
            swapInHeap(heap, i, izq);
            i = izq;
        }
        else {
            if (heap->cmpElemento(heap->contenido[i], heap->contenido[der]))
                break;
            
            swapInHeap(heap, i, der);
            i = der;
        }
    }
}

void printHeap(tHeap *heap) {
    printf("Heap:\n");
    printf("\tCapacidad: %d\n\tLargo: %d\n", heap->capacidad, heap->largo);
    printf("\tContenido: [");
    for(int i = 1; i < heap->largo; i++) {
        heap->printElemento(heap->contenido[i]);
        printf(", ");
    }
    if (heap->largo > 0)
        heap->printElemento(heap->contenido[heap->largo]);
    printf("]\n");
    return;
}