/**
	\file    <main.c>
	\brief   <main del ejercicio>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.15> 
	\version <1.0.0>
*/

//--------------
//-- Includes --
//--------------
#include <stdio.h>              
#include <stdlib.h>
#include "funciones_TP6.h" 

/**
	\fn     <int main()>
	\brief  <...>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\return  <Regresa 0>
*/

int main(){
    int opcion = CARGAR;
    int cant_peliculas = 0;
    Pelicula *listado;
    listado = (Pelicula*) malloc(sizeof(Pelicula));
    
    while(opcion != SALIR)         //Repito hasta salir
    {
        opcion = menu();    //Creo el menu
        
        
        if(opcion == CARGAR)
            ingreso_peliculas(&listado,&cant_peliculas);        //Cargo
        
        else if(opcion == ORDEN_RECAUDACION)
            ordenar_recaudacion(listado, cant_peliculas);       //Ordeno recaudacion
        
        else if(opcion == ORDEN_ANIO)
            ordenar_anio(listado, cant_peliculas);      //Ordeno año

        else if(opcion == IMPRIMIR)
            imprimir(listado,cant_peliculas);       //Imprimo
            
        else if(opcion == SALIR)
        {
            liberar(&listado);
            printf("Vuelva prontos.\n\n");      //libero y Salgo  
        }
    }
    return 0;
}
