#include "viaje.h"
#include "destino.h"
#include "arbolRN.h"
#include "validaciones.h"
#include <stdio.h>

bool registrarViaje(Destino* destino, int codigo, int capacidad) {
    if (!destino) {
        return false;
    }
    if (!esCodigoValido(codigo) || !esCodigoValido(capacidad)) {
        return false;
    }
    if (viajeCodigoDuplicadoEnDestino(destino, codigo)) {
        return false;
    }
    insertarRN(&destino->raizRN, codigo, capacidad);
    return true;
}

ArbolRNNode* buscarViajeDestino(const Destino* destino, int codigo) {
    if (!destino) {
        return NULL;
    }
    return buscarRN(destino->raizRN, codigo);
}

void mostrarViajesDestino(const Destino* destino) {
    if (!destino) {
        printf("Destino nulo.\n");
        return;
    }
    if (!destino->raizRN) {
        printf("No hay viajes programados para %s.\n", destino->nombre);
        return;
    }
    printf("Viajes programados para %s:\n", destino->nombre);
    mostrarArbolViajesRN(destino->raizRN, destino);
}

int contarViajesDestino(const Destino* destino) {
    return destino ? contarNodosRN(destino->raizRN) : 0;
}
