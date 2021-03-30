//
// Created by abraham on 17/3/21.
//

#include "futbolistas.h"
#include "../equipos/equipos.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"



int idMaxFutbolista = 0;


/**
 * Cabecera: Comprueba si la cadena recibida por parametros es un numero
 * Precondicion: cad inicializada
 * Postcondicion:   0-> La cadena no es un numero
 *                  1-> La cadena es un numero
 */
int esNumero(char *cad){
    for (int i = 0; i < strlen(cad); ++i) {
        if (!isdigit(cad[i])) return 0;
    }
    return 1;
}

/**
 * Cabecera: Comprueba si la cadena introducida esta vacia
 * Precondicion: La cadena tiene que estar inicializada
 * Postcondicion: 0->No esta vacia
 *                1->Esta vacia
 */
int cadenaVacia(char *cad){

    int len = strlen(cad);
    if (cad == NULL || len == 0) return 1;

    for (int i = 0; i < len; ++i) {
        if (cad[i] != '\0') return 0;
    }

    return 1;
}

/*
 * Cabecera: Recibe los datos de un futbolista y dependiendo del indice del campo
 * lo guardara donde corresponda dentro del futbolista.
 * Precondicion: *temp tiene que estar inicializada
 *               *dato tiene que estar inicializada
 *               indiceCampo tiene que ser un valor entre (0,1)
 * Postcondicion: El equipo *temp tendra el dato cargado
 */
void guardarDatoEnFutbolista(futbolista *temp, char *dato, int indiceCampo){

    char *dest = malloc(sizeof(char) * strlen(dato) + 1);
    strcpy(dest, dato);

    switch (indiceCampo) {

        // Es el id del jugador
        case 0:
            temp->id_jugador = dest;

            // Guardamos el mayor id de los jugadores
            {
                int idJug = idToInt(dest);
                if (idJug > idMaxFutbolista) idMaxFutbolista = idJug;
            }
            break;

        // Es el id del equipo
        case 1:
            temp->id_equipo = dest;
            break;

        // Es el nombre del futbolista
        case 2:
            temp->nombre = dest;
            break;

        // Es el precio del futbolista
        case 3:
            if (esNumero(dest)){
                temp->precio = atoi(dest);
            }
            break;

        // Es la valoracion del futbolista
        case 4:
            if (esNumero(dest)){
                temp->valoracion = atoi(dest);
            }
            break;
    }
}

/*
 * Cabecera: Preparamos las variabes para trabajar la siguiente cadena
 * Precondicion:
 * Postcondicion: Reinicia las variabes sus valores iniciales
*/
void reestablecerMemVecCadena(int tamBaseVectores, char **tempCadena, int *tamanioVecCadena, int *caracteresInsertados) {
    (*caracteresInsertados) = 0;
    (*tamanioVecCadena) = tamBaseVectores;
    free((*tempCadena));
    (*tempCadena) = (char *) malloc(sizeof(char) * (*tamanioVecCadena));
}

/*
 * Cabecera: Generamos un nuevo id para un futbolista
 * Precondicion:
 * Postcondicion: Devuelve el id del futbolista
*/
char * generarIdFutbolista(){
    idMaxFutbolista++;
    return idToChar(idMaxFutbolista);
}

/*
 * Cabecera: Traemos los elementos de un vector de adelante hacia atras
 * Precondicion: vector inicializado, fin > comienzo >= 0
 * Postcondicion: Devuelve el id del futbolista
*/
void reordenarElementosVector(futbolista *vector, int comienzo, int fin){

    if(comienzo > fin) return;
    if (comienzo < 0) return;
    if (vector == NULL) return;

    for (int i = comienzo; i < fin - 1; ++i) {
        vector[i] = vector[i+1];
    }
}

/**
 * Cabecera: Solicita los datos necesarios para anadir a un futbolista
 * Precondicion:
 * Postcondicion: Devuelve el futbolista con los datos necesarios
 */
