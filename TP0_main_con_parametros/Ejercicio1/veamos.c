
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define TODOOK 0
#define ERROR 1

int main (int cant, char* nombre_archivo[])
{
	int salida = ERROR;
	int fd;
    int i;
	char buffer;
	int cant_l;
    
    if(cant <= 1)
    {
        printf("No ingresaste los argumentos válidos. \n<---------------------------------------> \nModo de uso:\t./veamos <Nombre del archivo>\n<--------------------------------------->\n");
    }
    else
    {
        for(i=1;i<cant;i++)
        {
            fd = open(nombre_archivo[i], O_RDONLY);
            if (fd >= 0)
            {
                printf ("Me asigno el file descriptoir fd: %d\n", fd);
                printf ("------------------------------\n\n");
                salida = TODOOK;
                do
                {
                    cant_l = read(fd, &buffer, sizeof(buffer));
                    printf("%c", buffer);
                }
                while(cant_l > 0);
    
                if (cant_l < 0)
                {
                    printf("Error de lectura.\n");
                    salida = ERROR;
                }
                close(fd);
            }
            else
            {
                perror("Error de lectura: ");
                salida = ERROR;
            }
        }
    }
	return salida;
}

