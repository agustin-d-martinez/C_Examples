
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesff.h"
#include <unistd.h>

#define CUANTO 20
#define CUANCAR 6
#define CAMBIO 1
#define NOCAMBIO 0


int carga (ALUMNO *** listado)
{

	char * nombres[CUANTO] = {"Luna", "Nala", "Kira", "Lola", "Bimba", "Coco", "Thor", "Max", "Rocky", "Toby", "Mia", "Noa", "Kiara", "Dana", "Gala", "Simba", "Leo", "Lucas", "Zeus", "Bruno"};
	char * apellidos[CUANTO] = {"Azqueta", "Dellanoce", "Oreamuno", "Pretiz", "Riotte", "Soldevilla", "Trilite", "Villegas", "Xirinachs", "Irastorza", "Klein", "Freyre",  "Maisonave", "Teixido", "Zambrano", "Betancurt", "Gulubay", "Luarca", "Osorno", "Viscaino"};
	char * carreras[CUANCAR] = {"Electronica", "Sistemas", "Industrial", "Quimica    ", "Mecanica", "Naval      "};


	int contador;
	int i;
    char s_auxiliar[100];
    char * aux_s;


    printf("Ingrese la cantidad de alumnos a ingresar: ");
    scanf("%d", &contador);


    (*listado) = (ALUMNO **) malloc (sizeof(ALUMNO *)*contador);

    if (*listado != NULL)
    {
        for ( i = 0; i < contador; i++)
        {
        	*((*listado)+i) = (ALUMNO *) malloc(sizeof(ALUMNO));
	        (*((*listado)+i))->legajo = (rand()%90000)+10000;
//	        ((*listado)[i])->legajo = (rand()%90000)+10000;
//	        (*((*listado)[i])).legajo = (rand()%90000)+10000;
//	        (*(*(*listado)+i)).legajo = (rand()%90000)+10000;
            (*((*listado)+i))->promedio = ((rand()%70)/10.0)+3;

            sprintf(s_auxiliar, "%s, %s", apellidos[rand()%CUANTO], nombres[rand()%CUANTO]);

            aux_s = (char *) malloc(strlen(s_auxiliar)+1);
            if (aux_s != NULL)
            {
	            (*((*listado)+i))->nombre = aux_s;
                strcpy((*((*listado)+i))->nombre, s_auxiliar);
            }
            else
            {
            	limpiar(*listado, i);
    	        return ERROR;
            }

        	strcpy (s_auxiliar, carreras[rand()%CUANCAR]);

            aux_s = (char *) malloc(strlen(s_auxiliar)+1);
            if (aux_s != NULL)
            {
            	(*((*listado)+i))->carrera = aux_s;
            	strcpy((*((*listado)+i))->carrera, s_auxiliar);
            }
            else
            {
            	limpiar(*listado, i);
            	return ERROR;
            }


        }
        return contador;
    }
    return ERROR;
}


void mostrar (ALUMNO ** listado, int cantidad)
{
        int i;

		printf("Se anotaron: %d alumnos.\n", cantidad);

		for (i = 0; i < cantidad; i++)
		{
           printf("Alumno: %d\n", i+1);
           printf("\tLegajo: %d", (*(listado+i))->legajo);
           printf("\tPromedio: %.2f", (*(listado+i))->promedio);
           printf("\tCarrera: %s", (*(listado+i))->carrera);
           printf("\tNombre: %s\n", (*(listado+i))->nombre);
		}
		printf("-----------------------------------------------------\n\n");


}

void limpiar (ALUMNO ** listado, int cantidad)
{

	int i;

	for ( i = 0; i < cantidad; i++)
	{
		free((*(listado+i))->carrera);
// (*(listado+i))->carrera;
		free((*(listado+i))->nombre);
		free((*(listado+i)));
	}

    free(listado);

    printf("Vine a limpiar y lo hizo.\n");
    return;

}


