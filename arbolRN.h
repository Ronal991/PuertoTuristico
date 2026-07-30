#ifndef ARBOLRN_H
#define ARBOLRN_H

#include <stdbool.h>

typedef struct Destino Destino;
typedef struct Pasajero Pasajero;

typedef enum { ROJO, NEGRO } Color;
typedef enum { VIAJE_PROGRAMADO, VIAJE_FINALIZADO } EstadoViaje;

typedef struct ArbolRNNode {
    int codigo;
    int capacidad;
    Color color;
    EstadoViaje estado;
    Pasajero* embarcados;
    struct ArbolRNNode* padre;
    struct ArbolRNNode* izq;
    struct ArbolRNNode* der;
} ArbolRNNode;

ArbolRNNode* crearNodoRN(int codigo, int capacidad);
void insertarRN(ArbolRNNode** raiz, int codigo, int capacidad);
ArbolRNNode* buscarRN(const ArbolRNNode* raiz, int codigo);
void recorridoInordenRN(const ArbolRNNode* raiz);
void mostrarArbolViajesRN(const ArbolRNNode* raiz, const Destino* destino);
void mostrarPasajerosViaje(const ArbolRNNode* viaje);
void liberarRN(ArbolRNNode* raiz);
int contarNodosRN(const ArbolRNNode* raiz);

#endif
