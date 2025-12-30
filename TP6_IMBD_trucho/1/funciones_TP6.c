/**
	\file    <funciones_TP6.c>
	\brief   <Funciones del ejercicio>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.15> 
	\version <1.0.0>
*/


//--------------
//-- Includes --
//--------------

/*
	\fn     <Prototipo de la función>
	\brief  <Función de la función>
	\author <Apellido y Nombre (mail)>
	\date   <Año.Mes.Día> 
	\param  <Parámetro A>
	\param  <Parámetro B>
	\return <Lo que retorna>
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include "funciones_TP6.h" 


void ingreso_peliculas(Pelicula ** listado,int * cant_peliculas)
{
    int error = SIN_ERROR;
    int continuar = TRUE;
    
    while((error == SIN_ERROR) && (continuar == TRUE))
    {
        (*listado) = (Pelicula*)realloc((*listado), ((*cant_peliculas)+1) * sizeof(Pelicula));   //Agrego 1 al vector
        
        if((*listado) == NULL)
        {
            error = ERROR_MEM_DINAMICA;
            perror("Fallo al cargar la pelicula: ");        //Mensaje de error de Memoria dinamica
        }
        else
        {
            printf("Ingrese nombre de la película (máximo de %d caracteres): ",TAMANO_NOMBRE);        //Pregunto el nombre
            fgets((*listado)[*cant_peliculas].nombre, TAMANO_NOMBRE, stdin);            //Me guardo el nombre en el auxiliar
            sacar_enter((*listado)[*cant_peliculas].nombre);     //Saco el ENTER
            
            printf("Ingrese director de la película (máximo de %d caracteres): ",TAMANO_DIRECTOR);     //Pregunto el director
            fgets((*listado)[*cant_peliculas].director, TAMANO_DIRECTOR, stdin);      //Me guardo el director en el auxiliar
            sacar_enter((*listado)[*cant_peliculas].director);                            //Saco el ENTER
            
            printf("Ingrese año de la película: ");        //Pregunto el año de la peli
            scanf(" %d", &((*listado)[*cant_peliculas].anio));
            __fpurge(stdin);
            if(((*listado)[*cant_peliculas].anio) < 0)                 //Corrijo años negativos
                (*listado)[*cant_peliculas].anio = 0;        
            
            printf("Ingrese recaudacion de la película: ");            //Pregunto el puntaje
            scanf(" %f", &((*listado)[*cant_peliculas].recaudacion));
            __fpurge(stdin);
            
            (*cant_peliculas)=(*cant_peliculas)+1;          //Sumo 1 a la cantidad de pelis

            printf("\nDesea continuar: \n1-SI \n2-NO\n\n");
            scanf(" %d", &continuar);           //Verifico si continua o no
            __fpurge(stdin);
            
            if(continuar != TRUE)
                continuar = FALSE;
        }
    }
    return;
}

int menu()
{
    int opcion;
    printf("Qué desea hacer: \n\t1-Cargar pelis.\n\t2-Ordenar por recaudacion. \n\t3-Ordenar por año. \n\t4-Imprimir. \n\tOTRO-salir.\n\n");
    scanf(" %d",&opcion);
    __fpurge(stdin);

    if((opcion >= SALIR) || (opcion < CARGAR))
        opcion = SALIR;
    return opcion;
}

void ordenar_anio(Pelicula *listado, int largo)
{
    int vuelta, i = 0, cambio = 1;
    Pelicula aux;

    while(cambio == 1)
    {
        i++;
        cambio = 0;
        for(vuelta = 0; vuelta < (largo-i);vuelta++)
        {
            if(listado[vuelta].anio < listado[vuelta+1].anio)
            {
                aux = listado[vuelta];
                listado[vuelta] = listado[vuelta+1];
                listado[vuelta+1] = aux;
                cambio = 1;
            }
        }
    }
    return;
}

void ordenar_recaudacion(Pelicula *listado, int largo)
{
    int vuelta, i = 0, cambio = 1;
    Pelicula aux;
    
    while(cambio == 1)
    {
        i++;
        cambio = 0;
        for(vuelta = 0; vuelta < (largo-i);vuelta++)
        {
            if(listado[vuelta].recaudacion < listado[vuelta+1].recaudacion)
            {
                aux = listado[vuelta];
                listado[vuelta] = listado[vuelta+1];
                listado[vuelta+1] = aux;
                cambio = 1;
            }
        }
    }
    return;
}


void imprimir(Pelicula *listado,int cant_peliculas)
{
    int i;
    printf("\n----------------------------------\n");

    for(i=0;i<cant_peliculas;i++)
    {
        printf("Película %d\n\n",(i+1));
        printf("Nombre:\t\t%s\n",listado[i].nombre);
        printf("Director:\t%s\n",listado[i].director);
        printf("Año:\t\t%d\n",listado[i].anio);
        printf("Recaudación:\t%.2f\n",listado[i].recaudacion);
        printf("----------------------------------\n\n");
    }
    return;
}

void sacar_enter(char *palabra)
{
    if(palabra[strlen(palabra)-1] == '\n')          //Verifico que el string termine en ENTER
        palabra[strlen(palabra)-1] = '\0';          //Reemplazo el ENTER por un nul
    return;
}

void liberar (Pelicula ** listado)
{
    if((*listado) != NULL)
        free((*listado));
    
    return;
}
