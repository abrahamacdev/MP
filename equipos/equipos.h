//
// Created by abraham on 5/3/21.
//

#ifndef MP_EQUIPOS_H
#define MP_EQUIPOS_H

    typedef struct {
        char *id;       // Id con 2 digitos
        char *nombre;   // Nombre del equipo con 20 caracteres maximo (termina en \0)
    } equipo;

    extern equipo *equiposCargados;
    extern int numEquipos;

    extern int cargarEquipos();
    extern void mostrarDatosEquipo(equipo *);
    extern int guardarEquipos();

#endif

#ifndef NOMBRE_ARCHIVO_EQUIPOS
#define NOMBRE_ARCHIVO_EQUIPOS "/home/abraham/Equipos.txt"

#endif

#ifndef SEPARADOR_ARCHIVO_EQUIPOS
#define SEPARADOR_ARCHIVO_EQUIPOS '-'

#endif