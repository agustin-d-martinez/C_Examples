/**
	\file    <funciones.c>
	\brief   <Funciones del ejercicio 2>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.15> 
	\version <1.0.0>
*/


//--------------
//-- Includes --
//--------------

/**
	\fn     <unsigned char clrbit(unsigned char dato,char posicion)>
	\brief  <cambia el bit en una posicion a 0>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <byte a modificar>
	\param  <posicion a cambiar>
	\return <byte ya modificado>
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "funciones.h" 

#define SIN_ERROR   0
#define ERROR       -1

unsigned char clrbit(unsigned char dato,char posicion)
{
  unsigned char auxiliar = (1<<posicion);
  auxiliar = ~auxiliar;
  dato = dato & auxiliar;
  return dato;
}
