# Sistema de Gestion del Terminal Portuario Turistico de Buenaventura

## Descripcion
Este proyecto implementa un sistema de gestion de destinos, pasajeros y viajes en el Terminal Portuario Turistico de Buenaventura.

## Lenguaje
- C (programacion estructurada, apuntadores y memoria dinamica)

## Estructuras de datos utilizadas
- Lista enlazada dinamica de destinos
- Cola FIFO de pasajeros por destino
- Arbol Rojo-Negro para viajes programados por destino
- Arbol ABB historico de viajes

## Estructura de archivos
- main.c
- destino.h / destino.c
- pasajero.h / pasajero.c
- viaje.h / viaje.c
- arbolRN.h / arbolRN.c
- arbolABB.h / arbolABB.c
- estadisticas.h / estadisticas.c
- validaciones.h / validaciones.c
- Makefile
- README.md

## Compilacion
Ejecutar:

    make

O alternativamente:

    gcc -Wall -Wextra -std=c11 -o terminal main.c destino.c pasajero.c viaje.c arbolRN.c arbolABB.c estadisticas.c validaciones.c

## Ejecucion
Ejecutar:

    ./terminal

## Uso basico
1. Registrar destinos dinamicamente.
2. Registrar pasajeros en la cola FIFO de su destino.
3. Registrar viajes programados en el arbol Rojo-Negro del destino.
4. Buscar viajes por codigo y consultar pasajeros en espera o embarcados.
5. Consultar estadisticas del sistema.
