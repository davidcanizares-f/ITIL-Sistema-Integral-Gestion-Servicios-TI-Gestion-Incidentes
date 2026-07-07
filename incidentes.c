/*
 * incidentes.c
 Aquí colocamos toda la funcionalidad del programa y las acciones de todas las funciones.
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

// Busca un incidente por su código y muestra todos sus datos en pantalla
void buscarIncidente(struct incidente *cabeza) {
    int codigoBuscado;
    bool encontrado = false;
    struct incidente *actual = cabeza;

    if (cabeza == NULL) {
        printf(C_YELLOW "\n[INFO] El sistema no tiene incidentes registrados.\n" C_RESET);
        return;
    }

    printf(C_YELLOW C_BOLD "\n=========== BUSCADOR DE INCIDENTES ==========\n" C_RESET);
    printf("> Ingrese Codigo a buscar: ");
    while (scanf("%d", &codigoBuscado) != 1 || codigoBuscado <= 0) {
        printf(C_RED "  [ERROR] Ingrese un numero valido.\n" C_RESET);
        while (getchar() != '\n');
        printf("> Ingrese Codigo a buscar: ");
    }
    getchar();
    
    // Recorre la lista enlazada buscando el código
    while (actual != NULL) {
        if (actual->codigo == codigoBuscado) {
            encontrado = true;
            printf(C_CYAN "\n+------------------------------------------------+\n" C_RESET);
            printf(C_BOLD "  DETALLES DEL INCIDENTE #%d\n" C_RESET, actual->codigo);
            printf(C_CYAN "+------------------------------------------------+\n" C_RESET);
            printf("  " C_BOLD "Fecha:" C_RESET " %s\n", actual->fecha);
            printf("  " C_BOLD "Usuario:" C_RESET " %s\n", actual->usuario);
            printf("  " C_BOLD "Departamento:" C_RESET " %s\n", actual->departamento);
            printf("  " C_BOLD "Descripcion:" C_RESET " %s\n", actual->descripcion);
            printf("  " C_BOLD "Prioridad:" C_RESET " %s\n", actual->prioridad);
            
            /* Colorear el estado dependiendo de cuál sea */
            printf("  " C_BOLD "Estado:" C_RESET " ");
            if (strcmp(actual->estado, "Resuelto") == 0) printf(C_GREEN "%s\n" C_RESET, actual->estado);
            else if (strcmp(actual->estado, "Abierto") == 0) printf(C_RED "%s\n" C_RESET, actual->estado);
            else printf(C_YELLOW "%s\n" C_RESET, actual->estado);
            
            printf(C_CYAN "+------------------------------------------------+\n" C_RESET);
            break; // ya se encontró, no hace falta seguir recorriendo
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf(C_RED "\n[ERROR] No se encontro ningun incidente con el codigo %d.\n" C_RESET, codigoBuscado);
    }
}