void menu(ALUMNO ** listado, int cantidad)
{

	char opcion;
	int i, can_act = cantidad;

	ALUMNO ** ord_prom = NULL, ** ord_nom = NULL, ** fil_carrera = NULL, ** activo = NULL;

	ord_prom = (ALUMNO **) malloc (cantidad*sizeof(ALUMNO *));
	ord_nom = (ALUMNO **) malloc (cantidad*sizeof(ALUMNO *));

	if ((ord_prom != NULL) && (ord_nom != NULL))
	{
		for (i = 0; i < cantidad; i++)
		{
			*(ord_prom+i) = *(listado+i);
			*(ord_nom+i) = *(listado+i);
		}

		mostrar(ord_nom, can_act);


		while (tolower(opcion) != 's')
		{
			printf("Que desea hacer (además de ir a ve Netflix?\n");

			printf("\t P - Ordenar por promedio.\n");
			printf("\t N - Ordenar por nombre.\n");
			printf("\t C - Filtrar por carrera.\n");
            printf("\t F - Funcion agus.\n");
			printf("\t M - Muestra la última consulta realizada.\n");
			printf("\t S - Salir.\n");
			scanf(" %c", &opcion);

			switch (opcion)
			{
				case 'P':
				case 'p':
					activo = ord_prom;
					can_act = cantidad;
					fpromedio(activo, can_act);
					break;
				case 'N':
				case 'n':
					activo = ord_nom;
					can_act = cantidad;
					fnombre(activo, can_act);
					break;
				case 'C':
				case 'c':
					can_act = fcarrera(&fil_carrera, listado, cantidad);
					activo = fil_carrera;
					break;
				case 'M':
				case 'm':
					mostrar(activo, can_act);
					break;
                case 'F':
				case 'f':
					funcion_6 (listado, &cantidad);
                    printf("Está filtrado\n\n");
                    mostrar(listado, cantidad);
					break;
				case 'S':
				case 's':
					free(ord_prom);
					free(ord_nom);
					free(fil_carrera);
					break;
				default:
					printf("Mandaste fruta con la opción.\n");
			}
		}
	}

	return;
}

void fpromedio (ALUMNO ** listado, int cantidad)
{

	int i, j = 0, bandera = CAMBIO;
	ALUMNO * aux;

	while (bandera == CAMBIO)
	{
		bandera = NOCAMBIO;
		j++;
		for(i = 0; i < (cantidad-j); i++)
		{
//			if(listado[i]->promedio > listado[i+1]->promedio)
			if((*(listado+i))->promedio < (*(listado+i+1))->promedio)
			{
				aux = listado[i];
				listado[i] = listado[i+1];
				listado[i+1] = aux;
				bandera = CAMBIO;
			}

		}
	}

	return;
}

void fnombre (ALUMNO ** listado, int cantidad)
{
	int i, j = 0, bandera = CAMBIO;
	ALUMNO * aux;

	while (bandera == CAMBIO)
	{
		bandera = NOCAMBIO;
		j++;
		for(i = 0; i < (cantidad-j); i++)
		{
//			if(listado[i]->promedio > listado[i+1]->promedio)
			if(strcmp((*(listado+i))->nombre,(*(listado+i+1))->nombre) > 0)
			{
				aux = listado[i];
				listado[i] = listado[i+1];
				listado[i+1] = aux;
				bandera = CAMBIO;
				sleep(1);
			}

		}
	}

	return;
}

int fcarrera (ALUMNO *** filtro, ALUMNO ** listado, int cantidad)
{
	char filtroCar[13];
	int i, can_filtrado = 0;
	ALUMNO ** nuevo;
	char basura;

	scanf("%c", &basura);

	printf("¿Que carrera va a filtrar?: ");
	fgets(filtroCar,12,stdin);
	filtroCar[strlen(filtroCar)-1]='\0';

	for (i = 0; i < cantidad; i++)
	{
		if(strcmp((*(listado+i))->carrera,filtroCar) == 0)
		{
			if (can_filtrado == 0)
			{
				nuevo = (ALUMNO **) malloc(sizeof(ALUMNO *));
			}
			else
			{
				nuevo = (ALUMNO **) realloc(*filtro,sizeof(ALUMNO *)*(can_filtrado+1));
			}

			if (nuevo != NULL)
			{
				*filtro = nuevo;
				*((*filtro)+can_filtrado) = *(listado+i);
				can_filtrado++;
			}
			else
			{
				free(*filtro);
				*filtro = NULL;
				can_filtrado = -1;
			}
		}
	}
	return can_filtrado;
}

void funcion_6 (ALUMNO ** listado, int *cantidad)
{
    int i;
    int ya_borro = 0;
    int filtro;
    printf("Legajo a eliminar: ");
    scanf("%d",&filtro);
    
    for(i=0; i<(*cantidad);i++)
    {
        if(((*(listado+i))->legajo) == filtro)      //Activo la bandera cuando encuentro la que quiero borrar
        {
            ya_borro = 1;
            printf("Lo encontrè en la posicion %d\n",i+1);
        }
        if((ya_borro == 1) && (i<((*cantidad)-1)))
        {
            listado[i] = listado[i+1];     //Muevo todo una posición hacia atras
        }
    }
    
    if(ya_borro == 1)                       //Cuando termino libero la úlitma posición
    {
        free((*(listado+(i)))->carrera);    //I tiene el valor de la última posición
        free((*(listado+(i)))->nombre);
        free((*(listado+(i))));
        (*cantidad)= (*cantidad) -1;
    }
    return;
}

/*
Para clase que viene:
*Función de filtro por carrera.
*Función de ordenamiento por puntero a función.
*Vector de punteros para la información origen.
*Agregar los indices a la función de limpieza.
*/

