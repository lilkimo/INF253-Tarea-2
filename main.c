#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "utilities.h"
#include "heap.c"

typedef struct {
    int base;
    char *numero;
} tBase;

int cmptBase(void *numero1, void *numero2) {
    char *_numero = (*(tBase *)numero1).numero;
    int base = (*(tBase *)numero1).base, largo = strlen(_numero);
    
    int suma = 0;
    for (int i = 0, digito = (int)_numero[largo - 1 - i] - '0'; i < largo; digito = (int)_numero[largo - 1 - (++i)] - '0')
        suma += digito*(int)pow(base, i);
    
    _numero = (*(tBase *)numero2).numero;
    base = (*(tBase *)numero2).base;
    largo = strlen(_numero);

    for (int i = 0, digito = (int)_numero[largo - 1 - i] - '0'; i < largo; digito = (int)_numero[largo - 1 - (++i)] - '0')
        suma -= digito*(int)pow(base, i);

    if (suma > 0)
        return 1;
    return 0;
}

// Muestra los elementos del tipo tBase en pantalla de la forma "<numero>b<base>"".
// Si el número no está en base 10 añade su conversión de la forma "(<numeroEnBase10>b10)".
// Ej:
//      10 en base 4: 10b4(4b10)
//      7 en base 10: 7b10
void printtBase(void *numero) {
    char *_numero = (*(tBase *)numero).numero;
    int base = (*(tBase *)numero).base;
    printf("%sb%d", _numero, base);

    if (base != 10) {
        int largo = strlen(_numero), suma = 0;
        for (int i = 0, digito = (int)_numero[largo - 1 - i] - '0'; i < largo; digito = (int)_numero[largo - 1 - (++i)] - '0')
            suma += digito*(int)pow(base, i);
        printf("(%db10)", suma);
    }

    return;
}

void maxBases(tBase *array, int largo, int cantidadDeMaximos) {
    if (cantidadDeMaximos < 1 || cantidadDeMaximos > largo) {
        printf("La cantidad de maximos debe ser un número natural menor o igual al largo del array entregado\nFinalizando forzasamente el programa...\n");
        exit(0);
    }
    
    tHeap *heap = newHeap(cmptBase, printtBase);
    for (int i = 0; i < largo; i++)
        pushHeap(heap, &array[i]);
    //printHeap(heap);

    printf("(%d) Máximos: ", cantidadDeMaximos);
    for (;cantidadDeMaximos > 1; cantidadDeMaximos--) {
        printtBase(topHeap(heap));
        printf(", ");
        popHeap(heap);
    }
    printtBase(heap->contenido[1]);
    printf("\n");

    deleteHeap(heap);
    return;
}

void heapSort(void **array, int largo, int (* cmpElemento)(void *, void *), void (* printElemento)(void *)) {
    tHeap *heap = newHeap(cmpElemento, printElemento);
    for (int i = 0; i < largo; i++)
        pushHeap(heap, array[i]);
    //printHeap(heap);
    
    printf("Elementos del Heap ordenados: ");
    while (sizeHeap(heap) > 1) {
        printElemento(topHeap(heap));
        printf(", ");
        popHeap(heap);
    }
    printElemento(topHeap(heap));
    printf("\n");

    deleteHeap(heap);
    return;
}

int main() {
    
    tBase a;
    a.base = 10;
    a.numero = "9";
    tBase b;
    b.base = 10;
    b.numero = "3";
    tBase c;
    c.base = 10;
    c.numero = "8";
    tBase d;
    d.base = 10;
    d.numero = "1";
    tBase e;
    e.base = 10;
    e.numero = "2";
    tBase f;
    f.base = 10;
    f.numero = "7";
    tBase g;
    g.base = 10;
    g.numero = "6";
    
    tBase numeritos[] = {a, b, c, d, e, f, g};
    maxBases(numeritos, 7, 7);
    void *numeritosVoid[] = {&a, &b, &c, &d, &e, &f, &g};
    heapSort(numeritosVoid, 7, cmptBase, printtBase);

    return 1;
}