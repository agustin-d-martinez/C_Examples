/**
	\file    <funciones_menu.h>
	\brief   <Headers de funciones>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\version <1.0.0>
*/


#ifndef funciones_menu_H
#define funciones_menu_H

#define ORDEN_PUNTAJE       1
#define ORDEN_ANIO          2
#define ORDEN_DIRECTOR      3


//----------------
//-- Prototipos --
//----------------

//Acá poner los prototipos.


int menu ();
int menu_continuar();
int menu_ordenado();

void imprimir(Pelicula * listado, int largo, int tipo_orden, char* filtro);

#endif


