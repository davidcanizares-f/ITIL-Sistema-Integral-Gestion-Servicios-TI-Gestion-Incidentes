/*
 * incidentes.h
 * Archivo de cabecera que define las estructuras de datos y declara
 * los prototipos de todas las funciones del programa de Gestión de Incidentes.
 */

#ifndef INCIDENTES_H
#define INCIDENTES_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/* ─── Paleta de Colores ANSI para la Consola ─── */
// Códigos de escape ANSI para pintar texto en la terminal (colores + negrita)
#define C_RESET  "\x1b[0m" // resetea el color al default de la consola
#define C_RED  "\x1b[31m"  // rojo, se usa para errores
#define C_GREEN  "\x1b[32m" // verde, se usa para mensajes de éxito
#define C_YELLOW "\x1b[33m" // amarillo, se usa para advertencias/info
#define C_BLUE "\x1b[34m"
#define C_CYAN   "\x1b[36m" // cian, se usa para títulos y encabezados
#define C_BOLD "\x1b[1m"     // negrita

/*
 * Estructura incidente (Nodo de la Lista Doblemente Enlazada)
 */
// Cada incidente es un nodo de una lista doblemente enlazada,
// por eso tiene puntero al anterior y al siguiente
struct incidente {
    int codigo;     // identificador único del incidente
    char fecha[20];    // fecha en formato DD/MM/AAAA
    char usuario[100];     // quien reportó el incidente
    char departamento[100];   // departamento al que pertenece
    char descripcion[200];  // breve descripción del problema
    char prioridad[20]; /* Baja, Media, Alta, Critica */
    char estado[20];    /* Abierto, En Proceso, Resuelto */

    struct incidente *siguiente; // apunta al siguiente nodo de la lista
    struct incidente *anterior;  // apunta al nodo anterior de la lista
};

