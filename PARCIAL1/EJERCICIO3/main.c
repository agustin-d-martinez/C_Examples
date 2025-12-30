/**
	\file    <main.c>
	\brief   <main del ejercicio>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.15> 
	\version <1.0.0>
	gcc -c main.c -o main.o -Wall
	gcc -c funciones.c -o funciones.o -Wall
	gcc main.o funciones.o -o ejercicio3 -Wall
	./ejercicio3
*/

//--------------
//-- Includes --
//--------------
#include <stdio.h>              
#include <stdlib.h>
#include "funciones.h" 

#define CANT_ORACIONES 5
#define LARGO_ORACIONES 80

/**
	\fn     <int main()>
	\brief  <main para el ejercicio 3>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\return  <Regresa 0>
*/

int main(){
    int cantidad_palabras, i;
    char frase[100] = {'H','o','l','a','\n','p','r','o','f','e','\n','a','p','r','o','b','a','m','e','\n','\0'};
    char oraciones[CANT_ORACIONES][LARGO_ORACIONES];
    
    cantidad_palabras = separo_oraciones(frase, oraciones);
    printf("Las frases son: \n");
    
    for(i=0; i< cantidad_palabras; i++)
        printf("%s \n", oraciones[i]);
    return 0;
}
