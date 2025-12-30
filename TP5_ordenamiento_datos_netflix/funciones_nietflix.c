/**
	\file    <funciones_nietflix.c>
	\brief   <Funciones para nietflix>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\version <2.0.0>
*/


//--------------
//-- Includes --
//--------------

#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include "funciones_nietflix.h" 
#include "funciones_menu.h" 

/*
	\fn     <int ingreso_peliculas(Pelicula ** listado,int cant_peliculas)>
	\brief  <Carga las películas en la lista>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\param  <Listado a cargar>
	\param  <cantidad de películas actuales dentro del listado>
	\return <error o cantidad de películas luego de la carga>
*/

int ingreso_peliculas(Pelicula ** listado,int cant_peliculas)
{
    int error = SIN_ERROR;
    int continuar = TRUE;
    
    char buffer[TAMANO_BUFFER + 1];
    char * s_nombre_aux;
    char * s_director_aux;
    
    
    while((error == SIN_ERROR) && (continuar== TRUE))
    {
        if(cant_peliculas == 0)
            (*listado) = (Pelicula*) malloc(sizeof(Pelicula));                 //creo el vector
        else
            (*listado) = (Pelicula*)realloc((*listado), (cant_peliculas+1) * sizeof(Pelicula));   
        
        if((*listado) == NULL)
            error = ERROR_MEM_DINAMICA;
        
        printf("Ingrese nombre de la película (máximo de %d caracteres ): ",TAMANO_BUFFER);        //Pregunto el nombre
        fgets(buffer, TAMANO_BUFFER, stdin);            //Me guardo el nombre en el auxiliar
        sacar_enter(buffer);                            //Saco el ENTER
        s_nombre_aux = (char *)malloc(sizeof(char)*(strlen(buffer)+1));    //Genero el string en la dir S.nombre.aux
        if(s_nombre_aux == NULL)
            error = ERROR_MEM_DINAMICA;
        else
        {
            (*listado)[cant_peliculas].nombre = s_nombre_aux;           //Paso el string a mi lista de peliculas
            strcpy(((*listado)[cant_peliculas].nombre),buffer);     //Copio el nombre en la lista
        }
        
        printf("Ingrese año de la película: ");        //Pregunto el año de la peli
        fgets(buffer, TAMANO_BUFFER, stdin);
        (*listado)[cant_peliculas].anio= atoi(buffer);
        if((*listado)[cant_peliculas].anio < 0)                 //Corrijo años negativos
            (*listado)[cant_peliculas].anio = 0;        
        
        printf("Lista de generos: \n >1-Acción. \n >2-Comedia. \n >3-Drama \n >4-Romance.\n >5-Suspenso. \n >6-Documental. \n >7-Ciencia ficción.\n >OTRO-Miscelaneo.\n");
        printf("\nIngrese genero de la película: ");
        fgets(buffer, TAMANO_BUFFER, stdin);
        (*listado)[cant_peliculas].genero = (unsigned char)atoi(buffer);
        if(((*listado)[cant_peliculas].genero > 8) ||((*listado)[cant_peliculas].genero < 0))
            (*listado)[cant_peliculas].genero = 8;                  //Genero el Miscelaneo
        
        printf("Ingrese director de la película (máximo de %d caracteres): ",TAMANO_BUFFER);       //Pregunto el director
        fgets(buffer, TAMANO_BUFFER, stdin);            //Me guardo el director en el auxiliar
        sacar_enter(buffer);                            //Saco el ENTER
        s_director_aux = (char *)malloc(sizeof(char)*(strlen(buffer)+1));    //Genero el string en la dir S.dir.aux
        if(s_director_aux == NULL)
            error = ERROR_MEM_DINAMICA;
        else
        {
            (*listado)[cant_peliculas].director= s_director_aux;           //Paso el string a mi lista de peliculas
            strcpy(((*listado)[cant_peliculas].director),buffer);     //Copio el director en la lista
        }
        
        printf("Ingrese puntaje de la película: ");            //Pregunto el puntaje
        fgets(buffer, TAMANO_BUFFER, stdin);
        (*listado)[cant_peliculas].puntaje= atof(buffer);
        if((*listado)[cant_peliculas].puntaje > PUNTAJE_MAXIMO)     //Corrijo si se pasa del puntaje máximo
            (*listado)[cant_peliculas].puntaje = PUNTAJE_MAXIMO;
        
        continuar = menu_continuar();
        cant_peliculas++;
    }
    
    if(error == SIN_ERROR)
        error = cant_peliculas;
    return error;
}

/*
	\fn     <void sacar_enter(char *palabra)>
	\brief  <Saca el \n al final de un string>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\param  <String a controlar>
*/

void sacar_enter(char *palabra)
{
    if(palabra[strlen(palabra)-1] == '\n')          //Verifico que el string termine en ENTER
        palabra[strlen(palabra)-1] = '\0';          //Reemplazo el ENTER por un nul
    return;
}

/*
	\fn     <void liberar (Pelicula ** listado, int cant_peliculas)>
	\brief  <Libera todas las memorias dinámicas de nietflix>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\param  <Listado de películas>
	\param  <Cantidad de películas dentro de la lista>
*/

void liberar (Pelicula ** listado, int cant_peliculas)
{
    int i;
    for(i=0; i< cant_peliculas;i++)
    {
        free((*listado)[i].nombre);
        free((*listado)[i].director);
    }
    if((*listado) != NULL)
        free((*listado));
    
    return;
}
