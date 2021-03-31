//
// Created by abraham on 17/3/21.
//

#ifndef MP_FUTBOLISTAS_H
#define MP_FUTBOLISTAS_H

    #include "../estructuras.h"

    extern int idMaxFutbolista;         // Servira como "cache" a la hora de asignar nuevos ids a los jugadores

    extern void inicializarFutbolistas();   // Cargamos todos los futbolistas a sus correspondientes equipos
    extern int leerFutbolistas();           // Lee los futbolistas del arcchivo
    extern int guardarFutbolistas();        // Guardamos los futbolistas en el archivo
    extern void mostrarDatosFutbolista(futbolista *);   // Muestra los datos del futtbolista recibido por parametros
    extern void reestablecerMemVecCadena(int, char **, int *, int *);
    extern void guardarDatoEnFutbolista(futbolista *temp, char *dato, int indiceCampo);
    extern char * generarIdFutbolista();
    extern int esNumero(char *);            // Comprueba si la cadena recibida por parametros se pude considerar un numero
    extern int cadenaVacia(char *);         // Comprueba si la ccadena recibida esta vacia
    extern void reordenarElementosVector(futbolista *, int, int);   // Reordena los elementos de un vector despues de haber sufrido eliminaciones

    // --- Menu ---
    extern void pedirDatosAnadirFutbolista(futbolista *);
    extern void pedirDatosEliminarFutbolista(futbolista *);
    extern void pedirDatosEditarFutbolista(char **, futbolista *);
    extern void pedirDatosMostrarFutbolistas(equipo *);
    // ------------


    // ----- CRUD -----
    // --- Create ---
    extern int anadirFutbolista(futbolista *);
    extern int anadirFutbolistaConModo(futbolista *, int);      // El modo nos servira para abreviar a la hora de leer los futbolistas

    // --- Delete ---
    extern int eliminarFutbolistaPorNombre(char *);

    // --- Update ---
    extern int modificarFutbolista(char *, futbolista *);

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