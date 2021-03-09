#include <stdio.h>
#include <stdlib.h>
#include "./equipos/equipos.h"

void pruebaGuardado(){
    numEquipos = 2;
    equiposCargados = malloc(sizeof(equipo) * numEquipos);

    equiposCargados[0] = (equipo) {
            .id = "01",
            .nombre = "Cadiz"
    };

    equiposCargados[1] = (equipo) {
            .id = "02",
            .nombre = "Malaga"
    };

    guardarEquipos();
}

int main() {

    pruebaGuardado();
    cargarEquipos();

    int i;
    for (i = 0; i < numEquipos; i++) {
        mostrarDatosEquipo(&equiposCargados[i]);
    }

    return 0;
}
