#####################################################################
# AUTHOR INFORMATION 												#
#####################################################################
AUTHOR ?= Agustin martinez
DATE ?= 25/04/25
VERSION ?= 2.5

# $^ es una variable automática que representa a una lista de todos los pre-requisitos de un objetivo
# $@ es una variable automática que representa el objetivo a "buildear"
# $< es una variable automática que representa el PRIMER pre-requisito del objetivo

SHELL := /bin/bash
MAKEFLAGS += --warn-undefined-variables

#####################################################################
# APP NAME - Nombre del ejecutable									#
#####################################################################
APP ?= WebServer

#####################################################################
# DIRECTORY TREE, SOURCES, OBJECTS 									#
#####################################################################
CURRENT_DIR := $(shell pwd)
OBJ = obj
BIN = bin
INC = inc
SRC = src
LST = lst

MEMMAP_FILE = memmap.ld

# Encuentra todos los archivos .c y .s en los subdirectorios de src
SRCFILES = $(shell find $(SRC) -name '*.c' -o -name '*.s')
# Genera una lista de archivos .o correspondientes en el directorio obj
OBJFILES = $(patsubst $(SRC)/%, $(OBJ)/%, $(SRCFILES:.c=.o))
OBJFILES := $(patsubst $(SRC)/%, $(OBJ)/%, $(OBJFILES:.s=.o))

#####################################################################
# COMPILER AND ARGUMENTS 											#
#####################################################################
# Compilador
CC     = gcc
# Flags del compilador
CFLAGS = -Wall -I$(INC)
# Flags del ensamblador
AFLAGS=
# Flags del linker
LDFLAGS=

TARGET = $(BIN)/$(APP)

#####################################################################
# GIT         					 									#
#####################################################################
MSG_COMMIT ?= "Actualización desde Makefile"
REMOTE ?= origin
BRANCH ?= main

#####################################################################
# MAKE TARGETS					 									#
#####################################################################
# Phony targets
.PHONY: all clean rebuild run debug folder_tree help \
        git-init git-add git-commit git-push git-all \
        git-restore git-discard

# Regla principal
all: $(TARGET)
	@echo "Compilación finalizada. -> $(TARGET)"

# Regla para crear el ejecutable
$(TARGET): $(OBJFILES)| $(BIN)
	@echo ""
	@echo "Linkeando... "
	$(CC) $(OBJFILES) $(LDFLAGS) -o $@
	@echo "Ejecutable generado en $@"

# Regla para compilar archivos .c a .o
$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	@echo ""
	@echo "Compilando C $(notdir $<)..."
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilado finalizado!!"

# Regla para ensamblar archivos .s a .o
$(OBJ)/%.o: $(SRC)/%.s | $(OBJ)
	@echo "Compilando ASM $(notdir $<)..."
	mkdir -p $(dir $@)
	$(CC) $(AFLAGS) -c $< -o $@
	@echo "Compilado finalizado!!"

# Crea carpetas faltantes
$(OBJ) $(BIN):
	mkdir -p $@

# Limpia los archivos generados
clean:
	rm -rf $(OBJ) $(BIN)

# Reconstruye el proyecto limpiando primero
rebuild: clean all

# Ejecutar
run: $(TARGET)
	./$(TARGET) 8080

# Crea la estructura de directorios para empezar el desarrollo
folder_tree:
	mkdir -p $(SRC) $(INC)
	@echo "Estructura de directorios creada."

dist: clean
	tar czf $(APP)-$(VERSION).tar.gz $(SRC) $(INC) Makefile README.md

# Inicializa un nuevo repositorio git
git-init:
	git init
	@echo "Repositorio Git inicializado."

# Añade todos los cambios al staging area
git-add:
	git add .
	@echo "Todos los cambios añadidos al área de staging."

# Hace commit con el mensaje definido en MSG
git-commit:
	git commit -m $(MSG_COMMIT)
	@echo "Commit realizado con mensaje: $(MSG_COMMIT)"

# Hace push al remoto por defecto (origin) y rama por defecto (master/main)
git-push:
	git push $(REMOTE) $(BRANCH)
	@echo "Cambios enviados al remoto '$(REMOTE)' en la rama '$(BRANCH)'."

# Restaura un archivo eliminado del último commit
git-restore:
	git restore .

# Descarta todos los cambios
git-discard:
	git restore :/

# Combina add, commit, push 
git-all: git-add git-commit git-push
	@echo "Git: add → commit → push completado."

copy2BBB:
	sshpass -p 'temppwd' scp -r src debian@192.168.7.2:/home/debian/server
	sshpass -p 'temppwd' scp -r inc debian@192.168.7.2:/home/debian/server
	sshpass -p 'temppwd' scp -r web debian@192.168.7.2:/home/debian/server
	sshpass -p 'temppwd' scp config.ini debian@192.168.7.2:/home/debian/server
	sshpass -p 'temppwd' scp Makefile debian@192.168.7.2:/home/debian/server


# Objetivo de ayuda que lista los comandos disponibles y su descripción
help:
	@echo "-------------------------------------------------"
	@echo "         Guía de uso del Makefile               "
	@echo "-------------------------------------------------"
	@echo "all         : Compila y genera el ejecutable."
	@echo "clean       : Elimina archivos y directorios generados."
	@echo "rebuild     : Limpia y recompila todo el proyecto."
	@echo "run		   : Ejecuta el archivo."
	@echo "folder_tree : Crea la estructura de directorios (src, inc)."
	@echo "dist 	   : Comprime los archivos fuentes en un .zip/.tar."
	@echo "git-init    : Inicializa un repositorio Git local."
	@echo "git-add     : Añade todos los cambios al área de staging."
	@echo "git-commit  : Hace commit con mensaje (MSG)."
	@echo "git-push    : Envía los commits al remoto."
	@echo "git-all     : add → commit → push en un solo paso."
	@echo "git-restore : Restaura archivos borrados al último commit."
	@echo "git-discard : Descarta cambios locales no confirmados."
	@echo "help        : Muestra esta ayuda."
	@echo "-------------------------------------------------"
	@echo "Para iniciar se deben tener todos los fuentes y  "
	@echo "los headers en sus carpetas SRC y INC."
	@echo "-------------------------------------------------"

