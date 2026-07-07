/*
 * incidentes.c
 * Implementación con Interfaz Gráfica de Consola Mejorada (CLI).
 * Formato de listas verticales (sin tablas).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "incidentes.h"

// Imprime el título/banner que aparece al iniciar el programa
void etiquetaInicial() {
    printf(C_CYAN C_BOLD "\n=========================================================\n");
    printf("                        INCIDEX           \n");
    printf("=========================================================\n" C_RESET);
}

// Muestra el menú de opciones y valida que el usuario ingrese un número entre 1 y 7
int menuPrincipal(int *ptrOpcion) {
    printf(C_CYAN C_BOLD "\n=========================================================\n" C_RESET);
    printf(C_BOLD "                  MENU DE ACCIONES                       \n" C_RESET);
    printf(C_CYAN C_BOLD "=========================================================\n" C_RESET);
    printf("  " C_CYAN "[1]" C_RESET " Registrar nuevo incidente\n");
    printf("  " C_CYAN "[2]" C_RESET " Buscar incidente por codigo\n");
    printf("  " C_CYAN "[3]" C_RESET " Modificar estado de incidente\n");
    printf("  " C_CYAN "[4]" C_RESET " Listar incidentes abiertos\n");
    printf("  " C_CYAN "[5]" C_RESET " Listar incidentes por prioridad\n");
    printf("  " C_CYAN "[6]" C_RESET " Eliminar incidente resuelto\n");
    printf("  " C_CYAN "[7]" C_RESET " Guardar, generar reporte y Salir\n");
    printf(C_CYAN "---------------------------------------------------------\n" C_RESET);
    printf(C_BOLD "Escoja una opcion: " C_RESET);

    // Mientras no se ingrese un número válido entre 1 y 7, se sigue pidiendo
    while (scanf("%d", ptrOpcion) != 1 || *ptrOpcion > 7 || *ptrOpcion < 1) {
        printf(C_RED "  [ERROR] Opcion invalida. Intente de nuevo.\n" C_RESET);
        while (getchar() != '\n'); // limpia el buffer de entrada si hubo error
        printf(C_BOLD "Escoja una opcion: " C_RESET);
    }
    return *ptrOpcion;
}

// Pide los datos de un incidente nuevo y lo agrega al final de la lista enlazada
void registrarIncidente(struct incidente **ptrCabeza, struct incidente **ptrCola) {
    int codigo;
    char buffer[200];
    int opcionPrioridad, opcionEstado;
    bool duplicado;
    struct incidente *actual;
    
    // Reservamos memoria para el nuevo nodo
    struct incidente *nuevoIncidente = (struct incidente *)malloc(sizeof(struct incidente));
    if (nuevoIncidente == NULL) {
        printf(C_RED "\n[ERROR] Memoria insuficiente.\n" C_RESET);
        return;
    }

    printf(C_YELLOW C_BOLD "\n<<< REGISTRO DE NUEVO INCIDENTE >>>\n" C_RESET);
    printf("-----------------------------------\n");

    /* ── Código ── */
    printf("> Codigo (entero positivo): ");
    while ((scanf("%d", &codigo) != 1) || codigo <= 0) {
        printf(C_RED "  [ERROR] Ingrese un numero valido.\n" C_RESET);
        while (getchar() != '\n'); 
        printf("> Codigo (entero positivo): ");
    }
    getchar(); // se consume el salto de línea que deja el scanf

    /* ── Validación Duplicado ── */
    // Se recorre toda la lista para verificar que el código no exista todavía
    duplicado = true;
    while (duplicado) {
        duplicado = false;
        actual = *ptrCabeza;
        while (actual != NULL) {
            if (actual->codigo == codigo) {
                duplicado = true;
                break;
            }
            actual = actual->siguiente;
        }
        
        // Si el código ya existe, se le pide al usuario que ingrese otro
        if (duplicado) {
            printf(C_RED "  [ERROR] El codigo %d ya existe.\n" C_RESET, codigo);
            printf("> Intente con otro Codigo: ");
            while ((scanf("%d", &codigo) != 1) || codigo <= 0) {
                printf(C_RED "  [ERROR] Ingrese un numero valido.\n" C_RESET);
                while (getchar() != '\n');
                printf("> Codigo (entero positivo): ");
            }
            getchar();
        }
    }
    nuevoIncidente->codigo = codigo;

    /* ── Resto de Datos ── */
    // fgets + strcspn para leer las cadenas de texto y quitarles el salto de línea
    printf("> Fecha (DD/MM/AAAA): ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcpy(nuevoIncidente->fecha, buffer);

    printf("> Usuario reportador: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcpy(nuevoIncidente->usuario, buffer);
    
    printf("> Departamento: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcpy(nuevoIncidente->departamento, buffer);

    printf("> Breve Descripcion: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcpy(nuevoIncidente->descripcion, buffer);

    /* ── Prioridad ── */
    // Se pide un número del 1 al 4 y se traduce al texto correspondiente
    printf("> Prioridad " C_CYAN "[1]Baja [2]Media [3]Alta [4]Critica" C_RESET ": ");
    while ((scanf("%d", &opcionPrioridad) != 1) || opcionPrioridad < 1 || opcionPrioridad > 4) {
        printf(C_RED "  [ERROR] Opcion invalida.\n" C_RESET);
        while (getchar() != '\n');
        printf("> Prioridad: ");
    }
    getchar();
    if (opcionPrioridad == 1) strcpy(nuevoIncidente->prioridad, "Baja");
    else if (opcionPrioridad == 2) strcpy(nuevoIncidente->prioridad, "Media");
    else if (opcionPrioridad == 3) strcpy(nuevoIncidente->prioridad, "Alta");
    else strcpy(nuevoIncidente->prioridad, "Critica");

    /* ── Estado ── */
    // Igual que la prioridad, pero para el estado del incidente
    printf("> Estado " C_CYAN "[1]Abierto [2]En Proceso [3]Resuelto" C_RESET ": ");
    while ((scanf("%d", &opcionEstado) != 1) || opcionEstado < 1 || opcionEstado > 3) {
        printf(C_RED "  [ERROR] Opcion invalida.\n" C_RESET);
        while (getchar() != '\n');
        printf("> Estado: ");
    }
    getchar();
    if (opcionEstado == 1) strcpy(nuevoIncidente->estado, "Abierto");
    else if (opcionEstado == 2) strcpy(nuevoIncidente->estado, "En Proceso");
    else strcpy(nuevoIncidente->estado, "Resuelto");

    /* ── Inserción ── */
    // Se inserta el nuevo nodo al final de la lista doblemente enlazada
    nuevoIncidente->siguiente = NULL;
    nuevoIncidente->anterior = *ptrCola;

    if (*ptrCabeza == NULL) {
        // Si la lista estaba vacía, el nuevo nodo pasa a ser también la cabeza
        *ptrCabeza = nuevoIncidente;
    } else {
        (*ptrCola)->siguiente = nuevoIncidente;
    }
    *ptrCola = nuevoIncidente; // el nuevo nodo pasa a ser la nueva cola

    printf(C_GREEN C_BOLD "\n[EXITO] Incidente #%d registrado correctamente.\n" C_RESET, codigo);
}