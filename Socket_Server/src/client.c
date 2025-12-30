/*******************************************************************************************************************************//**
 *
 * @file		client.c
 * @brief		Funciones de manejo de clientes del servidor y manejo de HTML.
 * @date		08 oct. 2025
 * @author		Martinez Agustin
 *
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "../inc/client.h"

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn int client(int _client_id, struct sockaddr_in* _client_data)
 * \brief Maneja el cliente _client_id del servidor HTML.
 * \details Lee y responde a la petición del cliente. Guarda/borra KEYS en memoria compartida.
 * \param [in] _client_id: ID del cliente.
 * \param [in] _client_data: informacion del cliente.
 * \return Devuelve -1 si error. 0 sino.
*/
int client(int _client_id, int driver, KeyEntry_t* valid_keys, ActivityEntry_t*log, int sem_list[3])
{
    char buff_com[4096];

    KeyEntry_t key;

    int sem_k = sem_list[0];
    int sem_l = sem_list[1];
    int sem_write = sem_list[2];

    driver_msg_t driver_msg;
    driver_msg.command = ORANGE_LED;
    driver_msg.dec_ms = 200;

    // Lectura de mensaje recibido:
    int len = recv(_client_id, buff_com, sizeof(buff_com), 0);
    if (len == -1){
        shmdt(valid_keys);
        shmdt(log);
        return -1;
    }
    buff_com[len] = '\0';
    printf("*-------------------------------------------\n"
        "Recibido del cliente:\n\n%.30s\n"
        "*-------------------------------------------\n", buff_com);
    
    // Análisis del mensaje recibido:
    if (strstr(buff_com, "POST /agregar HTTP/1.1") != NULL) // Añado nueva clave valida
    { 
        if (GetKeyFromHTML(buff_com, &key) < 0){
            printf("Error clave no recibida");
            shmdt(valid_keys);
            shmdt(log);
            return -1;
        }
        int new_key = AddKey(key, valid_keys, sem_k);
        if (new_key < 0)
            printf("No pude añadir la KEY");
        
        if (new_key > 0)
        {
            if (writeDriver(driver, driver_msg, sem_write) == -1)
                return -1;
        }
        printf("Añadi la KEY: %s.\n", key.value);

        if (SendValidKeys(_client_id, valid_keys, sem_k) < 0){
            shmdt(valid_keys);
            shmdt(log);
            return -1;
        }
        printf("Envié keys.JSON\n\n");
    }
    if (strstr(buff_com, "POST /eliminar HTTP/1.1") != NULL)    // Borro nueva clave valida
    { 
        if (GetKeyFromHTML(buff_com, &key) < 0){
            printf("Error clave no recibida");
            shmdt(valid_keys);
            shmdt(log);
            return -1;
        }
        printf("Borré una KEY: %s.\n", key.value);
        
        int new_key = DeleteKey(key, valid_keys, sem_k);        
        if (new_key > 0)
        {
            if (writeDriver(driver, driver_msg, sem_write) == -1)
                return -1;
        }

        if (SendValidKeys(_client_id, valid_keys, sem_k) < 0){
            shmdt(valid_keys);
            shmdt(log);
            return -1;
        }
        printf("Envié keys.JSON\n\n");
    }
    if (strstr(buff_com, "GET /claves HTTP/1.1") != NULL)   //Envío la tabla de claves
    {
        if (SendValidKeys(_client_id, valid_keys, sem_k) < 0){
            shmdt(valid_keys);
            shmdt(log);
            return -1;
        }
        printf("Envié keys.JSON\n\n");
    }
    if (strstr(buff_com, "GET /log HTTP/1.1") != NULL)  //Envío la tabla de historial
    {
        if (SendLog(_client_id, log, sem_l) < 0){
            shmdt(valid_keys);
            shmdt(log);
            return -1;
        }
        printf("Envié log.JSON\n\n");
    }
    if (strstr(buff_com, "GET /favicon.ico HTTP/1.1") != NULL)  //Innecesario. YA coloqué un .ico vació en HTML
    {
        if (SendIco(_client_id, ICO_FILE) < 0)
        {
            printf("Error mandando el Icono\n");
            shmdt(valid_keys);
            shmdt(log);
            return -1;
        }
        printf("Se envió el icono\n");
    }
    if (strstr(buff_com, "GET / HTTP/1.1") != 0)
    {
        printf("Envio HTML\n");
        if (SendHTML(_client_id, PAGINA_HTML) < 0){
            printf("Error mandando el HTML\n");
            shmdt(valid_keys);
            shmdt(log);
            return -1;
        }
        printf("Se envió el HTML\n");
    }
    shmdt(valid_keys);
    shmdt(log);
    return 0;
    // Si get -> Envío la pantalla html (log actualizado)
    // Si post -> recibo claves/borro clave y envío la pantalla html
}

