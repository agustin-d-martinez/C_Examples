/**
	\file    <funciones_ordenar.c>
	\brief   <Funciones para ordenar en nietflix>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\version <1.0.0>
*/


//--------------
//-- Includes --
//--------------

#include "funciones_nietflix.h" 
#include "funciones_ordenar.h" 

/*
	\fn     <void ordenar_puntaje(Pelicula * listado, int largo)>
	\brief  <Ordena la lista de acuerdo al puntaje>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\param  <Lista a ordenar>
	\param  <Largo de la lista>
*/

void ordenar_puntaje(Pelicula * listado, int largo)
{
    int vuelta;
    int i = 0;
    int cambio = 1;
    Pelicula aux;
    
    while(cambio == 1)
    {
        i++;
        cambio = 0;
        for(vuelta = 0; vuelta < (largo-i);vuelta++)
        {
            if(listado[vuelta].puntaje < listado[vuelta+1].puntaje)
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

/*
	\fn     <void ordenar_anio(Pelicula * listado, int largo)>
	\brief  <Ordena la lista de acuerdo al año>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\param  <Lista a ordenar>
	\param  <Largo de la lis´ta>
*/

void ordenar_anio(Pelicula * listado, int largo)
{
    int vuelta, i = 0,cambio = 1;
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
