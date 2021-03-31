#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "./equipos/equipos.h"
#include "tests/tests_equipos.h"
#include "tests/tests_futbolistas.h"
#include "cronista.h"

void test_futbolistas(){

    // --- Añadimos un futbolista de prueba ---
    //test_anadir_futbolista();
    // -------------------

}

void test_equipos(){

    // --- Otros ---
    //test_idToChar();
    //test_idToInt();
    // -------------

    // --- Busqueda del equipo ---
    /*int resBusqueda = test_pruebaBusquedaPorNombre();
    if (resBusqueda == 0) printf("No ha encontrado el equipo\n");
    else printf("Lo ha encontrado\n");*/
    // ---------------------------

    // --- Añadimos el equipo de prueba ---
    //test_anadirEquipo();
    // --------------------------

    //mostrarMenuEquipos();

    menuCronista();
}

int main() {

    setbuf(stdout,NULL);

    inicializarCronista();

    test_equipos();

    //test_futbolistas();

    almacenarCronista();

    return 0;
}
