/**
	\file    <ejercicio_1.c>
	\brief   <main para analizar una frase. Determinar la cantidad de letras y cuáles fueron las más frecuentes>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.22>
	\version <1.0.0>
	gcc -c ejercicio_1.c -o ejercicio_1.o -Wall
	gcc -c funciones_strings.c -o funciones_strings.o -Wall
	gcc -c contador_mayor_frases.c -o contador_mayor_frases.o -Wall
	gcc ejercicio_1.o funciones_strings.o contador_mayor_frases.o -o ANALIZADOR_DE_FRASES -Wall
*/


//--------------
//-- Includes --
//--------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_strings.h"
#include "contador_mayor_frases.h"

#define MAX_LETRAS 150
#define CANT_NUM_REPETIDOS 5
#define CANT_LETRAS_ABECEDARIO 26

/**
	\fn      <int main()>
	\brief   <Me devuelve la cantidad de letras y caracteres especiales de una frase. La vuelve a imprimir en mayuscula. Realiza una tabla con las 5 letras más frecuentes>
	\author  <MARTINEZ, Agustin (agmartinez@frbg.utn.edu.ar)>
	\date    <2021.6.15>
	\return  <Devuelve 0>
*/

int main(){
    char frase[MAX_LETRAS+1];
    int caracteres_especiales = 0, numeros = 0;
    int abecedario[CANT_LETRAS_ABECEDARIO];
    int i, tamano = 0, letra_mayor;         //Variables
    
    for(i = 0; i < CANT_LETRAS_ABECEDARIO;i++)      //Pongo al abecedario en 0
    {
        abecedario[i] = 0;
    }
    
    printf("Ingrese frase (Máx %d letras):\n", MAX_LETRAS);
    fgets(frase, MAX_LETRAS, stdin);                            //Anoto la frase
    
    sacar_enter(frase);
    hacer_mayuscula(frase);     //corrijo la frase
    tamano = strlen(frase);
    
    contar_letras(frase, abecedario);                      //Cuento los caracteres
    contar_especiales(frase, &caracteres_especiales, &numeros);        

    printf("La frase posee %d caracteres especiales y %d letras.\n",caracteres_especiales, tamano-caracteres_especiales-numeros);                                                           //Devuelvo la cant de letras y caracteres especiales
    
    printf("El mensaje todo en MAYUSCULA es: %s\n", frase);             //Devuelvo la frase (ya se encuentra en mayusculas)
    
    printf("\t╔══╦═════╦════════╗\n");                                  //Imprimo el encabezado del cuadro
    printf("\t║Nº║LETRA║CANTIDAD║\n");
    
    for(i = 0; i < CANT_NUM_REPETIDOS; i++)
    {
        letra_mayor = mayor(abecedario, CANT_LETRAS_ABECEDARIO);        //Busco el mayor
        if(abecedario[letra_mayor] != 0)
        {
            printf("\t╠══╬═════╬════════╣\n");
            printf("\t║%d ║  %c  ║    %d   ║ \n", i+1, letra_mayor+'A', abecedario[letra_mayor]);   //Imprimo el mayor
            abecedario[letra_mayor] = 0;                                                            //Saco al mayor de la lista 
        }                                                                                           //así repito el proceso
    }
    printf("\t╚══╩═════╩════════╝\n");
    
    return 0;
}
