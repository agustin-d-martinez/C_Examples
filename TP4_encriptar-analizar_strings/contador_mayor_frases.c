/**
	\file    <contador_mayor_frases.c>
	\brief   <Funciones para el ejercicio 1>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.15> 
	\version <1.0.0>
*/


//--------------
//-- Includes --
//--------------

#include <string.h>
#include "funciones_strings.h"
#include "contador_mayor_frases.h"

/**
	\fn     <int mayor(int *vector, int largo)>
	\brief  <Busca el mayor numero dentro de un vector>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <Puntero con el vector a analizar>
	\param  <Largo del vector>
	\return  <Posicion del vector con el mayor número>
*/

int mayor(int *vector, int largo)
{
    int i, resultado = 0;   //Resultado inicia en posición 0
    for(i=0; i < largo; i++)            //Barro todo el vector
    {
        if(vector[i] > vector[resultado])       //Me fijo si el valor actual es mayor al anterior
            resultado = i;                      //Guardo el valor actual
    }
    return resultado;       //Devuelvo el valor que quedó al finalizar
}

/**
	\fn     <void contar(char *frase,int *histograma, int *caracteres_especiales,int *numeros)>
	\brief  <Cuenta la cantidad de letras y los guarda en el histograma>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <Puntero con el string a analizar>
	\param  <Puntero con el vector de 26 posiciones donde se guardan las letras>
*/

void contar_letras(char *frase,int *histograma)
{
    int tamano, i;
    tamano = strlen(frase);     //Calculo el tamaño
    for(i = 0; i < tamano; i++)     //Barro la frase
    {
        if(es_letra(frase[i]))      //Si es letra sumo en la posición i-A (i= valor letra en ascii)
            histograma[frase[i]-'A']++;                                 //(A = lo resto para pasar a número común)   
    }
    return;
}

/**
	\fn     <void contar(char *frase,int *histograma, int *caracteres_especiales,int *numeros)>
	\brief  <Cuenta la cantidad de números y caracteres caracteres especiales y los guarda en sus respectivas variables>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.15> 
	\param  <Puntero con el string a analizar>
	\param  <Puntero con el vector de 26 posiciones donde se guardan las letras>
	\param  <Puntero con el valor de los caracteres especiales>
	\param  <Puntero con el valor de los numeros>
*/

void contar_especiales(char *frase, int *caracteres_especiales,int *numeros)
{
    int tamano, i;
    tamano = strlen(frase);     //Calculo el tamaño
    for(i = 0; i < tamano; i++)     //Barro la frase
    {
        if(es_numero(frase[i]))        //Si es número, sumo en número
            *numeros += 1;
        else if(es_letra(frase[i]) == 0)      //Si no es una es letra, es un caracter especial
            *caracteres_especiales += 1;    
    }
    return;
}
