//
// Created by abraham on 5/3/21.
//

#ifndef MP_EQUIPOS_H
#define MP_EQUIPOS_H

    typedef struct {
        char *id;       // Id con 2 digitos
        char *nombre;   // Nombre del equipo con 20 caracteres maximo (termina en \0)
    } equipo;

    typedef struct {
        equipo* equipos;
        int numEquipos;
    } vector_equipos;

    extern vector_equipos equiposCargados;

    extern void inicializarEquipos();
    extern int cargarEquipos();
    extern void mostrarDatosEquipo(equipo *);
    extern void mostrarDatosTodosEquipo();
    extern int guardarEquipos();

    // ----- CRUD -----
    extern int anadirEquipo(equipo *);
    extern int eliminarEquipo(int);
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