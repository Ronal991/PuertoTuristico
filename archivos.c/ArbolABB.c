#include "arbolABB.h"
#include <stdio.h>
#include <stdlib.h>

ABBNode* crearNodoABB(int codigo, int capacidad, int destinoCodigo) {
    ABBNode* nodo = (ABBNode*)malloc(sizeof(ABBNode));
    if (!nodo) {
        return NULL;
    }
    nodo->codigo = codigo;
    nodo->capacidad = capacidad;
    nodo->destinoCodigo = destinoCodigo;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

void insertarABB(ABBNode** raiz, int codigo, int capacidad, int destinoCodigo) {
    if (!raiz) {
        return;
    }
    if (*raiz == NULL) {
        *raiz = crearNodoABB(codigo, capacidad, destinoCodigo);
        return;
    }
    if (codigo < (*raiz)->codigo) {
        insertarABB(&(*raiz)->izq, codigo, capacidad, destinoCodigo);
    } else if (codigo > (*raiz)->codigo) {
        insertarABB(&(*raiz)->der, codigo, capacidad, destinoCodigo);
    }
}

ABBNode* buscarABB(const ABBNode* raiz, int codigo) {
    while (raiz) {
        if (codigo == raiz->codigo) {
            return (ABBNode*)raiz;
        }
        if (codigo < raiz->codigo) {
            raiz = raiz->izq;
        } else {
            raiz = raiz->der;
        }
    }
    return NULL;
}

void recorridoInordenABB(const ABBNode* raiz) {
    if (!raiz) {
        return;
    }
    recorridoInordenABB(raiz->izq);
    printf("  Historico viaje %d | Capacidad: %d | Destino: %d\n",
           raiz->codigo,
           raiz->capacidad,
           raiz->destinoCodigo);
    recorridoInordenABB(raiz->der);
}

void recorridoPreordenABB(const ABBNode* raiz) {
    if (!raiz) {
        return;
    }
    printf("  Nodo %d | Capacidad: %d | Destino: %d\n",
           raiz->codigo,
           raiz->capacidad,
           raiz->destinoCodigo);
    recorridoPreordenABB(raiz->izq);
    recorridoPreordenABB(raiz->der);
}

void liberarABB(ABBNode* raiz) {
    if (!raiz) {
        return;
    }
    liberarABB(raiz->izq);
    liberarABB(raiz->der);
    free(raiz);
}
