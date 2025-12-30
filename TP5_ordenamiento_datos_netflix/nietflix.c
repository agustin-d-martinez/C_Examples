/*
	\file    <main.c>
	\brief   <Genera el programa NIETFLIX>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.9.2> 
	\version <1.0.0>
*/

//--------------
//-- Includes --
//--------------
#include <stdio.h>              
#include "funciones_nietflix.h" 
#include "funciones_menu.h" 
#include "funciones_ordenar.h" 

/*
	\fn     <int main()>
	\brief  <...>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\return  <Regresa 0>
*/
int main(){
    int opcion = 0;
    int opcion_ordenado = 0;
    int cant_peliculas = 0;
    char filtro[TAMANO_BUFFER+1];
    Pelicula* registro_peliculas = NULL;  
    
    printf("\tBienvenido a Nietflix! (Patente pendiente)\n\n");
    
    while(opcion != SALIR_PROGRAMA)
    {
        opcion = menu();
        switch(opcion)
        {
            case CARGAR_PELICULA:
                cant_peliculas = ingreso_peliculas(&registro_peliculas, cant_peliculas);        //Cargo pelis
                break;
                
            case ORDENAR_PELICULA:
                if(cant_peliculas != 0)
                {
                    opcion_ordenado = menu_ordenado();      //Pregunto como mostrar
                
                    if(opcion_ordenado == ORDEN_PUNTAJE)
                        ordenar_puntaje(registro_peliculas,cant_peliculas);     //Ordeno
                    
                    else if(opcion_ordenado == ORDEN_ANIO)
                        ordenar_anio(registro_peliculas,cant_peliculas);
                
                    else if(opcion_ordenado == ORDEN_DIRECTOR)
                    {
                        printf("\nNombre del director: ");
                        fgets(filtro, TAMANO_BUFFER, stdin);
                        sacar_enter(filtro);
                        ordenar_puntaje(registro_peliculas,cant_peliculas);
                    }
                
                    imprimir(registro_peliculas,cant_peliculas,opcion_ordenado,filtro);     //Imprimo
                }
                else
                    printf("No hay ninguna película en el catálogo.\n");
                break;
            
            default:    
            case SALIR_PROGRAMA:
                break;
        }

        if(cant_peliculas == ERROR_MEM_DINAMICA)
        {
            opcion = SALIR_PROGRAMA;
            printf("Lo lamentamos, falló el sistema. (Echale la culpa a windows)\n");
        }
    }
    
    liberar(&registro_peliculas, cant_peliculas);
    printf("Gracias, vuelva prontos.\n");
    
    return 0;
}
