
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define TODOOK 0
#define ERROR 1

int main (int cant, char* nombre_archivo[])
{

	int salida = ERROR;
	int fd;
	int i;
	int cant_l;

    if(cant <= 2)
    {
        printf("No ingresaste los argumentos válidos. \n<---------------------------------------> \nModo de uso:\t./borges <Nombre del archivo> <texto a escribir>\n<--------------------------------------->\n");
    }
    else
    {
        fd = open(nombre_archivo[1], O_WRONLY|O_APPEND|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
        if (fd >= 0)
        {
            printf ("Me asigno el file descriptor fd: %d\n", fd);
            printf ("------------------------------\n\n");
            salida = TODOOK;

            for(i=2;i<cant;i++)
            {
                cant_l = write(fd, nombre_archivo[i], sizeof(char)*strlen(nombre_archivo[i]));
    
                if (cant_l < 0)
                    printf("Error de lectura.\n");
            }
                close(fd);
        }
        else
        {
            perror("Error de apertura: ");
        }
    }
	return salida;
}

