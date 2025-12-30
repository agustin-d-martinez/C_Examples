/*******************************************************************************************************************************//**
 *
 * @file		main.h
 * @brief		Módulo principal.
 * @date		08 oct. 2025
 * @author		Martinez Agustin
 *
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef MAIN_H
#define MAIN_H

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <stdio.h>      // files, scanf
#include <stdlib.h>     // exit(), sleep()
#include <unistd.h>     // fork(), close()
#include <string.h>     // strlen(), memcmp()
#include <sys/socket.h> // AF_INET, SOCK_STREAM
#include <netinet/in.h> // struct sockaddr_in
#include <sys/wait.h>   // waitpid()
#include <signal.h>     // signal()
#include <errno.h>      // errno variable

#include "../inc/data.h"
#include "../inc/client.h"
#include "../inc/periph.h"

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
#define DEFAULT_BACKLOG         1
#define DEFAULT_MAXCONNECTIONS  1

int GetInitValue(const char* _file_name, const char* _key);
int MakeServer(int _port, int _backlog );
void setHandlers( void );

void ChildHandler(int signal);
void KillHandler(int signal);

#endif
