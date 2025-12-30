/*******************************************************************************************************************************//**
 *
 * @file		driverHandler.c
 * @brief		Funciones de manejo del driver my_alarm.
 * @date		08 oct. 2025
 * @author		Martinez Agustin
 *
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "../inc/driverHandler.h"

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn int writeDriver(const driver_msg_t _msg, const int time)
 * \brief Escritua en el driver.
 * \details Escribe el driver de forma segura con las variables pasadas.
 * \param [in] driver_fd: File Descriptor del Driver a escribir.
 * \param [in] _msg: Mensaje a enviar
 * \param [in] _sem: Semaforo para escritura
 * \return Devuelve -1 si error. 0 sino.
*/
int writeDriver(int driver_fd, const driver_msg_t _msg, int _sem)
{
    unsigned char buff[2];
    buff[0] = _msg.command;
    buff[1] = _msg.dec_ms;

    // Escribir dos caracteres
    if (lockSem(_sem) == -1)
        return -1;
    int n = write(driver_fd, buff,sizeof(buff));
    if (n != sizeof(buff)){
        unlockSem(_sem);
        return -1;
    }
    return unlockSem(_sem);
}
/**
 * \fn int readDriver( KeyEntry_t* _driver_buff )
 * \brief Lectura del driver.
 * \details Lee el driver de forma segura con las variables pasadas.
 * \param [in] _driver_buff: Buffer donde se guarda la lectura.
 * \return Devuelve -1 si error. 0 sino.
*/
int readDriver( int driver_fd, KeyEntry_t* _driver_buff )
{
    size_t n = read(driver_fd, _driver_buff->value, sizeof(_driver_buff->value));
    if (n < 0) {
        return -1;
    }
    return 0;
}