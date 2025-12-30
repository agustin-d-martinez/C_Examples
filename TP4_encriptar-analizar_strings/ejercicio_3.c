/**
	\file    <ejercicio_3.c>
	\brief   <main para desencriptar frases>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.22>
	\version <1.0.0>
	gcc -c ejercicio_3.c -o ejercicio_3.o -Wall
	gcc -c funciones_strings.c -o funciones_strings.o -Wall
	gcc -c encriptador.c -o encriptador.o -Wall
	gcc ejercicio_3.o funciones_strings.o encriptador.o -o DESENCRIPTADOR -Wall
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
	\brief   <Desencripta una frase>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.22>
	\return  <Devuelve 0>
*/

int main(){
    int clave_encriptacion;
    char buffer_clave[MAX_LETRAS+1];
    char frase[MAX_LETRAS+1];
    
    printf("Ingrese frase encriptada (Máx %d letras):\n", MAX_LETRAS);  //Pido la frase
    fgets(frase, MAX_LETRAS, stdin);
    
    sacar_enter(frase);     //Arreglo la frase
    hacer_mayuscula(frase);
    
    printf("Ingrese la clave de encriptacion:\n");//Pido la clave de encriptacion
    fgets(buffer_clave, MAX_LETRAS, stdin);                           
    clave_encriptacion = atoi(buffer_clave);                        //La transformo en número
    
    desencriptar(frase, clave_encriptacion);        //Desencripto
    
    printf("La frase desencriptada es:\n%s.\n",frase);      //Imprimo la frase
    
    return 0;
}

