/**
	\file    <ejercicio_4.c>
	\brief   <main para desencriptar frases de forma automática usando la frecuencia de letras>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.22>
	\version <1.0.0>
	gcc -c ejercicio_4.c -o ejercicio_4.o -Wall
	gcc -c funciones_strings.c -o funciones_strings.o -Wall
	gcc -c encriptador.c -o encriptador.o -Wall
	gcc -c contador_mayor_frases.c -o contador_mayor_frases.o -Wall
	gcc ejercicio_4.o funciones_strings.o encriptador.o contador_mayor_frases.o -o DESENCRIPTADOR_AUTOMATICO -Wall
*/


//--------------
//-- Includes --
//--------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_strings.h"
#include "encriptador.h"
#include "contador_mayor_frases.h"

#define MAX_LETRAS 150
#define CANT_LETRAS_ABECEDARIO 26

#define LETRA_COMUN_1 'E'
#define LETRA_COMUN_2 'A'
#define LETRA_COMUN_3 'O'
#define LETRA_COMUN_4 'S'
#define LETRA_COMUN_5 'R'

/**
	\fn      <int main()>
	\brief   <Desencripta una frase utilizando las letras más frecuentes que posea dicho idioma>
	\author  <MARTINEZ, Agustin (agmartinez@frbg.utn.edu.ar)>
	\date    <2021.6.22>
	\return  <Devuelve 0>
*/

int main(){
    int i, clave_encriptacion, letra_repetida;      //Declaro las variables
    
    char letras_frecuentes[5] = {LETRA_COMUN_1, LETRA_COMUN_2, LETRA_COMUN_3, LETRA_COMUN_4, LETRA_COMUN_5};
    char frase[MAX_LETRAS+1];       //Declaro los vectores
    char buffer[MAX_LETRAS+1];
    
    int abecedario[CANT_LETRAS_ABECEDARIO];
    
    for(i = 0; i < CANT_LETRAS_ABECEDARIO;i++)      //Pongo al abecedario en 0
    {
        abecedario[i] = 0;
    }
    
    printf("Ingrese frase encriptada (Máx %d letras):\n", MAX_LETRAS);  //Pido la frase
    fgets(frase, MAX_LETRAS, stdin);
    
    sacar_enter(frase);     //Arreglo la frase
    hacer_mayuscula(frase);
    
    contar_letras(frase, abecedario);        //Cuento los caracteres    
    
    letra_repetida = mayor(abecedario, CANT_LETRAS_ABECEDARIO);     //busco la letra que mas se repitio
    printf("La letra más repetida fue: %c. \n\n",letra_repetida + 'A');
    
    for(i=0; i < 5; i++)
    {
        strcpy(buffer, frase);  //Trabajo con el buffer que posee el mensaje original
        
        clave_encriptacion = letra_repetida+'A' - letras_frecuentes[i];   //Genero la clave (Letra_+_repetida - letra_+_comun)
        if(clave_encriptacion < 0)                          //Verifico que no me haya dado negativo
            clave_encriptacion = CANT_LETRAS_ABECEDARIO + clave_encriptacion;
        
        desencriptar(buffer, clave_encriptacion);        //Desencripto
        printf("╔════════════════════╦════════════════════════╗\n");
        printf("║Letra original : %c  ║Letra a reemplazar : %c  ║\n",letra_repetida+'A', letras_frecuentes[i]);
        printf("╚════════════════════╩════════════════════════╝\n");
        printf("Frase: %s.\n\n",buffer);      //Imprimo la frase
    }
    return 0;
}

