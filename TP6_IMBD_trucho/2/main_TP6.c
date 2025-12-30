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
    int opcion = 0;
    int cant_peliculas = 0;
    Pelicula *listado;
    
    listado = (Pelicula*) malloc(sizeof(Pelicula));
    
    leer(&listado,&cant_peliculas);     //Leo todo lo que tengo antes de iniciar
    
    do
    {
        opcion = menu();        //Llamo al menu
        
        if(opcion == CARGAR)
            ingreso_peliculas(&listado,&cant_peliculas);        //Cargo
            
        else if(opcion == GUARDAR)
            guardar(listado,cant_peliculas);

        else if(opcion == LEER)
            leer(&listado,&cant_peliculas);

        else if(opcion == IMPRIMIR)                 //Imprimo
            imprimir(listado,cant_peliculas);
        
        else                                    //Me voy
        {
            printf("Vuelva prontos.\n\n");
            liberar(&listado);      //Libero
        }
    }
    while(opcion != SALIR);         //Repito todo
    
    return 0;
}