void pedirDatosAnadirFutbolista(futbolista *fut){

    int continuar = 1;
    equipo equipo;
    char *nomEquipo;

    fut->nombre = malloc(sizeof(char) * 20);

    // Pedimos el nombre del jugador
    while (continuar){

        printf("Introduzca el nombre del jugador (hasta 20 caracteres)\n");
        scanf("%20s", fut->nombre);

        // Comprobamos que la cadena no este vacia
        if (cadenaVacia(fut->nombre)){
            printf("Por favor, introduzca un nombre\n");
        }

        // Comprobamos que no exista un jugdor con ese nombre
        else {

            futbolista * temp = buscarFutbolistaPorNombre(fut->nombre);
            if (temp != NULL) printf("Ya existe un jugador con ese nombre, por favor introduzca otro\n");
            else continuar = 0;
        }
    }

    // Pedimos el nombre del equipo
    continuar = 1;
    nomEquipo = malloc(sizeof(char) * 21);
    while (continuar){

        printf("Introduzca el nombre del equipo al que pertenecera\n");
        scanf("%s", nomEquipo);

        // Comprobamos que haya introducido un nombre de equipo valido
        if (cadenaVacia(nomEquipo)){
            printf("Por favor, introduzca un nombre\n");
        }

        // Comprobamos que exista un equipo con ese nombre
        else {
            int indxEquipo = buscarEquipoPorNombre(nomEquipo);
            if (indxEquipo == -1) printf("El equipo no existe. Por favor, introduzca otro\n");
            else {
                fut->id_equipo = equiposCargados.equipos[indxEquipo].id_equipo;
                continuar = 0;
            }
        }
    }


    // Pedimos el precio del jugador
    continuar = 1;
    while (continuar){

        printf("Introduzca el precio del jugador (>0)\n");
        scanf("%i", &fut->precio);

        // Comprobamos que haya introducido un precio valido
        if (fut->precio <= 0){
            printf("Por favor, introduzca un precio valido\n");
        }
        else continuar = 0;
    }


}

/**
 * Cabecera: Solicita los datos necesarios para eliminar a un futbolista
 * Precondicion:
 * Postcondicion: Devuelve el futbolista con los datos necesarios
 */
void pedirDatosEliminarFutbolista(futbolista *fut){

    int continuar = 1;

    fut->nombre = malloc(sizeof(char) * 21);

    // Pedimos el nombre del jugador
    while (continuar){

        printf("Introduzca el nombre del jugador (hasta 20 caracteres)\n");
        scanf("%20s", fut->nombre);

        // Comprobamos que la cadena no este vacia
        if (cadenaVacia(fut->nombre)){
            printf("Por favor, introduzca un nombre\n");
        }

            // Comprobamos que no exista un jugdor con ese nombre
        else {

            futbolista *temp = buscarFutbolistaPorNombre(fut->nombre);
            if (temp == NULL) printf("Introduzca el nombre de otro jugador\n");
            else {
                continuar = 0;
            }
        }
    }
}

/**
 * Cabecera: Solicita los datos necesarios para mostrar los futbolistas de un equipo
 * Precondicion:
 * Postcondicion: Devuelve el equipo con los datos necesarios
 */
void pedirDatosMostrarFutbolistas(equipo *eq){

    int continuar = 1;

    eq->nombre = malloc(sizeof(char) * 21);

    // Pedimos el nombre del jugador
    while (continuar){

        printf("Introduzca el nombre del equipo\n");
        scanf("%20s", eq->nombre);

        // Comprobamos que la cadena no este vacia
        if (cadenaVacia(eq->nombre)){
            printf("Por favor, introduzca un nombre\n");
        }

            // Comprobamos que no exista un jugdor con ese nombre
        else {

            int idx = buscarEquipoPorNombre(eq->nombre);
            if (idx == -1) printf("No existe un equipo con ese nombre\n");
            else {
                continuar = 0;

                // Guardamos el id del equipo
                eq->id_equipo = equiposCargados.equipos[idx].id_equipo;
            }
        }
    }
}



void inicializarFutbolistas(){
    leerFutbolistas();
}

