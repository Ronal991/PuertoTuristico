#ifndef VIAJE_H
#define VIAJE_H

#include <stdbool.h>

typedef struct Destino Destino;
typedef struct ArbolRNNode ArbolRNNode;

bool registrarViaje(Destino* destino, int codigo, int capacidad);
ArbolRNNode* buscarViajeDestino(const Destino* destino, int codigo);
void mostrarViajesDestino(const Destino* destino);
int contarViajesDestino(const Destino* destino);

#endif
