/**
	\file    <Nombre del archivo>
	\brief   <Que contiene el archivo>
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día> 
	\version <Versión (ejemplo: 1.0.0)>
*/

#define VIDAS_FACIL     -1      //El -1 se conciderara infinito
#define VIDAS_NORMAL    5
#define VIDAS_DIFICIL   3

#define CANT_NUMEROS    100
#define NUM_MINIMO      1

#ifndef funciones_juego_h
#define funciones_juego_h


//----------------
//-- Prototipos --
//----------------
void introduccion(void);
int menu(int *vidas);
int juego_mayor_menor(int intentos);
int juego_frio_caliente(int intentos);
//Acá poner los prototipos.

#endif


