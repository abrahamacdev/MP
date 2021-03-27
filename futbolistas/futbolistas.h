//
// Created by abraham on 17/3/21.
//

#ifndef MP_FUTBOLISTAS_H
#define MP_FUTBOLISTAS_H

    typedef struct {
        char *id_jugador;   // Id con 2 digitos
        char *id_equipo;    // Id del equipo
        char *nombre;       // Nombre del jugador con 20 caracteres
        int precio;       // Precio del futbolista
        int valoracion;     // Valoracion del jugador (0-10)
    } futbolista;

    typedef struct {
        futbolista* futbolistas;
        int numFutbolistas;
    } vector_futbolistas;

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
    extern futbolista * buscarFutbolistaPorId(char *);
    extern futbolista * buscarFutbolistaPorNombre(char *);
    extern vector_futbolistas buscarFutbolistasPorEquipo(char *);

#endif //MP_FUTBOLISTAS_H

#ifndef NOMBRE_ARCHIVO_FUTBOLISTAS
#define NOMBRE_ARCHIVO_FUTBOLISTAS "/home/abraham/Futbolistas.txt" // TODO Eliminar

#endif

#ifndef SEPARADOR_ARCHIVO_FUTBOLISTAS
#define SEPARADOR_ARCHIVO_FUTBOLISTAS '-'

#endif

#ifndef MAX_FUTBOLISTAS_POR_EQUIPO
#define MAX_FUTBOLISTAS_POR_EQUIPO 11

#endif