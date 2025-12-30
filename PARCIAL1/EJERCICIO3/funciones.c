/**
	\file    <funciones.c>
	\brief   <Funciones del ejercicio 3>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.15> 
	\version <1.0.0>
*/


//--------------
//-- Includes --
//--------------
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "funciones.h" 

/**
	\fn     <int separo_oraciones(char*origen,char (*oraciones)[80])>
	\brief  <Separa una frase en varios strings cuando encuentra un \n>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <frase original>
	\param  <MAtriz con frases a guardar>
	\return <Cantidad de frases extraidas>
*/



int separo_oraciones(char*origen,char (*oraciones)[80])
{
    int cant_palabras = 0;
    char * aux;
    const char separador[2] = "\n";
        
    aux = strtok(origen,separador);      //Busco la primer palabra
    
    if(aux != NULL)
    {
        cant_palabras++;
        strcpy(oraciones[cant_palabras-1],aux);     //La guardo
        
        aux = strtok(NULL,separador);        //Vuelvo a buscar

        while(aux != NULL)          //Repito hasta no encontrar mas
        {
            if(aux != NULL)
            {
                cant_palabras++;
                strcpy(oraciones[cant_palabras-1],aux);
            }    
    
            aux = strtok(NULL,separador);
        }
    }
    
    return cant_palabras;
}
