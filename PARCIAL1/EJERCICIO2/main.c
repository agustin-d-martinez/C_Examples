/**
	\file    <main.c>
	\brief   <main del ejercicio>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.15> 
	\version <1.0.0>
	gcc -c main.c -o main.o -Wall
	gcc -c funciones.c -o funciones.o -Wall
	gcc main.o funciones.o -o ejercicio2 -Wall
	./ejercicio2
*/

//--------------
//-- Includes --
//--------------
#include <stdio.h>              
#include <stdlib.h>
#include "funciones.h" 

/**
	\fn     <int main()>
	\brief  <main para el ejercicio 2>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\return  <Regresa 0>
*/

int main(){
    unsigned char dato;
    char posicion = 3;
    dato = 72;
    dato =  clrbit(dato,posicion);
    
    printf("%d \n", dato);

    return 0;
}
