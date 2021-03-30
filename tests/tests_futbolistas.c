//
// Created by abraham on 27/3/21.
//

#include "stdio.h"
#include "tests_futbolistas.h"
#include "../equipos/equipos.h"

void test_anadir_futbolista(){

    int idxEquipo = buscarEquipoPorId("01");
    equipo *equipo = &equiposCargados.equipos[idxEquipo];

    futbolista pepe = {
            .nombre = "Pepe",
            .id_equipo = "01",
            .precio = 100
    };

    int res = anadirFutbolista(&pepe);

    if (!res) printf("Se ha añadido al futbolista\n");
    else printf("No se ha podido añadir al futbolista\n");

    mostrarDatosCompletosTodosEquipos();
}