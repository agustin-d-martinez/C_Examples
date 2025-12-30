/*******************************************************************************************************************************//**
 *
 * @file		client.h
 * @brief		Funciones de manejo de clientes del servidor y manejo de HTML.
 * @date		08 oct. 2025
 * @author		Martinez Agustin
 *
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef CLIENT_H
#define CLIENT_H

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <sys/socket.h> // AF_INET, SOCK_STREAM, inet_ntoa()
#include <stdio.h>      // files, scanf
#include <netinet/in.h> // struct sockaddr_in, inet_ntoa()
#include <stdlib.h>     // exit()
#include <arpa/inet.h>  // inet_ntoa()
#include <string.h>     // strlen(), strstr(), memcmp()
#include <unistd.h>     // close()

#include "../inc/data.h"
#include "../inc/driverHandler.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define PAGINA_HTML "web/webserver.html"    /**< Archivo HTML principal del servidor */
#define ICO_FILE "web/favicon.ico"          /**< Ícono del sitio web */

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
/**
 * \fn int client(int _client_id, struct sockaddr_in* _client_data)
 * \brief Maneja el cliente _client_id del servidor HTML.
 * \details Lee y responde a la petición del cliente. Guarda/borra KEYS en memoria compartida.
 * \param [in] _client_id: ID del cliente.
 * \param [in] _client_data: informacion del cliente.
 * \return Devuelve -1 si error. 0 sino.
*/
int client(int _client_id, int driver, KeyEntry_t* valid_keys, ActivityEntry_t*log, int sem_list[3]);

/**
 * \fn int GetKeyFromHTML(char* _buff, KeyEntry_t* _key)
 * \brief Obtiene la KEY del mensaje HTML recibido.
 * \details Obtiene la KEY del mensaje HTML recibido.
 * \param [in] _buff: Mensaje HTML recibido.
 * \param [in] _key: Puntero a KEY leída.
 * \return Devuelve -1 si error. 0 sino.
*/
int GetKeyFromHTML(char* _buff, KeyEntry_t* _key);
/**
 * \fn int SendHTML(int _client_id, char* _html_file)
 * \brief Envía el archivo HTML indicado.
 * \details Envía el archivo HTML indicado.
 * \param [in] _client_id: ID del cliente a enviar.
 * \param [in] _html_file: Nombre/Path del archivo HTML.
 * \return Devuelve -1 si error. 0 sino.
*/
int SendHTML(int _client_id, char* _html_file);
/**
 * \fn int SendIco(int _client_id, char* _ico_file)
 * \brief Envía el icono indicado.
 * \details Envía el archivo .ico  indicado.
 * \param [in] _client_id: ID del cliente a enviar.
 * \param [in] _ico_file: Nombre/Path del archivo .ico.
 * \return Devuelve -1 si error. 0 sino.
*/
int SendIco(int _client_id, char* _ico_file);

/**
 * \fn int SendValidKeys(int _client_id, KeyEntry_t* _valid_keys, int _semId)
 * \brief Envía las KEYs válidas al servidor HTML.
 * \details Envía las KEYs válidas al servidor HTML.
 * \param [in] _client_id: ID del cliente a enviar.
 * \param [in] _valid_keys: Lista de valid KEYs.
 * \param [in] _semId: Id del semáforo de _valid_keys.
 * \return Devuelve -1 si error. 0 sino.
*/
int SendValidKeys(int _client_id, KeyEntry_t* _valid_keys, int _semId);
/**
 * \fn int SendLog(int _client_id, ActivityEntry_t* _log, int _semId)
 * \brief Envía el log al servidor HTML.
 * \details Envía el log al servidor HTML.
 * \param [in] _client_id: ID del cliente a enviar.
 * \param [in] _log: Log/Lista de actividades a enviar.
 * \param [in] _semId: Id del semárofo de _log.
 * \return Devuelve -1 si error. 0 sino.
*/
int SendLog(int _client_id, ActivityEntry_t* _log, int _semId);

#endif /* CLIENT_H */
