//
// Created by abraham on 22/3/21.
//

#include "tests_equipos.h"
#include "string.h"
#include "../equipos/equipos.h"
#include "stdio.h"

void test_idToChar(){

    int id = 2;
    char *res = idToChar(id);

    if (res[0] == '0' && res[1] == '2') printf("Id a char correcto\n");
    else printf("Id a char INCORRECTO\n");
}

void test_idToInt(){
    char *id = "02";
    int res = idToInt(id);

    if (res == 2) printf("Id a int correcto\n");
    else printf("Id a int INCORRECTO\n");
}

void test_anadirEquipo() {

    equipo temp;
    temp.nombre = "Sevilla";

    int res = anadirEquipo(&temp);

    if (res == 0) printf("Se ha añadido el equipo correctamente");
    else printf("NO se ha añadido el equipo");
}

int test_pruebaBusquedaPorNombre(){

    int idx = buscarEquipoPorNombre("Sevilla");

    return idx > -1 && strcmp(equiposCargados.equipos[idx].nombre, "Sevilla") == 0;
}

int test_cargar_equipos() {

    leerEquipos();

    return equiposCargados.numEquipos;
}

int test_guardar_equipo() {

    return guardarEquipos();
}