//
// Created by abraham on 5/3/21.
//

#ifndef MP_EQUIPOS_H
#define MP_EQUIPOS_H

    #include "../estructuras_cronista.h"

    extern vector_equipos equiposCargados;

    extern int idToInt(char *);
    extern char *idToChar(int);
    extern void guardarDatoEnEquipo(equipo *, char *, int);
    extern void finalizarCarga(equipo *, int, char *);
    extern char* generarIdEquipo();


    extern void inicializarEquipos();   // Inicializa el vector equiposCargados con los datos del correspondiente archivo
    extern int leerEquipos();           // Lee los equipos del archivo
    extern int guardarEquipos();        // Guardamos los equipos en el archivo
    extern void menuEquiposAdministrador();   // Muestra un menu para listar/modificar/añadir/eliminar equipos
    extern void mostrarDatosEquipo(equipo *);   // Muestra los datos del equipo recibido por parametros
    extern void mostrarDatosTodosEquipo();      // Muestra los datos de ttodos los equipos cargados en memoria
    extern void mostrarDatosCompletosTodosEquipos();    // Muestra los datos de todos los equipos junto con sus futbolistas
    extern void mostrarDatosCompletosEquipo(equipo *);  // Muestra los datos del equipo junto con sus futbolista

    // ----- CRUD -----
    // --- Create ---
    extern int anadirEquipo(equipo *);

    // --- Delete ---
    extern int eliminarEquipo(char *);

    // --- Update ---
    extern int modificarEquipo(char *, char *);

    // --- Read ---
    extern int buscarEquipoPorId(char *);
    extern int buscarEquipoPorNombre(char *);

#endif

#ifndef NOMBRE_ARCHIVO_EQUIPOS
#define NOMBRE_ARCHIVO_EQUIPOS "./Equipos.txt"

#endif

#ifndef SEPARADOR_ARCHIVO_EQUIPOS
#define SEPARADOR_ARCHIVO_EQUIPOS '-'

#endif