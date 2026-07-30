#include "destino.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Destino* crearDestino(int codigo, const char* nombre, const char* empresa) {
    Destino* nuevo = (Destino*)malloc(sizeof(Destino));
    if (!nuevo) {
        return NULL;
    }
    nuevo->codigo = codigo;
    strncpy(nuevo->nombre, nombre, sizeof(nuevo->nombre) - 1);
    nuevo->nombre[sizeof(nuevo->nombre) - 1] = '\0';
    strncpy(nuevo->empresa, empresa, sizeof(nuevo->empresa) - 1);
    nuevo->empresa[sizeof(nuevo->empresa) - 1] = '\0';
    nuevo->primero = NULL;
    nuevo->ultimo = NULL;
    nuevo->embarcados = NULL;
    nuevo->raizRN = NULL;
    nuevo->totalPasajerosRegistrados = 0;
    nuevo->totalPasajerosEmbarcados = 0;
    nuevo->siguiente = NULL;
    return nuevo;
}

bool registrarDestino(Destino** lista, int codigo, const char* nombre, const char* empresa) {
    if (!lista || !nombre || !empresa) {
        return false;
    }
    Destino* actual = *lista;
    while (actual) {
        if (actual->codigo == codigo) {
            return false;
        }
        actual = actual->siguiente;
    }
    Destino* nuevo = crearDestino(codigo, nombre, empresa);
    if (!nuevo) {
        return false;
    }
    if (*lista == NULL) {
        *lista = nuevo;
    } else {
        actual = *lista;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    return true;
}

Destino* buscarDestinoPorCodigo(Destino* lista, int codigo) {
    while (lista) {
        if (lista->codigo == codigo) {
            return lista;
        }
        lista = lista->siguiente;
    }
    return NULL;
}

void mostrarDestinos(const Destino* lista) {
    if (!lista) {
        printf("No hay destinos registrados.\n");
        return;
    }
    printf("\nDestinos registrados:\n");
    while (lista) {
        printf("  Codigo: %d | Nombre: %s | Empresa: %s | En espera: %d | Embarcados: %d\n",
               lista->codigo,
               lista->nombre,
               lista->empresa,
               cantidadPasajerosEnEspera(lista),
               lista->totalPasajerosEmbarcados);
        lista = lista->siguiente;
    }
}

bool modificarDestino(Destino* destino, const char* nombre, const char* empresa) {
    if (!destino || !nombre || !empresa) {
        return false;
    }
    strncpy(destino->nombre, nombre, sizeof(destino->nombre) - 1);
    destino->nombre[sizeof(destino->nombre) - 1] = '\0';
    strncpy(destino->empresa, empresa, sizeof(destino->empresa) - 1);
    destino->empresa[sizeof(destino->empresa) - 1] = '\0';
    return true;
}

int cantidadPasajerosEnEspera(const Destino* destino) {
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

void mostrarViajesProgramados(const Destino* destino) {
    if (!destino) {
        printf("Destino nulo.\n");
        return;
    }
    if (!destino->raizRN) {
        printf("No hay viajes programados para el destino %s.\n", destino->nombre);
        return;
    }
    printf("Viajes para el destino %s (codigo %d):\n", destino->nombre, destino->codigo);
    mostrarArbolViajesRN(destino->raizRN, destino);
}

static void liberarListaPasajeros(Pasajero* inicio) {
    while (inicio) {
        Pasajero* siguiente = inicio->siguiente;
        free(inicio);
        inicio = siguiente;
    }
}

void liberarDestinos(Destino* lista) {
    while (lista) {
        Destino* siguiente = lista->siguiente;
        liberarListaPasajeros(lista->primero);
        liberarListaPasajeros(lista->embarcados);
        liberarRN(lista->raizRN);
        free(lista);
        lista = siguiente;
    }
}

int contarDestinos(const Destino* lista) {
    int contador = 0;
    while (lista) {
        contador++;
        lista = lista->siguiente;
    }
    return contador;
}
