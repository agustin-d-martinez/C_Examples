/**
	\file    <funciones_nietflix.h>
	\brief   <Headers de funciones>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.9.2> 
	\version <1.0.0>
*/


#ifndef funciones_nietflix_H
#define funciones_nietflix_H

#define SIN_ERROR           0
#define ERROR_MEM_DINAMICA  -1

#define CARGAR_PELICULA     1
#define ORDENAR_PELICULA    2
#define SALIR_PROGRAMA      3

#define TAMANO_BUFFER       100

#define PUNTAJE_MAXIMO      100

#define TRUE                1
#define FALSE               2

typedef struct
{
    char * nombre;
    int anio;
    unsigned char genero;
    char* director;
    float puntaje;
} Pelicula;

//----------------
//-- Prototipos --
//----------------

//Acá poner los prototipos.
int ingreso_peliculas(Pelicula ** listado,int cant_peliculas);
void sacar_enter(char *palabra);


void ordenar_puntaje(Pelicula * listado, int largo);
void ordenar_anio(Pelicula * listado, int largo);


void liberar (Pelicula ** listado,int cant_peliculas);

#endif


