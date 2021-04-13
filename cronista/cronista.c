//
// Created by abraham on 30/3/21.
//

#include "cronista.h"
#include "equipos/equipos.h"
#include "futbolistas/futbolistas.h"
#include "stdio.h"
#include "stdlib.h"

void pedirDatosEquipo(char **);
void pedirDatosEditarValoracion(int *);
void valorarJugadores();

void pedirDatosEquipo(char **nombreEquipo){

    int continuar = 1;

    *nombreEquipo = malloc(sizeof(char) * 21);

    while (continuar){

        // Pedimos el nombre del jugador
        while (continuar){

            printf("Introduzca el nombre del equipo\n");
            scanf("%20s", *nombreEquipo);

            // Comprobamos que la cadena no este vacia
            if (cadenaVacia(*nombreEquipo)){
                printf("Por favor, introduzca un nombre\n");
            }

            // Comprobamos que exista un equipo con ese nombre
            else {
                int idx = buscarEquipoPorNombre(*nombreEquipo);
                if (idx == -1) printf("No existe ningun equipo con ese nombre, por favor introduzca otro\n");
                else continuar = 0;
            }
        }
    }
}

void pedirDatosEditarValoracion(int *valoracion){

    int continuar = 1;
    while (continuar){

        printf("Introduzca la valoracion del jugador (0-10)\n");
        scanf("%i", valoracion);

        // Comprobamos que la valoracion sea valida
        if (*valoracion < 0 || *valoracion > 10){
            printf("Por favor, introduzca una valoracion entre 0 y 10\n");
        }

        else continuar = 0;
    }
}

void valorarJugadores(){

    char *nombreEquipo = NULL;
    pedirDatosEquipo(&nombreEquipo);
    int idx = buscarEquipoPorNombre(nombreEquipo);
    mostrarDatosCompletosEquipo(&equiposCargados.equipos[idx]);  // Mostramos la informaccion completa del equipo

    char *nombreJugador = malloc(sizeof(char) * 21);
    int continuar = 1;
    while (continuar){

        printf("Introduzca el nombre del jugador\n");
        scanf("%20s", nombreJugador);

        // Comprobamos que la cadena no este vacia
        if (cadenaVacia(nombreJugador)){
            printf("Por favor, introduzca un nombre\n");
        }

        // Comprobamos que exista un jugador con ese nombre
        else {
            futbolista *fut = buscarFutbolistaPorNombre(nombreJugador);
            if (fut == NULL) printf("No existe ningun futbolista con ese nombre, por favor introduzca otro\n");
            else {

                int valoracion = -1;
                pedirDatosEditarValoracion(&valoracion);
                fut->valoracion = valoracion;
                modificarFutbolista(nombreJugador, fut);

                int subContinuar = 1;
                int subOpcion = -1;
                while (subContinuar){

                    printf("¿Quieres seguir valorando jugadores?\n");
                    printf("1. Si\n");
                    printf("2. No\n");
                    scanf("%i", &subOpcion);

                    switch (subOpcion) {

                        case 1:
                            subContinuar = 0;
                            break;

                        case 2:
                            subContinuar = 0;
                            continuar = 0;
                            break;

                        default:
                            printf("Escoja una opcion valida, por favor\n");
                            break;
                    }
                }
            }
        }
    }
}



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
void menu_cronista() {

    int continuar = 1;
    int opcion = -1;
    int mostrarMenuPrincipal = 1;

    while (continuar){

        if (mostrarMenuPrincipal){
            printf("\t\tMenu Cronista\t\t\n");
            printf("1. Listar equipos\n");
            printf("2. Valorar equipos\n");
            printf("3. Salir del sistema\n");
        }

        printf("Escoja una opcion: ");
        scanf("%i", &opcion);

        if (opcion < 1 || opcion > 3) {
            mostrarMenuPrincipal = 0;
            printf("Opcion no valida\n");
        }

        else {

            switch (opcion) {

                case 1:
                    // Mostramos los datos de todos los equipos
                    mostrarDatosTodosEquipo();
                    break;

                case 2:
                    // Valoramos los futbolistas
                    valorarJugadores();
                    break;

                case 3:
                    continuar = 0;
                    break;
            }

            mostrarMenuPrincipal = 1;
        }
    }

}

/**
 * Cabecera: Muestra la opcion 1 del menu del modulo Administrador
 * Precondicion:
 * Postcondicion:
 */
void mostrarMenuEquipos(){
    menuEquiposAdministrador();
}