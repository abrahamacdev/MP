//
// Created by abraham on 17/3/21.
//

#include "futbolistas.h"
#include "../equipos/equipos.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"



void reestablecerMemVecCadena(int, char **, int *, int *);
void guardarDatoEnFutbolista(futbolista *temp, char *dato, int indiceCampo);



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

        // Es el id del equipo
        case 0:
            temp->id_jugador = dest;
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
            if (isdigit(dest)){
                temp->precio = atoi(dest);
            }
            break;

        // Es la valoracion del futbolista
        case 4:
            if (isdigit(dest)){
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
        else if (tempChar == '\n' || tempChar == EOF){

            // Guardamos el dato recogido hasta ahora en el futbolista correspondiente
            guardarDatoEnFutbolista(&tempFutbolista, tempCadena, indiceCampo);

            // Comprobamos que halla datos que guardar (evita errores al leer archivo vacio)
            if (strlen(tempCadena) > 1){

                // Reestablecemos el indice del campo
                indiceCampo = 0;

                // Reestablecemos el vector #tempCadena
                reestablecerMemVecCadena(tamBaseVectores, &tempCadena, &tamanioVecCadena, &caracteresInsertados);
            }

            // Buscamos el equipo al que pertenece el jugador y lo añadimos a su vector
            int idEquipo = buscarEquipoPorId(tempFutbolista.id_equipo);
            if (idEquipo != -1){

                equipo tempEquipo = equiposCargados.equipos[idEquipo];
                int numFutbolistas = tempEquipo.vectorFutbolistas->numFutbolistas;

                // Es la primera vez que añadimos futbolistas al vector
                if (numFutbolistas == 0){
                    tempEquipo.vectorFutbolistas->futbolistas = malloc(sizeof(vector_futbolistas));
                }

                // Agrandamos el vector de futbolistas del equipo
                else {
                    tempEquipo.vectorFutbolistas->futbolistas = realloc(tempEquipo.vectorFutbolistas->futbolistas, sizeof(vector_futbolistas) * (numFutbolistas+1));
                }

                // Añadimos el futbolista al vector
                tempEquipo.vectorFutbolistas->futbolistas[numFutbolistas] = tempFutbolista;
                tempEquipo.vectorFutbolistas->numFutbolistas++;
            }

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
        for (int j = 0; j < tempEquipo->vectorFutbolistas->numFutbolistas; j++) {

            futbolista *tempFutbolista = &tempEquipo->vectorFutbolistas->futbolistas[j];

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
            if (j != tempEquipo->vectorFutbolistas->numFutbolistas - 1){
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

    // Id del equipo no valido
    int idxEquipo = buscarEquipoPorId(fut->id_equipo);
    if (idxEquipo == -1) return 1;

    // Ya existe otro jugador con ese id o nombre
    futbolista *futPorNombre = buscarFutbolistaPorNombre(fut->nombre);
    if (futPorNombre != NULL) return 1;
    futbolista *futPorId = buscarFutbolistaPorId(fut->id_jugador);
    if (futPorId != NULL) return 1;

    // Comprobamos que no se halla llegado al numero maximo de futbolistas por equipo


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
    if (strlen(id) != 2) return NULL;

    // Recorremos el vector de los equipos cargados
    for (int i = 0; i < equiposCargados.numEquipos; i++) {

        // Recorremos los jugadores del equipo
        vector_futbolistas *vectorFutbolistas = equiposCargados.equipos[i].vectorFutbolistas;
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
    if (strlen(nombre) == 0) return NULL;

    // Recorremos el vector de los equipos cargados
    for (int i = 0; i < equiposCargados.numEquipos; i++) {

        // Recorremos los jugadores del equipo
        vector_futbolistas *vectorFutbolistas = equiposCargados.equipos[i].vectorFutbolistas;
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





// ----- Debug -----
/*
 * Cabecera: Muestra la informacion del futbolista
 * Precondicion: El futbolista debe de esttar inicizalizado
 * Postcondicion:
*/
void mostrarDatosFutbolista(futbolista *futbolista){

    int indxEquipo = buscarEquipoPorId(futbolista->id_equipo);
    char *nombreEquipo = "N.E";

    // Guardamos el nombre del equipo para mostrarlo
    if (indxEquipo != -1){
        equipo *tempEquipo = &equiposCargados.equipos[indxEquipo];
        nombreEquipo = realloc(nombreEquipo, sizeof(char) * strlen(tempEquipo->nombre) + 1);
        strcpy(nombreEquipo, tempEquipo->nombre);
    }

    printf("(%s) - Equipo: %s - Nombre: %s - Precio: %i - Valoracion: %i", futbolista->id_jugador, futbolista->id_equipo, futbolista->nombre, futbolista->precio, futbolista->valoracion);
}