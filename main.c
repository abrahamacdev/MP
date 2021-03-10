#include <stdio.h>
#include <stdlib.h>
#include "./equipos/equipos.h"

void pruebaGuardado(){
    equiposCargados.numEquipos = 2;
    equiposCargados.equipos = malloc(sizeof(equipo) * equiposCargados.numEquipos);

    equiposCargados.equipos[0] = (equipo) {
            .id = "01",
            .nombre = "Cadiz"
    };

    equiposCargados.equipos[1] = (equipo) {
            .id = "02",
            .nombre = "Malaga"
    };

    guardarEquipos();
}

int main() {

    //pruebaGuardado();
    cargarEquipos();



    return 0;
}
