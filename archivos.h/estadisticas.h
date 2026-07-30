#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include <stdbool.h>

typedef struct Destino Destino;

double promedioPasajerosEnEspera(const Destino* lista);
double promedioPasajerosEmbarcadosPorViaje(const Destino* lista);
const Destino* destinoConMayorEspera(const Destino* lista);
const Destino* destinoConMenorEspera(const Destino* lista);
const Destino* destinoConMayorEmbarcacion(const Destino* lista);
const Destino* destinoConMenorEmbarcacion(const Destino* lista);
int totalPasajerosRegistrados(const Destino* lista);
int totalPasajerosEmbarcados(const Destino* lista);

#endif
