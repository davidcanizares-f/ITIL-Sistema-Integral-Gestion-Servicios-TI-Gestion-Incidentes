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

    etiquetaInicial();// muestra el banner del programa
    cargarDatos(ptrCabeza, ptrCola); // carga los incidentes guardados previamente (si existen)

    // Bucle principal del programa, se repite hasta que el usuario elija la opción 7 (salir)
    do {
        opcionMenuPrincipal = menuPrincipal(ptrOpcionMenuPrincipal);

        switch (opcionMenuPrincipal) {
            case 1: 
                registrarIncidente(ptrCabeza, ptrCola); // pide datos y agrega un nuevo incidente
                guardarDatos(cabeza); // se guarda el cambio en el archivo
                break;
            case 2: 
                buscarIncidente(cabeza); // busca por código y muestra el detalle
                break;
            case 3: 
                modificarEstado(cabeza); // cambia el estado de un incidente
                guardarDatos(cabeza);  // se guarda el cambio en el archivo
                break;
            case 4: 
                listarAbiertos(cabeza); // lista solo los incidentes abiertos
                break;
            case 5: 
                listarPorPrioridad(cabeza); // lista incidentes filtrados por prioridad
                break;
            case 6: 
                eliminarResuelto(ptrCabeza, ptrCola, cabeza); // elimina un incidente ya resuelto
                guardarDatos(cabeza);  // se guarda el cambio en el archivo
                break;
            case 7: 
                // opción de salida: se guarda todo, se genera el reporte final y se libera la memoria
                guardarDatos(cabeza);
                generarReporte(cabeza);
                liberarMemoria(ptrCabeza);
                printf(C_CYAN C_BOLD "\n=========================================================\n" C_RESET);
                printf(C_GREEN C_BOLD "         DATOS GUARDADOS. SALISTE DEL PROGRAMA         \n" C_RESET);
                printf(C_CYAN C_BOLD "=========================================================\n\n" C_RESET);
                break;
        }

    } while (opcionMenuPrincipal != 7); // se sale del bucle cuando eligen la opción 7
    
    return 0;
}