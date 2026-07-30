#include "validaciones.h"
#include "destino.h"
#include "arbolRN.h"
#include "arbolABB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool esTipoDocumentoValido(int tipo) {
    return tipo == 1 || tipo == 2 || tipo == 3;
}

const char* nombreTipoDocumento(int tipo) {
    switch (tipo) {
        case 1:
            return "Cedula de Ciudadania";
        case 2:
            return "Tarjeta de Identidad";
        case 3:
            return "Pasaporte";
        default:
            return "Tipo invalido";
    }
}

bool esCodigoValido(int codigo) {
    return codigo > 0;
}

int leerEntero(const char* mensaje) {
    char buffer[128];
    long valor;
    char* fin;
    while (true) {
        printf("%s", mensaje);
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            return 0;
        }

        valor = strtol(buffer, &fin, 10);
        if (fin == buffer) {
            printf("Entrada invalida. Intente de nuevo.\n");
            continue;
        }

        while (*fin == ' ' || *fin == '\t' || *fin == '\r' || *fin == '\n') {
            fin++;
        }

        if (*fin != '\0') {
            printf("Entrada invalida. Intente de nuevo.\n");
            continue;
        }

        return (int)valor;
    }
}

bool destinoCodigoDuplicado(Destino* lista, int codigo) {
    return buscarDestinoPorCodigo(lista, codigo) != NULL;
}

bool viajeCodigoDuplicadoEnDestino(const Destino* destino, int codigo) {
    return destino ? buscarRN(destino->raizRN, codigo) != NULL : false;
}

bool viajeCodigoDuplicadoEnABB(const ABBNode* raiz, int codigo) {
    return buscarABB(raiz, codigo) != NULL;
}
