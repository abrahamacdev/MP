//
// Created by abraham on 5/3/21.
//

#ifndef MP_EQUIPOS_H
#define MP_EQUIPOS_H

#include "../futbolistas/futbolistas.h"

    typedef struct {
        char *id_equipo;               // Id con 2 digitos
        char *nombre;           // Nombre del equipo con 20 caracteres maximo (termina en \0)
        futbolista *jugadores;  // Futbolistas del equipo
        int numFutbolistas;     // Cantidad de futbolistas que hay en el vector *jugadores
    } equipo;

    typedef struct {
        equipo* equipos;
        int numEquipos;
    } vector_equipos;

    extern vector_equipos equiposCargados;

    extern void inicializarEquipos();   // Inicializa el vector equiposCargados con los datos del correspondiente archivo
    extern int leerEquipos();           // Lee los equipos del archivo
    extern int guardarEquipos();        // Guardamos los equipos en el archivo
    extern void mostrarMenuEquipos();   // Muestra un menu para listar/modificar/añadir/eliminar equipos
    extern void mostrarDatosEquipo(equipo *);   // Muestra los datos del equipo recibido por parametros
    extern void mostrarDatosTodosEquipo();      // Muestra los datos de ttodos los equipos cargados en memoria
    extern void mostrarDatosCompletosTodosEquipos();   // Muestra los datos de todos los equipos junto con sus futbolistas

    // ----- CRUD -----
    // --- Create ---
    extern int anadirEquipo(equipo *);

    // --- Delete ---
    extern int eliminarEquipo(int);

    // --- Update ---
    extern int modificarEquipo(int, equipo);

    // --- Read ---
    extern int buscarEquipoPorId(int);
    extern int buscarEquipoPorNombre(char *);

#endif

#ifndef NOMBRE_ARCHIVO_EQUIPOS
#define NOMBRE_ARCHIVO_EQUIPOS "/home/abraham/Equipos.txt" // TODO Eliminar

#endif

#ifndef SEPARADOR_ARCHIVO_EQUIPOS
#define SEPARADOR_ARCHIVO_EQUIPOS '-'

#endif