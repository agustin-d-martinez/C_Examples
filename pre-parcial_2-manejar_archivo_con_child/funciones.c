/**
	\file    <funciones_menu.c>
	\brief   <Funciones del ejercicio>
	\author  <MARTINEZ, Agustin (agmartinez@frba.utn.edu.ar)>
	\date    <2021.10.21> 
	\version <1.0.0>
*/

#include "funciones.h"

void liberar (PALABRAS ** listado)
{
    if((*listado) != NULL)
        free((*listado));
    return;
}

int enunciado(char * dir_escritura, char * dir_lectura, int argc, char **argv)
{
    int error = SIN_ERROR;
    int i;
    int aux1 = 0, aux2 = 0;
    if(argc != 5)
        error = ERROR;
    
    if(error == SIN_ERROR)
    {
        for(i=0; i < argc;i++)
        {
            if((strcmp(argv[i], "-i") == 0) && (i != (argc-1)))
            {
                strcpy(dir_lectura, argv[i+1]);
                aux1++;
                i++;
            }
            else if((strcmp(argv[i], "-o") == 0) && (i != (argc-1)))
            {
                strcpy(dir_escritura, argv[i+1]);
                aux2++;
                i++;
            }
        }
    }
    if((aux1 != 1) || (aux2 != 1))
        error = ERROR;
    
    return error;
}

int EscribirPAlabrasEnArchivo(PALABRAS* listado, int cant, const char *dir_archivo)
{
    int error = SIN_ERROR;
    FILE * archivo;
    
    archivo = fopen(dir_archivo, "w+");
    if(archivo != NULL)
    {
        ordenar(listado, cant);
        escribir(listado, cant, archivo);
    }
    else
        error = ERROR;
    
    fclose(archivo);
    return error;
}

void escribir(PALABRAS* listado, int cant, FILE* archivo)
{
    int i;
    for(i=0; i < cant; i++)
    {
        fwrite(&(listado[i]), sizeof(PALABRAS),1,archivo);
    }
    return;
}
void ordenar(PALABRAS* listado, int cant)
{
    int bandera = VERDADERO;
	int i, j=0;
	PALABRAS aux;

	while (bandera == VERDADERO)
	{
		bandera = FALSO;
		for (i = 0; i < cant-1-j; i++)
		{
			if (strcmp(listado[i].nombre, listado[i+1].nombre) > 0 )
			{
				aux = listado[i];
				listado[i] = listado[i+1];
				listado[i+1] = aux;
				bandera = VERDADERO;
			}
		}
		j++;
	}

    return;
}

int CargarPalabras(const char* dir_archivo, PALABRAS ** listado)
{
    int error = SIN_ERROR;
    FILE * archivo;
    int cant = 0;
    char auxiliar[20];
    int letras_leidas;
    
    archivo = fopen(dir_archivo,"r");
    if(archivo == NULL)
        error =  ERROR;
    
    while((!feof(archivo)) && (error == SIN_ERROR))
    {
        strcpy(auxiliar, "");
        letras_leidas = leer_palabra(auxiliar, archivo);
        if(letras_leidas != 0)
        {
            minuscula(auxiliar);
            guardar(auxiliar, listado, &cant);
        }
    }
    if(error == SIN_ERROR)
        error = cant;
    fclose(archivo);
    return error;
}

void guardar(char * palabra, PALABRAS ** listado, int * cant)
{
    int i = 0;
    int finalizo = FALSO;
    while((i<(*cant)) && (finalizo == FALSO))
    {
        if(strcmp((*listado)[i].nombre, palabra) == 0)
        {
            (*listado)[i].cantidad = (*listado)[i].cantidad + 1;
            finalizo = VERDADERO;
        }
        i++;
    }
    
    if(finalizo == FALSO)
    {
        (*listado)= (PALABRAS*)realloc((*listado),((*cant)+1) * sizeof(PALABRAS));
        
        strcpy((*listado)[(*cant)].nombre,palabra);
        (*listado)[(*cant)].cantidad = 1;
        (*cant) = (*cant) + 1;
    }
    
    return;
}



int leer_palabra(char * palabra, FILE *archivo)     //Devuelve lo mismo que el fread
{
    char aux[2];
    int termino = FALSO;
    int letras_leidas;
    int tamano = 0;
    
    while ((termino == FALSO) && (!feof(archivo)))
    {
        letras_leidas = fread(aux, sizeof(char), 1, archivo);
        aux[1] = '\0';
        if((aux[0] != ',') && (aux[0] != '.') && (aux[0] != ' ') && (aux[0] != '\n') && (letras_leidas == 1))
        {
            strcat(palabra, aux);
            tamano++;
        }
        else
            termino = VERDADERO;
    }
    if(tamano == 0)
        letras_leidas = 0;
    return letras_leidas;
}

void minuscula(char * frase)
{
    int i;
    for(i=0;i < strlen(frase);i++)
        frase[i] = tolower(frase[i]);
    
    return;
}
