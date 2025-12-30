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
#include <stdio_ext.h>
#include <stdlib.h>
#include <unistd.h>
#include "funciones_TP6.h" 


void ingreso_peliculas(Pelicula ** listado,int * cant_peliculas)
{
    int error = SIN_ERROR;
    int continuar = TRUE;
    char buffer[TAMANO_NOMBRE];
    int aux_anio;
    float aux_recaudacion;
    
    while((error == SIN_ERROR) && (continuar == TRUE))
    {
        (*listado) = (Pelicula*)realloc((*listado), ((*cant_peliculas)+1) * sizeof(Pelicula));   //Agrego 1 al vector
        
        if((*listado) == NULL)
        {
            error = ERROR_MEM_DINAMICA;
            perror("Fallo al cargar la pelicula: ");
        }
        else
        {
            printf("Ingrese nombre de la película (máximo de %d caracteres): ",TAMANO_NOMBRE);        //Pregunto el nombre
            fgets(buffer, TAMANO_NOMBRE, stdin);            //Me guardo el nombre en el auxiliar
            sacar_enter(buffer);     //Saco el ENTER
            strcpy((*listado)[*cant_peliculas].nombre,buffer);
            
            printf("Ingrese director de la película (máximo de %d caracteres): ",TAMANO_DIRECTOR);     //Pregunto el director
            fgets(buffer, TAMANO_DIRECTOR, stdin);      //Me guardo el director en el auxiliar
            sacar_enter(buffer);                            //Saco el ENTER
            strcpy(((*listado)[*cant_peliculas].director),buffer);
            
            printf("Ingrese año de la película: ");        //Pregunto el año de la peli
            scanf(" %d", &aux_anio);
            __fpurge(stdin);
            (*listado)[*cant_peliculas].anio = aux_anio;
            if(((*listado)[*cant_peliculas].anio) < 0)                 //Corrijo años negativos
                (*listado)[*cant_peliculas].anio = 0;        
            
            printf("Ingrese recaudacion de la película: ");            //Pregunto el puntaje
            scanf(" %f", &aux_recaudacion);
            __fpurge(stdin);
            (*listado)[*cant_peliculas].recaudacion= aux_recaudacion;
            
            *cant_peliculas=(*cant_peliculas)+1;          //Sumo 1 a la cantidad de pelis

            printf("\nDesea continuar: \n1-SI \n2-NO\n\n");
            scanf(" %d", &continuar);           //Verifico si continua o no
            __fpurge(stdin);
            
            if(continuar != TRUE)
                continuar = FALSE;
        }
    }
    guardar(*listado,*cant_peliculas);   //cargo todo al archivo
    return;
}

int menu()
{
    int opcion;
    printf("Qué desea hacer: \n\t1-Cargar pelis. \n\t2-Guardar. \n\t3-Leer. \n\t4-Imprimir. \n\tOTRO-salir.\n\n");
    scanf(" %d",&opcion);
    __fpurge(stdin);

    if((opcion >= SALIR) || (opcion)< CARGAR)
        opcion = SALIR;
    return opcion;
}

void guardar(Pelicula * listado,int cant_peliculas)
{
    int i;
    
    FILE*archivo= NULL;
    char nombre_archivo[TAMANO_NOMBRE_ARCHIVO+1];
    
    printf("Guardar en: ");
    fgets(nombre_archivo, TAMANO_NOMBRE_ARCHIVO, stdin);            //Me guardo el nombre del archivo
    sacar_enter(nombre_archivo);
    archivo = fopen(nombre_archivo,"w");       //Abro el archivo
    
    printf("/-------------------Enviando datos...\n");
    sleep(1);

    if(archivo != NULL)
    {
        for(i=0;i<cant_peliculas;i++)               //Repito por la cantidad de películas que tengo 
        {
            fwrite(&(listado[i]),sizeof(Pelicula),1,archivo);                   //escribo una película
            printf("/-------------------%d%% completado\n",((i+1)*100/cant_peliculas));
            sleep(1);
        }
        printf("/-------------------Datos guardados con éxito\n\n");
    }
    else
        perror("Error al abrir el archivo: ");      //En caso de error
    
    fclose(archivo);
    return;
}

void leer(Pelicula ** listado,int * cant_peliculas)
{
    int continuar_leyendo;
    int error = SIN_ERROR;
    
    Pelicula aux;
    FILE *archivo= NULL;
    
    char nombre_archivo[TAMANO_NOMBRE_ARCHIVO+1];
    
    printf("Archivo a leer: ");
    fgets(nombre_archivo, TAMANO_NOMBRE_ARCHIVO, stdin);            //Me guardo el nombre del archivo
    sacar_enter(nombre_archivo);
    archivo = fopen(nombre_archivo,"a+");
    
    if(archivo != NULL)
    {
        printf("/-------------------Leyendo datos...\n");
        sleep(1);
        *cant_peliculas = 0;            //Al leer pierdo todo lo que aun no esté guardado
        
        while((!feof(archivo)) && (error == SIN_ERROR))
        {
            continuar_leyendo = fread(&aux,sizeof(Pelicula),1,archivo);     //leo 1 película
                
            if(continuar_leyendo)    //si no es el final
            {
                (*listado)= (Pelicula*)realloc((*listado),((*cant_peliculas)+1) * sizeof(Pelicula));  //Agrego 1 al vector
                
                if((*listado) != NULL)
                {
                    (*listado)[*cant_peliculas] = aux;      //guardo el auxiliar
                    *cant_peliculas = (*cant_peliculas)+1;  //sumo uno a la cant máxima
                    printf("/-------------------Película Nº%d cargada...\n",(*cant_peliculas));
                    sleep(1);
                }
                else
                {
                    error = ERROR_MEM_DINAMICA;
                    perror("Fallo al leer la pelicula: ");
                }
            }
        }
        printf("\n/-------------------Finalizacion de la lectura con éxito\n\n");
    }
    else
        perror("Error al abrir el archivo: ");
    
    fclose(archivo);
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
