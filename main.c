#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <math.h>

#include "utilities.h"
#include "heap.h"

typedef struct {
    int base;
    char *numero;
} tBase;

int cmpBase(void *numero1, void *numero2) {
    char *_numero = (*(tBase *)numero1).numero;
    int base = (*(tBase *)numero1).base, largo = strlen(_numero);
    
    int suma = 0;
    for (int i = 0, digito; i < largo; i++) {
        digito = (int)_numero[largo - 1 - i] - '0';
        suma += digito*(int)pow(base, i);
    }
    
    _numero = (*(tBase *)numero2).numero;
    base = (*(tBase *)numero2).base;
    largo = strlen(_numero);

    for (int i = 0, digito; i < largo; i++) {
        digito = (int)_numero[largo - 1 - i] - '0';
        suma -= digito*(int)pow(base, i);
    }

    if (suma > 0)
        return 1;
    return 0;
}

// Muestra los elementos del tipo tBase en pantalla de la forma "<numero>b<base>"".
// Si el número no está en base 10 añade su conversión de la forma "(<numeroEnBase10>b10)".
// Ej:
//      10 en base 4: 10b4(4b10)
//      7 en base 10: 7b10
void printBase(void *numero) {
    char *_numero = (*(tBase *)numero).numero;
    int base = (*(tBase *)numero).base;
    printf("%sb%d", _numero, base);

    if (base != 10) {
        int largo = strlen(_numero), suma = 0;
        for (int i = 0, digito; i < largo; i++) {
            digito = (int)_numero[largo - 1 - i] - '0';
            suma += digito*(int)pow(base, i);
        }
        printf("(%db10)", suma);
    }

    return;
}

void maxBases(tBase *array, int largo, int cantidadDeMaximos) {
    if (cantidadDeMaximos < 1 || cantidadDeMaximos > largo) {
        printf("La cantidad de maximos debe ser un número natural menor o igual al largo del array entregado\nFinalizando forzasamente el programa...\n");
        exit(0);
    }
    
    tHeap *heap = newHeap(cmpBase, printBase);
    for (int i = 0; i < largo; i++)
        pushHeap(heap, &array[i]);
    //printHeap(heap);

    printf("(%d) Máximos: ", cantidadDeMaximos);
    for (;cantidadDeMaximos > 1; cantidadDeMaximos--) {
        printBase(topHeap(heap));
        printf(", ");
        popHeap(heap);
    }
    printBase(heap->contenido[1]);
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
    /*
    Este es un conjunto de pruebas que hice con otro compañero que está en
    el ramo, así que es posible que vean estas mismas pruebas en otra tarea.
    */
    /*
    tBase a;
    a.base = 2;
    a.numero = "101010"; //42
    tBase b;
    b.base = 4;
    b.numero = "32212"; //934
    tBase c;
    c.base = 8;
    c.numero = "777"; //511
    tBase d;
    d.base = 10;
    d.numero = "721"; //721
    tBase e;
    e.base = 10;
    e.numero = "621"; //621
    tBase f;
    f.base = 2;
    f.numero = "1000100110"; //550
    tBase g;
    g.base = 8;
    g.numero = "3217"; //1679

    tBase numeritos[] = {a, b, c, d, e, f, g};
    maxBases(numeritos, 7, 7);
    void *numeritosVoid[] = {&a, &b, &c, &d, &e, &f, &g};
    heapSort(numeritosVoid, 7, cmpBase, printBase);
    
    char* palabritas[] = {"asdfgh", "bhqdgwjq", "cagswjgd", "Rdyuaoisdha", "DOU", "LKJLKJda", "jwlkdq"};
    heapSort((void **)palabritas, 7, cmpString, printString);
    
    float numerotes[] = {31.23, 65.1223, 3.14, 2.165, 234.64, 4564.123, 12312.656, 1234234, 31, 24};
    void *numerotesVoid[] = {&numerotes[0], &numerotes[1], &numerotes[2], &numerotes[3], &numerotes[4], &numerotes[5], &numerotes[6], &numerotes[7], &numerotes[8], &numerotes[9]};
    heapSort(numerotesVoid, 10, cmpFlotante, printFlotante);

    int numeritosxd[] = {7, 2, 4, 21, 12, 55, 32, 87, 11, 111};
    void *numeritosxdVoid[] = {&numeritosxd[0], &numeritosxd[1], &numeritosxd[2], &numeritosxd[3], &numeritosxd[4], &numeritosxd[5], &numeritosxd[6], &numeritosxd[7], &numeritosxd[8], &numeritosxd[9]};
    heapSort(numeritosxdVoid, 10, cmpEntero, printEntero);

    int numeritos1[] = {9, 2, 4, 21, 12, 55, 32, 87, 11, 111};
    int numeritos2[] = {7, 4, 32, 44, 66, 77, 123, 67};
    int numeritos3[] = {10, 0, 11, 22, 33, 44, 55, 66, 77, 88, 99};
    int numeritos4[] = {3, 69, 420, 1313};
    int numeritos5[] = {1, 23};

    void *arregloNumeritosVoid[] = {numeritos1, numeritos2, numeritos3, numeritos4, numeritos5};
    heapSort(arregloNumeritosVoid, 5, cmpArreglo, printArreglo);
    */
    return 0;
}