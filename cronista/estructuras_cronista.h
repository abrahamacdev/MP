//
// Created by abraham on 30/3/21.
//

#ifndef MP_ESTRUCTURAS_CRONISTA_H
#define MP_ESTRUCTURAS_CRONISTA_H

    typedef struct {
        char *id_jugador;   // Id con 2 digitos
        char *id_equipo;    // Id del equipo
        char *nombre;       // Nombre del jugador con 20 caracteres
        int precio;         // Precio del futbolista
        int valoracion;     // Valoracion del jugador (0-10)
    } futbolista;

    typedef struct {
        futbolista* futbolistas;
        int numFutbolistas;
    } vector_futbolistas;

    typedef struct {
        char *id_equipo;                // Id con 2 digitos
        char *nombre;                   // Nombre del equipo con 20 caracteres maximo (termina en \0)
        vector_futbolistas vectorFutbolistas;  // Futbolistas del equipo
    } equipo;

    typedef struct {
        equipo* equipos;
        int numEquipos;
    } vector_equipos;



#endif //MP_ESTRUCTURAS_CRONISTA_H
