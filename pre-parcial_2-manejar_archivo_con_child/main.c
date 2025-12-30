/**
	\file    <main_juego.c>
	\brief   <Juego de adivinar un número.>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.7> 
	\version <1.0.0>
*/

#define MAYOR_MENOR     1
#define FRIO_CALIENTE   2

//--------------
//-- Includes --
//--------------
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <signal.h>
#include "funciones.h"

int cant_hijos = 1;

void atiendo_chld (int signal)
{
	int fin = 1;
    
    fin = waitpid(-1, NULL, WNOHANG);
    if (fin > 0) cant_hijos--;
        
	return;
}

int main(int argc, char ** argv)
{
    int cant = 0;
    int i,pid;
    char dir_lectura[50];
    char dir_escritura[50];
    int p[2];
    PALABRAS * listado = malloc(sizeof(PALABRAS));
    signal (SIGCHLD, atiendo_chld);
    
    if(enunciado(dir_escritura, dir_lectura, argc, argv) == SIN_ERROR)
    {
        cant = CargarPalabras(dir_lectura, &listado);
    
        for(i=0;i<cant;i++)
            printf("Palabra: %s\t\t\t\tRepeticiones: %d\n",listado[i].nombre, listado[i].cantidad);
        
        pipe(p);
        pid = fork();
        
        if(pid == 0)        //Hijo
        {
            close(p[1]);
            read(p[0], dir_escritura, sizeof(char)*50);
            
            cant = EscribirPAlabrasEnArchivo(listado, cant, dir_escritura);
            close(p[0]);
        }
        else        //Padre
        {
            close(p[0]);
            write(p[1], dir_escritura, sizeof(char)*50);
            close(p[1]);
            
            while(cant_hijos != 0)
                sleep(1);
        }
    }
    else
        printf("Modo de uso: %s -i <Archivo entrada> -o <Archivo salida>\n",argv[0]);
    
    liberar(&listado);
    return 0;
}