// Busca un incidente por código y permite cambiar su estado
void modificarEstado(struct incidente *cabeza) {
    int codigoBuscado, opcionEstado;
    bool encontrado = false;
    struct incidente *actual = cabeza;

    if (cabeza == NULL) {
        printf(C_YELLOW "\n[INFO] El sistema no tiene incidentes registrados.\n" C_RESET);
        return;
    }

    printf(C_YELLOW C_BOLD "\n============= ACTUALIZAR ESTADO =============\n" C_RESET);
    printf("> Codigo del incidente: ");
    while (scanf("%d", &codigoBuscado) != 1 || codigoBuscado <= 0) {
        printf(C_RED "  [ERROR] Ingrese un numero valido.\n" C_RESET);
        while (getchar() != '\n');
        printf("> Codigo del incidente: ");
    }
    getchar();

    // Se busca el incidente con ese código
    while (actual != NULL) {
        if (actual->codigo == codigoBuscado) {
            encontrado = true;
            break;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf(C_RED "\n[ERROR] Incidente no encontrado.\n" C_RESET);
        return;
    }

    printf("\n" C_BOLD "Estado Actual:" C_RESET " %s\n", actual->estado);
    printf("Nuevo Estado " C_CYAN "[1]Abierto [2]En Proceso [3]Resuelto [4]Cancelar" C_RESET ": ");

    while (scanf("%d", &opcionEstado) != 1 || opcionEstado < 1 || opcionEstado > 4) {
        printf(C_RED "  [ERROR] Opcion invalida.\n" C_RESET);
        while (getchar() != '\n');
        printf("Escoja: ");
    }
    getchar();

    // Según la opción elegida se actualiza el estado, o se cancela la operación
    switch (opcionEstado) {
        case 1: strcpy(actual->estado, "Abierto"); break;
        case 2: strcpy(actual->estado, "En Proceso"); break;
        case 3: strcpy(actual->estado, "Resuelto"); break;
        case 4: 
            printf(C_YELLOW "\n[INFO] Operacion cancelada.\n" C_RESET);
            return; 
    }

    printf(C_GREEN C_BOLD "\n[EXITO] Estado actualizado a '%s'.\n" C_RESET, actual->estado);
}
// Recorre toda la lista mostrando únicamente los incidentes con estado "Abierto"
void listarAbiertos(struct incidente *cabeza) {
    struct incidente *actual = cabeza;
    bool hayAbiertos = false;

    printf(C_YELLOW C_BOLD "\n====================== INCIDENTES ABIERTOS ======================\n" C_RESET);

    while (actual != NULL) {
        if (strcmp(actual->estado, "Abierto") == 0) {
            printf(C_CYAN "[INCIDENTE #%d]\n" C_RESET, actual->codigo);
            printf("  " C_BOLD "Prioridad:" C_RESET " %s\n", actual->prioridad);
            printf("  " C_BOLD "Departamento:" C_RESET " %s\n", actual->departamento);
            printf("  " C_BOLD "Descripcion:" C_RESET " %s\n", actual->descripcion);
            printf("-----------------------------------------------------------------\n");
            hayAbiertos = true;
        }
        actual = actual->siguiente;
    }

    // Si no se encontró ninguno abierto, se avisa al usuario
    if (!hayAbiertos) {
        printf(C_GREEN "  ¡Excelente! No hay incidentes abiertos en este momento.\n" C_RESET);
        printf("=================================================================\n");
    }
}

// Filtra los incidentes según la prioridad que elija el usuario y los muestra
void listarPorPrioridad(struct incidente *cabeza) {
    struct incidente *actual = cabeza;
    int opcionPrioridad;
    char prioridadBuscada[20];
    bool hayIncidentes = false;

    if (cabeza == NULL) {
        printf(C_YELLOW "\n[INFO] El sistema no tiene incidentes registrados.\n" C_RESET);
        return;
    }

    printf(C_YELLOW C_BOLD "\n=========== FILTRAR POR PRIORIDAD ===========\n" C_RESET);
    printf("> Seleccione Prioridad " C_CYAN "[1]Baja [2]Media [3]Alta [4]Critica" C_RESET ": ");
    while ((scanf("%d", &opcionPrioridad) != 1) || opcionPrioridad < 1 || opcionPrioridad > 4) {
        printf(C_RED "  [ERROR] Opcion invalida.\n" C_RESET);
        while (getchar() != '\n');
        printf("> Seleccione: ");
    }
    getchar();

    // Se traduce la opción numérica a la cadena de texto de la prioridad
    if (opcionPrioridad == 1) strcpy(prioridadBuscada, "Baja");
    else if (opcionPrioridad == 2) strcpy(prioridadBuscada, "Media");
    else if (opcionPrioridad == 3) strcpy(prioridadBuscada, "Alta");
    else strcpy(prioridadBuscada, "Critica");

    printf(C_CYAN "\n--- RESULTADOS PARA PRIORIDAD: %s ---\n" C_RESET, prioridadBuscada);

    // Se recorre la lista mostrando solo los que coincidan con la prioridad elegida
    while (actual != NULL) {
        if (strcmp(actual->prioridad, prioridadBuscada) == 0) {
            printf(C_YELLOW "[INCIDENTE #%d]\n" C_RESET, actual->codigo);
            
            /* Colorear el estado dependiendo de cuál sea */
            printf("  " C_BOLD "Estado:" C_RESET " ");
            if (strcmp(actual->estado, "Resuelto") == 0) printf(C_GREEN "%s\n" C_RESET, actual->estado);
            else if (strcmp(actual->estado, "Abierto") == 0) printf(C_RED "%s\n" C_RESET, actual->estado);
            else printf(C_YELLOW "%s\n" C_RESET, actual->estado);

            printf("  " C_BOLD "Descripcion:" C_RESET " %s\n", actual->descripcion);
            printf("------------------------------------------------------\n");
            hayIncidentes = true;
        }
        actual = actual->siguiente;
    }

    if (!hayIncidentes) {
        printf(C_YELLOW "  No se encontraron incidentes con esta prioridad.\n" C_RESET);
        printf("------------------------------------------------------\n");
    }
}

// Elimina un incidente de la lista, pero solo si su estado es "Resuelto"
void eliminarResuelto(struct incidente **ptrCabeza, struct incidente **ptrCola, struct incidente *cabeza) {
    int codigoBuscado;
    bool encontrado = false;
    struct incidente *actual = *ptrCabeza;

    if (*ptrCabeza == NULL) {
        printf(C_YELLOW "\n[INFO] El sistema no tiene incidentes registrados.\n" C_RESET);
        return;
    }
    // Primero se revisa si hay incidentes resueltos antes de pedir el código a eliminar
    int hayResueltos = listarResueltos(cabeza);
    if(hayResueltos == 0){
        return;
    }
    printf(C_RED C_BOLD "\n============= ELIMINAR INCIDENTE RESUELTO ============\n" C_RESET);
    printf("> Ingrese Codigo a eliminar: ");
    while (scanf("%d", &codigoBuscado) != 1 || codigoBuscado <= 0) {
        printf(C_RED "  [ERROR] Ingrese un numero valido.\n" C_RESET);
        while (getchar() != '\n');
        printf("> Ingrese Codigo a eliminar: ");
    }
    getchar();

    // Se busca el nodo con el código indicado
    while (actual != NULL) {
        if (actual->codigo == codigoBuscado) {
            encontrado = true;
            break;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) {
        printf(C_RED "\n[ERROR] Incidente #%d no encontrado.\n" C_RESET, codigoBuscado);
        return;
    }

    // Solo se permite borrar si el incidente ya está resuelto
    if (strcmp(actual->estado, "Resuelto") != 0) {
        printf(C_YELLOW "\n[ADVERTENCIA] Solo se pueden eliminar incidentes en estado 'Resuelto'.\n" C_RESET);
        printf("El incidente #%d esta actualmente: %s\n", actual->codigo, actual->estado);
        return;
    }

    /* Desenlazar el nodo */
    // Se reconectan los punteros anterior/siguiente para sacar el nodo de la lista
    if (actual->anterior != NULL) actual->anterior->siguiente = actual->siguiente;
    else *ptrCabeza = actual->siguiente; // si era la cabeza, se actualiza la cabeza

    if (actual->siguiente != NULL) actual->siguiente->anterior = actual->anterior;
    else *ptrCola = actual->anterior; // si era la cola, se actualiza la cola

    free(actual); // se libera la memoria del nodo eliminado
    printf(C_GREEN C_BOLD "\n[EXITO] Incidente #%d eliminado permanentemente.\n" C_RESET, codigoBuscado);
}

// Lee el archivo de texto con los incidentes guardados y reconstruye la lista enlazada
void cargarDatos(struct incidente **ptrCabeza, struct incidente **ptrCola) {
    FILE *archivo = fopen("datos_incidentes.txt", "r");
    if (archivo == NULL) {
        printf(C_YELLOW "\n[INFO] Iniciando base de datos limpia (archivo no encontrado).\n" C_RESET);
        return;
    }

    char linea[500];
    // Se lee línea por línea, cada línea es un incidente separado por "|"
    while (fgets(linea, sizeof(linea), archivo)) {
        struct incidente *nuevo = (struct incidente *)malloc(sizeof(struct incidente));
        if (nuevo == NULL) break;
        
        linea[strcspn(linea, "\n")] = '\0';
        
        // Se van tomando los campos con strtok usando "|" como separador
        char *token = strtok(linea, "|");
        if(token) nuevo->codigo = atoi(token);
        
        token = strtok(NULL, "|");
        if(token) strcpy(nuevo->fecha, token);
        
        token = strtok(NULL, "|");
        if(token) strcpy(nuevo->usuario, token);
        
        token = strtok(NULL, "|");
        if(token) strcpy(nuevo->departamento, token);
        
        token = strtok(NULL, "|");
        if(token) strcpy(nuevo->descripcion, token);
        
        token = strtok(NULL, "|");
        if(token) strcpy(nuevo->prioridad, token);
        
        token = strtok(NULL, "|");
        if(token) strcpy(nuevo->estado, token);
        
        // Se enlaza el nuevo nodo al final de la lista
        nuevo->siguiente = NULL;
        nuevo->anterior = *ptrCola;

        if (*ptrCabeza == NULL) *ptrCabeza = nuevo;
        else (*ptrCola)->siguiente = nuevo;
        
        *ptrCola = nuevo;
    }
    fclose(archivo);
    printf(C_GREEN "\n[INFO] Datos locales cargados exitosamente.\n" C_RESET);
}

// Recorre la lista completa y guarda cada incidente como una línea en el archivo de texto
void guardarDatos(struct incidente *cabeza) {
    FILE *archivo = fopen("datos_incidentes.txt", "w");
    if (archivo == NULL) {
        printf(C_RED "\n[ERROR] No se pudo guardar el archivo de base de datos.\n" C_RESET);
        return;
    }

    struct incidente *actual = cabeza;
    while (actual != NULL) {
        // Se guarda cada campo separado por "|" para poder leerlo después con strtok
        fprintf(archivo, "%d|%s|%s|%s|%s|%s|%s\n", 
                actual->codigo, actual->fecha, actual->usuario, 
                actual->departamento, actual->descripcion, 
                actual->prioridad, actual->estado);
        actual = actual->siguiente;
    }
    fclose(archivo);
}

// Genera un archivo de texto con el reporte final de todos los incidentes registrados
void generarReporte(struct incidente *cabeza) {
    FILE *reporte = fopen("reporte_incidentes.txt", "w");
    if (reporte == NULL) return;

    fprintf(reporte, "================ REPORTE DE INCIDENTES ================\n\n");
    struct incidente *actual = cabeza;
    int contador = 0;

    // Se recorre la lista escribiendo los datos de cada incidente en el archivo
    while (actual != NULL) {
        fprintf(reporte, "[%d] %s\n", actual->codigo, actual->descripcion);
        fprintf(reporte, "    Fecha: %s | Usuario: %s\n", actual->fecha, actual->usuario);
        fprintf(reporte, "    Dpto: %s | Prioridad: %s | Estado: %s\n", actual->departamento, actual->prioridad, actual->estado);
        fprintf(reporte, "--------------------------------------------------------\n");
        actual = actual->siguiente;
        contador++;
    }
    fprintf(reporte, "\nTotal de incidentes registrados: %d\n", contador);
    fprintf(reporte, "========================================================\n");
    fclose(reporte);
}

// Recorre la lista liberando cada nodo, se usa al salir del programa para no dejar memoria sin liberar
void liberarMemoria(struct incidente **ptrCabeza) {
    struct incidente *actual = *ptrCabeza;
    struct incidente *siguiente;
    
    while (actual != NULL) {
        siguiente = actual->siguiente; // se guarda el siguiente antes de liberar el actual
        free(actual);
        actual = siguiente;
    }
    *ptrCabeza = NULL;
}


// Muestra los incidentes que están en estado "Resuelto" y devuelve 1 si encontró alguno, 0 si no
int listarResueltos(struct incidente *cabeza) {
    struct incidente *actual = cabeza;
    bool hayResueltos = false;

    printf(C_YELLOW C_BOLD "\n====================== INCIDENTES RESUELTOS ======================\n" C_RESET);

    while (actual != NULL) {
        if (strcmp(actual->estado, "Resuelto") == 0) {
            printf(C_CYAN "[INCIDENTE #%d]\n" C_RESET, actual->codigo);
            printf("  " C_BOLD "Prioridad:" C_RESET " %s\n", actual->prioridad);
            printf("  " C_BOLD "Departamento:" C_RESET " %s\n", actual->departamento);
            printf("  " C_BOLD "Descripcion:" C_RESET " %s\n", actual->descripcion);
            printf("-----------------------------------------------------------------\n");
            hayResueltos = true;
        }
        actual = actual->siguiente;
    }

    // El valor de retorno se usa en eliminarResuelto() para saber si vale la pena seguir
    if (!hayResueltos) {
        printf(C_GREEN "  No hay incidentes resueltos en este momento.\n" C_RESET);
        printf("=================================================================\n");
        return 0;
    } else{
        return 1;
    }
}