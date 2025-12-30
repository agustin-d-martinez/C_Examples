/**
	\file    <funciones_strings.c>
	\brief   <Funciones varias que facilitan el uso de strings>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.15> 
	\version <1.0.0>
*/


//--------------
//-- Includes --
//--------------

#include <string.h>
#include <ctype.h>
#include "funciones_strings.h"

#define SI 1
#define NO 0
/**
	\fn     <void sacar_enter(char *palabra)>
	\brief  <Elimina el \n al final del string en caso de existir>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <Puntero con el string a manejar>
*/

void sacar_enter(char *palabra)
{
    if(palabra[strlen(palabra)-1] == '\n')          //Verifico que el string termine en ENTER
        palabra[strlen(palabra)-1] = '\0';          //Reemplazo el ENTER por un nul
    return;
}

/**
	\fn     <void hacer_mayuscula(char *palabra)>
	\brief  <Pasa todo el string a mayuscula>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <Puntero con el string a manejar>
*/

void hacer_mayuscula(char *palabra)
{
    int tamano, i;
    tamano = strlen(palabra);                   //Calculo el tamaño  
    for (i = 0; i < tamano; i++)
        palabra[i] = toupper(palabra[i]);       //Paso cada posición a mayúscula 
    return;
}

/**
	\fn     <int es_letra(char letra)>
	\brief  <Indica si el caracter enviado es una letra o no>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <char con la letra a manejar>
	\return <1 si es letra
             0 si no es letra>
*/

int es_letra(char letra)
{
    int devolucion = NO;
    if(letra >= 'A' && letra <= 'Z')    //Si se encuentra entre A y Z cambia la devolucion (Letras mayúsculas)
        devolucion = SI;
    if(letra >= 'a' && letra <= 'z')    //Si se encuentra entre a y z cambia la devolucion (Letras minúsculas)
        devolucion = SI;
    return devolucion;
}

/**
	\fn     <int es_numero(char letra)>
	\brief  <Indica si el caracter enviado es un numero o no>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <char con la letra a manejar>
	\return <1 si es numero
             0 si no es numero>
*/

int es_numero(char letra)
{
    int devolucion = NO;
    if(letra >= '0' && letra <= '9')        //Si se encuentra entre 0 y 9 cambia la devolucion
        devolucion = SI;
    return devolucion;
}

/**
	\fn     <int es_car_control(char letra)>
	\brief  <Indica si el caracter enviado es un caracter de control o no>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <char con la letra a manejar>
	\return <1 si es caracter de control
             0 si no>
*/

int es_car_control(char letra)
{
    int devolucion = NO;
    if(letra >= 0 && letra <= 32) //Si se encuentra entre 0 y 32 (caracteres de control ASCII) cambia la devolucion
        devolucion = SI;
    return devolucion;
}
