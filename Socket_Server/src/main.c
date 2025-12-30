/*******************************************************************************************************************************//**
 *
 * @file		main.h
 * @brief		Funciones principal del TP0.
 * @date		08 oct. 2025
 * @author		Martinez Agustin
 *
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "../inc/main.h"

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
volatile int cant_clients = 0;
volatile int running = 1;

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn int main(int argc, char *argv[])
 * \brief main del Servidor.
 * \details Crea el servidor. Crea la Memoria Compartida. 
 * Realiza el fork para lectura del driver. Se queda esperando clientes nuevos.
 * \param [in] argc: Cantidad de argumentos.
 * \param [in] argv: Puntero a char con los argumentos.
 * \return Devuelve -1 si error. 0 sino.
*/
int main(int argc, char *argv[])
{
    int smId_k = -1;
    int smId_l = -1;

    int semId_k = -1;
    int semId_l = -1;
    int sem_write = -1;
    
    int server_Id = -1;
    int pid_procces_teclado = -1;

    int driver = -1;

    int backlog, max_connections;
    KeyEntry_t* valid_keys = NULL;
    ActivityEntry_t* log = NULL;

    printf("%s\n\n\n",argv[0]);
    if (argc != 2){
        printf("Error en ejecución de programa.\nTP2 <puerto>\n\n");
        exit(1);
    }

    // Lectura de config file:
    backlog = GetInitValue("config.ini", "BACKLOG");
    if (backlog <= 0){
        printf("Valor de BACKLOG por defecto");
        backlog = DEFAULT_BACKLOG;
    }
    max_connections = GetInitValue("config.ini", "MAX_CONNECTIONS");
    if ( max_connections <= 0){
        printf("Valor de MAX_CONNECTIONS por defecto");
        max_connections = DEFAULT_MAXCONNECTIONS;
    }

    // Creacion de la memoria compartida:
    valid_keys = (KeyEntry_t*)createShMem(argv[0],SM_ID_K,(sizeof(KeyEntry_t)*MAX_VALID_KEYS),&smId_k);
    if (valid_keys == (KeyEntry_t *)-1) {
        perror("Error al pedir memoria compartida KEY");
        exit(1);
    }
    semId_k = createSem(argv[0],SEM_ID_K);
    if (semId_k == -1){
        perror("Error al crear el semáforo KEY\n");
        shmdt(valid_keys);
        shmctl(smId_k, IPC_RMID, 0);
        exit(1);
    }

    log = (ActivityEntry_t*)createShMem(argv[0],SM_ID_L,(sizeof(ActivityEntry_t)*MAX_LOG),&smId_l);
    if (log == (ActivityEntry_t *)-1) {
        perror("Error al pedir memoria compartida LOG");
        shmdt(valid_keys);
        shmctl(smId_k, IPC_RMID, 0);
        closeSem(semId_k);
        exit(1);
    }
    semId_l = createSem(argv[0],SEM_ID_L);
    if (semId_l == -1){
        perror("Error al crear el semáforo LOG\n");
        shmdt(valid_keys);
        shmctl(smId_k, IPC_RMID, 0);
        shmdt(log);
        shmctl(smId_l, IPC_RMID, 0);
        closeSem(semId_k);
        exit(1);
    }
    sem_write = createSem(argv[0],SEM_ID_WR);
    if (sem_write == -1){
        perror("Error al crear el semáforo DRIVER\n");
        shmdt(valid_keys);
        shmdt(log);
        shmctl(smId_l, IPC_RMID, 0);
        shmctl(smId_k, IPC_RMID, 0);
        closeSem(semId_l);
        closeSem(semId_k);
        exit(1);
    }


    int sem_list[3] = {semId_k, semId_l, sem_write};
    // Inicializo con 0:
    for(int i=0; i < MAX_VALID_KEYS; i++ ){
        valid_keys[i].value[0] = '\0';
    }
    for(int i=0; i < MAX_LOG; i++){
        log[i].code[0] = '\0';
    }
    driver = open("/dev/my_alarm", O_RDWR);
    if (driver < 0){
        closeSem(semId_k);
        closeSem(semId_l);
        closeSem(sem_write);
        shmctl(smId_k, IPC_RMID, 0);
        shmctl(smId_l, IPC_RMID, 0);
        exit(1);
    }
    // Fork para telcado y server:
    pid_procces_teclado = fork();
    if (pid_procces_teclado < 0){
        perror("Error de fork");
        shmctl(smId_k, IPC_RMID, NULL);
        shmctl(smId_l, IPC_RMID, NULL);
        closeSem(semId_k);
        closeSem(semId_l);
        closeSem(sem_write);
        exit(1);
    } 
    if (pid_procces_teclado == 0) {  // Hijo va a teclado
        periph(driver, valid_keys, log, sem_list);
        return 0;
    }

    // Creación del server:
    server_Id = MakeServer(atoi(argv[1]), backlog);
    if (server_Id < 0){
        perror("Error creando el server");
        kill(pid_procces_teclado, SIGTERM);
        shmctl(smId_k, IPC_RMID, NULL);
        shmctl(smId_l, IPC_RMID, NULL);
        closeSem(semId_k);
        closeSem(semId_l);
        closeSem(sem_write);
        exit(1);
    }

    // Signals:
    setHandlers();
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);

    // Espero clientes:
    while (running) {
        struct sockaddr_in client_data;
        unsigned int client_data_size = sizeof(client_data);
        int pid;

        sigprocmask(SIG_BLOCK, &mask, &oldmask);    //Bloqueo el sigchild
        while (cant_clients >= max_connections){
            sigsuspend(&oldmask);   //Similar a pause(). Funcion bloqueante hasta que llegue SIGCHLD.
            printf("Termino un cliente. Leyendo el siguiente\n");
        }
        sigprocmask(SIG_SETMASK, &oldmask, NULL);   //Desbloqueo el sigchild (trabajo normal)
        if(!running){
            break;
        }

        int client_Id = accept(server_Id, (struct sockaddr *)&client_data, &client_data_size);
        if (client_Id < 0){
            if (errno == EINTR){
                break;
            }
            perror("Error en aceppt");
            close(server_Id);
            kill(pid_procces_teclado, SIGTERM);
            shmctl(smId_k, IPC_RMID, NULL);
            shmctl(smId_l, IPC_RMID, NULL);
            closeSem(semId_k);
            closeSem(semId_l);
            closeSem(sem_write);
            exit(1);
        }

        pid = fork();
        if (pid < 0){
            perror("Error fork");
            close(client_Id);
            close(server_Id);
            kill(pid_procces_teclado, SIGTERM);
            shmctl(smId_k, IPC_RMID, NULL);
            shmctl(smId_l, IPC_RMID, NULL);
            closeSem(semId_k);
            closeSem(semId_l);
            closeSem(sem_write);
            exit(1);
        }
        if (pid == 0){      // Cliente
            signal(SIGINT, SIG_DFL);

            if (client(client_Id, driver, valid_keys, log, sem_list) < 0){
                perror("Error al trabajar al cliente. ##");
            }
            close(client_Id);
            close(server_Id);
            close(driver);
            exit(0);
        }
        cant_clients++;
        close(client_Id);
    }

    // Si cliente -> creo hijo, cierro conexión y repito
    kill(pid_procces_teclado, SIGTERM);
    printf("Esperando que terminen %d clientes\n", cant_clients);

    sigprocmask(SIG_BLOCK, &mask, &oldmask);    //Bloqueo el sigchild
    while (cant_clients > 0){
            sigsuspend(&oldmask);   //Desbloqueo por 1 vez.
            //printf("Termino un cliente. Leyendo el siguiente\n");
        }
    sigprocmask(SIG_SETMASK, &oldmask, NULL);   //Desbloqueo el sigchild (trabajo normal)

    /*while (cant_clients > 0){
        pause();
    }*/
    printf("Todos los clientes terminaron. Me voy\n");
    
    close(driver);
    close(server_Id);
    shmctl(smId_k, IPC_RMID, NULL);
    shmctl(smId_l, IPC_RMID, NULL);
    closeSem(semId_k);
    closeSem(semId_l);
    closeSem(sem_write);
    return 0;
}