/**
 * \fn int GetKeyFromHTML(char* _buff, KeyEntry_t* _key)
 * \brief Obtiene la KEY del mensaje HTML recibido.
 * \details Obtiene la KEY del mensaje HTML recibido.
 * \param [in] _buff: Mensaje HTML recibido.
 * \param [in] _key: Puntero a KEY leída.
 * \return Devuelve -1 si error. 0 sino.
*/
int GetKeyFromHTML(char* _buff, KeyEntry_t* _key)
{
    const char* aux = strstr(_buff, "{\"clave\":\"");
    if(aux == NULL){
        return -1;
    }
    strncpy(_key->value, (aux + 10), KEY_SIZE);
    _key->value[KEY_SIZE] = '\0';
    return 0;
}

/**
 * \fn int SendHTML(int _client_id, char* _html_file)
 * \brief Envía el archivo HTML indicado.
 * \details Envía el archivo HTML indicado.
 * \param [in] _client_id: ID del cliente a enviar.
 * \param [in] _html_file: Nombre/Path del archivo HTML.
 * \return Devuelve -1 si error. 0 sino.
*/
int SendHTML(int _client_id, char* _html_file)
{
    FILE *file = fopen(_html_file, "rb");
    if (!file)
        return -1;
    

    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* buff_file = (char*)malloc(sizeof(char)*file_size + 1);
    if(!buff_file){
        fclose(file);
        return -1;
    }
    char* buff_com = (char*)malloc(sizeof(char)*(file_size+110));
    if(!buff_com){
        free(buff_file);
        fclose(file);
        return -1;
    }

    fread(buff_file, sizeof(char), file_size, file);
    buff_file[file_size] = '\0';
    fclose(file);

    sprintf(buff_com,
            "HTTP/1.1 200 OK\n"
            "Content-Length: %ld\n"
            "Content-Type: text/html; charset=utf-8\n"
            "Connection: Closed\n\n"
            "%s",
            file_size, buff_file);

    // Envia el mensaje al cliente
    int lenght = strlen(buff_com);
    int sent = 0;
    while (sent < lenght)
    {
        int aux = send(_client_id, buff_com + sent, lenght - sent, 0);
        if (aux <= 0){
            free(buff_file);
            free(buff_com);
            return -1;
        }
        sent += aux;
    }

    free(buff_com);
    free(buff_file);
    return 0;
}

/**
 * \fn int SendIco(int _client_id, char* _ico_file)
 * \brief Envía el icono indicado.
 * \details Envía el archivo .ico  indicado.
 * \param [in] _client_id: ID del cliente a enviar.
 * \param [in] _ico_file: Nombre/Path del archivo .ico.
 * \return Devuelve -1 si error. 0 sino.
*/
int SendIco(int _client_id, char* _ico_file)
{
    FILE *file = fopen(_ico_file, "rb");
    if (!file){
        return -1;
    }

    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* buff_file = (char*)malloc(sizeof(char)*file_size + 1);
    if(!buff_file){
        fclose(file);
        return -1;
    }
    char* buff_com = (char*)malloc(sizeof(char)*(file_size+110));
    if(!buff_com){
        free(buff_file);
        fclose(file);
        return -1;
    }

    fread(buff_file, sizeof(char), file_size, file);
    buff_file[file_size] = '\0';
    fclose(file);

    sprintf(buff_com,
            "HTTP/1.1 200 OK\n"
            "Content-Length: %ld\n"
            "Content-Type: image/x-icon; charset=utf-8\n"
            "Connection: Closed\n\n"
            "%s",
            file_size, buff_file);

    // Envia el mensaje al cliente
    int lenght = strlen(buff_com);
    int sent = 0;
    while (sent < lenght){
        int aux = send(_client_id, buff_com + sent, lenght - sent, 0);
        if (aux <= 0){
            free(buff_file);
            free(buff_com);
            return -1;
        }
        sent += aux;
    }

    free(buff_com);
    free(buff_file);
    return 0;
}

