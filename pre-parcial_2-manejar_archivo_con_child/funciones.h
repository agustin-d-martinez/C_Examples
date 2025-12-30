/**
	\file    funciones.h
	\brief   Prototipos de las funciones incluidas en funciones.c
	\author  MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)
	\date    2021.10.21
	\version 1.0.0
*/


#ifndef FUNCIONES_H
	#define FUNCIONES_H

	//--------------
	//-- Includes --
	//--------------

	#include <stdlib.h>
	#include <stdio.h>     //Entrada/salida (teclado/pantalla)
	#include <string.h>    //manejo strings
    #include <unistd.h>    //Función sleep() - fork
    #include <ctype.h>     //Función tolower
    #include <sys/types.h>  //para el fork - wait
    #include <sys/wait.h>   //para wait

	
	#define VERDADERO   1
	#define FALSO       0
	
    #define SIN_ERROR   0
    #define ERROR       -1
	//------------
	//-- Struct --
	//------------

	//Estructura definida para usuarios.
    typedef struct palabras
    {
        char nombre[20];
        int cantidad;
    }PALABRAS;


	//----------------
	//-- Prototipos --
	//----------------
    int enunciado(char * dir_escritura, char * dir_lectura, int argc, char **argv);
    void liberar (PALABRAS ** listado);

    int CargarPalabras(const char* dir_archivo, PALABRAS ** listado);
    int leer_palabra(char * auxiliar, FILE *archivo);
    void guardar(char * palabra, PALABRAS ** listado, int * cant);
    void minuscula(char * frase);

    int EscribirPAlabrasEnArchivo(PALABRAS* listado, int cant, const char *dir_archivo);
    void escribir(PALABRAS* listado, int cant, FILE* archivo);
    void ordenar(PALABRAS* listado, int cant);

#endif



