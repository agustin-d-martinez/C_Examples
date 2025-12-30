/**
	\file    <funciones_juego.c>
	\brief   <Las funciones de los dos modos de juego del TP3>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.6.7> 
	\version <1.0.0>
*/





//--------------
//-- Includes --
//--------------
#include <stdio.h> 
#include <stdlib.h> 
#include "randomizador_frases.h" 
#include "funciones_juego.h"
#include "error.h"


/**
	\fn     <void introduccion(void)>
	\brief  <Introduce el juego e indica las reglas del mismo.>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.7>  
*/
void introduccion(void){
    int opcion;
    printf("\t\t\t    Bienvenido a:\n \t\t\t--ADIVINA EL NUMERO--\n\n\n");
    printf("  ¿Desea ver las reglas?\n1-SI \n2-NO\n");
    scanf("%d",&opcion);                                                        //Pregunto si quiere leerse las reglas
    error(&opcion, 2, 1);   //Verifico que lo escriba bien
    if(opcion == 1){
        printf("\n\tEl juego consiste en adivinar un numero entre %d y %d.",NUM_MINIMO,CANT_NUMEROS+NUM_MINIMO-1);
        printf(" Existen 2 modos de juego. En uno te ayudaremos señalando cuando estes cerca del numero a adivinar (aunque ambos sabemos que eso nunca va a pasar). En el otro te insultaremos cuando te pases de largo o te falte para llegar al numero correcto.\n");
        printf("\tPor ultimo, deberas elegir entre 3 dificultades que limitaran tu cantidad de intentos.\n\n\tY recuerda,  cualquiera puede ganar, SALVO TU!!");
    }
    else
        printf("Ahh, veo que tenemos a un listillo....\t Continuemos.");
    return;
}

/**
	\fn     <int menu(int *vidas)>
	\brief  <genera un menu para el juego del TP2.>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.7>  
	\param  <Puntero que retornara con la cantidad de vidas que seleccionó el usuario>
	\return <El modo de juego elegido>
*/
int menu(int *vidas){
    int opcion, auxiliar_dificultad;
    printf("\n\nIndique modo de juego\n 1-mayor/menor.\n 2-frio/caliente\n");   //Eije el modo de juego
    scanf("%d",&opcion);
    error(&opcion, 2, 1);   //Verifico que lo escriba bien
    
    printf("Elija la dificultad:\n\n1-Sigo en pañales \n2-Todo un hombre \n3-Me gusta el dolor\n"); //Elije la dificultad
    scanf("%d",&auxiliar_dificultad);
    error(&auxiliar_dificultad, 3, 1);   //Verifico que lo escriba bien
    
    if(auxiliar_dificultad == 1)        //Asigno la cantidad de vidas
        *vidas = VIDAS_FACIL;
    else if(auxiliar_dificultad == 2)
        *vidas = VIDAS_NORMAL;
    else if(auxiliar_dificultad == 3)
        *vidas = VIDAS_DIFICIL;
    
    return opcion;      //Devuelvo el modo de juego
}

/**
	\fn     <int juego_mayor_menor(int intentos)>
	\brief  <Realiza el juego con pistas del tipo mayor/menor.>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.7>  
	\param  <Cantidad de vidas que posee el usuario (-1 si son infinitas)>
	\return <1 si se ganó el juego, 0 si se perdió el juego>
*/
int juego_mayor_menor(int intentos){
    int ganar = 0, numero = 0, num_ingresado = 0;
    
    numero = rand()%CANT_NUMEROS + NUM_MINIMO;      //Genero el número aleatorio
    
    printf("\t\t\t--ADIVINA EL NUMERO--\n\n");
    do
    {
        if(intentos != VIDAS_FACIL)
            printf("Tenés %d intentos restantes.\n",intentos);
        
        scanf("%d", &num_ingresado);    //El usuario ingresa su intento
        
        if(intentos == VIDAS_FACIL)     //genera el infinito
            intentos++;
        
        if(numero < num_ingresado){         //Verifico si el intento es mayor al objetivo
            intentos--;     //resto 1 intento
            if(intentos != 0)
                frase(BAJAR);   //tiro la frase
        }
        else if(numero > num_ingresado){    //Verifico si el intento es menor al objetivo
            intentos--;     //resto 1 intento
            if(intentos != 0)
                frase(SUBIR);   //tiro la frase
        }
        else
            ganar = 1;
        
        if((intentos == 0) && (ganar == 0))     //Si pierde le digo cuál era el número
            printf("el numero era %d.\n", numero);
        
    }while((ganar == 0) && (intentos != 0));
    
    return ganar;   //Devuelvo si ganó
}

/**
	\fn     <int juego_frio_caliente(int intentos)>
	\brief  <Realiza el juego con pistas del tipo frio/caliente.>
	\author <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date   <2021.6.7>  
	\param  <Cantidad de vidas que posee el usuario (-1 si son infinitas)>
	\return <1 si se ganó el juego, 0 si se perdió el juego>
*/
int juego_frio_caliente(int intentos){
    int ganar = 0, numero = 0, num_ingresado = 0, tipo_frase = 0;
    
    numero = rand()%CANT_NUMEROS + NUM_MINIMO;  //Genero el número aleatorio
    
    printf("\t\t\t--ADIVINA EL NUMERO--\n\n");
    
    do
    {
        if(intentos != VIDAS_FACIL)
            printf("Tenés %d intentos restantes.\n",intentos);      //Indico cuántos intentos le quedan
        
        scanf("%d", &num_ingresado);    //Leo el intento del usuario
        
        if(intentos == VIDAS_FACIL)     //genera el infinito
            intentos++;
        
        if(numero == num_ingresado)     //Verifico si acertó
            ganar = 1;
        
        else if((numero-num_ingresado < 5) && (numero- num_ingresado > -5))     //Verifico si está a +-5
            tipo_frase = CALIENTE;
            
        else if((numero-num_ingresado < 20) && (numero- num_ingresado > -20))   //Verifico si está a +-20
            tipo_frase = TIBIO;
            
        else
            tipo_frase = FRIO;
        
        if(ganar == 0){
            intentos--;             //Si aun no gana, le resto un intento
            if(intentos == 0)
                printf("El numero era %d.\n", numero);      //SI se quedó sin intentos le digo la respuesta
            else
                frase(tipo_frase);    //Le tiro la frase
        }
    
    }while((ganar == 0) && (intentos != 0));
    
    return ganar;       //Devuelvo si ganó
}
