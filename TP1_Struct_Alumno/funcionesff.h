
#define ERROR -1

typedef struct Alumno
{
	int legajo;				//4 bytes
	char * nombre;			//8 bytes
	char * carrera;			//8 bytes
	float promedio;			//4 bytes
} ALUMNO;					// Total = 24 bytes!!!!


int carga (ALUMNO *** listado);
void mostrar (ALUMNO ** listado, int cantidad);
void limpiar (ALUMNO ** listado, int cantidad);
void menu(ALUMNO **listado, int cantidad);
void fpromedio (ALUMNO ** listado, int cantidad);
void fnombre (ALUMNO ** listado, int cantidad);
int fcarrera (ALUMNO *** filtro, ALUMNO ** listado, int cantidad);
void funcion_6 (ALUMNO ** listado, int *cantidad);
