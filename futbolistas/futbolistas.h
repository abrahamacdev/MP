//
// Created by abraham on 17/3/21.
//

#ifndef MP_FUTBOLISTAS_H
#define MP_FUTBOLISTAS_H

#include "../equipos/equipos.h"

    typedef struct {
        char *id_jugador;   // Id con 2 digitos
        char *id_equipo;    // Id del equipo
        char *nombre;       // Nombre del jugador con 20 caracteres
        float precio;       // Precio del futbolista
        int valoracion;     // Valoracion del jugador (0-10)
    } futbolista;

    extern void inicializarFutbolistas();   // Cargamos todos los futbolistas a sus correspondientes equipos
    extern int leerFutbolistas();           // Lee los futbolistas del arcchivo
    extern int guardarFutbolistas();        // Guardamos los futbolistas en el archivo
    extern void mostrarDatosFutbolista(futbolista *);   // Muestra los datos del futtbolista recibido por parametros

    // ----- CRUD -----
    // --- Create ---
    extern int anadirFutbolista(futbolista *);

    // --- Delete ---
    extern int eliminarFutbolista(int);

    // --- Update ---
    extern int modificarFutbolista(int, futbolista *);

    // --- Read ---
    extern int buscarFutbolistaPorId(int);
    extern int buscarFutbolistaPorNombre(char *);

#endif //MP_FUTBOLISTAS_H