/*
 * Cabecera: Lee todos los futbolistas del archivo
 * Precondicion:
 * Postcondicion: Devuelve el estado de la carga:
 *      0-> Todo salio segun lo esperado
 *      1-> Ocurrio un error
*/
int leerFutbolistas(){

    int tamBaseVectores = 8;

    futbolista tempFutbolista;

    char *tempCadena;           // Vector con los caracteres leidos hasta ahora
    int tamanioVecCadena = tamBaseVectores;   // Tamaño del vector de caracteres
    int caracteresInsertados = 0;   // Cantidad de caracteres de la cadena

    int indiceCampo=0;                    // Indica que campo es el leido (0=id, 1=nombre)
    char tempChar;              // Variable en la que iremoos almacenando cada caracter leido
    int continuar = 1;          // 1-> Continuamos || 0->Paramos de iterar
    FILE *archivo;

    // Inicializamos los vectores
    tempCadena = (char *) malloc(sizeof(char) * tamanioVecCadena);

    // No se han cargado equipos
    if (equiposCargados.numEquipos == 0) return 1;

    // Abrimos el archivo para leer los datos
    if ((archivo = fopen(NOMBRE_ARCHIVO_FUTBOLISTAS, "r")) == NULL) return 1;

    while (continuar){

        tempChar = getc(archivo);

        // Comprobamos si es un caracter alfanumerico o valido
        if (isalnum(tempChar) || tempChar == ' ' || tempChar == '_'){

            tempCadena[caracteresInsertados] = tempChar;

            // Comprobamos que quede mas espacio para llenar la #tempCadena
            if (caracteresInsertados == tamanioVecCadena - 1){

                // Agrandamos el tamaño del vector #tempCadena
                tamanioVecCadena += tamBaseVectores;
                tempCadena = realloc(tempCadena, sizeof(char) * tamanioVecCadena);
            }

            // Sumamos el caracter insertado
            caracteresInsertados++;
        }

        // Comprobamos si es el separador de campos "-"
        else if (tempChar == SEPARADOR_ARCHIVO_FUTBOLISTAS){

            // Guardamos el dato recogido hasta ahora en el equipo correspondiente
            guardarDatoEnFutbolista(&tempFutbolista, tempCadena, indiceCampo);

            // Los siguientes datos correspondenn con un campo nuevo
            indiceCampo++;

            // Reestablecemos el vector #tempCadena
            reestablecerMemVecCadena(tamBaseVectores, &tempCadena, &tamanioVecCadena, &caracteresInsertados);
        }

        // Comprobamos si es un salto de linea o final del archivo
        else if(tempChar == '\n' || tempChar == EOF){

            // Guardamos el dato recogido hasta ahora en el futbolista correspondiente
            guardarDatoEnFutbolista(&tempFutbolista, tempCadena, indiceCampo);

            // Reestablecemos el vector #tempCadena
            reestablecerMemVecCadena(tamBaseVectores, &tempCadena, &tamanioVecCadena, &caracteresInsertados);

            // Reestablecemos el indice del campo
            indiceCampo = 0;

            // AÑadimos al futbolista a su respectivo equipo
            anadirFutbolistaConModo(&tempFutbolista, 1);

            // Solo cuando acabemos de leer el archivo pararemmos de iterar
            if (tempChar == EOF){
                continuar = 0;
            }
        }
    }

    // Cerramos el archivo
    fclose(archivo);

    return 0;
}

/*
 * Cabecera: Guarda todos los futbolistas del equipo en el correspondiente archivo
 * Precondicion:
 * Postcondicion: Devuelve el estado del guardado:
 *      0-> Todo salio segun lo esperado
 *      1-> Ocurrio un error
*/
int guardarFutbolistas(){

    FILE *archivo;

    // Si ocurre algun error, retornaremos codigo de estado 1
    if((archivo = fopen(NOMBRE_ARCHIVO_FUTBOLISTAS, "w")) == NULL) return 1;

    // Iteramos cada equipo existente en el vector
    for (int i = 0; i < equiposCargados.numEquipos; i++) {
        equipo *tempEquipo = &equiposCargados.equipos[i];

        // Iteramos cada futbolista del equipo
        for (int j = 0; j < tempEquipo->vectorFutbolistas.numFutbolistas; j++) {

            futbolista *tempFutbolista = &tempEquipo->vectorFutbolistas.futbolistas[j];

            // Escribimos el id del futbolista
            fputs(tempFutbolista->id_jugador, archivo);

            // Escribimos el separador
            fputc(SEPARADOR_ARCHIVO_FUTBOLISTAS, archivo);

            // Escribimos el id del equipo
            fputs(tempFutbolista->id_equipo, archivo);

            // Escribimos el separador
            fputc(SEPARADOR_ARCHIVO_FUTBOLISTAS, archivo);

            // Escribimos el nombre del futbolista
            fputs(tempFutbolista->nombre, archivo);

            // Escribimos el separador
            fputc(SEPARADOR_ARCHIVO_FUTBOLISTAS, archivo);

            // Escribimos el precio del futbolista
            fprintf(archivo, "%i", tempFutbolista->precio);

            // Escribimos el separador
            fputc(SEPARADOR_ARCHIVO_FUTBOLISTAS, archivo);

            // Escribimos la valoracion del futbolista
            fprintf(archivo, "%i", tempFutbolista->valoracion);

            // Comprobamos si quedan mas futbolistas que guardar para añadir el salto de linea
            if (j != tempEquipo->vectorFutbolistas.numFutbolistas - 1){
                fputc('\n', archivo);
            }
        }
    }

    // Cerramos el archivo
    fclose(archivo);

    return 0;
}




