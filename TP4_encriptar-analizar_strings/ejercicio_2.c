/**
	\file    <ejercicio_2.c>
	\brief   <main para encriptar frases>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.22>
	\version <1.0.0>
	gcc -c ejercicio_2.c -o ejercicio_2.o -Wall
	gcc -c funciones_strings.c -o funciones_strings.o -Wall
	gcc -c encriptador.c -o encriptador.o -Wall
	gcc ejercicio_2.o funciones_strings.o encriptador.o -o ENCRIPTADOR -Wall
*/


//--------------
//-- Includes --
//--------------
#include <stdio.h>
#include <stdlib.h>
#include "funciones_strings.h"
#include "encriptador.h"

#define MAX_LETRAS 150

/**
	\fn      <int main()>
	\brief   <Encripta una frase>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.22>
	\return  <Devuelve 0>
*/

int main(){
    char buffer_clave[MAX_LETRAS+1];
    unsigned int clave_encriptacion;
    char frase[MAX_LETRAS+1];
    
    printf("Ingrese frase (Máx %d letras):\n", MAX_LETRAS);
    fgets(frase, MAX_LETRAS, stdin);                            //Pido el mensaje
    
    sacar_enter(frase);             //Corrijo el mensaje
    hacer_mayuscula(frase);
    
    printf("Ingrese la clave de encriptacion (Debe ser un número):\n");//Pido la clave
    fgets(buffer_clave, MAX_LETRAS, stdin);                           
    clave_encriptacion = atoi(buffer_clave);                        //La transformo en número
    
    encriptar(frase, clave_encriptacion);       //Encripto el mensaje
    
    printf("La frase encriptada es:\n%s.\n",frase);
    
    return 0;
}

