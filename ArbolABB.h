#ifndef ARBOLABB_H
#define ARBOLABB_H

#include <stdbool.h>

typedef struct ABBNode {
    int codigo;
    int capacidad;
    int destinoCodigo;
    struct ABBNode* izq;
    struct ABBNode* der;
} ABBNode;

ABBNode* crearNodoABB(int codigo, int capacidad, int destinoCodigo);
void insertarABB(ABBNode** raiz, int codigo, int capacidad, int destinoCodigo);
ABBNode* buscarABB(const ABBNode* raiz, int codigo);
void recorridoInordenABB(const ABBNode* raiz);
void recorridoPreordenABB(const ABBNode* raiz);
void liberarABB(ABBNode* raiz);

#endif