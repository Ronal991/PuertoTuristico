#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "destino.h"
#include "pasajero.h"
#include "viaje.h"
#include "arbolABB.h"
#include "estadisticas.h"
#include "validaciones.h"


static void mostrarOpcionesRegistroDestino(void) {
    printf("\nOpciones de destinos disponibles:\n");
    printf("Opcion 1. La Bocana - Empresa viajaMar\n");
    printf("Opcion 2. Ladrilleros - Empresa MaresTuristico\n");
    printf("Opcion 3. Pianguita - Empresa PlayaAventura\n");
}

static bool registrarDestinoPredeterminado(Destino** lista, int opcion) {
    int codigo = 0;
    const char* nombre = NULL;
    const char* empresa = NULL;

    switch (opcion) {
        case 1:
            codigo = 1;
            nombre = "La Bocana";
            empresa = "viajaMar";
            break;
        case 2:
            codigo = 2;
            nombre = "Ladrilleros";
            empresa = "MaresTuristico";
            break;
        case 3:
            codigo = 3;
            nombre = "Pianguita";
            empresa = "PlayaAventura";
            break;
        default:
            return false;
    }

    return registrarDestino(lista, codigo, nombre, empresa);
}

static void mostrarPasajerosEnEsperaPorDestino(const Destino* lista) {
    const Destino* actual = lista;
    bool encontrado = false;

    while (actual) {
        if (actual->primero) {
            encontrado = true;
            printf("\nDestino: %s\n", actual->nombre);
            Pasajero* pasajero = actual->primero;
            while (pasajero) {
                if (pasajero->estado == EN_ESPERA) {
                    printf("  - Documento: %d | Tipo: %s\n",
                           pasajero->documento,
                           nombreTipoDocumento(pasajero->tipoDocumento));
                }
                pasajero = pasajero->siguiente;
            }
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf("No hay pasajeros en espera registrados.\n");
    }
}

static int embarcarPasajerosEnEspera(Destino* destino, ArbolRNNode* viaje) {

    if (!destino || !viaje)
        return 0;

    if (viaje->estado == VIAJE_FINALIZADO) {
        printf("Este viaje ya fue realizado.\n");
        return 0;
    }

    int embarcados = 0;

    while (destino->primero && embarcados < viaje->capacidad) {

        if (!embarcarPrimerPasajeroEnViaje(destino, viaje))
            break;

        embarcados++;
    }

    if (embarcados > 0)
        viaje->estado = VIAJE_FINALIZADO;

    return embarcados;
}

int main(void) {
    Destino* listaDestinos = NULL;
    ABBNode* raizABB = NULL;
    int opcion = -1;

    while (opcion != 0) {
        printf("\n=== TERMINAL PORTUARIO TURISTICO DE BUENAVENTURA ===\n");
        printf("1. Registrar destino\n");
        printf("2. Registrar pasajero\n");
        printf("3. Mostrar pasajeros por destino\n");
        printf("4. Registrar viaje programado\n");
        printf("5. Buscar viaje\n");
        printf("6. Mostrar arbol de viajes\n");
        printf("7. Mostrar embarcacion\n");
        printf("8. Consultar pasajero\n");
        printf("9. Mostrar estadisticas\n");
        printf("0. Salir\n");
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: {
                mostrarOpcionesRegistroDestino();
                int opcionDestino = leerEntero("Seleccione una opcion: ");
                if (registrarDestinoPredeterminado(&listaDestinos, opcionDestino)) {
                    printf("Destino registrado correctamente.\n");
                } else {
                    printf("Opcion invalida o el destino ya fue registrado.\n");
                }
                break;
            }
            case 2: {
                if (!listaDestinos) {
                    printf("No hay destinos registrados.\n");
                    break;
                }
                mostrarDestinos(listaDestinos);
                printf("\nSeleccione la opcion del destino: ");
                int destinoCodigo = leerEntero("");
                Destino* destino = buscarDestinoPorCodigo(listaDestinos, destinoCodigo);
                if (!destino) {
                    printf("Destino no encontrado.\n");
                    break;
                }
                printf("Tipo de identificacion:\n");
                printf("1. Cedula de Ciudadania\n");
                printf("2. Tarjeta de Identidad\n");
                printf("3. Pasaporte\n");
                int tipoDocumento = leerEntero("Seleccione el tipo de identificacion: ");
                if (!esTipoDocumentoValido(tipoDocumento)) {
                    printf("Tipo de documento invalido.\n");
                    break;
                }
                int documento = leerEntero("Numero de identificacion: ");
                if (!esCodigoValido(documento)) {
                    printf("Documento invalido.\n");
                    break;
                }
                if (!registrarPasajero(destino, documento, tipoDocumento)) {
                    printf("No se pudo registrar pasajero. Documento duplicado o error.\n");
                } else {
                    printf("Pasajero registrado correctamente en espera para %s.\n", destino->nombre);
                }
                break;
            }
            case 3: {
                if (!listaDestinos) {
                    printf("No hay destinos registrados.\n");
                    break;
                }
                printf("Pasajeros en espera por destino:\n");
                mostrarPasajerosEnEsperaPorDestino(listaDestinos);
                break;
            }
            case 4: {
                if (!listaDestinos) {
                    printf("No hay destinos registrados.\n");
                    break;
                }
                mostrarDestinos(listaDestinos);
                printf("\nSeleccione la opcion del destino para el viaje: ");
                int destinoCodigo = leerEntero("");
                Destino* destino = buscarDestinoPorCodigo(listaDestinos, destinoCodigo);
                if (!destino) {
                    printf("Destino no encontrado.\n");
                    break;
                }
                int viajeCodigo = leerEntero("Codigo del viaje: ");
                int capacidad = leerEntero("Capacidad maxima: ");
                if (!esCodigoValido(capacidad)) {
                    printf("Capacidad invalida.\n");
                    break;
                }
                if (viajeCodigoDuplicadoEnDestino(destino, viajeCodigo) || viajeCodigoDuplicadoEnABB(raizABB, viajeCodigo)) {
                    printf("Ya existe un viaje programado para este destino.\n");
                    break;
                }
                if (registrarViaje(destino, viajeCodigo, capacidad)) {
                    insertarABB(&raizABB, viajeCodigo, capacidad, destinoCodigo);
                    ArbolRNNode* viaje = buscarViajeDestino(destino, viajeCodigo);
                    int embarcados = embarcarPasajerosEnEspera(destino, viaje);
                    printf("Viaje registrado y embarcacion realizada correctamente para %s. Pasajeros embarcados: %d.\n",
                           destino->nombre,
                           embarcados);
                } else {
                    printf("Error al registrar viaje.\n");
                }
                break;
            }
            case 5: {
                if (!listaDestinos) {
                    printf("No hay destinos registrados.\n");
                    break;
                }
                int viajeCodigo = leerEntero("Codigo del viaje a buscar: ");
                bool encontrado = false;
                Destino* actual = listaDestinos;
                while (actual) {
                    ArbolRNNode* viaje = buscarViajeDestino(actual, viajeCodigo);
                    if (viaje) {
                        printf("Viaje encontrado en destino %s (codigo %d): Capacidad %d\n",
                               actual->nombre, actual->codigo, viaje->capacidad);
                        encontrado = true;
                        break;
                    }
                    actual = actual->siguiente;
                }
                if (!encontrado) {
                    printf("Viaje no encontrado.\n");
                }
                break;
            }
            case 6: {
                if (!listaDestinos) {
                    printf("No hay destinos registrados.\n");
                    break;
                }
                mostrarDestinos(listaDestinos);
                int destinoCodigo = leerEntero("Codigo del destino para mostrar su arbol de viajes: ");
                Destino* destino = buscarDestinoPorCodigo(listaDestinos, destinoCodigo);
                if (!destino) {
                    printf("Destino no encontrado.\n");
                    break;
                }
                mostrarViajesDestino(destino);
                break;
            }
            case 7: {
                if (!listaDestinos) {
                    printf("No hay destinos registrados.\n");
                    break;
                }
                mostrarDestinos(listaDestinos);
                int destinoCodigo = leerEntero("Codigo del destino para mostrar la embarcacion: ");
                Destino* destino = buscarDestinoPorCodigo(listaDestinos, destinoCodigo);
                if (!destino) {
                    printf("Destino no encontrado.\n");
                    break;
                }
                if (!destino->raizRN) {
                    printf("No hay viajes programados para %s.\n", destino->nombre);
                    break;
                }
                printf("\nDestino: %s\n\n", destino->nombre);
                int viajeCodigo = leerEntero("Codigo del viaje a mostrar: ");
                ArbolRNNode* viaje = buscarViajeDestino(destino, viajeCodigo);
                if (!viaje) {
                    printf("Viaje no encontrado para %s.\n", destino->nombre);
                    break;
                }
                mostrarPasajerosViaje(viaje);
                break;
            }
            case 8: {
                if (!listaDestinos) {
                    printf("No hay destinos registrados.\n");
                    break;
                }
                printf("Tipo de identificacion:\n");
                printf("1. Cedula de Ciudadania\n");
                printf("2. Tarjeta de Identidad\n");
                printf("3. Pasaporte\n");
                int tipoDocumento = leerEntero("Seleccione el tipo de identificacion: ");
                if (!esTipoDocumentoValido(tipoDocumento)) {
                    printf("Tipo de documento invalido.\n");
                    break;
                }
                int documento = leerEntero("Numero de identificacion: ");
                Destino* actual = listaDestinos;
                bool encontrado = false;
                while (actual) {
                    Pasajero* pasajero = buscarPasajeroPorDocumento(actual, documento);
                    if (pasajero && pasajero->tipoDocumento == tipoDocumento) {
                        printf("Pasajero encontrado en destino %s.\n", actual->nombre);
                        printf("  Documento: %d\n", pasajero->documento);
                        printf("  Tipo: %s\n", nombreTipoDocumento(pasajero->tipoDocumento));
                        printf("  Estado: %s\n", pasajero->estado == EN_ESPERA ? "En espera" : "Embarcado");
                        encontrado = true;
                        break;
                    }
                    actual = actual->siguiente;
                }
                if (!encontrado) {
                    printf("Pasajero no encontrado.\n");
                }
                break;
            }
            case 9: {
                if (!listaDestinos) {
                    printf("No hay destinos registrados.\n");
                    break;
                }
                printf("Estadisticas generales:\n");
                printf("  Total destinos: %d\n", contarDestinos(listaDestinos));
                printf("  Total pasajeros registrados: %d\n", totalPasajerosRegistrados(listaDestinos));
                printf("  Total pasajeros embarcados: %d\n", totalPasajerosEmbarcados(listaDestinos));
                printf("  Promedio de pasajeros en espera por destino: %.2f\n", promedioPasajerosEnEspera(listaDestinos));
                printf("  Promedio de pasajeros embarcados por viaje: %.2f\n", promedioPasajerosEmbarcadosPorViaje(listaDestinos));
                const Destino* mayor = destinoConMayorEspera(listaDestinos);
                const Destino* menor = destinoConMenorEspera(listaDestinos);
                const Destino* mayorEmbarcacion = destinoConMayorEmbarcacion(listaDestinos);
                const Destino* menorEmbarcacion = destinoConMenorEmbarcacion(listaDestinos);
                if (mayor) {
                    printf("  Destino con mayor espera: %s (%d pasajeros)\n", mayor->nombre, cantidadPasajerosEnEspera(mayor));
                }
                if (menor) {
                    printf("  Destino con menor espera: %s (%d pasajeros)\n", menor->nombre, cantidadPasajerosEnEspera(menor));
                }
                if (mayorEmbarcacion) {
                    printf("  Destino con mayor embarcacion: %s (%d pasajeros)\n", mayorEmbarcacion->nombre, mayorEmbarcacion->totalPasajerosEmbarcados);
                }
                if (menorEmbarcacion) {
                    printf("  Destino con menor embarcacion: %s (%d pasajeros)\n", menorEmbarcacion->nombre, menorEmbarcacion->totalPasajerosEmbarcados);
                }
                break;
            }
            case 0:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    }

    liberarDestinos(listaDestinos);
    liberarABB(raizABB);
    return 0;
}