// ----- CRUD -----
// --- Create ---
/*
 * Cabecera: Añade el futbolista al sistema
 * Precondicion: futbolista debe de estar inicializado
 * Postcondicion:
 *      0-> Todo salio segun lo esperado
 *      1-> Ocurrio un error
*/
int anadirFutbolista(futbolista *fut){
    return anadirFutbolistaConModo(fut, 0);
}

/*
 * Cabecera: Añade el futbolista al sistema
 * Precondicion: futbolista debe de estar inicializado y el modo debe de estar entre 0-1 (0: Nuevo, 1: Leyendo de archivo)
 * Postcondicion:
 *      0-> Todo salio segun lo esperado
 *      1-> Ocurrio un error
*/
int anadirFutbolistaConModo(futbolista *fut, int modo){
    equipo *equipo;

    // Id del equipo no valido
    int idxEquipo = buscarEquipoPorId(fut->id_equipo);
    if (idxEquipo == -1) return 1;
    equipo = &equiposCargados.equipos[idxEquipo];

    // El equipo no admite mas futbolistas
    if (equipo->vectorFutbolistas.numFutbolistas == MAX_FUTBOLISTAS_POR_EQUIPO) return 1;

    // Nombre no valido
    if (fut->nombre == NULL || strlen(fut->nombre) > 20) return 1;

    // Ya existe otro jugador con ese id o nombre
    futbolista *futPorNombre = buscarFutbolistaPorNombre(fut->nombre);
    if (futPorNombre != NULL) return 1;
    futbolista *futPorId = buscarFutbolistaPorId(fut->id_jugador);
    if (futPorId != NULL) return 1;

    // No tiene un precio valido
    if (fut->precio < 1) return 1;

    // Añadimos algunos datos necesarios para el futbolista
    fut->valoracion = 0;

    // Hay que generar un id para el jugador
    if (modo == 0){
        fut->id_jugador = generarIdFutbolista();
    }

    // No habia futbolistas en el vector, lo inicializamos
    if (equipo->vectorFutbolistas.numFutbolistas == 0){
        equipo->vectorFutbolistas.futbolistas = malloc(sizeof(futbolista));
    }
        // Agrandamos el vector
    else {
        equipo->vectorFutbolistas.futbolistas = realloc(equipo->vectorFutbolistas.futbolistas, sizeof(futbolista) * equipo->vectorFutbolistas.numFutbolistas + 1);
    }

    // Añadimos al futbolista al equipo
    equipo->vectorFutbolistas.futbolistas[equipo->vectorFutbolistas.numFutbolistas] = *fut;
    equipo->vectorFutbolistas.numFutbolistas++;

    return 0;
}



// --- Read ---
/*
 * Cabecera: Busca si hay algun futbolista qque tenga el id recibido por parametros
 * Precondicion: id debe de estar inicializado
 * Postcondicion:
 *      0-> Todo salio segun lo esperado
 *      1-> Ocurrio un error
*/
futbolista * buscarFutbolistaPorId(char *id){

    // No se ha llegado a cargar equipo o ingresar por primmera vez ningun equipo
    if (equiposCargados.numEquipos == 0) return NULL;

    // El id no tiene 2 digitos
    if (id == NULL || strlen(id) != 2) return NULL;

    // Recorremos el vector de los equipos cargados
    for (int i = 0; i < equiposCargados.numEquipos; i++) {

        // Recorremos los jugadores del equipo
        vector_futbolistas *vectorFutbolistas = &equiposCargados.equipos[i].vectorFutbolistas;
        for (int j = 0; j < vectorFutbolistas->numFutbolistas; j++) {

            futbolista *tempFutbolista = &vectorFutbolistas->futbolistas[j];

            // Comprobamos que el id sea el mismo
            if (strcmp(tempFutbolista->id_jugador, id) == 0){
                return tempFutbolista;
            }
        }
    }

    return NULL;
}

