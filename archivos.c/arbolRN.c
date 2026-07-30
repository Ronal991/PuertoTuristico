#include "arbolRN.h"
#include "destino.h"
#include "validaciones.h"
#include <stdio.h>
#include <stdlib.h>

static void rotarIzquierda(ArbolRNNode** raiz, ArbolRNNode* x) {
    ArbolRNNode* y = x->der;
    x->der = y->izq;
    if (y->izq) {
        y->izq->padre = x;
    }
    y->padre = x->padre;
    if (!x->padre) {
        *raiz = y;
    } else if (x == x->padre->izq) {
        x->padre->izq = y;
    } else {
        x->padre->der = y;
    }
    y->izq = x;
    x->padre = y;
}

static void rotarDerecha(ArbolRNNode** raiz, ArbolRNNode* y) {
    ArbolRNNode* x = y->izq;
    y->izq = x->der;
    if (x->der) {
        x->der->padre = y;
    }
    x->padre = y->padre;
    if (!y->padre) {
        *raiz = x;
    } else if (y == y->padre->izq) {
        y->padre->izq = x;
    } else {
        y->padre->der = x;
    }
    x->der = y;
    y->padre = x;
}

static void insertarFixup(ArbolRNNode** raiz, ArbolRNNode* z) {
    while (z->padre && z->padre->color == ROJO) {
        ArbolRNNode* abuelo = z->padre->padre;
        if (!abuelo) {
            break;
        }
        if (z->padre == abuelo->izq) {
            ArbolRNNode* tio = abuelo->der;
            if (tio && tio->color == ROJO) {
                z->padre->color = NEGRO;
                tio->color = NEGRO;
                abuelo->color = ROJO;
                z = abuelo;
            } else {
                if (z == z->padre->der) {
                    z = z->padre;
                    rotarIzquierda(raiz, z);
                }
                z->padre->color = NEGRO;
                abuelo->color = ROJO;
                rotarDerecha(raiz, abuelo);
            }
        } else {
            ArbolRNNode* tio = abuelo->izq;
            if (tio && tio->color == ROJO) {
                z->padre->color = NEGRO;
                tio->color = NEGRO;
                abuelo->color = ROJO;
                z = abuelo;
            } else {
                if (z == z->padre->izq) {
                    z = z->padre;
                    rotarDerecha(raiz, z);
                }
                z->padre->color = NEGRO;
                abuelo->color = ROJO;
                rotarIzquierda(raiz, abuelo);
            }
        }
    }
    if (*raiz) {
        (*raiz)->color = NEGRO;
    }
}

ArbolRNNode* crearNodoRN(int codigo, int capacidad) {
    ArbolRNNode* nodo = (ArbolRNNode*)malloc(sizeof(ArbolRNNode));
    if (!nodo) {
        return NULL;
    }
    nodo->codigo = codigo;
    nodo->capacidad = capacidad;
    nodo->color = ROJO;
    nodo->estado = VIAJE_PROGRAMADO;
    nodo->embarcados = NULL;
    nodo->padre = NULL;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

void insertarRN(ArbolRNNode** raiz, int codigo, int capacidad) {
    if (!raiz) {
        return;
    }
    ArbolRNNode* nodo = crearNodoRN(codigo, capacidad);
    if (!nodo) {
        return;
    }
    ArbolRNNode* padre = NULL;
    ArbolRNNode* actual = *raiz;
    while (actual) {
        padre = actual;
        if (codigo < actual->codigo) {
            actual = actual->izq;
        } else if (codigo > actual->codigo) {
            actual = actual->der;
        } else {
            free(nodo);
            return;
        }
    }
    nodo->padre = padre;
    if (!padre) {
        *raiz = nodo;
    } else if (codigo < padre->codigo) {
        padre->izq = nodo;
    } else {
        padre->der = nodo;
    }
    insertarFixup(raiz, nodo);
}

ArbolRNNode* buscarRN(const ArbolRNNode* raiz, int codigo) {
    while (raiz) {
        if (codigo == raiz->codigo) {
            return (ArbolRNNode*)raiz;
        }
        if (codigo < raiz->codigo) {
            raiz = raiz->izq;
        } else {
            raiz = raiz->der;
        }
    }
    return NULL;
}

void recorridoInordenRN(const ArbolRNNode* raiz) {
    if (!raiz) {
        return;
    }
    recorridoInordenRN(raiz->izq);
    printf("  Viaje: %d | Capacidad: %d | Color: %s\n",
           raiz->codigo,
           raiz->capacidad,
           raiz->color == ROJO ? "Rojo" : "Negro");
    recorridoInordenRN(raiz->der);
}

static const char* nombreColorRN(Color color) {
    return color == ROJO ? "Rojo" : "Negro";
}

static const char* nombreEstadoViaje(EstadoViaje estado) {
    return estado == VIAJE_FINALIZADO ? "Finalizado" : "Programado";
}

static void mostrarArbolJerarquicoRN(const ArbolRNNode* raiz, int espacio) {
    if (!raiz) {
        return;
    }
    espacio += 8;
    mostrarArbolJerarquicoRN(raiz->der, espacio);
    printf("%*sViaje %d (%s) | Capacidad: %d | Estado: %s\n",
           espacio,
           "",
           raiz->codigo,
           nombreColorRN(raiz->color),
           raiz->capacidad,
           nombreEstadoViaje(raiz->estado));
    mostrarArbolJerarquicoRN(raiz->izq, espacio);
}

static int contarPasajerosEmbarcadosRN(const ArbolRNNode* viaje) {
    int contador = 0;
    const Pasajero* actual = viaje ? viaje->embarcados : NULL;
    while (actual) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

void mostrarArbolViajesRN(const ArbolRNNode* raiz, const Destino* destino) {
    if (!destino) {
        printf("Destino nulo.\n");
        return;
    }
    if (!raiz) {
        printf("No hay viajes programados para %s.\n", destino->nombre);
        return;
    }
    printf("Destino: %s\n\n", destino->nombre);
    mostrarArbolJerarquicoRN(raiz, 0);
    printf("------------------------------------------------\n");
}

static void liberarListaPasajerosViaje(Pasajero* inicio) {
    while (inicio) {
        Pasajero* siguiente = inicio->siguiente;
        free(inicio);
        inicio = siguiente;
    }
}

void liberarRN(ArbolRNNode* raiz) {
    if (!raiz) {
        return;
    }
    liberarRN(raiz->izq);
    liberarRN(raiz->der);
    liberarListaPasajerosViaje(raiz->embarcados);
    free(raiz);
}

void mostrarPasajerosViaje(const ArbolRNNode* viaje) {
    if (!viaje) {
        printf("Viaje no encontrado.\n");
        return;
    }
    printf("Viaje: %d\n", viaje->codigo);
    printf("Estado: %s\n", nombreEstadoViaje(viaje->estado));
    printf("Capacidad: %d\n", viaje->capacidad);
    int totalPasajeros = contarPasajerosEmbarcadosRN(viaje);
    printf("Pasajeros embarcados: %d\n\n", totalPasajeros);
    if (!viaje->embarcados) {
        printf("No hay pasajeros embarcados en este viaje.\n");
        return;
    }
    const Pasajero* pasajero = viaje->embarcados;
    int indice = 1;
    while (pasajero) {
        printf("%d. Documento: %d\n", indice++, pasajero->documento);
        pasajero = pasajero->siguiente;
    }
}

int contarNodosRN(const ArbolRNNode* raiz) {
    if (!raiz) {
        return 0;
    }
    return 1 + contarNodosRN(raiz->izq) + contarNodosRN(raiz->der);
}