/**
 * \fn int SendValidKeys(int _client_id, KeyEntry_t* _valid_keys, int _semId)
 * \brief Envía las KEYs válidas al servidor HTML.
 * \details Envía las KEYs válidas al servidor HTML.
 * \param [in] _client_id: ID del cliente a enviar.
 * \param [in] _valid_keys: Lista de valid KEYs.
 * \param [in] _semId: Id del semáforo de _valid_keys.
 * \return Devuelve -1 si error. 0 sino.
*/
int SendValidKeys(int _client_id, KeyEntry_t* _valid_keys, int _semId)
{
    int pos = 1;
    int file_size;

    if (lockSem(_semId) == -1){
        return -1;
    }

    char* buff_file = (char*)malloc((sizeof(char)*MAX_VALID_KEYS*7+2));
    if(!buff_file){
        unlockSem(_semId);
        return -1;
    }

    buff_file[0] = '[';
    buff_file[1] = '\0';
    for (int i = 0; i < MAX_VALID_KEYS; i++){
        if (_valid_keys[i].value[0] == '\0'){  
            break;
        }
        pos += sprintf(buff_file + pos, "\"%s\"", _valid_keys[i].value);
        if (i < (MAX_VALID_KEYS-1)){ //Si no estoy en el último posible
            if (_valid_keys[i+1].value[0] != '\0'){  //Si el que sigue existe
                pos += sprintf(buff_file + pos, ",");
            }
        }
    }
    sprintf(buff_file + pos, "]");
    file_size = strlen(buff_file);
    printf("Envio: %s", buff_file);

    if(unlockSem(_semId) < 0){
        free(buff_file);
        return -1;
    }

    char* buff_com = (char*)malloc(sizeof(char)*(file_size+115));
    if(!buff_com){
        free(buff_file);
        return -1;
    }

    sprintf(buff_com,
            "HTTP/1.1 200 OK\n"
            "Content-Length: %d\n"
            "Content-Type: application/json; charset=utf-8\n"
            "Connection: Closed\n\n"
            "%s",
            file_size, buff_file);

    // Envia el mensaje al cliente
    int lenght = strlen(buff_com);
    int sent = 0;
    while (sent < lenght){
        int aux = send(_client_id, buff_com + sent, lenght - sent, 0);
        if (aux <= 0){
            free(buff_file);
            free(buff_com);
            return -1;
        }
        sent += aux;
    }

    free(buff_com);
    free(buff_file);
    return 0;
}

/**
 * \fn int SendLog(int _client_id, ActivityEntry_t* _log, int _semId)
 * \brief Envía el log al servidor HTML.
 * \details Envía el log al servidor HTML.
 * \param [in] _client_id: ID del cliente a enviar.
 * \param [in] _log: Log/Lista de actividades a enviar.
 * \param [in] _semId: Id del semárofo de _log.
 * \return Devuelve -1 si error. 0 sino.
*/
int SendLog(int _client_id, ActivityEntry_t* _log, int _semId)
{
    int pos = 1;
    int file_size;

    if (lockSem(_semId) == -1){
        return -1;
    }
    char* buff_file = (char*)malloc((sizeof(char)*MAX_LOG*75+3));    //CAMBIAR
    if(!buff_file){
        unlockSem(_semId);
        return -1;
    }
    buff_file[0] = '[';
    buff_file[1] = '\0';
    for (int i = 0; i < MAX_LOG; i++){
        if (_log[i].code[0] == '\0'){  //Terminé la lista
            break;
        }
        char date[11]; // "YYYY/MM/DD\0"
        snprintf(date, sizeof(date), "%.4s/%.2s/%.2s",
                 _log[i].date, _log[i].date + 4, _log[i].date + 6);
        char time[9]; // "HH:MM:SS\0"
        snprintf(time, sizeof(time), "%.2s:%.2s:%.2s",
                 _log[i].time, _log[i].time + 2, _log[i].time + 4);

        pos += sprintf(buff_file + pos,
            "{\"fecha\":\"%s\",\"hora\":\"%s\",\"clave\":\"%s\",\"estado\":\"%d\"}",
            date, time, _log[i].code, _log[i].status);
        if ((i+1) < MAX_LOG ){  //Si no es el último posible
            if (_log[i+1].code[0] != '\0'){  //Si el que le sigue existe
                pos += sprintf(buff_file + pos, ",");
            }
        }
    }
    sprintf(buff_file + pos, "]");
    printf("Envio: %s", buff_file);
    file_size = strlen(buff_file);

    if(unlockSem(_semId) == -1){
        free(buff_file);
        return -1;
    }

    char* buff_com = (char*)malloc(sizeof(char)*(file_size+120));
    if(!buff_com){
        free(buff_file);
        return -1;
    }

    sprintf(buff_com,
            "HTTP/1.1 200 OK\n"
            "Content-Length: %d\n"
            "Content-Type: application/json; charset=utf-8\n"
            "Connection: Closed\n\n"
            "%s",
            file_size, buff_file);

    // Envia el mensaje al cliente
    int lenght = strlen(buff_com);
    int sent = 0;
    while (sent < lenght){
        int aux = send(_client_id, buff_com + sent, lenght - sent, 0);
        if (aux <= 0){
            free(buff_file);
            free(buff_com);
            return -1;
        }
        sent += aux;
    }

    free(buff_com);
    free(buff_file);
    return 0;
}
