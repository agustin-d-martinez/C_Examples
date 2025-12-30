/**
	\file    <encriptador.c>
	\brief   <Funciones para encriptar>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.15> 
	\version <1.0.0>
*/


//--------------
//-- Includes --
//--------------

#include <string.h>
#include "funciones_strings.h"
#include "encriptador.h"

/**
	\fn     <void encriptar (char *palabra, int clave_encriptacion)>
	\brief  <encripta la palabra usando la clave>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <Puntero con el string que posee la frase a encriptar>
	\param  <Número para encriptar>
*/

void encriptar (char *palabra, int clave_encriptacion){
    int tamano = strlen(palabra);
    int i = 0;
    
    for(i = 0; i < tamano; i++)
    {
        if(es_letra(palabra[i]) == 1){                  //Solo encripto letras
            palabra[i] += clave_encriptacion%26;        //Le sumo la clave (dividica por la cant de letras del abecedario)
            palabra[i] = ajusto(palabra[i]);            //Ajusto el num en caso de haberme pasado de la Z
            
        }
    }
    return;
}

void desencriptar (char *palabra, int clave_encriptacion){
    int tamano = strlen(palabra);
    int i = 0;
    
    for(i = 0; i < tamano; i++)
    {
        if(es_letra(palabra[i]) == 1){              //Solo desencripto letras
            palabra[i] -= clave_encriptacion%26;    //Le resto la clave (dividica por la cant de letras del abecedario)
            palabra[i] = ajusto(palabra[i]);        //Ajusto el num en caso de haberme ido más abajo que la A
            
        }
    }
    return;
}

/**
	\fn     <char ajusto(char letra)>
	\brief  <Ajusta el número en caso de haberse pasado de las letras del alfabeto>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <Char con el valor desfazado>
	\return  <Char con el valor corregido>
*/

char ajusto(char letra)
{
    while(letra < 'A' || letra > 'Z'){
        if(letra > 'Z')                 //Si me pasé de la Z
        {
            letra = (letra - 'Z') + ('A'-1);    //La diferencia la sumo al inicio
        }
        if(letra < 'A')                 //Si estoy por debajo de la A
        {
            letra = ('Z'+ 1) - ('A' - letra);    //Le resto la diferencia al valor final del abecedario 
        }
        
    }
    return letra;       //Devuelvo la letra corregida
}
