#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define LARGO 100
#define PUERTO 3490

#define SIN_ERROR 0
#define ERROR -10

int inicio_socket(int *socket_fd, int puerto,struct hostent *addr);
void comunicacion(int socket_fd);

int main (int argc, char ** argv)
{

	int socket_fd, error = SIN_ERROR;
	int puerto = PUERTO;
	struct hostent *addr;

	if ((argc < 2) || (argc > 3))
	{
		printf("Uso del programa: \n%s direccion [puerto]\n", argv[0]);
		error =  ERROR;
	}

	if(error == SIN_ERROR)
    {
        addr = gethostbyname(argv[1]);     //Guardo la direccion IP en addr
        if (addr == NULL)
        {
            perror("Error Direccion IP");
            error = ERROR;
        }
    }
    
	if (argc == 3)
		puerto = atoi(argv[2]);
    
    if(error != ERROR)
        error = inicio_socket(&socket_fd, puerto, addr);        //Creo y conecto el socket
        
    if(error == SIN_ERROR)
    {
        printf("Conexión con el servidor establecida\n");
        comunicacion(socket_fd);         //Me comunico
    }
	close(socket_fd);
    
	return 0;
}

int inicio_socket(int *socket_fd, int puerto, struct hostent *addr)
{
    int error = SIN_ERROR;
    struct sockaddr_in destino;

    (*socket_fd) = socket(AF_INET, SOCK_STREAM, 0);     //Creo el socket

	if ((*socket_fd) == -1)
	{
		perror("Error Socket");
		error = ERROR;
	}
    else
    {
        destino.sin_family = AF_INET;               //Configuro el destino
        destino.sin_port = htons(puerto);
        destino.sin_addr = *((struct in_addr*) addr->h_addr);
        memset(&(destino.sin_zero), 0, 8);

        error = connect((*socket_fd),(struct sockaddr *) &destino, sizeof(struct sockaddr_in));        //Me conecto
    }
    
	if (error == -1)
	{
		perror("Error Connect");
        error = ERROR;
	}
	
    return error;
}

void comunicacion(int socket_fd)
{
    char mensaje[LARGO] = {"Hola"};
    int error = SIN_ERROR;
    int finalizada = 0;
    error = send(socket_fd, mensaje, LARGO, 0);     //Evio el mensaje

	if (error == -1)
    {
		perror("Error Send");
        finalizada = 1;
    }
    
    if(finalizada == 0)
    {
        error = recv(socket_fd, mensaje, LARGO, 0);     //Recibo un mensaje

        if (error == -1)
            perror("Error Recv");
        else if (error == 0)
            printf("No se recibió nada.\n");
        else if(error != ERROR)
            printf("Recibí: %s\n", mensaje);
    }
    return;
}