/*
 * Cabecera: Busca si hay algun futbolista qque tenga el nombre recibido por parametros
 * Precondicion: nombre debe de estar inicializado
 * Postcondicion:
 *      0-> Todo salio segun lo esperado
 *      1-> Ocurrio un error
*/
futbolista * buscarFutbolistaPorNombre(char *nombre){

    // No se ha llegado a cargar equipo o ingresar por primmera vez ningun equipo
    if (equiposCargados.numEquipos == 0) return NULL;

    // Nombre sin caracteres
    if (nombre == NULL || strlen(nombre) == 0) return NULL;

    // Recorremos el vector de los equipos cargados
    for (int i = 0; i < equiposCargados.numEquipos; i++) {

        // Recorremos los jugadores del equipo
        vector_futbolistas *vectorFutbolistas = &equiposCargados.equipos[i].vectorFutbolistas;
        for (int j = 0; j < vectorFutbolistas->numFutbolistas; j++) {

            futbolista *tempFutbolista = &vectorFutbolistas->futbolistas[j];

            // Comprobamos que el id sea el mismo
            if (strcmp(tempFutbolista->nombre, nombre) == 0){
                return tempFutbolista;
            }
        }
    }

    return NULL;
}


// --- Delete ---
/*
 * Cabecera: Elimina el futbolista que tenga el nombre recibido por parametros
 * Precondicion: el id debe de estar inicializado
 * Postcondicion:
 *      0-> Todo salio segun lo esperado
 *      1-> Ocurrio un error
*/
int eliminarFutbolistaPorNombre(char *nombre){

    // Comprobamos si la cadena es valida
    if (nombre == NULL || cadenaVacia(nombre)) return 1;

    for (int i = 0; i < equiposCargados.numEquipos; ++i) {
        equipo *tempEquipo = &equiposCargados.equipos[i];
        for (int j = 0; j < tempEquipo->vectorFutbolistas.numFutbolistas; ++j) {
            futbolista *tempFutbolista = &tempEquipo->vectorFutbolistas.futbolistas[j];

            // Comprobamos si los ids coinciden
            if (strcmp(tempFutbolista->nombre, nombre) == 0){
                reordenarElementosVector(tempEquipo->vectorFutbolistas.futbolistas, j, tempEquipo->vectorFutbolistas.numFutbolistas);
                tempEquipo->vectorFutbolistas.numFutbolistas--;
                tempEquipo->vectorFutbolistas.futbolistas = realloc(tempEquipo->vectorFutbolistas.futbolistas, sizeof(futbolista) * tempEquipo->vectorFutbolistas.numFutbolistas);
                return 0;
            }
        }
    }

    return 1;
}



// ----- Debug -----
/*
 * Cabecera: Muestra la informacion del futbolista
 * Precondicion: El futbolista debe de esttar inicizalizado
 * Postcondicion:
*/
void mostrarDatosFutbolista(futbolista *futbolista){

    int indxEquipo = buscarEquipoPorId(futbolista->id_equipo);
    char *sinEquipo = "N.E";
    char *nombreEquipo;

    // Guardamos el nombre del equipo para mostrarlo
    if (indxEquipo != -1){
        equipo *tempEquipo = &equiposCargados.equipos[indxEquipo];
        nombreEquipo = malloc(sizeof(char) * strlen(tempEquipo->nombre) + 1);
        strcpy(nombreEquipo, tempEquipo->nombre);
        printf("(%s) - Equipo: %s - Nombre: %s - Precio: %i - Valoracion: %i\n", futbolista->id_jugador, nombreEquipo, futbolista->nombre, futbolista->precio, futbolista->valoracion);
    }
    else {
        printf("(%s) - Equipo: %s - Nombre: %s - Precio: %i - Valoracion: %i\n", futbolista->id_jugador, sinEquipo, futbolista->nombre, futbolista->precio, futbolista->valoracion);
    }
}