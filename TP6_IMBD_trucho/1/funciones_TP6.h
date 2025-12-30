/**
	\file    <funciones_TP6.h>
	\brief   <Headers de funciones>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\version <1.0.0>
*/


#ifndef funciones_TP6_H
#define funciones_TP6_H

#define SIN_ERROR           0
#define ERROR_MEM_DINAMICA  -1

#define TAMANO_NOMBRE       30
#define TAMANO_DIRECTOR     15

#define TRUE      1
#define FALSE     0

enum
{
    CARGAR = 1,
    ORDEN_RECAUDACION,
    ORDEN_ANIO,
    IMPRIMIR,
    SALIR,
};

typedef struct
{
    char nombre [TAMANO_NOMBRE];
    char director [TAMANO_DIRECTOR];
    int anio;
    float recaudacion;
} Pelicula;

//----------------
//-- Prototipos --
//----------------

//Acá poner los prototipos.
int menu();

void ingreso_peliculas(Pelicula ** listado,int * cant_peliculas);
void ordenar_recaudacion(Pelicula * listado, int largo);
void ordenar_anio(Pelicula * listado, int largo);
void imprimir(Pelicula *listado,int cant_peliculas);

void liberar (Pelicula ** listado);

void sacar_enter(char *palabra);

#endif


