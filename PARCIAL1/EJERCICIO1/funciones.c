/*
	\file    <funciones.c>
	\brief   <funciones del ejercicio1>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\version <1.0.0>
*/


//--------------
//-- Includes --
//--------------


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funciones.h" 

#define SIN_ERROR   0
#define ERROR -1

/**
    \fn     <int muestras(int *datos,float **valores)>
	\brief  <Crea un vector de muestras>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <vector con datos>
	\param  <vector con los resultados>
	\return <cantidad de resultados/ error>
*/
int muestras(int *datos,float **valores)
{
    int error = SIN_ERROR; 
    int i=0;
    int cant_resultados = 0;
    float resultado;
    
    *valores = (float*)calloc(1,sizeof(float));     //Creo la mem_DINAMICA
    
    while((i<50) && (error == SIN_ERROR))
    {
        resultado = reemplazar_formula(datos[i]);
        
        if(resultado >= 0)  //Solo si es positivo
        {
            cant_resultados++;
            
            *valores = (float*) realloc((*valores),cant_resultados*sizeof(float));    //Aumento la MEM_DINAMICA

            if((*valores) == NULL)
            {
                error = ERROR;
            }
            else
            {
                (*valores)[cant_resultados-1] = resultado;      //Guardo el valor
            }
        }
        i++;
    }
    
    if((cant_resultados == 0) || (error == ERROR))      //Libero si fallò
        free(*valores);
    else            
        error = cant_resultados;            //Envio los resultados
    
    return error;
}

/**
    \fn     <float reemplazar_formula(float resultado )>
	\brief  <reeemplaza en la fòrmula>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <valor a reemplazar>
	\return <resultado reemplazado>
*/

float reemplazar_formula(float resultado )
{
    float valor;
    valor = (float)pow(resultado,3)/1920;
    valor += (float)pow(resultado,2)/32;
    valor += (float)resultado/16;
    valor = (float)valor/2; //Acá reemplazé en la fórmula
    valor = valor + 0.75;
    return valor;
}
