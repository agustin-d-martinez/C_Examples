/*******************************************************************************************************************************//**
 *
 * @file		data.c
 * @brief		Funciones de manejo de información y memoria compartida KEY y LOGS.
 * @date		08 oct. 2025
 * @author		Martinez Agustin
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "../inc/data.h"

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn void* createShMem(int _id, size_t _size, int* _shmId)
 * \brief Crea/abre un Shared Memory.
 * \details Crea/abre el Shared Memory con la Key correspondiente. 
 * \param [in] _path: Path al archivo generador de clave.
 * \param [in] _proj_id: ID para el ftok.
 * \param [in] _size: TAmaño de la Shared Memory.
 * \param [in] _shmId: Puntero a la ID de la Shared Memory.
 * \return Devuelve el puntero a la Shared Memory o NULL si falla.
*/
void* createShMem(char* _path, int _proj_id, size_t _size, int* _shmId)
{
    int shmflags = 0660 | IPC_CREAT;
    
    key_t key = ftok(_path, _proj_id);
    if (key == -1){
        return NULL;
    }
    (*_shmId) = shmget(key, _size, shmflags);
    if ((*_shmId) == -1){
        return NULL;
    }
    void* addr;
    addr = shmat((*_shmId), NULL, 0);
    if (addr == (void*)-1) {
        return NULL;
    }
    return addr;
}

/**
 * \fn int createSem(int _id, int _create)
 * \brief Crea/abre un semáforo.
 * \details Crea/abre el semáforo con la Key correspondiente. 
 * \param [in] _path: Path al archivo generador de clave.
 * \param [in] _proj_id: ID para el ftok.
 * \return Devuelve -1 si error. 0 sino.
*/
int createSem(char* _path, int _proj_id)
{
    int semId = -1;
    int semflags = 0660 | IPC_CREAT;

    key_t key = ftok(_path, _proj_id);
    if( key == -1){
        printf("Estoy fallando aca\n");
        return -1;
    }
    semId = semget(key, 1, semflags);

    if (semId == -1){
        return -1;
    }

    union semun arg;
    // initialize semaphore to 1 (binari)
    arg.val = 1;
    if (semctl(semId, 0, SETVAL, arg) == -1)
    {
        semctl(semId, 0, IPC_RMID, arg);
        return -1;
    }

    return semId;
}

/**
 * \fn void closeSem(int _semId)
 * \brief Cierra un semáforo.
 * \details Cierra el semáforo con la ID correspondiente.
 * \param [in] _semId: ID del semáforo.
 * \return Void.
*/
void closeSem(int _semId)
{
    union semun arg;
    arg.val = 1;
    semctl(_semId, 0, IPC_RMID, arg);
}

/**
 * \fn int lockSem(int _semId)
 * \brief Bloquea un semáforo.
 * \details Bloquea el semáforo con la ID correspondiente.
 * \param [in] _semId: ID del semáforo.
 * \return Devuelve -1 si error. 0 sino.
*/
int lockSem(int _semId)
{
    struct sembuf sb = {0, -1, 0};
    //printf("Semaforo LOCK");
    if (semop(_semId, &sb, 1) == -1) {
        return -1;
    }
    return 0;
}

/**
 * \fn int unlockSem(int _semId)
 * \brief Desbloquea un semáforo.
 * \details DEsbloquea el semáforo con la ID correspondiente.
 * \param [in] _semId: ID del semáforo.
 * \return Devuelve -1 si error. 0 sino.
*/
int unlockSem(int _semId)
{
    struct sembuf sb = {0, 1, 0};
    //printf("Semaforo UNLOCK");
    if (semop(_semId, &sb, 1) == -1) {
        return -1;
    }
    return 0;
}

/**
 * \fn int AddKey(const KeyEntry_t _key, KeyEntry_t* _valid_keys, int _semId)
 * \brief Añade una Key a la lista de Keys.
 * \details Añade una Key a la lista de Keys.
 * \param [in] _key: Clave a guardar.
 * \param [in] _valid_keys: Lista de valid Keys.
 * \param [in] _semId: Id del semáforo para utilizar.
 * \return Devuelve -1 si error. 0 sino.
*/
int AddKey(const KeyEntry_t _key, KeyEntry_t* _valid_keys, int _semId)
{
    int ret = 0;
    if (lockSem(_semId) == -1){
        return -1;
    }
    for(int i=0; i < MAX_VALID_KEYS; i++)
    {
        if(_valid_keys[i].value[0] == '\0')
        {
            strcpy(_valid_keys[i].value, _key.value);
            ret = i+1;
            break;
        }
        if (strcmp(_key.value, _valid_keys[i].value) == 0){
            break;
        }
    }
    if (unlockSem(_semId) == -1){
        return -1;
    }
    return ret;
}

