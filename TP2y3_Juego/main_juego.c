/**
	\file    <main_juego.c>
	\brief   <Juego de adivinar un número.>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.7> 
	\version <1.0.0>
	gcc -c main_juego.c -o main_juego.o -Wall
	gcc -c funciones_juego.c -o funciones_juego.o -Wall
	gcc -c randomizador_frases.c -o randomizador_frases.o -Wall
	gcc -c error.c -o error.o -Wall
	gcc main_juego.o funciones_juego.o randomizador_frases.o error.o -o ADIVINA_EL_NUMERO -Wall
*/

#define MAYOR_MENOR     1
#define FRIO_CALIENTE   2

//--------------
//-- Includes --
//--------------
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include "funciones_juego.h" 
#include "randomizador_frases.h" 
#include "error.h"

/**
	\fn     <int main()>
	\brief  <Juego de adivinar un número entre 1 y 100>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.7>  
	\return <Devuelve 0.>
*/
int main(){
    
    srand(time(NULL));  //Inicializo el rand
    
    int modo_de_juego=0, ganador = 0, cantidad_vidas = 0, volver_a_jugar = 1;
    
    introduccion(); //Muestro la introduccion al juego
    
    do{
        modo_de_juego = menu(&cantidad_vidas);  //Elijo la dificultad
    
        if(modo_de_juego == MAYOR_MENOR)        
        {
            ganador = juego_mayor_menor(cantidad_vidas);       //Pongo el juego en el modo mayor/menor
        }
        else if(modo_de_juego == FRIO_CALIENTE)
        {
            ganador = juego_frio_caliente(cantidad_vidas);      //Pongo el juego en el modo frio/caliente
        }
    
        if(ganador)         //verifico si ganó
            frase(GANAR);
        else
            frase(PERDER);
        
        printf("\n¿Desea volver a jugar?\n\n1-Sí \n2-No\n\n");     //Consulto si quiere volver a jugar 
        scanf("%d",&volver_a_jugar);
        error(&volver_a_jugar, 2, 1);   //Verifico que lo escriba bien
    }while(volver_a_jugar == 1);        //Genero la repeticion del juego
    
    printf("\n\nGracias por jugar, vuelva prontos\n");
    return 0;
}

