/**
	\file    <error.c>
	\brief   <Función de error>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.7> 
	\version <1.0.0>
*/


//--------------
//-- Includes --
//--------------
#include <stdio.h> 
#include "error.h"
/**
	\fn     <void error(int *valor, int max, int min)>
	\brief  <Solo permite que salga de la funcion si la variable se encuentra entre el MAX y el MIN>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.7>  
	\param  <Puntero con la variable a corregir>
	\param  <Valor máximo>
	\param  <Valor mínimo>
*/

void error(int *valor, int max, int min)
{
    while((*valor > max)||(*valor < min) )
    {
        printf("Ingrese un valor válido\n");
        scanf("%d", &*valor);
    }
    return;
}
