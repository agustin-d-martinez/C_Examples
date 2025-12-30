/**
	\file    <funciones_menu.c>
	\brief   <Funciones para el menu de nietflix>
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
	\fn     <int menu ()>
	\brief  <Imprime el menú principal>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\return <Devuelve la opción elegida>
*/

int menu ()
{
    char aux[11];
    printf("\n\tIndique acción a realizar:\n");
    printf("1- Ingresar película. \n2- Consultar películas. \nOTRO- Salir del programa.\n");
    fgets(aux, 10, stdin);
    return atoi(aux);
}

/*
	\fn     <int menu_continuar()>
	\brief  <Imprime el menú para continuar>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\return <Devuelve la opción elegida>
*/

int menu_continuar()
{
    char buffer[11];
    printf("\n\t¿desea continuar?\n");
    printf("\t1-Sí.\t2-No.\n");
    fgets(buffer,10,stdin);
    return atoi(buffer);
}

/*
	\fn     <int menu_ordenado()>
	\brief  <Imprime el menú del 2do modo de nietlfix>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\return <Devuelve la opción elegida>
*/

int menu_ordenado()
{
    char aux[11];
    printf("\n\tIndique filtro de películas:\n");
    printf("1- Por puntaje. \n2- Por año de lanzamiento. \n3- Por director.\n");
    fgets(aux, 10, stdin);
    return atoi(aux);
}


/*
	\fn     <void imprimir(Pelicula * listado, int largo, int tipo_orden, char* filtro)>
	\brief  <Imprime el registro según los filtros elegidos>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\param  <Listado a imprimir>
	\param  <Largo del listado>
	\param  <Tipo de orden que se debe imprimir>
	\param  <Nombre del director filtrado>
*/

void imprimir(Pelicula * listado, int largo, int tipo_orden, char* filtro)
{
    int i=0;
    while(i<largo)
    {
        if(tipo_orden == ORDEN_ANIO)
        {
            printf("#--------------------------------\n");
            printf("Nombre: %s.\n",listado[i].nombre);
            printf("Año: %d.\n\n",listado[i].anio);
            printf("#--------------------------------\n\n");
        }
        else if(tipo_orden == ORDEN_PUNTAJE)
        {
            printf("#--------------------------------\n");
            printf("Nombre: %s.\n",listado[i].nombre);
            printf("Puntaje: %.2f.\n\n",listado[i].puntaje);
            printf("#--------------------------------\n\n");
        }
        else if(tipo_orden == ORDEN_DIRECTOR)
            if(strcmp(filtro,listado[i].director) == 0)
            {
                printf("#--------------------------------\n");
                printf("Nombre: %s.\n",listado[i].nombre);
                printf("Puntaje: %.2f.\n\n",listado[i].puntaje);
                printf("#--------------------------------\n\n");
            }
        i++;
    }
    return;
}
