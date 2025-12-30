##################################################
#Archivo compilador: Makefile-- MARTINEZ, Agustin#
##################################################

##########################################
#Variables de tipo de compilador/banderas#
##########################################

CC	= gcc
CFLAGS	= -c -Wall
LDFLAGS	= -Wall 

##########################################
#Nombre de los archivos			 #
##########################################

OBJS	= main.o funciones.o
SOURCES	= main.c funciones.c
HEADERS	= funciones.c
LIBS	=

EJEC	= ejec

##########################################
#Informacion del autor			 #
##########################################
TP	= 5
LEGAJO	= 2032790
ENTREGA	= entrega_tp_$(TP)_$(LEGAJO)


##########################################
#Genera el ejecutable			 #
##########################################
$(EJEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

##########################################
#Genera los archivos objeto		 #
##########################################
%.o: %.c Makefile
	$(CC) $(CFLAGS) $< -o $@

##########################################
#Borra los ejecutables y .o		 #
##########################################
clean:
	rm -f *.o
	rm -f $(EJEC)

##########################################
#Borra y compila de nuevo		 #
##########################################
new: clean $(EJEC)

##########################################
#Sube al GIT				 #
##########################################
git:
	git commit -m "Entrega Nº $(TP)"
	git push

$(ENTREGA).tar.gz: $(SOURCES) $(HEADERS) Makefile
	tar -zcvf $(ENTREGA).tar.gz $(SOURCES) $(HEADERS) Makefile

help:
	@echo ''
	@echo '-----------------------------'
	@echo 'Uso: '
	@echo 'make $(EJEC):		Genera el ejecutable'
	@echo '<Nombre>.o:		Genera el archivo objeto'
	@echo 'make clean:		Borra los archivos generados'
	@echo 'make new:		Borra los archivos y vuelve a compilar'
	@echo 'make git:		Envía la carpeta al GIT'
	@echo '$(ENTREGA).tar.gz:	Comprime todo en un tar'
	@echo 'make help:		Muestra ayuda'