/**
 * \fn int MakeServer(int _port, int _backlog )
 * \brief Crea el servidor.
 * \details Crea el servidor.
 * \param [in] _port: Puerto del servidor a crear.
 * \param [in] _backlog: Cantidad de clientes que permite en espera.
 * \return Devuelve -1 si error. 0 sino.
*/
int MakeServer(int _port, int _backlog ) 
{
    int server_Id;
    struct sockaddr_in server_data;

    server_Id = socket(AF_INET, SOCK_STREAM, 0); // Creo el socket para comunicación IPv4
    if (server_Id == -1)
        return -1;
    int opt=1;
    setsockopt(server_Id, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    server_data.sin_family = AF_INET;
    server_data.sin_port = htons(_port);
    server_data.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_Id, (struct sockaddr *)&server_data, sizeof(server_data)) == -1) // Enlazo el server a un puerto
        return -1;

    if (listen(server_Id, _backlog) < 0){ // MAX cant de pedidos en espera
        close(server_Id);
        return -1;
    }
    printf("Servidor creado con éxito en 127.0.0.1:%d\n\n",_port);
    return server_Id;
}

/**
 * \fn int GetInitValue(const char* _file_name, const char* _key, char* _value, const size_t _size )
 * \brief Obtiene valores iniciales NUMÉRICOS de un archivo.
 * \details Obtiene valores iniciales NUMÉRICOS de un archivo.
 * \param [in] _file_name: Nombre del archivo .ini.
 * \param [in] _key: Nombre de la variable a buscar.
 * \return Devuelve -1 si error. el valor a leer sino.
*/
int GetInitValue(const char* _file_name, const char* _key)
{
    char line[256];
    char key[256];
    char value[256];
    int ret = -1;
    FILE* config_file = fopen(_file_name, "rb");
    if(!config_file){
        return -2;
    }

    // Leo linea y comparo con key. Devuelvo el valor tal y como está escrito.
    while(fgets(line, sizeof(line), config_file)){
        if (sscanf(line, "%[^=]=%s", key, value) == 2) {
            if(strcmp(key, _key) == 0){
                ret = 1;
                break;
            }
        }
    }
    fclose(config_file);
    
    value[255] = '\0';
    
    if (ret == 1){
        ret = atoi(value);
    }
    return ret;
}

/**
 * \fn void setHandlers( void )
 * \brief Setea los Handlers de señales.
 * \details Configura SIGCHLD con ChildHandler y SIGINT con KillHandler. 
 * Este último no continua con acciones bloqueantes, lo que permite salir.
 * \return void.
*/
void setHandlers( void )
{
    struct sigaction sa;

    sa.sa_handler = ChildHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;  
    sigaction(SIGCHLD, &sa, NULL);
    
    sa.sa_handler = KillHandler;    //NOTA: Se utilizo SIGACTION para que SIGINT pueda salir del accept (que es bloqueante)
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;           
    sigaction(SIGINT, &sa, NULL);

}

/**
 * \fn void ChildHandler(int _signal )
 * \brief Handler de procesos hijos.
 * \details Handler de procesos hijos.
 * \param [in] _signal: Señal enviada.
*/
void ChildHandler(int signal)
{
    while(waitpid(-1, NULL, WNOHANG) > 0){
        cant_clients--;
    }
}

/**
 * \fn void KillHandler(int _signal )
 * \brief Handler de finalización de programa.
 * \details Handler de finalización de programa.
 * \param [in] _signal: Señal enviada.
*/
void KillHandler(int signal)
{
    running = 0;
}