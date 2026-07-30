#include "estadisticas.h"
#include "destino.h"
#include "viaje.h"
#include <stdlib.h>

double promedioPasajerosEnEspera(const Destino* lista) {
    if (!lista) {
        return 0.0;
    }
    int totalEspera = 0;
    int destinos = 0;
    while (lista) {
        totalEspera += cantidadPasajerosEnEspera(lista);
        destinos++;
        lista = lista->siguiente;
    }
    return destinos > 0 ? (double)totalEspera / destinos : 0.0;
}

double promedioPasajerosEmbarcadosPorViaje(const Destino* lista) {
    if (!lista) {
        return 0.0;
    }
    int totalEmbarcados = 0;
    int totalViajes = 0;
    while (lista) {
        totalEmbarcados += lista->totalPasajerosEmbarcados;
        totalViajes += contarViajesDestino(lista);
        lista = lista->siguiente;
    }
    return totalViajes > 0 ? (double)totalEmbarcados / totalViajes : 0.0;
}

const Destino* destinoConMayorEspera(const Destino* lista) {
    if (!lista) {
        return NULL;
    }
    const Destino* mayor = lista;
    int maxEspera = cantidadPasajerosEnEspera(lista);
    lista = lista->siguiente;
    while (lista) {
        int espera = cantidadPasajerosEnEspera(lista);
        if (espera > maxEspera) {
            maxEspera = espera;
            mayor = lista;
        }
        lista = lista->siguiente;
    }
    return mayor;
}

const Destino* destinoConMenorEspera(const Destino* lista) {
    if (!lista) {
        return NULL;
    }
    const Destino* menor = lista;
    int minEspera = cantidadPasajerosEnEspera(lista);
    lista = lista->siguiente;
    while (lista) {
        int espera = cantidadPasajerosEnEspera(lista);
        if (espera < minEspera) {
            minEspera = espera;
            menor = lista;
        }
        lista = lista->siguiente;
    }
    return menor;
}

const Destino* destinoConMayorEmbarcacion(const Destino* lista) {
    if (!lista) {
        return NULL;
    }
    const Destino* mayor = lista;
    int maxEmbarcados = lista->totalPasajerosEmbarcados;
    lista = lista->siguiente;
    while (lista) {
        if (lista->totalPasajerosEmbarcados > maxEmbarcados) {
            maxEmbarcados = lista->totalPasajerosEmbarcados;
            mayor = lista;
        }
        lista = lista->siguiente;
    }
    return mayor;
}

const Destino* destinoConMenorEmbarcacion(const Destino* lista) {
    if (!lista) {
        return NULL;
    }
    const Destino* menor = lista;
    int minEmbarcados = lista->totalPasajerosEmbarcados;
    lista = lista->siguiente;
    while (lista) {
        if (lista->totalPasajerosEmbarcados < minEmbarcados) {
            minEmbarcados = lista->totalPasajerosEmbarcados;
            menor = lista;
        }
        lista = lista->siguiente;
    }
    return menor;
}

int totalPasajerosRegistrados(const Destino* lista) {
    int total = 0;
    while (lista) {
        total += lista->totalPasajerosRegistrados;
        lista = lista->siguiente;
    }
    return total;
}

int totalPasajerosEmbarcados(const Destino* lista) {
    int total = 0;
    while (lista) {
        total += lista->totalPasajerosEmbarcados;
        lista = lista->siguiente;
    }
    return total;
}
