# Socket Server en C

Este proyecto es un ejemplo simple de un **servidor TCP implementado en C**, utilizando la API de **sockets POSIX**.  
Forma parte del repositorio **C_Examples**.

Posee las siguientes características:
- Creación de un socket de servidor con puerto definido y comunicación TCP.
- Comunicación con una página web vía HTML.
- Lectura y escritura de claves a través de un driver personalizado (ver: xxxx).
- Utilización de procesos, memoria compartida, semáforos y señales.

---

## Requisitos

- Sistema operativo tipo Unix (Linux, macOS)
- Compilador **GCC** o compatible
- Librerías estándar de C

---

## Compilación

Desde el directorio `Socket_Server`, ejecutar:

```bash
make
```

---

## Ejecución

Una vez compilado, ejecutar:

```bash
make run
```

Por defecto, el servidor se creará con el puerto 8080 (Ver Makefile).

---

## Uso

El servidor acepta conexiones TCP de clientes. Presenta valores de backlog y cantidad de clientes definidos en un archivo `.ini`.
El cliente se conecta al puerto y recibe una página web HTML por comunicación HTTP 1.1.
La página muestra una lista de claves válidas y una tabla de historial de ingreso.

Las claves válidas las podrá modificar el cliente, mientras que el historial se actualizará al leer el driver custom de una alarma.

El objetivo de este servidor es realizar una comunicación completa de una alarma con clave de seguridad utilizando HTTP y páginas web. Para su correcto funcionamiento se debe añadir el driver específico o, en caso contrario, reemplazarlo por un equivalente.

---

## Estructura del proyecto
```
Socket_Server/
├── inc/
│   ├── client.h
│   ├── data.h
│   ├── driverHandler.h
│   ├── main.h
│   └── periph.h
│
├── src/
│   ├── client.c
│   ├── data.c
│   ├── driverHandler.c
│   ├── main.c
│   └── periph.c
│
├── web/
│   ├── favicon.ico
│   └── webserver.html
│
├── config.ini
├── Makefile
├── README.md
└── .gitignore

```
---
