/*
 =============== UNIVERSIDAD DE LAS AMÉRICAS ===============
        FACULTAD DE INGENIERÍA Y CIENCIAS APLICADAS
                INGENIERÍA DE SOFTWARE
                    PROGRAMACIÓN I
Autores:
    -David Cañizares
    -Sebastián Orbe
    -Jean Pierre Rosas
    -Derek Yépez

=============== SISTEMA INTEGRAL DE GESTIÓN DE SERVICIOS TI =============
                          GESTIÓN DE INCIDENTES

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>    INCIDEX   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

*/

// Inclusión de librerías.
#include <stdio.h>
#include <stdlib.h>
#include "incidentes.h"
#include "incidentes.c" // se incluye directamente el .c porque así compilamos todo en un solo archivo

int main() {
    // Punteros a la cabeza y cola de la lista doblemente enlazada de incidentes
    struct incidente *cabeza = NULL;
    struct incidente *cola = NULL;

    // Usamos doble puntero para poder modificar cabeza/cola dentro de las funciones
    struct incidente **ptrCabeza = &cabeza;
    struct incidente **ptrCola = &cola;

    int opcionMenuPrincipal = 0;
    int *ptrOpcionMenuPrincipal = &opcionMenuPrincipal;



     while (opcionMenuPrincipal != 7); // se sale del bucle cuando eligen la opción 7
    
    return 0; 
}
