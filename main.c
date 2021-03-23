#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "./equipos/equipos.h"
#include "tests/tests_equipos.h"

int main() {

    setbuf(stdout,NULL);

    // --- Otros ---
    //test_idToChar();
    //test_idToInt();
    // -------------

    // --- Leemos los equipos del archivo ---
    test_cargar_equipos();
    // --------------------------------------

    // --- Busqueda del equipo ---
    /*int resBusqueda = test_pruebaBusquedaPorNombre();
    if (resBusqueda == 0) printf("No ha encontrado el equipo\n");
    else printf("Lo ha encontrado\n");*/
    // ---------------------------

    // --- Añadimos el equipo de prueba ---
    //test_anadirEquipo();
    // --------------------------

    mostrarMenuEquipos();

    // --- Guardamos los datos en el archivo ---
    test_guardar_equipo();
    // -----------------------------------------

    return 0;
}