/**
 * \fn int DeleteKey(const KeyEntry_t _key, KeyEntry_t* _valid_keys, int _semId)
 * \brief Elimina una Key a la lista de Keys.
 * \details Elimina una Key a la lista de Keys.
 * \param [in] _key: Clave a borrar.
 * \param [in] _valid_keys: Lista de valid Keys.
 * \param [in] _semId: Id del semáforo a utilizar.
 * \return Devuelve -1 si error. 0 sino.
*/
int DeleteKey(const KeyEntry_t _key, KeyEntry_t* _valid_keys, int _semId)
{
    if( lockSem(_semId) == -1){
        return -1;
    }
    int pos = -1;
    for(int i=0; i < MAX_VALID_KEYS; i++)   //Busco la clave
    {
        if(_valid_keys[i].value[0] == '\0'){
            break;
        }
        if (strcmp(_key.value, _valid_keys[i].value) == 0)
        {
            pos = i;
            break;
        }
    }
    if (pos == -1) { //No existía la clave
        return unlockSem(_semId);
    }
        
    for(int i=pos; i < MAX_VALID_KEYS-1;i++)    //Muevo todo hacia atras
    {
        strcpy(_valid_keys[i].value, _valid_keys[i+1].value);
        if(_valid_keys[i+1].value[0] == '\0')
        {
            _valid_keys[i].value[0] = '\0';
            break;
        }
    }
    _valid_keys[MAX_VALID_KEYS-1].value[0] = '\0';

    if( unlockSem(_semId) == -1){
        return -1;
    }
    return (pos+1);
}

/**
 * \fn int HasKey(const KeyEntry_t _key, const KeyEntry_t* _valid_keys, int _semId)
 * \brief Detecta si una Key está en una lista o no.
 * \details Detecta si una Key está en una lista o no.
 * \param [in] _key: Clave a buscar.
 * \param [in] _valid_keys: Lista de valid Keys.
 * \param [in] _semId: Id del semáforo a utilizar.
 * \return 1 si posee la KEY. 0 si no.
*/
int HasKey(const KeyEntry_t _key, const KeyEntry_t* _valid_keys, int _semId)
{
    int val = 0;

    if( lockSem(_semId) == -1){
        return -1;
    }
    for(int i=0; i < MAX_VALID_KEYS; i++)
    {
        if(_valid_keys[i].value[0] == '\0'){
            break;
        }
        if (strcmp(_key.value, _valid_keys[i].value) == 0){
            val = 1;
            break;
        }
    }
    if( unlockSem(_semId) == -1){
        return -1;
    }
    return val;
}

/**
 * \fn int AddLog(const ActivityEntry_t _activity, ActivityEntry_t* _log, int _semId)
 * \brief Añade una actividad a un log de actividades.
 * \details Añade una actividad a un log de actividades.
 * \param [in] _activity: actividad a guardar.
 * \param [in] _log: log de actividades.
 * \param [in] _semId: Id del semáforo a utilizar.
 * \return Devuelve -1 si error. 0 sino.
*/
int AddLog(const ActivityEntry_t _activity, ActivityEntry_t* _log, int _semId)
{
    int ret = -1;
    if( lockSem(_semId) == -1){
        return -1;
    }
    for(int i=0; i < MAX_LOG; i++)
    {
        if(_log[i].code[0] == '\0')
        {
            strcpy(_log[i].code, _activity.code);
            strcpy(_log[i].date, _activity.date);
            _log[i].status = _activity.status;
            strcpy(_log[i].time, _activity.time);
            ret = i;
            break;
        }
    }

    if( unlockSem(_semId) == -1){
        return -1;
    }
    return (ret+1);
}

/**
 * \fn int CreateActivityEntry(ActivityEntry_t* _activity, KeyEntry_t _code, const int _status)
 * \brief Crea un ActivityEntry_t.
 * \details Crea un ActivityEntry_t con la fecha actual y los valores indicados.
 * \param [in] _activity: puntero a actividad a crear.
 * \param [in] _code: Codigo de la actividad creada.
 * \param [in] _status: Status de la actividad creada.
 * \return Devuelve -1 si error. 0 sino.
*/
int CreateActivityEntry(ActivityEntry_t* _activity, KeyEntry_t _code, const int _status)
{
    time_t t = time(NULL);
    struct tm tm_info;
    localtime_r(&t, &tm_info); 

    strcpy(_activity->code, _code.value);
    strftime(_activity->date, sizeof(_activity->date), "%Y%m%d", &tm_info);
    _activity->status = _status;
    strftime(_activity->time, sizeof(_activity->time), "%H%M%S", &tm_info);

    return 0;
}