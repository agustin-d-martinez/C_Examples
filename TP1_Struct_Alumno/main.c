

#include <stdio.h>
#include "funcionesff.h"



int main (void)
{

	ALUMNO ** listado;
	int cantidad;

	cantidad = carga(&listado);

	if (cantidad >= 0)
	{
//		mostrar(listado, cantidad);

		menu(listado, cantidad);

        limpiar(listado, cantidad);
	}
	else
	{
		printf("Pasas que cosan en la carga.\n");
	}

	return 0;
}
