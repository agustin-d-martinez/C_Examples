/**
	\file    <main.c>
	\brief   <main del ejercicio>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.15> 
	\version <1.0.0>
*/

//--------------
//-- Includes --
//--------------
#include <stdio.h>              
#include <stdlib.h>
#include <time.h>
#include "funciones.h" 

#define TAMANO_NUM_ALEATORIO 320
#define NUM_INICIAL -120

/**
	\fn     <int main()>
	\brief  <main del ejercicio 1>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\return  <Regresa 0>
*/

int main(){
    
    int num_aleatorio, cant_numeros, i;
    int numeros[50];
    float *resultados= NULL;
    
    srand(time(NULL));      //inicio semilla del randomizador
    for(i=0;i<50;i++)
    {
        num_aleatorio = rand()%TAMANO_NUM_ALEATORIO + NUM_INICIAL;
        numeros[i] = num_aleatorio;
        printf("%d ", num_aleatorio);
    }
    printf("\n");
    cant_numeros =  muestras(numeros, &resultados);
    
    if(cant_numeros >= 0)
    {
        for(i=0;i<cant_numeros;i++)
        {
            printf("%.2f ",resultados[i]);
        }
    }
    printf("\n");
    
    free(resultados);
    
    return 0;
}
