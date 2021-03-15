#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "./equipos/equipos.h"

int test_anadirEquipo() {

    equipo temp;
    temp.nombre = "Sevilla";

    return anadirEquipo(&temp);
}

int test_pruebaBusquedaPorNombre(){

    int idx = buscarEquipoPorNombre("Sevilla");

    return idx > -1 && strcmp(equiposCargados.equipos[idx].nombre, "Sevilla") == 0;
}

int test_cargar_equipos() {

    cargarEquipos();

    return equiposCargados.numEquipos;
}

int test_guardar_equipo() {

    return guardarEquipos();
}

int main() {

    test_cargar_equipos();

    // --- Busqueda del equipo ---
    int resBusqueda = test_pruebaBusquedaPorNombre();
    if (resBusqueda == 0) printf("No ha encontrado el equipo\n");
    else printf("Lo ha encontrado\n");
    // ---------------------------

    // --- Añadimos el equipo de prueba ---
    /*test_anadirEquipo();
    printf("Añadido: %s\n", equiposCargados.equipos[0].id);
    printf("%s\n", equiposCargados.equipos[0].nombre);*/
    // --------------------------

    // --- Guardamos los datos en el archivo ---
    //test_guardar_equipo();
    // -----------------------------------------

    return 0;
}
