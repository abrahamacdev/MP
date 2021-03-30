//
// Created by abraham on 30/3/21.
//

#include "cronista.h"
#include "equipos/equipos.h"
#include "futbolistas/futbolistas.h"

/**
 * Cabecera: Carga los datos necesarios para que el modulo Cronista funcione correctamente
 * Precondicion:
 * Postcondicion:
 */
void inicializarCronista(){
    leerEquipos();
    leerFutbolistas();
}

/**
 * Cabecera: Guarda todos los datos necesarios para que el modulo Cronista funcione correctamente
 * Precondicion:
 * Postcondicion:
 */
void almacenarCronista(){
    guardarEquipos();
    guardarFutbolistas();
}

/**
 * Cabecera: Muestra el menu del modulo Cronista
 * Precondicion:
 * Postcondicion:
 */
void menuCronista() {

}

/**
 * Cabecera: Muestra la opcion 1 del menu del modulo Administrador
 * Precondicion:
 * Postcondicion:
 */
void mostrarMenuEquipos(){
    menuEquiposAdministrador();
}