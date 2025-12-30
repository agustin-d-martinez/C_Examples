/*******************************************************************************************************************************//**
 *
 * @file		periph.c
 * @brief		Manejo de la lectura de la alarma y log.
 * @date		08 oct. 2025
 * @author		Martinez Agustin
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "../inc/periph.h"

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn int periph( int driver )
 * \brief Función de manejo del periférico
 * \details Abre la memoria compartida, lee el teclado y analiza la respuesta. 
 * \param [in] driver: File descriptor del driver a utilizar. 
 * Las respuestas activan los leds y se guardan en el log.
*/
int periph( int driver, KeyEntry_t* valid_keys, ActivityEntry_t*log, int sem_list[3])
{
    KeyEntry_t driver_buff;
    ActivityEntry_t activity;
    driver_msg_t msg;

    int sem_k = sem_list[0];
    int sem_l = sem_list[1];
    int sem_write = sem_list[2];

    while(1){
        //Pido clave a driver teclado.
        if(readDriver(driver, &driver_buff) < 0){
            perror("Error al leer de /dev/my_alarm");
            sleep(1);
            continue;
        }

        //Verifico que sea correcta.
        if(HasKey(driver_buff, valid_keys, sem_k)){
            CreateActivityEntry(&activity, driver_buff, 1);
            //Si es correcta -> prendo led, prendo buzzer f2, guardo en log.
            msg.command = GREEN_LED;
            msg.dec_ms = 100;       //1s
            if (writeDriver(driver, msg, sem_write) < 0){
                perror("Error al escribir Led Verde");
            }
            msg.command = BUZZER;
            msg.dec_ms = 10;        //100ms
            if (writeDriver(driver, msg, sem_write) < 0){
                perror("Error al escribir Buzzer");
            }
        }
        else{
            CreateActivityEntry(&activity, driver_buff, 0);
            //Si es incorrecta -> prendo led, prendo buzzer f1, guardo en log.
            msg.command = RED_LED;
            msg.dec_ms = 200;       //2s
            if (writeDriver(driver, msg, sem_write) < 0){
                perror("Error al escribir Led Rojo");
            }
            msg.command = BUZZER;
            msg.dec_ms = 200;
            if (writeDriver(driver, msg, sem_write) < 0){
                perror("Error al escribir Buzzer");
            }
        }
        int aux = AddLog(activity, log, sem_l);
        if (aux < 0){
            perror("Error al guardar el log");
        }
    }
    
    shmdt(valid_keys);
    shmdt(log);

    return 0;

}
