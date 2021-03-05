//
// Created by abraham on 5/3/21.
//

#ifndef MP_EQUIPOS_H
#define MP_EQUIPOS_H

    typedef struct {
        char *id;       // Id con 2 digitos
        char *nombre;   // Nombre del equipo con 20 caracteres maximo (termina en \0)
    } equipo;


    extern int cargarEquipos();
    void guardarDatoEnEquipo(equipo *, char *, int);

#endif

#ifndef NOMBRE_ARCHIVO_EQUIPOS
#define NOMBRE_ARCHIVO_EQUIPOS "/home/abraham/Equipos.txt"

#endif