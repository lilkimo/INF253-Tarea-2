#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    void **contenido;

    int capacidad;  // Refiere a la capacidad máxima
    int largo;      // Refiere al espacio ocupado

    int (* cmpElemento)(void *, void *);
    void (* printElemento)(void *);
    
    int error;
} tHeap;

tHeap * newHeap(int (* cmpElemento)(void *, void *), void (* printElemento)(void *));
void deleteHeap(tHeap *heap);
void clearHeap(tHeap *heap);
void *topHeap(tHeap* heap);
int sizeHeap(tHeap* heap);
void popHeap(tHeap* heap);
void pushHeap(tHeap* heap, void *elemento);
int is_goodHeap(tHeap* heap);
int emptyHeap(tHeap* heap);
void printheap(tHeap* heap);

#endif