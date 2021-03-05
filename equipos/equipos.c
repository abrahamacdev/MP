//
// Created by abraham on 5/3/21.
//

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

#include "equipos.h"


equipo *equipos;

/**
 * Cabecera: Recibe los datos de un equipo y dependiendo del indice del campo
 * lo guardara donde corresponda dentro del equipo.
 * Precondicion: *temp tiene que estar inicializada
 *               *dato tiene que estar inicializada
 *               indiceCampo tiene que ser un valor entre (1,2)
 * Postcondicion: El equipo *temp tendra el dato cargado
 */
void guardarDatoEnEquipo(equipo *temp, char *dato, int indiceCampo){

    switch (indiceCampo) {

        // Es el id del equipo
        case 1:
            temp->id = dato;
            break;

            // Es el nombre del equipo
        case 2:
            temp->nombre = dato;
            break;
    }
}

/*
 * Cabecera: Cargara todos los equipos del archivo
 * Precondicion:
 * Postcondicion: Devuelve el estado de la carga:
 *      1-> Ocurrio un error
 *      0-> Todo salio segun lo esperado
*/
int cargarEquipos(){

    int tamBaseVectores = 8;

    equipo *tempVecEquipos;
    int tamanioVecEquipos = tamBaseVectores;  // Cantidad de elementos en el vector *tempEquipo
    int equiposInsertados = 0;  // Cantidad de equipos insertados en el vector

    char *tempCadena;           // Vector con los caracteres leidos hasta ahora
    int tamanioVecCadena = tamBaseVectores;   // Tamaño del vector de caracteres
    int caracteresInsertados = 0;   // Cantidad de caracteres de la cadena

    int indiceCampo=0;                    // Indica que campo es el leido (0=id, 1=nombre)
    char tempChar;              // Variable en la que iremoos almacenando cada caracter leido
    FILE *archivo;

    // Si ocurre algun error, retornaremos codigo de estado 1
    if((archivo = fopen(NOMBRE_ARCHIVO_EQUIPOS, "r")) == NULL) return 1;

    // Inicializamos los vectores
    tempVecEquipos = (equipo *) malloc(sizeof(equipo) * tamanioVecEquipos);
    tempCadena = (char *) malloc(sizeof(char) * tamanioVecEquipos);

    // Iteraremos hasta que se acabe el archivo
    while ((tempChar = getc(archivo)) != EOF){

        // Comprobamos si es un caracter alfanumerico
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
        else if (tempChar == '-'){

            // Guardamos el dato recogido hasta ahora en el equipo correspondiente
            guardarDatoEnEquipo(&tempVecEquipos[equiposInsertados], tempCadena, indiceCampo);

            // Los siguientes datos correspondenn con un campo nuevo
            indiceCampo++;

            // Reestablecemos el vector #tempCadena
            caracteresInsertados = 0;
            tamanioVecCadena = tamBaseVectores;
            tempCadena = realloc(tempCadena, sizeof(char) * tamanioVecCadena);
        }

        // Comprobamos si es un salto de linea
        else if (tempChar == '\n'){

            // Comprobamos que quede mas espacio en el vector de equipos
            if (equiposInsertados == tamanioVecEquipos - 1){

                // Agrandamos el tamaño del vector #tempVecEquipos
                tamanioVecEquipos += tamBaseVectores;
                tempVecEquipos = realloc(tempVecEquipos, sizeof(equipo) * tamanioVecEquipos);
            }

            // Sumamos el equipo parseado
            equiposInsertados++;

            // Reestablecemos el indice del campo
            indiceCampo = 0;

            // Reestablecemos el vector #tempCadena
            caracteresInsertados = 0;
            tamanioVecCadena = tamBaseVectores;
            tempCadena = realloc(tempCadena, sizeof(char) * tamanioVecCadena);
        }
    }

    // Reducimos el tamaño del vector para no desperdiciar memoria
    tempVecEquipos = realloc(tempVecEquipos, sizeof(equipo) * equiposInsertados);

    // Guardamos los equipos en memoria
    equipos = tempVecEquipos;

    // Liberamos la memoria de las variables innecesarias
    free(tempCadena);

    // Cerramos el archivo
    fclose(archivo);

    printf("Se han cargado %i equipos", equiposInsertados);

    return 0;
}