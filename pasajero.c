#include "pasajero.h"
#include "destino.h"
#include "validaciones.h"
#include <stdio.h>
#include <stdlib.h>

Pasajero* crearPasajero(int documento, int tipoDocumento) {
    Pasajero* nuevo = (Pasajero*)malloc(sizeof(Pasajero));
    if (!nuevo) {
        return NULL;
    }
    nuevo->documento = documento;
    nuevo->tipoDocumento = tipoDocumento;
    nuevo->estado = EN_ESPERA;
    nuevo->siguiente = NULL;
    return nuevo;
}

bool documentoDuplicadoEnDestino(const Destino* destino, int documento) {
    Pasajero* actual = destino ? destino->primero : NULL;
    while (actual) {
        if (actual->documento == documento) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

bool registrarPasajero(Destino* destino, int documento, int tipoDocumento) {
    if (!destino) {
        return false;
    }
    if (documentoDuplicadoEnDestino(destino, documento)) {
        return false;
    }
    Pasajero* nuevo = crearPasajero(documento, tipoDocumento);
    if (!nuevo) {
        return false;
    }
    if (!destino->primero) {
        destino->primero = nuevo;
        destino->ultimo = nuevo;
    } else {
        destino->ultimo->siguiente = nuevo;
        destino->ultimo = nuevo;
    }
    destino->totalPasajerosRegistrados++;
    return true;
}

Pasajero* consultarPrimerPasajero(const Destino* destino) {
    return destino ? destino->primero : NULL;
}

Pasajero* embarcarPrimerPasajero(Destino* destino) {
    if (!destino || !destino->primero) {
        return NULL;
    }
    Pasajero* salida = destino->primero;
    destino->primero = salida->siguiente;
    if (!destino->primero) {
        destino->ultimo = NULL;
    }
    salida->siguiente = NULL;
    salida->estado = EMBARCADO;
    if (!destino->embarcados) {
        destino->embarcados = salida;
    } else {
        Pasajero* actual = destino->embarcados;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = salida;
    }
    destino->totalPasajerosEmbarcados++;
    return salida;
}

Pasajero* embarcarPrimerPasajeroEnViaje(Destino* destino, ArbolRNNode* viaje) {
    if (!destino || !viaje || !destino->primero || viaje->estado == VIAJE_FINALIZADO) {
        return NULL;
    }
    Pasajero* salida = destino->primero;
    destino->primero = salida->siguiente;
    if (!destino->primero) {
        destino->ultimo = NULL;
    }
    salida->siguiente = NULL;
    salida->estado = EMBARCADO;
    if (!viaje->embarcados) {
        viaje->embarcados = salida;
    } else {
        Pasajero* actual = viaje->embarcados;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = salida;
    }
    destino->totalPasajerosEmbarcados++;
    return salida;
}

void mostrarPasajeros(const Destino* destino) {
    if (!destino) {
        printf("Destino nulo.\n");
        return;
    }
    Pasajero* actual = destino->primero;
    if (!actual) {
        printf("No hay pasajeros en espera para %s.\n", destino->nombre);
        return;
    }
    printf("Pasajeros en espera para %s:\n", destino->nombre);
    while (actual) {
        printf("  Documento: %d | Tipo: %s | Estado: %s\n",
               actual->documento,
               nombreTipoDocumento(actual->tipoDocumento),
               actual->estado == EN_ESPERA ? "En espera" : "Embarcado");
        actual = actual->siguiente;
    }
}

int contarPasajerosEnEspera(const Destino* destino) {
    int contador = 0;
    Pasajero* actual = destino ? destino->primero : NULL;
    while (actual) {
        if (actual->estado == EN_ESPERA) {
            contador++;
        }
        actual = actual->siguiente;
    }
    return contador;
}

static Pasajero* buscarPasajeroEnViajesRN(const ArbolRNNode* viaje, int documento) {
    if (!viaje) {
        return NULL;
    }
    Pasajero* actual = viaje->embarcados;
    while (actual) {
        if (actual->documento == documento) {
            return actual;
        }
        actual = actual->siguiente;
    }
    Pasajero* encontrado = buscarPasajeroEnViajesRN(viaje->izq, documento);
    if (encontrado) {
        return encontrado;
    }
    return buscarPasajeroEnViajesRN(viaje->der, documento);
}

Pasajero* buscarPasajeroPorDocumento(const Destino* destino, int documento) {
    if (!destino) {
        return NULL;
    }
    Pasajero* actual = destino->primero;
    while (actual) {
        if (actual->documento == documento) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return buscarPasajeroEnViajesRN(destino->raizRN, documento);
}

bool esColaVacia(const Destino* destino) {
    return destino ? destino->primero == NULL : true;
}

void liberarColaPasajeros(Destino* destino) {
    if (!destino) {
        return;
    }
    Pasajero* actual = destino->primero;
    while (actual) {
        Pasajero* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    destino->primero = NULL;
    destino->ultimo = NULL;
}

void liberarPasajerosEmbarcados(Destino* destino) {
    if (!destino) {
        return;
    }
    Pasajero* actual = destino->embarcados;
    while (actual) {
        Pasajero* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    destino->embarcados = NULL;
}
