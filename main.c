#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "cronista/equipos/equipos.h"
#include "cronista/tests/tests_equipos.h"
#include "cronista/tests/tests_futbolistas.h"
#include "cronista/cronista.h"

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

    menu_cronista();
}

int main() {

    setbuf(stdout,NULL);

    inicializarCronista();

    //menuEquiposAdministrador();
    menu_cronista();

    almacenarCronista();

    return 0;
}
