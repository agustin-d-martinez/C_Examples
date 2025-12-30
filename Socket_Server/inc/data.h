/*******************************************************************************************************************************//**
 *
 * @file		data.h
 * @brief		Funciones de manejo de información y memoria compartida KEY y LOGS.
 * @date		08 oct. 2025
 * @author		Martinez Agustin
 *
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef DATA_H
#define DATA_H

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <sys/ipc.h>    // Claves IPC para memoria compartida y semáforos
#include <sys/shm.h>    // Manejo de memoria compartida
#include <sys/sem.h>    // Manejo de semáforos
#include <string.h>     // Funciones de manejo de cadenas (strcmp, strcpy, etc.)
#include <time.h>       // Formateo de fecha y hora
#include <stdio.h>      // Funciones de salida estándar

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define SM_ID_K     1111    /**< ID de memoria compartida para las claves válidas */
#define SEM_ID_K    2222    /**< ID de semáforo para las claves válidas */
#define SM_ID_L     3333    /**< ID de memoria compartida para los registros de log */
#define SEM_ID_L    4444    /**< ID de semáforo para los registros de log */
#define SEM_ID_WR   1234    /**< ID de escritura del driver */

#define MAX_VALID_KEYS  5  /**< Cantidad máxima de claves válidas almacenadas */
#define MAX_LOG         5  /**< Cantidad máxima de registros de actividad */

#define KEY_SIZE        4   /**< Largo máximo de la clave */

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
/**
 * \union semun
 * \brief Estructura requerida por las funciones semctl() para inicializar semáforos.
 */
union semun {
    int val;               /**< Value for SETVAL */
    struct semid_ds *buf;  /**< Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /**< Array for GETALL, SETALL */
    struct seminfo *__buf; /**< Buffer for IPC_INFO (Linux specific) */
};

/**
 * \struct KeyEntry_t
 * \brief Estructura de una clave de la alarma.
 */
typedef struct {    
    char value[KEY_SIZE+1]; /**< Valor de la clave en formato string */
} KeyEntry_t;

/**
 * \struct ActivityEntry_t
 * \brief Estructura que representa una entrada en el log de actividad del sistema.
 */
typedef struct {      
    char date[9];               /**< Fecha en formato YYYYMMDD */
    char time[7];               /**< Hora en formato HHMMSS */
    char code[KEY_SIZE + 1];    /**< Clave utilizada */
    int status;                 /**< Resultado: 1 si fue aceptada, 0 si fue denegada */
} ActivityEntry_t;

/***********************************************************************************************************************************
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn void* createShMem(int _id, size_t _size, int _create, int* _shmId)
 * \brief Crea/abre un Shared Memory.
 * \details Crea/abre el Shared Memory con la Key correspondiente. 
 * \param [in] _path: Path al archivo generador de clave.
 * \param [in] _proj_id: ID para el ftok.
 * \param [in] _size: TAmaño de la Shared Memory.
 * \param [in] _shmId: Puntero a la ID de la Shared Memory.
 * \return Devuelve el puntero a la Shared Memory o NULL si falla.
*/
void* createShMem(char* _path, int _proj_id, size_t _size, int* _shmId);
/**
 * \fn int createSem(int _id, int _create)
 * \brief Crea/abre un semáforo.
 * \details Crea/abre el semáforo con la Key correspondiente. 
 * \param [in] _path: Path al archivo generador de clave.
 * \param [in] _proj_id: ID para el ftok.
 * \return Devuelve -1 si error. 0 sino.
*/
int createSem(char* _path, int _proj_id);

/**
 * \fn int lockSem(int _semId)
 * \brief Bloquea un semáforo.
 * \details Bloquea el semáforo con la ID correspondiente.
 * \param [in] _semId: ID del semáforo.
 * \return Devuelve -1 si error. 0 sino.
*/
int lockSem(int _semId);
/**
 * \fn int unlockSem(int _semId)
 * \brief Desbloquea un semáforo.
 * \details DEsbloquea el semáforo con la ID correspondiente.
 * \param [in] _semId: ID del semáforo.
 * \return Devuelve -1 si error. 0 sino.
*/
int unlockSem(int _semId);
/**
 * \fn void closeSem(int _semId)
 * \brief Cierra un semáforo.
 * \details Cierra el semáforo con la ID correspondiente.
 * \param [in] _semId: ID del semáforo.
 * \return Void.
*/
void closeSem(int _semId);

//int CreateKey(KeyEntry_t* _key, char* _value);
/**
 * \fn int AddKey(const KeyEntry_t _key, KeyEntry_t* _valid_keys, int _semId)
 * \brief Añade una Key a la lista de Keys.
 * \details Añade una Key a la lista de Keys.
 * \param [in] _key: Clave a guardar.
 * \param [in] _valid_keys: Lista de valid Keys.
 * \param [in] _semId: Id del semáforo para utilizar.
 * \return Devuelve -1 si error. 0 sino.
*/
int AddKey(const KeyEntry_t _key, KeyEntry_t* _valid_keys, int _semId);
/**
 * \fn int DeleteKey(const KeyEntry_t _key, KeyEntry_t* _valid_keys, int _semId)
 * \brief Elimina una Key a la lista de Keys.
 * \details Elimina una Key a la lista de Keys.
 * \param [in] _key: Clave a borrar.
 * \param [in] _valid_keys: Lista de valid Keys.
 * \param [in] _semId: Id del semáforo a utilizar.
 * \return Devuelve -1 si error. 0 sino.
*/
int DeleteKey(const KeyEntry_t _key, KeyEntry_t* _valid_keys, int _semId);
/**
 * \fn int HasKey(const KeyEntry_t _key, const KeyEntry_t* _valid_keys, int _semId)
 * \brief Detecta si una Key está en una lista o no.
 * \details Detecta si una Key está en una lista o no.
 * \param [in] _key: Clave a buscar.
 * \param [in] _valid_keys: Lista de valid Keys.
 * \param [in] _semId: Id del semáforo a utilizar.
 * \return 1 si posee la KEY. 0 si no.
*/
int HasKey(const KeyEntry_t _key, const KeyEntry_t* _valid_keys, int _semId);

/**
 * \fn int CreateActivityEntry(ActivityEntry_t* _activity, KeyEntry_t _code, const int _status)
 * \brief Crea un ActivityEntry_t.
 * \details Crea un ActivityEntry_t con la fecha actual y los valores indicados.
 * \param [in] _activity: puntero a actividad a crear.
 * \param [in] _code: Codigo de la actividad creada.
 * \param [in] _status: Status de la actividad creada.
 * \return Devuelve -1 si error. 0 sino.
*/
int CreateActivityEntry(ActivityEntry_t* _activity, KeyEntry_t _code, const int _status);
/**
 * \fn int AddLog(const ActivityEntry_t _activity, ActivityEntry_t* _log, int _semId)
 * \brief Añade una actividad a un log de actividades.
 * \details Añade una actividad a un log de actividades.
 * \param [in] _activity: actividad a guardar.
 * \param [in] _log: log de actividades.
 * \param [in] _semId: Id del semáforo a utilizar.
 * \return Devuelve -1 si error. 0 sino.
*/
int AddLog(const ActivityEntry_t _activity, ActivityEntry_t* _log, int _semId);
//int DeleteLog(const ActivityEntry_t _activity, ActivityEntry_t* _log, int _semId);
//int HasLog(const ActivityEntry_t _activity, ActivityEntry_t* _log, int _semId);

#endif /* DATA_H */
