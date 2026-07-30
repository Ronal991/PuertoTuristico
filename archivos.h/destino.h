#ifndef DESTINO_H
#define DESTINO_H

#include <stdbool.h>
#include "pasajero.h"
#include "arbolRN.h"

typedef struct Destino {
    int codigo;
    char nombre[50];
    char empresa[50];
    Pasajero* primero;
    Pasajero* ultimo;
    Pasajero* embarcados;
    ArbolRNNode* raizRN;
    int totalPasajerosRegistrados;
    int totalPasajerosEmbarcados;
    struct Destino* siguiente;
} Destino;

Destino* crearDestino(int codigo, const char* nombre, const char* empresa);
bool registrarDestino(Destino** lista, int codigo, const char* nombre, const char* empresa);
Destino* buscarDestinoPorCodigo(Destino* lista, int codigo);
void mostrarDestinos(const Destino* lista);
bool modificarDestino(Destino* destino, const char* nombre, const char* empresa);
int cantidadPasajerosEnEspera(const Destino* destino);
void mostrarViajesProgramados(const Destino* destino);
void liberarDestinos(Destino* lista);
int contarDestinos(const Destino* lista);

#endif
