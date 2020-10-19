#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <stdio.h>
#include <ctype.h>

int cmpString(void *string1, void *string2) {
    if (!isalpha(*(char *)string1)) {
        printf("Se ha intentado pushear un string que comienza por un caractér no alfabético:\n\t\"%s\"\n\t ^\nFinalizando forzasamente el programa...\n", (char *)string1);
        exit(0);
    }
    if (!isalpha(*(char *)string2)) {
        printf("Se ha intentado pushear un string que comienza por un caractér no alfabético:\n\t\"%s\"\n\t ^\nFinalizando forzasamente el programa...\n", (char *)string2);
        exit(0);
    }
    
    if (toupper(*(char *)string1) < toupper(*(char *)string2))
        return 1;
    return 0;
}

void printString(void *string) {
    printf("\"%s\"", (char *)string);
}

int cmpEntero(void *entero1, void *entero2) {
    if (*(int *)entero2 > *(int *)entero1)
        return 1;
    return 0;
}
void printEntero(void *entero) {
    printf("%d",*(int *)entero);
}

int cmpFlotante(void *flotante1, void *flotante2) {
    if (*(int *)flotante1 > *(int *)flotante2)
        return 1;
    return 0;
}
void printFlotante(void *flotante) {
    printf("%f",*(float *)flotante);
}

int cmpArreglo(void *arreglo1, void *arreglo2) {
    int i, sumaArreglo = 0;
    int *_arreglo;
    for (i = 1, _arreglo = (int *)arreglo2; i <= _arreglo[0]; i++)
        sumaArreglo += _arreglo[i];
    for (i = 1, _arreglo = (int *)arreglo1; i <= _arreglo[0]; i++)
        sumaArreglo -= _arreglo[i];

    if (sumaArreglo > 0)
        return 1;
    return 0;
}

void printArreglo(void *arreglo) {
    int *_arreglo = (int *)arreglo;
    int largo = _arreglo[0];
    
    printf("[%d",  _arreglo[0]);
    for(int i = 1; i <= largo; i++)
        printf(", %d", _arreglo[i]);
    printf("]");
    return;
}

#endif