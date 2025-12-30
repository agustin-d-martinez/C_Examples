/**
	\file    <randomizador_frases.c>
	\brief   <Un switch con frases aleatorias.>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.7> 
	\version <1.0.0>
*/


//--------------
//-- Includes --
//--------------
#include <stdio.h> 
#include <stdlib.h> 
#include "randomizador_frases.h" 

/**
	\fn      <void frase(int tipo)>
	\brief   <Un switch con frases aleatorias.>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.7> 
	\param   <Indica el tipo de frase que será impresa>
*/



void frase(int tipo){
    int numero_frase = 0;
    switch(tipo){
        case FRIO:
                numero_frase = rand()%5+1;
                if(numero_frase == 1)
                    printf("Mas frio que hincha de boca.\n");
                else if(numero_frase == 2)
                    printf("Mas frio que el culo de Sub-zero.\n");
                else if(numero_frase == 3)
                    printf("Estas mas frio que el profe corrigiendo el trabajo practico.\n");
                else if(numero_frase == 4)
                    printf("Estas mas cerca de conseguir novia que acertar al numero.\n ");
                else if(numero_frase == 5)
                    printf("Mas lejos que Higuain pateando un penal.\n");
        break;
        
        case TIBIO:
            numero_frase = rand()%4+1;
            if(numero_frase == 1)
                printf("Te estas acercando.\n");
            else if(numero_frase == 2)
                printf("Se va calentando la cosa.\n");
            else if(numero_frase == 3)
                printf("Estás a medio camino.\n");
            else if(numero_frase == 4)
                printf("Está tibia la cosa.\n");
        break;    
        
        case CALIENTE:
            numero_frase = rand()%5+1;
            if(numero_frase == 1)
                printf("Más caliente que pava para mate.\n");
            else if(numero_frase == 2)
                printf("EStás más caliente que cura en guardería.\n");
            else if(numero_frase == 3)
                printf("Estás hirviendo.\n");
            else if(numero_frase == 4)
                printf("Estás tan cerca que ya no cumplis el distanciamiento social.\n");
            else if(numero_frase == 5)
                printf("Dalee, la tenés ahí nomás.\n");
        break;
        
        case SUBIR:
            numero_frase = rand()%5+1;
            if(numero_frase == 1)
                printf("¿Estamos tacaños hoy? Dale un poco más.\n");
            else if(numero_frase == 2)
                printf("Aumentala un poquito o nos quedamos acá esperándote.\n");
            else if(numero_frase == 3)
                printf("Hacé como el dolar y subí un poquito más\n");
            else if(numero_frase == 4)
                printf("Otra vez fallaste. Aumentá el número, dale.\n");
            else if(numero_frase == 5)
                printf("subila un poco.\n");
        break;
        
        case BAJAR:
            numero_frase = rand()%5+1;
            if(numero_frase == 1)
                printf("Te pasaste de largo.\n");
            else if(numero_frase == 2)
                printf("¿Te comiste un yogurísimo? Bajala un poco.\n");
            else if(numero_frase == 3)
                printf("Bajala como hiciste con tu nota de Informática.\n");
            else if(numero_frase == 4)
                printf("Ahora hacé como el peso argentino y baja un poco.\n");
            else if(numero_frase == 5)
                printf("EScupiste para arriba, ahora bajá tu número.\n");
        break;
        
        case GANAR:
            numero_frase = rand()%5+1;
            if(numero_frase == 1)
                printf("Ganaste pibe!!! Así se hace.\n");
            else if(numero_frase == 2)
                printf("Nada mal muchacho. Ganaste un juego.\n");
            else if(numero_frase == 3)
                printf("Quizá ganaste esta vez, pero en el ahorcado te gano yo seguro.\n");
            else if(numero_frase == 4)
                printf("JUEGO COMPLETADO. Obtuviste el ""good ending"".\n");
            else if(numero_frase == 5)
                printf("Inrecible, ganaste. Ninguno de nosotros se lo esperaba.\n");
        break;
        
        case PERDER:
            numero_frase = rand()%5+1;
            if(numero_frase == 1)
                printf("Apostamos a que ibas a perder. No nos decepcionaste.\n");
            else if(numero_frase == 2)
                printf("Sabemos que diste tu mejor esfuerzo, pero perdiste de todas formas.\n");
            else if(numero_frase == 3)
                printf("Para la próxima bajale la dificultad.\n");
            else if(numero_frase == 4)
                printf("Perdiste. Espero que no te vaya tan mal en el final de Informática.\n");
            else if(numero_frase == 5)
                printf("JUEGO COMPLETADO. Obtuviste el ""BAD ending"".\n");
        break;
    }
    return;
}
