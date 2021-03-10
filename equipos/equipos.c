//
// Created by abraham on 5/3/21.
//

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

#include "equipos.h"


/*
 * Cabecera:
 * Precondicion:
 * Postcondicion:
*/

vector_equipos equiposCargados;

void reestablecerMemVecCadena(int, char **, int *, int *);
void guardarDatoEnEquipo(equipo *, char *, int);
char* generarIdEquipo();



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
 * Cabecera: Recibe los datos de un equipo y dependiendo del indice del campo
 * lo guardara donde corresponda dentro del equipo.
 * Precondicion: *temp tiene que estar inicializada
 *               *dato tiene que estar inicializada
 *               indiceCampo tiene que ser un valor entre (0,1)
 * Postcondicion: El equipo *temp tendra el dato cargado
 */
void guardarDatoEnEquipo(equipo *temp, char *dato, int indiceCampo){

    char *dest = malloc(sizeof(char) * strlen(dato));
    strcpy(dest, dato);

    switch (indiceCampo) {

        // Es el id del equipo
        case 0:
            temp->id = dest;
            break;

        // Es el nombre del equipo
        case 1:
            temp->nombre = dest;
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
    int continuar = 1;          // 1-> Continuamos || 0->Paramos de iterar
    FILE *archivo;

    // Si ocurre algun error, retornaremos codigo de estado 1
    if((archivo = fopen(NOMBRE_ARCHIVO_EQUIPOS, "r")) == NULL) return 1;

    // Inicializamos los vectores
    tempVecEquipos = (equipo *) malloc(sizeof(equipo) * tamanioVecEquipos);
    tempCadena = (char *) malloc(sizeof(char) * tamanioVecEquipos);

    // Iteraremos hasta que se acabe el archivo
    while (continuar){
        tempChar = getc(archivo);

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
        else if (tempChar == SEPARADOR_ARCHIVO_EQUIPOS){

            // Guardamos el dato recogido hasta ahora en el equipo correspondiente
            guardarDatoEnEquipo(&tempVecEquipos[equiposInsertados], tempCadena, indiceCampo);

            // Los siguientes datos correspondenn con un campo nuevo
            indiceCampo++;

            // Reestablecemos el vector #tempCadena
            reestablecerMemVecCadena(tamBaseVectores, &tempCadena, &tamanioVecCadena, &caracteresInsertados);
        }

        // Comprobamos si es un salto de linea o final del archivo
        else if (tempChar == '\n' || EOF){

            // Guardamos el dato recogido hasta ahora en el equipo correspondiente
            guardarDatoEnEquipo(&tempVecEquipos[equiposInsertados], tempCadena, indiceCampo);

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
            reestablecerMemVecCadena(tamBaseVectores, &tempCadena, &tamanioVecCadena, &caracteresInsertados);

            // Solo cuando acabemos de leer el archivo pararemmos de iterar
            if (tempChar == EOF){
                continuar = 0;
            }
        }
    }

    // Reducimos el tamaño del vector para no desperdiciar memoria
    tempVecEquipos = realloc(tempVecEquipos, sizeof(equipo) * equiposInsertados);

    // Guardamos los equipos en #vectorEquipos
    if (equiposInsertados == 0){
        tempVecEquipos = NULL;
    }
    equiposCargados.equipos = tempVecEquipos;
    equiposCargados.numEquipos = equiposInsertados;

    // Liberamos la memoria de las variables innecesarias
    free(tempCadena);

    // Cerramos el archivo
    fclose(archivo);

    // TODO Eliminar
    printf("Se han cargado %i equipos\n", equiposInsertados);

    return 0;
}

/*
 * Cabecera: Guardamos los equipos recibidos por parametros en el archivo #NOMBRE_ARCHIVO_EQUIPOS
 * Precondicion: vector_equipos tiene que estar inicializado
 * Postcondicion: 0-> Todo salio bien
 *                1-> Ocurrio un error
*/
int guardarEquipos(){

    FILE *archivo;

    // No hay equipos que guardar
    if (equiposCargados.numEquipos == 0) return 0;

    // Si ocurre algun error, retornaremos codigo de estado 1
    if((archivo = fopen(NOMBRE_ARCHIVO_EQUIPOS, "w")) == NULL) return 1;

    // Iteramos cada equipo existente en el vector
    for (int i = 0; i <equiposCargados.numEquipos ; i++) {
        equipo *tempEquipo = &equiposCargados.equipos[i];

        // Escribimos el id
        fputs(tempEquipo->id, archivo);

        // Esccribimos el separador
        fputc(SEPARADOR_ARCHIVO_EQUIPOS, archivo);

        // Escribimos el nombre del equipo
        fputs(tempEquipo->nombre, archivo);

        // Comprobamos si quedan mas equipos que guardar para añadir el salto de linea
        if (i != equiposCargados.numEquipos - 1){
            fputc('\n', archivo);
        }
    }

    // Cerramos el archivo
    fclose(archivo);

    return 0;
}


char* generarIdEquipo(){

    char *ultId;
    ultId = malloc(sizeof(char) * 2);
    ultId[0] = '0';
    ultId[1] = '0';

    int max = 0;

    // Recorremos el vector de los equipos cargados
    for (int i = 0; i < equiposCargados.numEquipos; i++) {

        equipo *tempEquipo = &equiposCargados.equipos[i];
        int tempId = atoi(tempEquipo->id);

        // Nos quedamos con el id del mayor
        if (tempId > max){
            max = tempId;
        }
    }

    max++;

    // Devolvemos 0X o XX segun convenga
    if (max > 9){
        sprintf(ultId, "%d", max);
    }
    else {
        ultId[1] = max + '0';
    }

    return ultId;
}


/* ----- CRUD ----- */
/*
 * Cabecera: Añade el equipo al archivo
 * Precondicion: #equipo debe de  estar iniciaizado y contener unicamente el nombre del equipo
 * Postcondicion:   0->Se ha guardado correctamente
 *                  1->Ocurrio un error
*/
int anadirEquipo(equipo equipo){

    // No puede tener un id ya contenido
    if (equipo.id != NULL) return 1;

    int lonNombre = strlen(equipo.nombre);
    // El equipo tiene un nombre sin caracteres o con demasiados caraccteres
    if (lonNombre == 0 || lonNombre > 20) return 1;

    // Existe un equipo con ese nombre
    if (buscarEquipoPorNombre(equipo.nombre) != -1) return 1;


    // Generammos un id para el equipo
    equipo.id = generarIdEquipo();

    // Agrandamos el vector de equipos y añadimos el nuevo equipo
    equiposCargados.numEquipos++;
    equiposCargados.equipos = realloc(equiposCargados.equipos, sizeof(equipo) * equiposCargados.numEquipos);
    equiposCargados.equipos[equiposCargados.numEquipos-1] = equipo;

    return 0;
}



// ----- Read -----
/*
 * Cabecera: Busca en #vector_equipos si existe algun equipo con el #id solicitado
 * Precondicion: El id debe de ser positivo y vectorEquipos inicializado
 * Postcondicion:   -1->No hay ningun equipo con ese id
 *                  x->Id del equipo en el vector #equiposCargados
*/
int buscarEquipoPorId(int id){

    equipo equiposBuscado;

    // No se ha llegado a cargar equipo o ingresar por primmera vez ningun equipo
    if (equiposCargados.numEquipos == 0) return -1;

    // Recorremos el vector de los equipos cargados
    for (int i = 0; i < equiposCargados.numEquipos; i++) {

        equipo *tempEquipo = &equiposCargados.equipos[i];

        if (tempEquipo->id == id){
            return i;
        }
    }

    return -1;
}

/*
 * Cabecera: Busca en #vector_equipos si existe algun equipo con el #nombre solicitado
 * Precondicion: El nombre debe de estar inicializado y vectorEquipos inicializado
 * Postcondicion:   -1->No hay ningun equipo con ese nombre
 *                  x->Id del equipo en el vector #equiposCargados
*/
int buscarEquipoPorNombre(char *nombre){

    equipo equiposBuscado;

    // No tiene caracteres
    if (strlen(nombre) == 0) return -1;

    // No se ha llegado a cargar equipo o ingresar por primmera vez ningun equipo
    if (equiposCargados.numEquipos == 0) return -1;

    // Recorremos el vector de los equipos cargados
    for (int i = 0; i < equiposCargados.numEquipos; i++) {

        equipo *tempEquipo = &equiposCargados.equipos[i];

        // Comprobamos si los nombres son iguales
        if (strcmp(nombre, tempEquipo->nombre) == 0){
            return i;
        }
    }

    return -1;
}
// ----------------


/* ---------------- */




// ----- Debug ----
/*
 * Cabecera: Muestra la informacion del equipo recibido por parametros
 * Precondicion: #equipo debe de estar inicializada
 * Postcondicion: Se muesttra lla informacion del equipo por pantalla
*/
void mostrarDatosEquipo(equipo *equipo){
    printf("Equipo -> Id:%s\t\tNombre:%s\n", equipo->id, equipo->nombre);
}

void mostrarDatosTodosEquipo(){
    int i;
    for (i = 0; i < equiposCargados.numEquipos; i++) {
        mostrarDatosEquipo(&equiposCargados.equipos[i]);
    }
}