#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <stdbool.h>

typedef struct Destino Destino;
typedef struct ABBNode ABBNode;

bool esTipoDocumentoValido(int tipo);
bool esCodigoValido(int codigo);
int leerEntero(const char* mensaje);
bool destinoCodigoDuplicado(Destino* lista, int codigo);
bool viajeCodigoDuplicadoEnDestino(const Destino* destino, int codigo);
bool viajeCodigoDuplicadoEnABB(const ABBNode* raiz, int codigo);
const char* nombreTipoDocumento(int tipo);

#endif
