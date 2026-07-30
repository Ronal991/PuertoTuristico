#ifndef PASAJERO_H
#define PASAJERO_H

#include <stdbool.h>

typedef struct Destino Destino;
typedef struct ArbolRNNode ArbolRNNode;

typedef enum {
    EN_ESPERA = 1,
    EMBARCADO = 2
} EstadoPasajero;

typedef struct Pasajero {
    int documento;
    int tipoDocumento;
    int estado;
    struct Pasajero* siguiente;
} Pasajero;

Pasajero* crearPasajero(int documento, int tipoDocumento);
bool registrarPasajero(Destino* destino, int documento, int tipoDocumento);
Pasajero* consultarPrimerPasajero(const Destino* destino);
Pasajero* embarcarPrimerPasajero(Destino* destino);
Pasajero* embarcarPrimerPasajeroEnViaje(Destino* destino, ArbolRNNode* viaje);
void mostrarPasajeros(const Destino* destino);
int contarPasajerosEnEspera(const Destino* destino);
Pasajero* buscarPasajeroPorDocumento(const Destino* destino, int documento);
bool esColaVacia(const Destino* destino);
bool documentoDuplicadoEnDestino(const Destino* destino, int documento);
void liberarColaPasajeros(Destino* destino);
void liberarPasajerosEmbarcados(Destino* destino);

#endif
