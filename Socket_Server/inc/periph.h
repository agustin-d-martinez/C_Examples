/*******************************************************************************************************************************//**
 *
 * @file		periph.h
 * @brief		Manejo de la lectura de la alarma y log.
 * @date		08 oct. 2025
 * @author		Martinez Agustin
 *
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef PERIPH_H
#define PERIPH_H
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "../inc/data.h"
#include "../inc/driverHandler.h"

#include <stdio.h>      // files, scanf
#include <stdlib.h>     // sleep
#include <unistd.h>     // sleep

/***********************************************************************************************************************************
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn int periph( int driver )
 * \brief Función de manejo del periférico
 * \details Abre la memoria compartida, lee el teclado y analiza la respuesta. 
 * \param [in] driver: File descriptor del driver a utilizar. 
 * Las respuestas activan los leds y se guardan en el log.
*/
int periph( int driver, KeyEntry_t* valid_keys, ActivityEntry_t*log, int sem_list[3]);

#endif