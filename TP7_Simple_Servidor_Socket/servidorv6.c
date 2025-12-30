//AGREGO WHILE 1
//AGREGO SETSOCKOPT
//AGREGO FORK
//AGREGO WAIT
//AGREGO CONTADOR DE HIJOS y fin de programa.

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/*
Abrir el socket: socket  int socket(int domain, int type, int protocol);
Enlazar el socket con el puerto: bind int bind(int sockfd, const struct sockaddr *addr,  socklen_t addrlen);
Poner el servicio en modo escucha: listen int listen(int sockfd, int backlog);
Pregunto y atiendo si aparece una conexión: accept  int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
*/

#define PUERTO      3490
#define BACKLOG     10
#define LARGO       100

#define MAX_CHLD    3

#define SIN_ERROR   0
#define ERROR       1

#define TRUE        1
#define FALSE       0

#define HIJO        0

int cant_hijos = 0;
int mantener_on = TRUE;

int crear_server(int *socket_fd);

void hijo (int n_socket_fd, struct sockaddr_in dir_cliente);
void atiendo_chld (int signal);
void atiendo_usr1 (int signal);

int main (void)
{
    int pid;
    int error;
    int socket_fd, n_socket_fd;
    struct sockaddr_in dir_cliente;
    socklen_t tamanio = sizeof(struct sockaddr);    

    error = crear_server(&socket_fd);       //Creo e inicializo el server

    signal (SIGCHLD, atiendo_chld);     //Genero las señales
    signal (SIGUSR1, atiendo_usr1);

    while((mantener_on == TRUE) && (error == SIN_ERROR) && (pid != HIJO))
    {

        while ((cant_hijos == MAX_CHLD) && (mantener_on == TRUE))       //Duerme cuando faltan hijos por terminar
            sleep(1);

        if (mantener_on == FALSE) 
            n_socket_fd = -1;
        else
            n_socket_fd = accept(socket_fd, (struct sockaddr *) &dir_cliente, &tamanio);

        if(n_socket_fd != -1)
        {
            pid = fork();
            if (pid < 0)
            {
                printf("Error creando hijo.\n");
                close(n_socket_fd);
            }
            else if (pid == HIJO)       //Progama hijo
            {
                close(socket_fd);
                hijo(n_socket_fd, dir_cliente);
            }
            else
            {
                cant_hijos++;
                close(n_socket_fd);     //Programa padre
            }
        }
        else if(mantener_on == FALSE)
        {
            perror("Error de accept");
            error = ERROR;
        }
    }
    
    if(pid != HIJO)
        printf("Servidor apagado.\n");
    close(socket_fd);
    
    return 0;
}

void hijo (int n_socket_fd, struct sockaddr_in dir_cliente)
{
    int error;
    char mensaje[LARGO];

    printf("El cliente %s se conectó por el puerto %d.\n", inet_ntoa(dir_cliente.sin_addr), dir_cliente.sin_port);

    error = recv (n_socket_fd, mensaje, LARGO, 0);
    if (error == -1)
    {
        perror("Error de recv");
        close(n_socket_fd);
        exit (1);
    }

    if(strcmp(mensaje, "Hola") != 0)
    {
        printf("Cliente no autorizado.\n");
        close(n_socket_fd);
        exit(1);
    }

    printf("ACCESS GRANTED.\n");

    printf("Que le querés decir al cliente:\n");
    fgets(mensaje, LARGO-1, stdin);
    error = send (n_socket_fd, mensaje, LARGO, 0);
    if (error == -1)
    {
        perror("Error de send");
        close(n_socket_fd);
        exit (1);

    }

    close(n_socket_fd);
    return;
}

void atiendo_chld (int signal)
{
	int fin = 1;
	while(fin > 0)
	{
		fin = waitpid(-1, NULL, WNOHANG);
		if (fin > 0) cant_hijos--;
	}
}

void atiendo_usr1 (int signal)
{
    printf("Me mandaron a matar\n");
	mantener_on = FALSE;
}

int crear_server(int *socket_fd)
{
    int error = SIN_ERROR;
    struct sockaddr_in dir_server;
    int optval;

    (*socket_fd) = socket(AF_INET, SOCK_STREAM, 0);     //Creo el socket
    if ((*socket_fd) == -1)
    {
        perror("Error de socket");
        error = ERROR;
    }
    
    if(error != ERROR)      //Verifica que se pueda crear el server
    {
        error = setsockopt((*socket_fd), SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));     
        if (error == -1)
        {
            perror("Error de setsockopt");
            error = ERROR;
        }
    }
    
    if(error != ERROR)      //Enlazo el server a una IP
    {
        dir_server.sin_family = AF_INET;
        dir_server.sin_port = htons(PUERTO);
        dir_server.sin_addr.s_addr = htonl(INADDR_ANY);
        memset(&(dir_server.sin_zero), 0, 8);

        error = bind ((*socket_fd), (struct sockaddr *) &dir_server, sizeof(struct sockaddr));
        if (error == -1)
        {
            perror("Error de bind");
            error = ERROR;
        }
    }
    
    if(error != ERROR)      //Me pongo a escuchar
    {
        error = listen ((*socket_fd), BACKLOG);
        if (error == -1)
        {
            perror("Error de listen");
            error = ERROR;
        }
        else
            printf("Servidor activado. Esperando conexiones.\n\n");

    }
    
    return error;
}
